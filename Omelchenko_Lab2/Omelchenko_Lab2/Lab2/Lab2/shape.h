#pragma once

class Shape
{
protected:
	long xs, ys, xe, ye;

public:
	void Set(long, long, long, long);
	virtual void Show(HDC) = 0;
};

class PointShape : public Shape  
{
public:
	void Show(HDC);
};

class LineShape : public Shape
{
public:
	void Show(HDC);
};

class RectShape : public Shape
{
public:
	void Show(HDC);
};

class EllipseShape : public Shape
{
public:
	void Show(HDC);
};

