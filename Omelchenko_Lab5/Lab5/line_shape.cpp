#include "framework.h"
#include <string>
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

void LineShape::GiveOutData(void AddNodeCallback(std::string, long, long, long, long))
{
	AddNodeCallback("Ë³í³ÿ", xs, ys, xe, ye);
}