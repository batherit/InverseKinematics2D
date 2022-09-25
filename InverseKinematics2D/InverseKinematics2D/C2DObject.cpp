#include "stdafx.h"
#include "C2DObject.h"
#include "C2DMesh.h"

C2DObject::~C2DObject()
{
	for (const auto& childPtr : ChildList)
	{
		delete childPtr;
	}
}

void C2DObject::SetParent(C2DObject* const InParentPtr)
{
	ParentPtr = InParentPtr;
	ParentPtr->ChildList.push_back(this); // 오브젝트 매니저가 생성하는 방식으로 고쳐야 됨.
}

void C2DObject::SetMesh(const std::shared_ptr<C2DMesh> InMeshPtr)
{
	MeshPtr = InMeshPtr;
}

void C2DObject::SetPosition(const C2DVector& InVector)
{
	Position = InVector;
}

const C2DObject* C2DObject::GetParent(void) const
{
	return ParentPtr;
}

C2DVector C2DObject::GetWorldPosition(void)
{
	C2DVector position(Position);

	if (ParentPtr)
	{
		C2DMatrix wParentMatrix(ParentPtr->GetWorldMatrix());
		CVectorOperation::C2DTransform(&position, &position, &wParentMatrix);
	}

	return position;
}

C2DMatrix C2DObject::GetWorldMatrix(void)
{
	C2DMatrix matrix;

	matrix.m_f11 = Right.m_fX * Scale.m_fX;
	matrix.m_f12 = Right.m_fY * Scale.m_fX;
	matrix.m_f13 = 0.f;
	matrix.m_f21 = Up.m_fX * Scale.m_fY;
	matrix.m_f22 = Up.m_fY * Scale.m_fY;
	matrix.m_f23 = 0.f;
	matrix.m_f31 = Position.m_fX;
	matrix.m_f32 = Position.m_fY;
	matrix.m_f33 = 1.f;

	if (ParentPtr)
	{
		C2DMatrix wParentMatrix(ParentPtr->GetWorldMatrix());
		CVectorOperation::C2DTransform(&matrix, &matrix, &wParentMatrix);
	}
	return matrix;
}

void C2DObject::Scaling(float InDeltaX, float InDeltaY)
{
	Scale.m_fX += InDeltaX;
	Scale.m_fY += InDeltaY;
}

void C2DObject::Rotate(float InRadianZ)
{
	SetRadianZ(RadianZ + InRadianZ);
}

void C2DObject::Translate(float InDeltaX, float InDeltaY)
{
	Scale.m_fX += InDeltaX;
	Scale.m_fY += InDeltaY;
}

void C2DObject::Translate(const C2DVector& InDeltaXY)
{
	Scale.m_fX += InDeltaXY.m_fX;
	Scale.m_fY += InDeltaXY.m_fY;
}

void C2DObject::SetRadianZ(float InRadianZ)
{
	RadianZ = InRadianZ;

	C2DMatrix mtxRotate;

	Right.m_fX = cosf(RadianZ); Right.m_fY = sinf(RadianZ);
	Up.m_fX = -sinf(RadianZ); Up.m_fY = cosf(RadianZ);
}

void C2DObject::Update(float InElapsedTime)
{
	for (const auto& childPtr : ChildList)
	{
		childPtr->Update(InElapsedTime);
	}
}

void C2DObject::Render(HDC hdc, const C2DCamera& InCamera)
{
	if (MeshPtr)
	{
		MeshPtr->Render(hdc, GetWorldMatrix(), InCamera);
	}

	for (const auto& childPtr : ChildList)
	{
		childPtr->Render(hdc, InCamera);
	}
}