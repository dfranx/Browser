#ifndef __BROWSER_THICKNESS_H__
#define __BROWSER_THICKNESS_H__

#include <Browser/Rect.h>


namespace sb
{

////////////////////////////////////////////////////////////////////////////////////////////////////
struct Thickness
{
    Thickness(): left(0), top(0), right(0), bottom(0) {}

    Thickness(float l, float t, float r, float b): left(l), top(t), right(r), bottom(b) {}

    inline Rect AsRect() const { return Rect(left, top, right - left, bottom - top); }

    float left;
    float top;
    float right;
    float bottom;
};

}

#endif //__BROWSER_THICKNESS_H__
