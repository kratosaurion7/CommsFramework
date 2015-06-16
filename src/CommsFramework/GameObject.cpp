#include "GameObject.h"



GameObject::GameObject()
{
}


GameObject::~GameObject()
{
	if (Ident != NULL)
		delete Ident;
}
