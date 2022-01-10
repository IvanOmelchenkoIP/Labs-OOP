#include "framework.h"
#include <list>
#include <string>
#include "table.h"
#include "table_window.h"

static BOOL CALLBACK DlgTableProc(HWND, UINT, WPARAM, LPARAM);

//---------------------------
//dialog window class methods
	//object of TableWindow class is needed for processing procedure of its own and main window
TableWindow* TableWindow::twpInstance;
TableWindow* TableWindow::GetInstance()
{
	if (!twpInstance) twpInstance = new TableWindow;
	return twpInstance;
}

	//initiating and showing window
void TableWindow::InitTableWindowData(HWND hWnd)
{
	RECT parentRect;
	GetClientRect(hWnd, &parentRect);

	int dlgLeft = parentRect.left;
	int dlgTop = parentRect.bottom - 200;
	int dlgRight = 300;
	int dlgBottom = 200;

	dlgHeader.style = DS_MODALFRAME | WS_POPUP | WS_CAPTION | WS_SYSMENU | WS_VSCROLL;
	dlgHeader.cdit = 0;
	dlgHeader.x = dlgLeft;
	dlgHeader.y = dlgTop;
	dlgHeader.cx = dlgRight;
	dlgHeader.cy = dlgBottom;

	hdlgTable = GlobalAlloc(GMEM_ZEROINIT, sizeof(DLGTEMPLATE) + 6);
	if (hdlgTable) pdlgHDR = (BYTE*)GlobalLock(hdlgTable);

	if (pdlgHDR)
	{
		memcpy(pdlgHDR, &dlgHeader, sizeof(DLGTEMPLATE));
		hwndTableWin = CreateDialogIndirectW((HINSTANCE)GetWindowLong(hWnd, GWLP_HINSTANCE), (LPDLGTEMPLATE)pdlgHDR, hWnd, (DLGPROC)DlgTableProc);
	}
}

void TableWindow::ShowTableWindow()
{	
	ShowWindow(hwndTableWin, TRUE);
	if (!hwndTableWin) return;
}

	//adding rows to the table and clearing the table
void TableWindow::AddTableRow(std::string type, long xs, long ys, long xe, long ye)
{
	table.AddRow(type, xs, ys, xe, ye);
	table.PaintTable();
}

void TableWindow::ClearTable()
{
	table.ClearRowList();
}

	//message process procedures
void TableWindow::OnInit(HWND hwndTable)
{
	table.InitTable(hwndTable);
}

void TableWindow::OnPaint(HDC hdc)
{	
	SetBkMode(hdc, TRANSPARENT);
	table.PaintTable();
}


//-----------------------------------------
//dialog window message processing function
BOOL CALLBACK DlgTableProc(HWND hwndTableWin, UINT message, WPARAM wParam, LPARAM lParam)
{
	SCROLLINFO si;

	static int curY = 0;
	static int scrollY = 0;

	static TableWindow* tw = TableWindow::GetInstance();

	switch (message)
	{
	case WM_INITDIALOG:
		RECT rect;
		GetClientRect(hwndTableWin, &rect);

		si.cbSize = sizeof(SCROLLINFO);
		si.fMask = SIF_ALL;
		si.nMin = 0;
		si.nMax = 30 * 120;
		si.nPage = (rect.bottom - rect.top);
		si.nPos = 0;
		si.nTrackPos = 0;
		SetScrollInfo(hwndTableWin, SB_VERT, &si, true);

		tw->OnInit(hwndTableWin);
		break;
	case WM_PAINT:
		{
		PAINTSTRUCT ps;
		HDC hdc = BeginPaint(hwndTableWin, &ps);
		
		tw->OnPaint(hdc);

		EndPaint(hwndTableWin, &ps);
		}
		break;
	case WM_VSCROLL:
	{
		WPARAM action = LOWORD(wParam);
		switch (action)
		{
		case SB_THUMBPOSITION: case SB_THUMBTRACK:
			curY = HIWORD(wParam);
			break;
		case SB_LINEDOWN:
			curY = scrollY + 30;
			break;
		case SB_LINEUP:
			curY = scrollY - 30;
			break;
		}
		if (curY < 0) return 0;

		si.cbSize = sizeof(SCROLLINFO);
		si.fMask = SIF_POS;
		si.nPos = curY;
		si.nTrackPos = 0;

		SetScrollInfo(hwndTableWin, SB_VERT, &si, true);

		ScrollWindow(hwndTableWin, 0, -(si.nPos - scrollY), NULL, NULL);
		UpdateWindow(hwndTableWin);

		scrollY = curY;
	}
	break;
	case WM_SYSCOMMAND:
		if (wParam == SC_CLOSE) ShowWindow(hwndTableWin, FALSE);
		break;
	case WM_DESTROY:
		DestroyWindow(hwndTableWin);
		PostQuitMessage(0);
		break;
	default: break;
	}
	return false;
}