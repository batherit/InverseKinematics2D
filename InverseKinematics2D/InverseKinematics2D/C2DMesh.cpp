#include "stdafx.h"
#include "C2DMesh.h"
#include "C2DCamera.h"

void C2DLines::Render(HDC Inhdc, const C2DMatrix& InWorldMatrix, const C2DCamera& InCamera)
{
	if (PointList.size() < 2)
		return;

	C2DMatrix mtxToScreen(InWorldMatrix);
	mtxToScreen *= InCamera.GetFromWorldToScreen();

	C2DVector sPoint;
	bool isFirstPoint = true;
	for (const C2DVector& lPoint : PointList)
	{
		CVectorOperation::C2DTransform(&sPoint, &lPoint, &mtxToScreen);
		if (isFirstPoint)
		{
			MoveToEx(Inhdc, sPoint.GetX(), sPoint.GetY(), NULL);
			isFirstPoint = false;
		}
		else
		{
			LineTo(Inhdc, sPoint.GetX(), sPoint.GetY());
		}	
	}
}
