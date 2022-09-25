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