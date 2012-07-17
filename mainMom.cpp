#include <iostream>

#include "mom.hpp"
#include "tools.hpp"

using namespace std;

int main()
{
  banner();
  mom m;

  m.wakeChildren();

  m.chores();

  //m.payup();

  exit(0);
}

