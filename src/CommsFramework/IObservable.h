#pragma once

#include "IObserver.h"
#include "PointerList.h"

template <class TNotifyArg>
class IObservable
{
public:
    IObservable()
    {
        subjects = new PointerList<IObserver<TNotifyArg>*>();
    };
    
    ~IObservable()
    {
        subjects->Release();
        delete(subjects);
    };

    void IObservable::Register(IObserver<TNotifyArg>* observer)
    {
        subjects->Add(observer);
    };

    void IObservable::Unregister(IObserver<TNotifyArg>* observer)
    {
        subjects->Remove(observer);
    };

    void NotifyObservers(TNotifyArg* args)
    {
        auto it = subjects->GetContainer()->begin();
        while (it != subjects->GetContainer()->end())
        {
            IObserver<TNotifyArg>* obs = (*it);

            obs->Notify(args);

            it++;
        }        
    };
    
private:
    PointerList<IObserver<TNotifyArg>*>* subjects;
};

