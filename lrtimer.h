/*******************************************************************************
* lrtimer.h                                                                    *
*                                                                              *
* Written by Max Gurdziel 2005 under GNU General Public License                *
* contact me: max@remotesos.com                                                *
*                                                                              *
* LRTimer is a low resolution timer class with own timing thread. It allows    *
*  an external callback function to be supplied that will be called in         *
*  pre-defined time intervals. The smallest timer interval you can use is 1ms. *
*                                                                              *
*  System requirements:                                                        *
*  - WindowsXP, NT                                                             *
*  - gcc compiler under mingw                                                  *
*                                                                              *
*                                                                              *
*   Usage:  copy and paste below sample code to test LRTimer                   *
*                                                                              *
________________________________________________________________________________

#include <stdlib.h>
#include "lrtimer.h"

using namespace std;

// define callback function
void callback()
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
  lrt.setCallbackFunction(&callback);  // set the callback function by reference
  lrt.setInterval(50);                 // set delay interval in miliseconds
  lrt.start();                         // start the timer
  getchar();                           // let it run for a while - press Enter
  lrt.stop();                          // stop the timer
  getchar();                           // wait to show it's stopped - Enter
  lrt.start(200);                      // start with different delay
  getchar();
  lrt.stop();
  system("PAUSE");
  return 0;
}

________________________________________________________________________________
*                                                                              *
* Permission to use, copy, modify, and distribute this software and its        *
* documentation under the terms of the GNU General Public License is hereby    *
* granted. No representations are made about the suitability of this software  *
* for any purpose. It is provided "as is" without express or implied warranty. *
* See http://www.gnu.org/copyleft/gpl.html for more details.                   *
*                                                                              *
* All I ask is that if you use LRTimer in your project please retain the       *
* copyright notice. If you have any comments and suggestions please email me   *
* max@remotesos.com                                                            *
*                                                                              *
*******************************************************************************/

#ifndef LRTIMER_H__
#define LRTIMER_H__



#define _WIN32_WINNT 0x0500

#include <windows.h>
#include <stdio.h>

#define _SECOND 10000000

class LRTimer {

	public:
    // default constructor
  	LRTimer();
  	
  	// default destructor
		virtual ~LRTimer();
		
		// starts timer by creating new thread using preset interval
		VOID start();
		
		// starts timer with given interval in miliseconds
		VOID start(DWORD _interval_ms);
		
		// stops the timer
		VOID stop();
		
		// sets interval in miliseconds
		VOID setInterval(DWORD _interval_ms);
		
		// returns interval
		DWORD getInterval();
		
		// sets function that will be called on time
		VOID setCallbackFunction( VOID (*_pCallback)(VOID));
  	BOOL isRunning();

  private:
  	DWORD m_dwInterval;
  	VOID __stdcall (*m_pCallback)(VOID); //__attribute__((stdcall))
  	BOOL m_bRunning;
  	HANDLE m_hTimerThread; // handle to timer thread
  	DWORD m_iID; //timer thread id
  	virtual DWORD WINAPI timerThread();
  	static DWORD WINAPI timerThreadAdapter(PVOID _this) {
  		return ((LRTimer*) _this)->timerThread();
 		}
 		virtual VOID CALLBACK TimerAPCProc(LPVOID, DWORD, DWORD);
 		static VOID CALLBACK TimerAPCProcAdapter(PVOID _this, DWORD a1=0, DWORD a2=0) {
 			return ((LRTimer*) _this)->TimerAPCProc( NULL, a1, a2 );
		}
};
#endif
