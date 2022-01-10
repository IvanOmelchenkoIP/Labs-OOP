// lab6_obj3.cpp : Определяет точку входа для приложения.
//
#include "framework.h"
#include <string>
#include <list>
#include "data_processor.h"
#include "lab6_obj3.h"

#define MAX_LOADSTRING 100

// Глобальные переменные:
HINSTANCE hInst;                                // текущий экземпляр
WCHAR szTitle[MAX_LOADSTRING];                  // Текст строки заголовка
WCHAR szWindowClass[MAX_LOADSTRING];            // имя класса главного окна

//-----------------------
//global program identifiers
HWND hwndMain;

HWND hwndText;
long width, height;

std::list<double> dataList;

//onn window creation
void OnCreateWin(HWND, SCROLLINFO*);

//copying from clipboard
void OnClipboardCopy(HWND, WPARAM);

//on paint
void OnPaint(HDC);
//------------------


// Отправить объявления функций, включенных в этот модуль кода:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: Разместите код здесь.

    // Инициализация глобальных строк
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_LAB6OBJ3, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Выполнить инициализацию приложения:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_LAB6OBJ3));

    MSG msg;

    // Цикл основного сообщения:
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    return (int) msg.wParam;
}

//
//  ФУНКЦИЯ: MyRegisterClass()
//
//  ЦЕЛЬ: Регистрирует класс окна.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_LAB6OBJ3));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_LAB6OBJ3);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

//
//   ФУНКЦИЯ: InitInstance(HINSTANCE, int)
//
//   ЦЕЛЬ: Сохраняет маркер экземпляра и создает главное окно
//
//   КОММЕНТАРИИ:
//
//        В этой функции маркер экземпляра сохраняется в глобальной переменной, а также
//        создается и выводится главное окно программы.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // Сохранить маркер экземпляра в глобальной переменной

   HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

//
//  ФУНКЦИЯ: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  ЦЕЛЬ: Обрабатывает сообщения в главном окне.
//
//  WM_COMMAND  - обработать меню приложения
//  WM_PAINT    - Отрисовка главного окна
//  WM_DESTROY  - отправить сообщение о выходе и вернуться
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    SCROLLINFO si;
    static int curY;
    static int scrollY = 0;

    switch (message)
    {
    case WM_CREATE:
        OnCreateWin(hWnd, &si);
        break;
    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            // Разобрать выбор в меню:
            switch (wmId)
            {
            case IDM_ABOUT:
                DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
                break;
            case IDM_EXIT:
                DestroyWindow(hWnd);
                break;
            default:
                return DefWindowProc(hWnd, message, wParam, lParam);
            }
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

        SetScrollInfo(hWnd, SB_VERT, &si, true);

        ScrollWindow(hWnd, 0, -(si.nPos - scrollY), NULL, NULL);
        UpdateWindow(hWnd);

        scrollY = curY;
    }
    case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps);
            
            OnPaint(hdc);

            EndPaint(hWnd, &ps);
        }
        break;
    case MSG_COPY_CLIPBOARD:
        OnClipboardCopy(hWnd, wParam);
        break;
    case WM_DESTROY:
        if (hwndMain) SendMessage(hwndMain, MSG_NULL_OBJ3, (WPARAM)hWnd, NULL);
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

// Обработчик сообщений для окна "О программе".
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}


//------------------
//on creating window
void OnCreateWin(HWND hWnd, SCROLLINFO* si)
{
    POINT screenSize;
    screenSize.x = GetSystemMetrics(SM_CXSCREEN);
    screenSize.y = GetSystemMetrics(SM_CYSCREEN);

    long xs = screenSize.x / 2;
    long ys = screenSize.y / 2;
    long width = screenSize.x - xs;
    long height = screenSize.y - ys;

    MoveWindow(hWnd, xs, ys, width, height, TRUE);

    RECT rect;
    GetClientRect(hWnd, &rect);

    si->cbSize = sizeof(SCROLLINFO);
    si->fMask = SIF_ALL;
    si->nMin = 0;
    si->nMax = 20 * 1000;
    si->nPage = (rect.bottom - rect.top);
    si->nPos = 0;
    si->nTrackPos = 0;
    SetScrollInfo(hWnd, SB_VERT, si, true);

    hwndMain = FindWindow(L"LAB6", NULL);
    SendMessage(hWnd, MSG_COPY_CLIPBOARD, (WPARAM)hWnd, NULL);
}
//---------------------

//--------------------
//copying clipboard data
void OnClipboardCopy(HWND hWnd, WPARAM wParam)
{
    if (!hwndMain) hwndMain = (HWND)wParam;
    DataProcessor dProc;

    dataList = dProc.GetListFromClipboard(hWnd);

    RECT rect;
    GetClientRect(hWnd, &rect);

    width = (rect.right - rect.left);
    height = rect.bottom - rect.top;

    long nHeight = dataList.size() / 4 * 20 + 60;
    height = height > nHeight ? height : nHeight;
    if (!hwndText) hwndText = CreateWindowEx(NULL, L"STATIC", NULL, WS_CHILD | WS_VISIBLE, 0, 0, width, height, hWnd, NULL, NULL, 0);
    else SetWindowPos(hwndText, HWND_TOP, 0, 0, width, height, SWP_NOMOVE | SWP_SHOWWINDOW);
    InvalidateRect(hwndText, NULL, TRUE);

    InvalidateRect(hWnd, NULL, TRUE);
}
//-------------------

//---------------------
//on paint
void OnPaint(HDC hdc)
{
    TCHAR tmp_buf[BUF_SIZE];
    
    int x = 10;
    int y = 40;
    int deltaY = 20;
    long deltaWidth = width / 4;

    PAINTSTRUCT ps;
    HDC hdcText = BeginPaint(hwndText, &ps);
    
    TextOut(hdcText, x, 10, L"Відсортовані елементи вектора:", 32);
    for (auto iter = dataList.begin(); iter != dataList.end(); iter++)
    {
        swprintf_s(tmp_buf, L"%.3lf", *iter);
        TextOut(hdcText, x, y, tmp_buf, _tcslen(tmp_buf));

        x += deltaWidth;
        if (x > width)
        {
            x = 10;
            y += deltaY;
        }
    }

    EndPaint(hwndText, &ps);
}
//-------------------