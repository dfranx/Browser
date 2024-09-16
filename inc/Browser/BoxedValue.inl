
namespace sb
{

////////////////////////////////////////////////////////////////////////////////////////////////////
template <typename T>
class BoxImpl : public BoxedValue
{
public:
    explicit BoxImpl(const T& value) : mValue(value) {}

    const T& GetValue() const { return mValue; }

    virtual std::unique_ptr<BoxedValue> Clone() const override
    {
        return std::make_unique<BoxImpl<T>>(mValue);
    }

private:
    T mValue;
};

////////////////////////////////////////////////////////////////////////////////////////////////////
template <typename T>
std::unique_ptr<BoxedValue> Box(const T& value)
{
    return std::make_unique<BoxImpl<T>>(value);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
template <typename T>
bool CanUnbox(BoxedValue* val)
{
    return dynamic_cast<BoxImpl<T>*>(val) != nullptr;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
template <typename T>
const T& Unbox(BoxedValue* boxedValue)
{
    BoxImpl<T>* box = dynamic_cast<BoxImpl<T>*>(boxedValue);
    if (box)
    {
        return box->GetValue();
    }
    else
    {
        throw std::bad_cast();
    }
}

}