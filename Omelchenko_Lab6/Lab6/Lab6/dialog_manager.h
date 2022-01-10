#pragma once

#define BUF_SIZE 32

class DialogManager
{
private:
	int n_res;
	double min_res;
	double max_res;

	bool ConvertBuffersToNums();

public:
	bool LaunchDialog(HINSTANCE, HWND, double*, double*, double*);
};

