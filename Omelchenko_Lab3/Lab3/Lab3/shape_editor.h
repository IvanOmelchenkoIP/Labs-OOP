#pragma once

class ShapeObjectsEditor
{
private:
	const int MAX_OBJ = 119;
	int counter = 0;

	ShapeEditor* sEditor;
	Shape* sObject[119];

public:
	ShapeObjectsEditor();
	~ShapeObjectsEditor();

	void StartPointEditor(HWND);
	void StartLineEditor(HWND);
	void StartRectEditor(HWND);
	void StartEllipseEditor(HWND);

	void OnLBdown(HWND);
	void OnLBup(HWND);
	void OnMouseMove(HWND);
	void OnPaint(HWND);
	void OnClear(HWND);
};

