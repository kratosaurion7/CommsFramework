#pragma once

enum PrimitiveDrawTypes
{
	DrawType_Line,
	DrawType_LineList,
	DrawType_Rect
};

struct PrimitiveDrawInfo
{
	~PrimitiveDrawInfo();

	int ZIndex;

	unsigned int Color;

	PrimitiveDrawTypes CallType;

	void* DrawData;
};

struct PrimitiveLineDraw
{
	float xA;
	float yA;

	float xB;
	float yB;
};

struct PrimitiveLineListDraw
{
	~PrimitiveLineListDraw();

	int PointPairsLength;
	float* PointPairsArray;
};

struct PrimitiveRectDraw
{
	float x;
	float y;
	float h;
	float w;
};