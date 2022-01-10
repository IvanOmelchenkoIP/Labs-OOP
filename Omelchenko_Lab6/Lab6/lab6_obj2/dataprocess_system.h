#pragma once
#define BUF_SIZE 32

#ifndef _UNICODE
#define _UNICODE
#endif

class DataProcessSystem
{
private:
	int nVals;
	double minVal;
	double maxVal;

	std::vector<double> dataVector;

	void GetDataCopy(HWND, LPARAM);
	void FillVector();

public:
	std::vector<double> GetDataVector(HWND, LPARAM, int*, double*, double*);
};


class ClipboardCopier
{
private:
	std::wstring wstr_buf;

	void FormClipboardBuffer(std::vector<double>);

public:
	int CopyToClipboard(HWND hWnd, std::vector<double>);
};