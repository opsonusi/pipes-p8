//#ifndef CHILD_HPP
//#define CHILD_HPP

#pragma once

#include <pthread.h>
#include "shared.hpp"
#include "tools.hpp"
#include <stdio.h>
#include <sys/types.h>
#include <errno.h>

class Child
{
public:
  //Child(int cid,  mom* pM);
  Child(int cid );
  void worker();

private:
  int childId;
  //mom* pMom;
  Job lazyChild();
  Job prissyChild();
  Job ADDChild();
  Job greedyChild();
  int doJob();
  int totPoints;
  vector<Job> myJobs;
  Job jb;
  FILE* inStream;
  FILE* outStream;
  Job* jobs;
};

//#endif // CHILD_HPP
