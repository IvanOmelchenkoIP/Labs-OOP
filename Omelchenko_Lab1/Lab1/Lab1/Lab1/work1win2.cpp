#include "framework.h"

#include "work1states.h"

#include "resource2.h"
#include "work1win2.h"

static INT CALLBACK DialogWin2(HWND, UINT, WPARAM, LPARAM);

int LaunchWin2(HINSTANCE hInst, HWND hWnd)
{
    return DialogBoxW(hInst, MAKEINTRESOURCE(IDD_WORK1WIN2), hWnd, (DLGPROC)DialogWin2);
}

INT CALLBACK DialogWin2(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_COMMAND:
        int command = LOWORD(wParam);

        if (command == IDGOBACK)
        {
            return EndDialog(hDlg, BACK);
        }
        else if (command == IDOK || command == IDCANCEL) 
        {
            return EndDialog(hDlg, COMPLETE_DENY);
        }

        break;
    }
    return COMPLETE_DENY;
}