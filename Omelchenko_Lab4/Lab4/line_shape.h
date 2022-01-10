#pragma once

class LineShape :
    public virtual Shape
{
public:
    virtual void Show(HDC, bool);

    void MakeNewInstance(Shape*&);
};

