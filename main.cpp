#include <stdlib.h>
#include "lrtimer.h"

using namespace std;

// define callback function
VOID callback(VOID) {
  static DWORD cnt = 0;
  char c;
  cnt++;
  switch (cnt % 4) {
    case 0: c = '|'; break;
    case 1: c = '/'; break;
    case 2: c = '-'; break;
    case 3: c = '\\';
  }
  printf("\b%c",c);
}


int main(int argc, char *argv[])
{

  LRTimer lrt;
  lrt.setCallbackFunction(&callback);
  lrt.setInterval(50);
  lrt.start();
  getchar();
  lrt.stop();
  getchar();
  lrt.start(200);
  getchar();
  lrt.stop();
  system("PAUSE");
  return 0;
}
