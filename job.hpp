//#ifndef JOB_HPP
//#define JOB_HPP
#pragma once
#include <string>
#include "tools.hpp"

class Job
{
public:
  enum SPEED
  {
    TAKEN = 0,
    QUICK=1,
    LITTLE_QUICK=2,
    SPEED_OK=3,
    LITTLE_SLOW=4,
    SLOW=5
  };

  enum DIRT
  {
    PLEASANT=1,
    LITTLE_PLEASANT=2,
    DIRT_OK=3,
    LITTLE_DIRTY=4,
    DIRTY=5
  };

  enum EASE
  {
    EASY=1,
    LITTLE_EASY=2,
    EASE_OK=3,
    LITTLE_HEAVY=4,
    HEAVY=5
  };

  Job() {}
  Job(SPEED t,DIRT d,EASE e);
  Job(int t,int d,int e);
  ~Job(){}
  string toString();

  int getSpeedCoef() { return speedCoef; }

  int getDirtCoef() { return dirtCoef; }

  void setTaken() { speedCoef = TAKEN; }

  bool isTaken() { return speedCoef == TAKEN; }

  int getEaseCoef() { return easeCoef; }

 private:
  SPEED speedCoef;
  DIRT dirtCoef;
  EASE easeCoef;
  int jobId;
};

enum MESSAGES
{
  READY,  //I am kid N. Please send me the job table(kidId)
  TABLE,  //here is the table(50 short ints, 5 each for 10 jobs)
  CHOICE, //I am kid N and I have selected a job(kidId and jobId)
  ACK,    //Your choice is approved - do it.
  NACK,   //No go - somebody else already took that job
  QUIT,   //Time to quit( from mom to kid)
  SCORE   //i am kid N; here is my total score(followed by kidID and the score)
};

//#endif // JOB_HPP
