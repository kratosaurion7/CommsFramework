#pragma once

#include "BaseList.h"

#include "Macros.h"

template <class T> class PointerList : public BaseList<T>
{
public:
    PointerList()
    {

    };

    ~PointerList()
    {
        delete(_container);
    };

    void PointerList::Release()
    {
        for (std::list<T>::iterator it = _container->begin(); it != _container->end(); it++)
        {
            SAFE_DELETE((*it));
        }

        _container->clear();
    };
};

