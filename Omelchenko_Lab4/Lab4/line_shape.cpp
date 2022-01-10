#include "framework.h"
#include "colors.h"
#include "shape.h"
#include "line_shape.h"

void LineShape::Show(HDC hdc, bool isTrace)
{
	MoveToEx(hdc, xs, ys, NULL);
	LineTo(hdc, xe, ye);
}

void LineShape::MakeNewInstance(Shape*& targetShape)
{
	if (targetShape) delete targetShape;
	targetShape = new LineShape;
}