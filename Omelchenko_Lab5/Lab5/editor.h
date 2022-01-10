#pragma once

class EditorSingleton
{
private: 
	static EditorSingleton* epInstance;

	EditorSingleton();
	EditorSingleton(const EditorSingleton&) = delete;
	EditorSingleton& operator=(EditorSingleton&) = delete;

	const int MAX_LENGTH = 120;
	int length = 10;
	int counter = 0;

	Shape** sObject;

	bool isTrace = false;
	long xs, ys, xe, ye;

	void ResizeArray();

public:
	~EditorSingleton();

	static EditorSingleton * GetInstance();

	void ChooseShape(Shape*);
	void OnLBdown(HWND);
	void OnLBup(HWND, void AddNodeCallback(std::string, long, long, long, long));
	void OnMouseMove(HWND);
	void OnPaint(HWND, HDC);
	void OnClear(HWND, void ClearTable());
};

