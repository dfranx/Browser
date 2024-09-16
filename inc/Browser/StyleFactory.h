#ifndef __BROWSER_STYLEFACTORY_H__
#define __BROWSER_STYLEFACTORY_H__

#include <Browser/StyleProperty.h>
#include <Browser/Color.h>
#include <Browser/DisplayType.h>
#include <Browser/FontDescription.h>
#include <Browser/Thickness.h>
#include <Browser/TextSize.h>

#include <memory>
#include <map>
#include <string>


namespace sb
{

class Style;
class PageElement;
enum StylePropertyId : int;
struct Color;
enum DisplayType: int;
enum FontStyle: int;
enum FontStretch: int;
struct TextSize;
enum Cursor: int;
struct Thickness;

////////////////////////////////////////////////////////////////////////////////////////////////////
/// Class for managing Styles
////////////////////////////////////////////////////////////////////////////////////////////////////
class StyleFactory
{
public:
    StyleFactory() = default;

    // Load the default CSS values from the given CSS
    void LoadDefaultStyles(const char* css, unsigned int css_length);

    // Get the style for an element
    std::shared_ptr<Style> ComputeStyle(PageElement* element);

    // Get the default value for a given property
    std::unique_ptr<BoxedValue> GetDefaultValue(StylePropertyId property_id) const;

    // Get the in-memory default CSS contents if no file default.css is present
    static std::string GetDefaultCSS();

private:
    void InitMetadata();

    void ParseProperty(Style* style, const std::string& name, const std::string& value);

    TextSize ParseSize(const std::string& value);
    Color ParseColor(const std::string& value);
    DisplayType ParseDisplay(const std::string& value);
    TextDecoration ParseTextDecoration(const std::string& value);
    Cursor ParseCursor(const std::string& value);
    FontStyle ParseFontStyle(const std::string& value);
    FontStretch ParseFontStretch(const std::string& value);
    FontWeight ParseFontWeight(const std::string& value);
    std::wstring ParseFontFamily(const std::string& value);
    Thickness ParseThickness(const std::string& value);

private:
    std::map<StylePropertyId, StylePropertyMetadata> mMetadata;
    std::map<std::string, std::shared_ptr<Style>> mStyles;
};

}

#endif //__BROWSER_STYLEFACTORY_H__
