#ifndef __BROWSER_DOCUMENT_H__
#define __BROWSER_DOCUMENT_H__

#include <Browser/FontDescription.h>
#include <Browser/StyleFactory.h>

#include <d2d1.h>
#include <dwrite.h>
#include <map>
#include <string>
#include <vector>
#include <functional>


struct myhtml_tree_node;
struct myhtml_tree;

namespace sb
{

class Renderer;
class PageElement;
struct Rect;

////////////////////////////////////////////////////////////////////////////////////////////////////
/// Class that loads appropriate HTML and CSS, lays them out and renders them
////////////////////////////////////////////////////////////////////////////////////////////////////
class Document
{
public:
    Document(Renderer* renderer);

    /// Load CSS and HTML
    void LoadDefaultStyles(const char* css, unsigned int css_length);
    void LoadHTML(const char* html, unsigned int html_length);

    /// Event handlers
    void OnMouseMove(float x, float y);
    void OnMouseDown(float x, float y);

    /// Memory cleanup
    void Shutdown();

    /// Lay out the elements (position and size them)
    void InvalidateLayout();

    /// Render the document to the window
    void Render();

    /// Get the bounds available for this document
    Rect GetBounds() const;

    /// Get/set the current cursor shown by the document
    inline Cursor GetMouseCursor() const { return mCursor; }
    void SetMouseCursor(Cursor cursor);

    /// Get the root element of the page
    void SetRoot(PageElement* root) { mRoot = root; }
    inline PageElement* GetRoot() const { return mRoot; }

    /// Create brushes and fonts (if cached, just return existing ones)
    ID2D1SolidColorBrush* CreateSolidColorBrush(unsigned int rgba);
    IDWriteTextFormat* CreateTextFormat(const wchar_t* name, float size, FontWeight weight,
    FontStyle style, FontStretch stretch);
    void GetFontInformation(const wchar_t* name, float size, FontWeight weight,
        FontStyle style, FontStretch stretch, float& horizAdvance, float& vertAdvance,
        IDWriteFontFace** fontFace);

    /// Various getters
    inline StyleFactory& GetStyleFactory() { return mStyleFactory; }
    inline Renderer* GetRenderer() const { return mRenderer; }

private:
    void ProcessHTMLNode(struct myhtml_tree* tree, struct myhtml_tree_node* node, PageElement* parent);
    void PostProcess();

    void RemoveHTMLWhiteSpaces(std::string& content) const;
    bool IsInlineTag(PageElement* element) const;

    void DeleteElement(PageElement* element);

protected:
    Renderer* mRenderer;
    PageElement* mRoot;
    StyleFactory mStyleFactory;

    Cursor mCursor;

private:
    struct Font
    {
        IDWriteTextFormat* dwriteFormat;

        IDWriteFontFace* dwriteFontFace;
        float verticalAdvance;
        float horizontalAdvance;

        std::wstring name;
        float size;
        FontWeight weight;
        FontStyle style;
        FontStretch stretch;
    };
    std::vector<Font> mFontCache;

    std::map<unsigned int, ID2D1SolidColorBrush*> mBrushCache;
};

}

#endif //__BROWSER_DOCUMENT_H__
