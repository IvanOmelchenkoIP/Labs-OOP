#include "framework.h"

#include <vector>
#include <string>
#include <time.h>

#include "dataprocess_system.h"

//-----------------------
//data system to form vector of random numbers based on copied data
std::vector<double> DataProcessSystem::GetDataVector(HWND hWnd, LPARAM lParam, int* n, double* min, double* max)
{
    GetDataCopy(hWnd, lParam);

    dataVector.resize(nVals);
    FillVector();

    *n = nVals;
    *min = minVal;
    *max = maxVal;

    return dataVector;
}

void DataProcessSystem::GetDataCopy(HWND hWnd, LPARAM lParam)
{
    PCOPYDATASTRUCT cds;

    cds = (PCOPYDATASTRUCT)lParam;
    double* data = (double*)cds->lpData;
    nVals = (int)data[0];
    minVal = data[1];
    maxVal = data[2];
}

void DataProcessSystem::FillVector()
{
    srand(time(NULL));
    for (int i = 0; i < nVals; i++) dataVector[i] = (double)rand() / (double)RAND_MAX * (maxVal - minVal) + minVal;
}
//------------------------


//-----------------------
//copying to clipboard
int ClipboardCopier::CopyToClipboard(HWND hWnd, std::vector<double> data)
{
    FormClipboardBuffer(data);
    TCHAR * copy_buf = (wchar_t * ) wstr_buf.c_str(); 

    HGLOBAL hglbCopy;
    WCHAR* pTmp;
    
    if (copy_buf == NULL) return 0;
    size_t buf_size = _tcslen(copy_buf);
    size_t alloc_size = (buf_size + 1) * sizeof(TCHAR);

    hglbCopy = GlobalAlloc(GHND, alloc_size);
    if (hglbCopy == NULL) return 0;

    pTmp = (WCHAR*)GlobalLock(hglbCopy);
    wcscpy_s(pTmp, buf_size + 2, copy_buf);
    GlobalUnlock(hglbCopy);

    if (!OpenClipboard(hWnd))
    {
        GlobalFree(hglbCopy);
        return 0;
    }

    EmptyClipboard();
    SetClipboardData(CF_UNICODETEXT, hglbCopy);
    CloseClipboard();

    return 1;
}

void ClipboardCopier::FormClipboardBuffer(std::vector<double> data) 
{
    std::string dataUnit;
    std::string str_buf;

    for (int i = 0; i < data.size(); i++)
    {
        dataUnit = std::to_string(data[i]);
        str_buf += dataUnit;
        str_buf += "\n";
    }

    wstr_buf = std::wstring(str_buf.begin(), str_buf.end());
}
//---------------------