#pragma once

class Shape
{
protected:
	long xs, ys, xe, ye;

public:
	virtual ~Shape() {};
	Shape(void) { xs = ys = xe = ye = 0; };

	void Set(long, long, long, long);
	virtual void Show(HDC, bool) = 0;

	virtual void MakeNewInstance(Shape*&) = 0;
	virtual void GiveOutData(void AddNodeCallback(std::string, long, long, long, long)) = 0;
};

