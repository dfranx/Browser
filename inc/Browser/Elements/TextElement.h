#ifndef __BROWSER_TEXTELEMENT_H__
#define __BROWSER_TEXTELEMENT_H__

#include <Browser/Elements/PageElement.h>

#include <d2d1.h>
#include <dwrite.h>


namespace sb
{

////////////////////////////////////////////////////////////////////////////////////////////////////
class TextElement: public PageElement
{
public:
    TextElement(const wchar_t* text, const char* tag, Document* doc, PageElement* parent);

    /// Get/set the text that's going to be displayed by this element
    inline const wchar_t* GetText() const { return mText.c_str(); }
    inline void SetText(const wchar_t* text) { mText = text; }

    /// Layout the text
    virtual Point Arrange(const Rect& availableSpace, Point cursor, float blockAdvance) override;

    /// Render the text
    virtual void Render() override;

    /// Get the size in pixels of a ' ' character
    inline float GetHorizontalAdvance() const { return mHorizontalAdvance; }
    inline float GetVerticalAdvance() const { return mVerticalAdvance; }

private:
    std::wstring mText;
    IDWriteTextFormat* mDWFormat;
    IDWriteTextLayout* mDWLayout;
    ID2D1SolidColorBrush* mBrush;

    float mHorizontalAdvance;
    float mVerticalAdvance;
};

}

#endif //__BROWSER_TEXTELEMENT_H__
