#pragma once

class Editor
{
public:
	virtual ~Editor(void) {};

	virtual void OnLBdown(HWND) = 0;
	virtual void OnLBup(HWND) = 0;
	virtual void OnMouseMove(HWND) = 0;
};

class ShapeEditor : public Editor
{
private:
	const int OBJ_MENU = 1;

	virtual void SetStartCoords(POINT coords);
	virtual void DrawRubberTrace(HWND, HDC, POINT) = 0;

protected:
	BOOL isTrace = false;
	long xs, ys, xe, ye;

public:
	void OnLBdown(HWND);
	void OnLBup(HWND);
	void OnMouseMove(HWND);

	virtual void CreateShape(Shape*&) = 0;
};


class PointEditor : public ShapeEditor
{
private:
	void DrawRubberTrace(HWND, HDC, POINT);

public:
	void CreateShape(Shape*&);
};

class LineEditor : public ShapeEditor
{
private:
	void DrawRubberTrace(HWND, HDC, POINT);

public:
	void CreateShape(Shape*&);
};

class RectEditor : public ShapeEditor
{
private:
	long xm, ym;

	void SetStartCoords(POINT coords);
	void DrawRubberTrace(HWND, HDC, POINT);

public:
	void CreateShape(Shape*&);
};

class EllipseEditor : public ShapeEditor
{
private:
	void DrawRubberTrace(HWND, HDC, POINT);

public:
	void CreateShape(Shape*&);
};