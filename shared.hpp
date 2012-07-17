

//#ifndef JOB_HPP
//#define JOB_HPP
#pragma once


#define TIME_UNIT 5
#define NUM_JOBS 10
#define IN 0
#define OUT 1

#include <string>
#include "tools.hpp"


class Job
{
public:

  Job() {}

  Job(int id, int s, int d, int e)
  {
    jobId = id;
    speedCoef = s;
    dirtCoef = d;
    easeCoef = e;
  }
  ~Job(){}

  string toString()
  {
    stringstream ss;
    ss << "Job ID: " << jobId
       << "\tSpeed Coef: " << speedCoef
       << "\tDirt Coef: " << dirtCoef
       << "\tEase Coef: " << easeCoef;
    return ss.str();

  }

  int getSpeedCoef() { return speedCoef; }

  int getDirtCoef() { return dirtCoef; }

  void setTaken() { speedCoef = 0; }

  bool isTaken() { return speedCoef == 0; }

  int getEaseCoef() { return easeCoef; }

 //private:
  int speedCoef;
  int dirtCoef;
  int easeCoef;
  int jobId;
};



//#endif // JOB_HPP


enum MESSAGES {
  READY,
  TABLE,
  CHOICE,
  ACK,
  NACK,
  QUIT,
  SCORE
};
