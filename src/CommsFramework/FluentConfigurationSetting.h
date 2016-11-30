#pragma once

template <class T>
class FluentConfigurationSetting
{
public:

    FluentConfigurationSetting()
    {
        hasDefaultValueFallback = false;
    };

    FluentConfigurationSetting(T* value)
    {
        this->Value = value;
    };

    ~FluentConfigurationSetting()
    {

    };

    template<class Y>
    FluentConfigurationSetting<Y>* As();

    FluentConfigurationSetting<T>* FluentConfigurationSetting::WithDefault(T defaultValue)
    {
        this->hasDefaultValueFallback = true;
        this->defaultValue = defaultValue;

        return this;
    };


    T* FluentConfigurationSetting::Get()
    {
        if (this->Value == NULL)
        {
            return &this->defaultValue;
        }
        else
        {
            return this->Value;
        }
    };

    
    // Really wish I could hide those
    bool hasDefaultValueFallback;
    T defaultValue;

private:
    T* Value;

};

template<class T>
template<class Y>
inline FluentConfigurationSetting<Y>* FluentConfigurationSetting<T>::As()
{
    Y* newValue = (Y*)this->Value;

    FluentConfigurationSetting<Y>* nextObject = new FluentConfigurationSetting<Y>(newValue);
    nextObject->hasDefaultValueFallback = this->hasDefaultValueFallback;
    nextObject->defaultValue = this->defaultValue;

    return nextObject;
}