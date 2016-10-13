#pragma once

#include <vector>

#include <functional>
#include <algorithm>
#include <cassert>

template <class T>
class ArrayList
{
public:
	ArrayList()
	{
		_container = new std::vector<T>();
	};

	ArrayList(int initialSize)
	{
		_container = new std::vector<T>();

		_container->reserve(initialSize);
	};

	~ArrayList()
	{
		_container->clear();
		delete(_container);
	};

	void ArrayList::Add(T item)
	{
		_container->push_back(item);
	};

	void ArrayList::AddRange(ArrayList<T>* items)
	{
		auto it = items->GetContainer()->begin();

		while (it != items->GetContainer()->end())
		{
			T listItem = *it;

			_container->push_back(listItem);

			it++;
		}
	};

	T ArrayList::Get(int index)
	{
		int i = 0;

		for (std::list<T>::iterator it = _container->begin(); it != _container->end(); it++)
		{
			if (index == i)
			{
				return *it;
			}

			i++;
		}

		return NULL;
	};

	T ArrayList::GetBy(std::function<bool(T)> predicate)
	{
		for (std::list<T>::iterator it = _container->begin(); it != _container->end(); it++)
		{
			T element = *it;

			if (predicate(element))
			{
				return element;
			}
		}

		return NULL;
	};

	T ArrayList::First()
	{
		auto it = _container->begin();

		return (*it);
	};

	T ArrayList::Last()
	{
		auto it = _container->end();

		it--;

		return (*it);
	};

	ArrayList<T>* ArrayList::Where(std::function<bool(T)> predicate)
	{
		ArrayList<T>* retList = new ArrayList<T>();

		for (std::list<T>::iterator it = _container->begin(); it != _container->end(); it++)
		{
			auto test = predicate(*it);

			if (test)
			{
				retList->Add(*it);
			}
		}

		return retList;
	};

	T ArrayList::Single(std::function<bool(T)> predicate)
	{
		T retValue = NULL;

		for (std::list<T>::iterator it = _container->begin(); it != _container->end(); it++)
		{
			T val = *it;

			auto test = predicate(*it);

			if (test)
			{
				retValue = val;
			}
		}

		return retValue;
	};

	bool ArrayList::Contains(std::function<bool(T)> predicate)
	{
		for (std::list<T>::iterator it = _container->begin(); it != _container->end(); it++)
		{
			T element = *it;

			if (predicate(element))
			{
				return true;
			}
		}

		return false;
	};

	bool ArrayList::ContainsItem(T item)
	{
		for (std::list<T>::iterator it = _container->begin(); it != _container->end(); it++)
		{
			T element = *it;

			if (element == item)
			{
				return true;
			}
		}

		return false;
	}

	void ArrayList::ForEach(std::function<void(T)> func)
	{
		for (std::list<T>::iterator it = _container->begin(); it != _container->end(); it++)
		{
			T val = *it;

			func(val);
		}
	};

	int ArrayList::IndexOf(T item)
	{
		int i = 0;

		for (std::list<T>::iterator it = _container->begin(); it != _container->end(); it++)
		{
			T current = (*it);

			if (current == item)
			{
				return i;
			}
		}

		return NULL;
	};

	void ArrayList::Swap(int indexA, int indexB)
	{
		auto x = _container->begin();
		auto y = _container->begin();
		// I would like to know what type to put in instead of auto
		auto elementA = std::next(x, indexA);
		auto elementB = std::next(y, indexB);

		std::iter_swap(elementA, elementB);
	};

	void ArrayList::Shuffle()
	{
		int length = this->Count();
		RandomGen rng;

		for (int i = length - 1; i > 0; i--)
		{
			int randomIndex = rng.GetRandom(length - 1);

			this->Swap(length - 1, randomIndex);
		}
	};


	void ArrayList::RemoveAt(int index)
	{
		auto it = _container->begin();

		std::advance(it, index);

		_container->erase(it);
	};

	void ArrayList::RemoveObject(T object)
	{
		for (std::list<T>::iterator it = _container->begin(); it != _container->end(); it++)
		{
			T current = (*it);

			if (current == object)
			{
				_container->erase(it);

				break;
			}
		}
	};

	void Clear()
	{
		_container->clear();
	};

	int ArrayList::Count()
	{
		return _container->size();
	};

	T** GetListAs2dArray(int width)
	{
		assert(width > 0);

		int totalItems = this->Count();

		if (totalItems % width != 0)
			return NULL;


		int columnIndex = 0;
		int rowIndex = 0;

		T** resultList = new T*[totalItems];
		T* row = new T[width];
		resultList[rowIndex] = row;

		auto it = this->GetContainer()->begin();
		while (it != this->GetContainer()->end())
		{
			resultList[rowIndex][columnIndex] = (*it);

			columnIndex++;

			if (columnIndex % width == 0)
			{
				rowIndex++;
				T* newRow = new T[width];
				resultList[rowIndex] = newRow;

				columnIndex = 0;
			}

			it++;
		}

		return resultList;
	};

	std::vector<T>* GetContainer()
	{
		return _container;
	};



protected:
	std::vector<T>* _container;

private:

};

template <class T, class U>
ArrayList<U>* ListSelect(ArrayList<T>* input, std::function<U(T)> selector)
{
	ArrayList<U>* outList = new ArrayList<U>();

	for (std::vector<T>::iterator it = input->GetContainer()->begin(); it != input->GetContainer()->end(); it++)
	{
		auto projected = selector(*it);

		outList->Add(projected);
	}

	return outList;
};

template <class T, class Agg>
Agg ListAggregate(ArrayList<T>* input, Agg initial, std::function<Agg(Agg, T)> func)
{
	Agg aggregateValue = initial;

	for (std::vector<T>::iterator it = input->GetContainer()->begin(); it != input->GetContainer()->end(); it++)
	{
		T element = *it;

		aggregateValue = func(aggregateValue, element);
	}

	return aggregateValue;
}