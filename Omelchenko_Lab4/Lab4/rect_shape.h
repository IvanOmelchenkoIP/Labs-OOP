#pragma once

class RectShape :
    public virtual Shape
{
public:
    virtual void Show(HDC, bool);

    void MakeNewInstance(Shape*&);
};

