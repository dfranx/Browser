#include <BrowserJam/Elements/PageElement.h>
#include <BrowserJam/Style.h>

#include "BrowserJam/Document.h"
#include "BrowserJam/Renderer.h"
#include "BrowserJam/StyleFactory.h"
#include <BrowserJam/Cursor.h>


using namespace sb;


PageElement::PageElement(const char* tag, Document* doc, PageElement* parent):
    mTag(tag), mDocument(doc), mParent(parent)
{
}

DisplayType PageElement::GetDisplayType() const
{
    if (mStyle && mStyle->Has(StylePropertyId_Display))
    {
        return Unbox<DisplayType>(mStyle->Get(StylePropertyId_Display));
    }
    return DisplayType_Block;
}

void PageElement::OnMouseMove(float x, float y)
{
    bool handled = false;

    if (mStyle)
    {
        if (mStyle->Has(StylePropertyId_Cursor))
        {
            Cursor cursor = Unbox<Cursor>(mStyle->Get(StylePropertyId_Cursor));
            if (mDocument->GetMouseCursor() != cursor)
            {
                handled = true;
                mDocument->SetMouseCursor(cursor);
            }
        }
        else if (mDocument->GetMouseCursor() != Cursor_Default)
        {
            mDocument->SetMouseCursor(Cursor_Default);
        }
    }

    if (!handled)
    {
        for (auto& child: mChildren)
        {
            if (child->GetContentBounds().Contains(x, y))
            {
                child->OnMouseMove(x, y);
            }
        }
    }
}

void PageElement::OnMouseDown(float x, float y)
{
    bool handled = false;

    if (mTag == "a")
    {
        std::string link = mAttributes["href"];
        printf("Clicked on: %s\n", link.c_str());
        handled = true;
    }

    if (!handled)
    {
        for (auto& child: mChildren)
        {
            if (child->GetContentBounds().Contains(x, y))
            {
                child->OnMouseDown(x, y);
            }
        }
    }
}

Point PageElement::Arrange(const Rect& availableSpace, Point cursor, float blockAdvance)
{
    mStyle = mDocument->GetStyleFactory().ComputeStyle(this);

    Thickness margin, padding;

    if (mStyle->Has(StylePropertyId_Margin))
    {
        margin = Unbox<Thickness>(mStyle->Get(StylePropertyId_Margin));
    }
    if (mStyle->Has(StylePropertyId_Padding))
    {
        padding = Unbox<Thickness>(mStyle->Get(StylePropertyId_Padding));
    }

    Rect contentSpace = availableSpace;
    contentSpace.x = cursor.x + margin.left + padding.left;
    contentSpace.y = cursor.y + margin.top + padding.top;
    contentSpace.width -= (cursor.x - availableSpace.x) + margin.left + padding.left + margin.right + padding.right;
    contentSpace.height -= (cursor.y - availableSpace.y) + margin.top + padding.top + margin.bottom + padding.bottom;

    DisplayType display = GetDisplayType();
    if (display == DisplayType_Block)
    {
        contentSpace.x = availableSpace.x + margin.left + padding.left;
        cursor.x = contentSpace.x;
        cursor.y = cursor.y + blockAdvance + margin.top + padding.top;
    }

    Point myCursor = cursor; // Store the original cursor position

    float childrenRight = contentSpace.x;
    float childrenBottom = contentSpace.y;
    float childBlockHeight = 0.0f;

    for (auto& child : mChildren)
    {
        cursor = child->Arrange(contentSpace, cursor, childBlockHeight);

        const Rect& lb = child->GetLayoutBounds();
        childrenBottom = std::max<float>(childrenBottom, lb.y + lb.height);
        childrenRight = std::max<float>(childrenRight, lb.x + lb.width);
        childBlockHeight = lb.height;
    }

    mLayoutBounds = Thickness(myCursor.x - margin.left - padding.left,
        myCursor.y - margin.top - padding.top,
        childrenRight + margin.right + padding.right,
        childrenBottom + margin.bottom + padding.bottom).AsRect();
    mContentBounds = Thickness(myCursor.x - padding.left, myCursor.y - padding.top,
        childrenRight + padding.right, childrenBottom + padding.bottom).AsRect();

    return { mLayoutBounds.x + mLayoutBounds.width, mLayoutBounds.y };
}

void PageElement::Render()
{
    auto rt = mDocument->GetRenderer()->GetRenderTarget();

    // Draw background
    if (mStyle && !mTag.empty())
    {
        float borderRadius = Unbox<Thickness>(mStyle->GetOrDefaultValue(StylePropertyId_BorderRadius).get()).left;
        D2D1_ROUNDED_RECT roundedRect;
        roundedRect.rect = { mContentBounds.x, mContentBounds.y, mContentBounds.x + mContentBounds.width, mContentBounds.y + mContentBounds.height };
        roundedRect.radiusX = borderRadius;
        roundedRect.radiusY = borderRadius;

        if (mStyle->Has(StylePropertyId_BackgroundColor))
        {
            Color color = Unbox<Color>(mStyle->Get(StylePropertyId_BackgroundColor));
            ID2D1SolidColorBrush* brush = mDocument->CreateSolidColorBrush(color.AsUInt32());

            if (borderRadius == 0.0f)
            {
                rt->FillRectangle(roundedRect.rect, brush);
            }
            else
            {
                rt->FillRoundedRectangle(roundedRect, brush);
            }
        }
        if (mStyle->Has(StylePropertyId_BorderWidth))
        {
            Thickness border = Unbox<Thickness>(mStyle->Get(StylePropertyId_BorderWidth));
            Color color = Unbox<Color>(mStyle->GetOrDefaultValue(StylePropertyId_BorderColor)->Clone().get());

            ID2D1SolidColorBrush* brush = mDocument->CreateSolidColorBrush(color.AsUInt32());

            if (borderRadius == 0.0f)
            {
                rt->DrawRectangle(roundedRect.rect, brush, border.left, nullptr);
            }
            else
            {
                rt->DrawRoundedRectangle(roundedRect, brush, border.left, nullptr);
            }
        }
    }

    for (auto& child : mChildren)
        child->Render();
}
