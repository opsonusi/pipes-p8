#include "child.hpp"


//Child::Child(int cid, mom* pM) {
  //cerr << "in child: Creating child: " << cid << endl;
//  childId = cid;
//  pMom = pM;
//}

Child::Child(int cid ) {
  cerr << "in child: Creating child: " << cid << endl;
  childId = cid;
  if((outStream = fdopen(1,"w")) == NULL)
    fatal("Error - outstream: %s", strerror(errno));
  if((inStream = fdopen(0, "r")) == NULL)
    fatal("Error - instream: %s", strerror(errno));
}


//carl
Job Child::ADDChild() {
    Job jb;
    int j = 6;
    int y = -1;
    for(int k=0; k<10; k++){
        if (jobs[k].isTaken()) continue;
        int x = jobs[k].getSpeedCoef();
        if ( x < j ) {
            j = x;
            y=k;
          }
      }
    if(y>-1){
        cerr << "Carl Choosing Job: " << y << endl;
        jb = jobs[y];
        jobs[y].setTaken();
       }
  return jb;
}

//betty
Job Child::prissyChild() {
    Job jb;
    int j = 6;
    int y = -1;

    for(int k=0; k<10; k++){
        if (jobs[k].isTaken()) continue;
        int x = jobs[k].getDirtCoef();
        if ( x < j ) {
            j = x;
            y=k;
          }
      }
    if(y>-1){
        cerr << "Betty Choosing Job: " << y << endl;
        jb = jobs[y];
        jobs[y].setTaken();
       }
  return jb;
}

//andy
Job Child::lazyChild() {
    Job jb;
    int j = 6;
    int y = -1;
    for(int k=0; k<10; k++){
        if (jobs[k].isTaken()) continue;
        int x = jobs[k].getEaseCoef();
        if ( x < j ) {
            j = x;
            y=k;
          }
      }
    if(y>-1){
        cerr << "Andy Choosing Job: " << y << endl;
        jb = jobs[y];
        jobs[y].setTaken();
       }
  return jb;
}

//dick
Job Child::greedyChild() {
    Job jb;
    int j = 1;
    int y = -1;
    for(int k=0; k<10; k++){
        if (jobs[k].isTaken()) continue;
        int x = jobs[k].getSpeedCoef() + jobs[k].getDirtCoef() + jobs[k].getEaseCoef();
        if ( x > j ) {
            j = x;
            y=k;
          }
      }
    if(y>-1){
        cerr << "Dick Choosing Job: " << y << endl;
        jb = jobs[y];
        jobs[y].setTaken();
      }
  return jb;
}


void Child::worker() {
  totPoints = 0;
  cerr << "I'm here, working. Child: " << childId << endl ;
  for(;;) {
      int ret;
    if((ret=fprintf(outStream,"%d %d", READY, childId)) < 0)
      fatal("Error - writing to outstream: %s", strerror(errno));
    fflush(outStream);
    cerr << childId  << " CHILD-INPUT: In the WORKER fxn waiting for job-table: "<< ret << endl;
    for(int x=0; x<NUM_JOBS;x++){
      int ret;
      if((ret = fscanf(inStream,"%d %d %d %d",
                       &jobs[x].jobId,&jobs[x].speedCoef,&jobs[x].dirtCoef,&jobs[x].easeCoef))<0)
        fatal("Error - reading job-table: %d %s",ret, strerror(errno));
      }
    cerr << childId  << " CHILD-INPUT: In the WORKER fxn done reading job-table" << endl;
    switch(childId) {
      case 0:
        jb = lazyChild();
        break;
      case 1:
        jb = prissyChild();
        break;
      case 2:
        jb = ADDChild();
        break;
      case 3:
        jb = greedyChild();
        break;
    }
    //if (jb.isTaken()) continue;
    //job selected send ack to mom
    fprintf(outStream,"%d%d%d", CHOICE,childId,jb.jobId);
    fflush(outStream);

    int reply;
    cerr << childId  << " CHILD-INPUT: In the WORKER fxn waiting for reply" << endl;
    fscanf(inStream,"%d", &reply);
    if(reply == NACK) continue;
    else if (reply == QUIT)  break;
    else if (reply == ACK) totPoints += doJob();

   }


    //send points to mom and quit
    cerr << "\nSending total points earned: " << totPoints << endl;
    fprintf(outStream,"%d%d%d", CHOICE,childId,totPoints);

    cerr << "Child: " << childId << ", Done!" << endl;

}

int Child::doJob() {
  //sleep for time units to do job (using seconds for this test)
  sleep(jb.getSpeedCoef() * TIME_UNIT);
  myJobs.push_back(jb);
  int earned = jb.getDirtCoef() + jb.getSpeedCoef() + jb.getEaseCoef();

  //print job completion message
  cerr << "\nJob Completed by Child: " << childId << endl;
  cerr << jb.toString() << endl;
  cerr << "Points Earned: " <<  earned << endl;


  //return points earned
  return earned;
}
