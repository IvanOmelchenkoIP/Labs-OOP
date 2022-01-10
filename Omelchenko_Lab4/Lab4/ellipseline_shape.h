#pragma once

class EllipseLineShape :
    public EllipseShape, public LineShape
{
public:
    void Show(HDC, bool);

    void MakeNewInstance(Shape*&);
};

