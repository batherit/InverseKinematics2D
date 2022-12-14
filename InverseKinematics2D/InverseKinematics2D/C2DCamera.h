#pragma once

#include"CVectorOperation.h"

class C2DCamera
{
public:
	C2DCamera();
	virtual ~C2DCamera();

public:
	void SetPosition(C2DVector vPos);
	C2DVector GetPosition(void);

	void GenerateView(C2DVector vEye, C2DVector vUp);
	void GenerateProj(float fWidth, float fHeight);
	void GenerateScreen(float xStart, float yStart, float fWidth, float fHeight);

	C2DMatrix GetFromScreenToWorld() const
	{
		C2DMatrix mtxToWorld = m_mtxView * m_mtxScale * m_mtxProj * m_mtxScreen;
		CVectorOperation::C2DInverse(&mtxToWorld, &mtxToWorld);
		return mtxToWorld;
	}
	C2DMatrix GetFromWorldToScreen() const
	{
		C2DMatrix mtxToScreen = m_mtxView * m_mtxScale * m_mtxProj * m_mtxScreen;
		return mtxToScreen;
	}

	void TransformView(C2DMatrix* outM, C2DMatrix* inM) const;
	void TransformView(C2DVector* outV, C2DVector* inV) const;
	void TransformScale(C2DMatrix* outM, C2DMatrix* inM) const;
	void TransformScale(C2DVector* outV, C2DVector* inV) const;
	void TransformProj(C2DMatrix* outM, C2DMatrix* inM) const;
	void TransformProj(C2DVector* outV, C2DVector* inV) const;
	void TransformScreen(C2DMatrix* outM, C2DMatrix* inM) const;
	void TransformScreen(C2DVector* outV, C2DVector* inV) const;

	void TransformRatio(C2DVector* outV, C2DVector* inV) const;

	void RotateZ(float fRadian);
	void Move(const C2DVector& vector);

	void ZoomInOrOut(float fMultiple);
	void ZoomInit(void);

	float GetZoomScale(void);

protected:
	C2DMatrix m_mtxView;
	C2DMatrix m_mtxScale;
	C2DMatrix m_mtxProj;
	C2DMatrix m_mtxScreen;
	C2DMatrix m_mtxRatio;

	C2DVector m_vPosW;
	C2DVector m_vUpW;
	C2DVector m_vRightW;
};