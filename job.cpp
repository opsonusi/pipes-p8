#include "job.hpp"

Job::Job(SPEED s, DIRT d, EASE e)
{
  speedCoef = s;
  dirtCoef = d;
  easeCoef = e;
}

Job::Job(int s, int d, int e)
{
  switch(s){
    case 1:
      speedCoef = QUICK;
      break;
    case 2:
      speedCoef = LITTLE_QUICK;
      break;
    case 3:
      speedCoef = SPEED_OK;
      break;
    case 4:
      speedCoef = LITTLE_SLOW;
      break;
    case 5:
      speedCoef = SLOW;
      break;
    }
  switch(d){
    case 1:
      dirtCoef = PLEASANT;
      break;
    case 2:
      dirtCoef = LITTLE_PLEASANT;
      break;
    case 3:
      dirtCoef = DIRT_OK;
      break;
    case 4:
      dirtCoef = LITTLE_DIRTY;
      break;
    case 5:
      dirtCoef = DIRTY;
      break;
    }
  switch(e){
    case 1:
      easeCoef = EASY;
      break;
    case 2:
      easeCoef = LITTLE_EASY;
      break;
    case 3:
      easeCoef = EASE_OK;
      break;
    case 4:
      easeCoef = LITTLE_HEAVY;
      break;
    case 5:
      easeCoef = HEAVY;
      break;
    }
}

string
Job::toString()
{
  stringstream ss;
  ss << "Speed Coef: " << speedCoef
     << "\tDirt Coef: " << dirtCoef
     << "\tEase Coef: " << easeCoef;
  return ss.str();

}

