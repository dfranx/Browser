#ifndef __BROWSER_BOXEDVALUE_H__
#define __BROWSER_BOXEDVALUE_H__

#include <memory>


namespace sb
{

////////////////////////////////////////////////////////////////////////////////////////////////////
/// Box a value into a class.
////////////////////////////////////////////////////////////////////////////////////////////////////
class BoxedValue
{
public:
    virtual ~BoxedValue() = default;

    virtual std::unique_ptr<BoxedValue> Clone() const = 0;
};

/// Function for creating BoxedValue containing type T
template <typename T>
std::unique_ptr<BoxedValue> Box(const T& value);

/// Check whether BoxedValue contains the type T
template <typename T>
bool CanUnbox(BoxedValue* val);

/// Get the value from BoxedValue. If it doesn't contain T, this function throws an exception
template <typename T>
const T& Unbox(BoxedValue* boxedValue);

}

#include <Browser/BoxedValue.inl>

#endif //__BROWSER_BOXEDVALUE_H__
