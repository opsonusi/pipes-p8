#include <iostream>


#include "child.hpp"
#include "tools.hpp"

using namespace std;

int main(int argc, char* argv[])
{
  banner();
  //cout << "argc= " << argc << " " << argv[1] << endl;
  if(argc == 2) {
      //cout << "cid= " << atoi(argv[1])<< endl;
      Child c(atoi(argv[1]));
      c.worker();
    }
  exit(0);
}

