#pragma once

#include "Collections/BaseList.h"

#include "Macros.h"

template <class T> 
class PointerList : public BaseList<T>
{
public:
    PointerList()
    {

    };

    ~PointerList()
    {
        //delete(_container);
    };

    void Release()
    {
        for (typename std::list<T>::iterator it = this->_container->begin(); it != this->_container->end(); it++)
        {
			T obj = *it;

			if (obj != NULL)
			{
				delete(obj);
			}
        }

        this->_container->clear();
    };
};

