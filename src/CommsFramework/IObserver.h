#pragma once

template <class TNotifyArg>
class IObserver
{
public:
    IObserver()
    {

    };

    ~IObserver()
    {

    };

    virtual void Notify(TNotifyArg* arg) = 0;
};

