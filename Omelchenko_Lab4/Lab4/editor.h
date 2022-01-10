#pragma once

class Editor
{
private: 
	const int MAX_LENGTH = 120;
	int length = 10;
	int counter = 0;

	Shape** sObject;

	bool isTrace = false;
	long xs, ys, xe, ye;

	void ResizeArray();

public:
	Editor();
	~Editor();

	void ChooseShape(Shape*);
	void OnLBdown(HWND);
	void OnLBup(HWND);
	void OnMouseMove(HWND);
	void OnPaint(HWND, HDC);
	void OnClear(HWND);
};

