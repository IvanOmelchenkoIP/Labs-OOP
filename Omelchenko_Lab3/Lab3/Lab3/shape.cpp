#include "framework.h"

#include "colors.h"
#include "shape.h"

void Shape::Set(long x1, long y1, long x2, long y2)
{
	xs = x1;
	ys = y1;
	xe = x2;
	ye = y2;
}


void PointShape::Show(HDC hdc)
{
	SetPixel(hdc, xs - 1, ys, BLACK);
	SetPixel(hdc, xs + 1, ys, BLACK);
	SetPixel(hdc, xs, ys - 1, BLACK);
	SetPixel(hdc, xs, ys + 1, BLACK);
	SetPixel(hdc, xs - 1, ys + 1, BLACK);
	SetPixel(hdc, xs + 1, ys + 1, BLACK);
	SetPixel(hdc, xs + 1, ys - 1, BLACK);
	SetPixel(hdc, xs - 1, ys - 1, BLACK);

	SetPixel(hdc, xs, ys, BLACK);
}

void LineShape::Show(HDC hdc)
{
	MoveToEx(hdc, xs, ys, NULL);
	LineTo(hdc, xe, ye);
}

void RectShape::Show(HDC hdc)
{
	RECT pRect;
	HBRUSH hBrush, hBrushOld;

	hBrush = (HBRUSH)CreateSolidBrush(GREEN);
	hBrushOld = (HBRUSH)SelectObject(hdc, hBrush);

	SetRect(&pRect, xs, ys, xe, ye);
	FillRect(hdc, &pRect, hBrush);

	MoveToEx(hdc, xs, ys, NULL);
	LineTo(hdc, xs, ye);
	MoveToEx(hdc, xs, ye, NULL);
	LineTo(hdc, xe, ye);
	MoveToEx(hdc, xe, ye, NULL);
	LineTo(hdc, xe, ys);
	MoveToEx(hdc, xe, ys, NULL);
	LineTo(hdc, xs, ys);

	SelectObject(hdc, hBrushOld);
	DeleteObject(hBrush);
}

void EllipseShape::Show(HDC hdc)
{
	HBRUSH hBrush, hBrushOld;

	hBrush = (HBRUSH)CreateSolidBrush(YELLOW);
	hBrushOld = (HBRUSH)SelectObject(hdc, hBrush);

	Ellipse(hdc, xs, ys, xe, ye);

	SelectObject(hdc, hBrushOld);
	DeleteObject(hBrush);
}



