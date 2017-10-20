#include "Primitives.h"

PrimitiveDrawInfo::~PrimitiveDrawInfo()
{
    switch (this->CallType)
    {
        case DrawType_Line:
        {
            PrimitiveLineDraw* prim = (PrimitiveLineDraw*)this->DrawData;

            delete(prim);

            break;
        }
        case DrawType_LineList:
        {
            PrimitiveRectDraw* prim = (PrimitiveRectDraw*)this->DrawData;

            delete(prim);

            break;
        }
        case DrawType_Rect:
        {
            PrimitiveRectDraw* prim = (PrimitiveRectDraw*)this->DrawData;

            delete(prim);

            break;
        }
    }
}

PrimitiveLineListDraw::~PrimitiveLineListDraw()
{
    delete(PointPairsArray);
}
