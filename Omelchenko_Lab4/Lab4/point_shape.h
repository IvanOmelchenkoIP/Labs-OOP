#pragma once

class PointShape :
    public Shape
{
public:
    void Show(HDC, bool);

    void MakeNewInstance(Shape*&);
};

