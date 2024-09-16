#ifndef __BROWSER_RECT_H__
#define __BROWSER_RECT_H__

namespace sb
{

////////////////////////////////////////////////////////////////////////////////////////////////////
struct Rect
{
    Rect(): x(0), y(0), width(0), height(0) {}
    Rect(float x, float y, float w, float h): x(x), y(y), width(w), height(h) {}

    inline bool Contains(float mx, float my) const
    {
        return (mx >= x && mx <= x + width && my >= y && my <= y + height);
    }

    float x, y, width, height;
};

}

#endif //__BROWSER_RECT_H__
