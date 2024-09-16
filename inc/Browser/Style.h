#ifndef __BROWSER_STYLE_H__
#define __BROWSER_STYLE_H__

#include <Browser/BoxedValue.h>
#include <Browser/StyleProperty.h>

#include <map>
#include <assert.h>
#include <memory>


namespace sb
{

class StyleFactory;

////////////////////////////////////////////////////////////////////////////////////////////////////
class Style
{
public:
    Style(Style&&) = delete;
    explicit Style(StyleFactory* factory): mFactory(factory) {}

    // Check if Style has property set
    inline bool Has(StylePropertyId id) const { return mProperties.find(id) != mProperties.end(); }

    // Get the value of the style
    inline BoxedValue* Get(StylePropertyId id) const
    {
        assert(Has(id));
        auto it = mProperties.find(id);
        return it->second.get();
    }

    // Get the value from style if it exists, or get it's default value if it doesn't exist
    std::unique_ptr<BoxedValue> GetOrDefaultValue(StylePropertyId id) const;

    // Set the property value
    inline void Set(StylePropertyId id, std::unique_ptr<BoxedValue> value)
    {
        mProperties[id] = std::move(value);
    }

    // Clone the Style (so it can be modified by other elements for their own purpose)
    std::shared_ptr<Style> Clone() const;

private:
    StyleFactory* mFactory;
    std::map<StylePropertyId, std::unique_ptr<BoxedValue>> mProperties;
};

}

#endif //__BROWSER_STYLE_H__
