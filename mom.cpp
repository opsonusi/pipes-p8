#include "mom.hpp"
//#include "child.hpp"

mom::mom()
{
  //clock = 0;
  jobCounter  = 1;

  //initial job array
  srand( time(NULL) );
  for(int k=0; k<NUM_JOBS; k++) {
      vJobs[k]= newJob();
    }

  //define const array - kids' names
  const string kidNames[]  = {"ANDY","BETTY","CARL","DICK"};

  //kids' scores array
  for(int x=0;x<NUM_CHILDREN;childrenTotals[x++]=0);

  //print initial job board
  cout << "\nMom's Initial Job Board" << endl;
  printJobBoard();
}

void
mom::wakeChildren() {
  int pipeFd[NUM_CHILDREN*2+2];
  if(pipe(pipeFd) < 0)
    fatal("Error - mom input pipe: %s", strerror(errno));

  for(int x=1; x<=NUM_CHILDREN; ++x) {
    if(pipe(&pipeFd[x*2]) < 0)
      fatal("Error - mom output pipe: %s", strerror(errno));
    }


  //forking loop
  pid_t pid;
  for(int t=0;t<NUM_CHILDREN;t++) {
      if((pid = fork()) < 0)
        fatal("Error - forking new process: %s", strerror(errno));
      //kid's code
      if(pid == 0) {
          //for(int x= 0; x<4; x++) close()
          setupKid(t, pipeFd);
          break;
        }
    }
  //parent's code
  close(pipeFd[1]);
  for(int x=1; x<=NUM_CHILDREN; ++x) close(pipeFd[x*2]);
  cout << "We are here after forking procs" << endl;
  //open instream
  if ((pipeArr[0] = fdopen(pipeFd[0],"r")) == NULL)
    fatal("Error-MOM - opening inStream: %s", strerror(errno));
  //open outstreams
  for(int x=1; x<=NUM_CHILDREN;++x){
    if ((pipeArr[x] = fdopen(pipeFd[x*2+1],"w")) == NULL)
      fatal("Error-MOM - opening outStream %d: %s",x, strerror(errno));
    }
}

Job
mom::newJob(){
  int s = rand() % 5 + 1;
  int d = rand() % 5 + 1;
  int e = rand() % 5 + 1;
  return Job(jobCounter++,s,d,e);
}

void
mom::replaceTakenJob(){
  for(int k=0; k<NUM_JOBS; k++) {
      if( vJobs[k].getSpeedCoef() == 0) vJobs[k] = newJob();
    }
}

void
mom::chores() {
  cout << "In the chores fxn waiting" << endl;
  clock = time(NULL);
  for(;;) {
     int chMsg;
     int chID;
     cout << "MOM-INPUT: In the CHORES fxn waiting for input" << endl;
     if(fscanf(pipeArr[0],"%d%d", &chMsg,&chID)< 0)
       fatal("Error - mom can read chmsg: %s", strerror(errno));
     cout << "MOM-INPUT: In the CHORES fxn read child: " << chID << " message " << chMsg << endl;
     if(chMsg == READY) {
        if(!ready()) break;
       }
     else if(chMsg == CHOICE) {
         choice();
       }
      cout << "Still in the chores fxn waiting" << endl;
    }
}

bool
mom::ready() {
  cout << "In the ready fxn waiting" << endl;
  time_t curTime = time(NULL);
  int childId;
  bool ret = false;
  cout << "MOM-INPUT: In the READY fxn waiting for input" << endl;
  if(fscanf(pipeArr[0],"%d", &childId) < 0)
    fatal("Error - reading input from child: %s", strerror(errno));
  cout << "Orig Elapsed time = " << curTime-clock << " compared with: " << ELAPSED_TIME << endl;
  if ((curTime-clock)>ELAPSED_TIME) {
      for(int t=0;t<NUM_CHILDREN;t++){
          if(fprintf(pipeArr[t+1],"%d",QUIT)<0)
            fatal("Error - sending QUIT to children: %s", strerror(errno));
        }
      ret = false;
    }
  else{
      for(int t=0; t<NUM_JOBS; t++){
         if(fprintf(pipeArr[childId+1],"%d%d%d%d",
                    vJobs[t].jobId,vJobs[t].speedCoef,vJobs[t].dirtCoef,vJobs[t].easeCoef)
                    < 0)
           fatal("Error - sending job table to children: %s", strerror(errno));
        }
      ret = true;
    }
  fflush (pipeArr[childId+1]);
  return ret;
}

void
mom::choice(){
   cout << "In the choices fxn waiting" << endl;
  int childId;
  int jobId;
  bool found = false;
  cout << "MOM-INPUT: In the CHOICE fxn waiting for input" << endl;;
  if(fscanf(pipeArr[0],"%d%d", &childId,&jobId)<0)
    fatal("Error - reading child's job selection: %s", strerror(errno));
  cout << "MOM-INPUT: In the CHOICE fxn read inputs: childId=" << childId << " jobId="  << jobId << endl;;
  for(int t=0; t<NUM_JOBS; t++){
     if ((found=(vJobs[t].jobId == jobId))) {
        //send NACK
        if(fprintf(pipeArr[childId+1],"%d",ACK)<0)
          fatal("Error - sending ACK to child: %s", strerror(errno));
        Job jb = vJobs[t];
        jb.jobId = childId;
        dbJobs.push_back(jb);
        vJobs[t] = newJob();
        break;
       }
    }
  if(!found)
    if(fprintf(pipeArr[childId+1],"%d",NACK)<0)
      fatal("Error - sending NACK to child: %s", strerror(errno));
  fflush (pipeArr[childId+1]);
}



void
mom::payup() {
    // Wait for all children to finish
    //for(;;) {

     // }
   //find winner
   int temp = 0;
   int winner=0;
   for(int x=0; x<NUM_CHILDREN; x++){
      if (temp < childrenTotals[x]) {
          temp = childrenTotals[x];
          winner  = x;
        }
     }
   //display winner
   cout << "End-of-day earnings " << "\n----------------------------"<< endl;
   for(int x=0; x<NUM_CHILDREN; x++) {
       if (x==winner)
         cout << "Child: " << x << "\tEarnings: $" << childrenTotals[x] + 5 << "\tWINNER(added +5 Dollars)\n";
       else
         cout << "Child: " << x << "\tEarnings: $" << childrenTotals[x] << "\n";
     }
}

void
mom::setTotal(int cid, int earning) {
  childrenTotals[cid] += earning;
}

void
mom::printJobBoard() {
  for(int k=0; k<NUM_JOBS; k++) {
      cout << vJobs[k].toString() << endl;
    }
}


void
mom::setupKid(int N, int* fd) {
  close(fd[0]);
  close(1);
  dup(fd[1]);
  close(fd[1]);
  fcntl(1,F_SETFD,0);

  close(fd[2*N+3]);
  close(0);
  dup(fd[2*N+2]);
  close(fd[2*N+2]);
  fcntl(0,F_SETFD,0);
  cout << "About calling child code for child: " << kidNames[N] << endl;

  stringstream s;
  s << N;
  int ret;
  //cout << "s= " << s.str() << endl;

  //call execlp
  if ((ret = execlp("p8kid","p8kid", s.str().c_str(), (char*)0)) < 0)
    fatal("execlp error: %s", strerror(errno));

  //never-to-be-seen code
  cout << "after calling child code for child: " << N << endl;
}
