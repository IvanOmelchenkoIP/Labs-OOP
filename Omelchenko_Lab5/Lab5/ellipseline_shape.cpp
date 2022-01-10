#include "framework.h"
#include <string>
#include <cmath>
#include "colors.h"
#include "shape.h"
#include "line_shape.h"
#include "ellipse_shape.h"
#include "ellipseline_shape.h"

void EllipseLineShape::Show(HDC hdc, bool isTrace)
{
	long xs_generic = xs;
	long ys_generic = ys;
	long xe_generic = xe;
	long ye_generic = ye;
	long k = sqrt( (pow(abs(xe_generic - xs_generic), 2) + pow(abs(ye_generic - ys_generic), 2)) / 2) / 10;

	long xs1 = xs_generic - k;
	long ys1 = ys_generic - k;
	long xe1 = xs_generic + k;
	long ye1 = ys_generic + k;

	long xs2 = xe_generic - k;
	long ys2 = ye_generic - k;
	long xe2 = xe_generic + k;
	long ye2 = ye_generic + k;

	Set(xs_generic, ys_generic, xe_generic, ye_generic);
	LineShape::Show(hdc, isTrace);
	Set(xs1, ys1, xe1, ye1);
	EllipseShape::Show(hdc, isTrace);
	Set(xs2, ys2, xe2, ye2);
	EllipseShape::Show(hdc, isTrace);

	Set(xs_generic, ys_generic, xe_generic, ye_generic);
}

void EllipseLineShape::MakeNewInstance(Shape*& targetShape)
{
	if (targetShape) delete targetShape;
	targetShape = new EllipseLineShape;
}

void EllipseLineShape::GiveOutData(void AddNodeCallback(std::string, long, long, long, long))
{
	AddNodeCallback("Гантеля", xs, ys, xe, ye);
}