#pragma once

template <class TNotifyArg>
class IObserver<TNotifyArg>
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

