#include "framework.h"

#include "work1states.h"
#include "work1.h"

#include "work1win1.h"
#include "work1win2.h"

int Work1(HINSTANCE hInst, HWND hWnd) {
	int state = LaunchWin1(hInst, hWnd);

	while (1) 
	{
		if (state == FORWARD)
		{
			state = LaunchWin2(hInst, hWnd);
		}
		else if (state == BACK)
		{
			state = LaunchWin1(hInst, hWnd);
		}
		else if (state == COMPLETE_DENY)
		{
			return state;
		} 
	}

}