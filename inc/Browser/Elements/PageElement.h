#ifndef __BROWSER_PAGEELEMENT_H__
#define __BROWSER_PAGEELEMENT_H__

#include <Browser/Style.h>
#include <Browser/Rect.h>
#include <Browser/Point.h>
#include <Browser/DisplayType.h>

#include <memory>
#include <vector>
#include <string>


namespace sb
{

class Document;

////////////////////////////////////////////////////////////////////////////////////////////////////
/// Visual representation of each element of the Document
////////////////////////////////////////////////////////////////////////////////////////////////////
class PageElement
{
public:
    PageElement(const char* tag, Document* doc, PageElement* parent);

    /// Get/set the parent of this element
    inline void SetParent(PageElement* parent) { mParent = parent; }
    inline PageElement* GetParent() const { return mParent; }

    /// Get the HTML tag (TODO: use myHTML tag ID enum)
    inline const std::string& GetTag() const { return mTag; }

    /// Get the children of this element
    inline std::vector<PageElement*>& GetChildren() { return mChildren; }

    /// Get the attributes applied to this element
    inline std::map<std::string, std::string>& GetAttributes() { return mAttributes; }

    /// Layout information
    DisplayType GetDisplayType() const;
    inline const Rect& GetLayoutBounds() {return mLayoutBounds; }
    inline const Rect& GetContentBounds() {return mContentBounds; }

    /// Event handlers
    virtual void OnMouseMove(float x, float y);
    virtual void OnMouseDown(float x, float y);

    /// Update the layout of this element and it's children
    virtual Point Arrange(const Rect& availableSpace, Point cursor, float blockAdvance);

    /// Render the element
    virtual void Render();

protected:
    std::string mTag;
    Document* mDocument;
    PageElement* mParent;
    std::vector<PageElement*> mChildren;

    std::shared_ptr<Style> mStyle;

    Rect mLayoutBounds;
    Rect mContentBounds;

    std::map<std::string, std::string> mAttributes;
};

}

#endif //__BROWSER_PAGEELEMENT_H__
