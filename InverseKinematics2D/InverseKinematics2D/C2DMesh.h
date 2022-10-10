#pragma once
#include "C2DCamera.h"
#include "CVectorOperation.h"
#include <vector>

class C2DCamera;

class C2DMesh
{
public:
	virtual void Render(HDC Inhdc, const C2DMatrix& InWorldMatrix, const C2DCamera& InCamera) = 0;
};

class C2DLines : public C2DMesh
{
public:
	C2DLines(const std::vector<C2DVector>& InPointList)
		:
		PointList(InPointList)
	{}
	~C2DLines()
	{
		PointList.clear();
	}
	virtual void Render(HDC Inhdc, const C2DMatrix& InWorldMatrix, const C2DCamera& InCamera) override;

private:
	std::vector<C2DVector> PointList;
};

class C2DLine : public C2DLines
{
public:
	C2DLine(const C2DVector& InStartPoint, const C2DVector& InEndPoint)
		:
		C2DLines({ InStartPoint, InEndPoint })
	{}
};

class C2DBox : public C2DLines
{
	C2DBox(const C2DVector& InLeftTopPoint, const C2DVector& InRightBottomPoint)
		:
		C2DLines({ 
			// left-top
			InLeftTopPoint,
			// right-top
			C2DVector(InRightBottomPoint.m_fX, InLeftTopPoint.m_fY),
			// right-bottom
			InRightBottomPoint,
			// left-bottom
			C2DVector(InLeftTopPoint.m_fX, InRightBottomPoint.m_fY),
			InLeftTopPoint
		})
	{}
};