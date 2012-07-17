#pragma once

#define NUM_CHILDREN 4
#define ELAPSED_TIME 1

#include <unistd.h>
#include <fcntl.h>
#include <string>
#include "shared.hpp"
#include <sys/types.h>
#include <errno.h>
#include <time.h>


class mom
{
public:
  mom();
  ~mom() {}

  void chores();
  Job newJob();
  void replaceTakenJob();
  void payup();
  int getClock() { return clock; }
  Job* getVJobs() { return vJobs; }
  void setTotal(int cid, int earning);
  void printJobBoard();
  void wakeChildren();
  void setupKid(int N, int* fd);
  void choice();
  bool ready();

private:
  Job vJobs[NUM_JOBS];
  time_t clock;
  int childrenTotals[NUM_CHILDREN];
  FILE* pipeArr[5];
  const string kidNames[NUM_CHILDREN];
  int jobCounter;
  vector<Job> dbJobs;

};

