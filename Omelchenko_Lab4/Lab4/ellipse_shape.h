#pragma once

class EllipseShape :
    virtual public Shape
{
public:
    virtual void Show(HDC, bool);

    void MakeNewInstance(Shape*&);
};

