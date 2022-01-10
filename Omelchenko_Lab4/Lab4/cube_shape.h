#pragma once

class CubeShape :
    public RectShape, public LineShape
{
public:
    void Show(HDC, bool);

    void MakeNewInstance(Shape*&);
};

