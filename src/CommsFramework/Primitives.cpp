#include "Primitives.h"

PrimitiveDrawInfo::~PrimitiveDrawInfo()
{
	switch (this->CallType)
	{
		case DrawType_LineList:
		{
			PrimitiveRectDraw* prim = (PrimitiveRectDraw*)this->DrawData;
		
			delete(prim);

			break;
		}
		default:
			delete(DrawData);

			break;
	}
}

PrimitiveLineListDraw::~PrimitiveLineListDraw()
{
	delete(PointPairsArray);
}
