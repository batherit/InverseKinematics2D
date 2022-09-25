#pragma once
#include<memory>
#include<vector>
#include"CVectorOperation.h"
#include"C2DCamera.h"

class C2DMesh;

class C2DObject
{
public:
	~C2DObject();

	void SetParent(C2DObject* const InParentPtr);
	void SetMesh(const std::shared_ptr<C2DMesh> InMeshPtr);
	void SetPosition(const C2DVector& InVector);

	const C2DObject* GetParent(void) const;
	C2DVector GetWorldPosition(void);
	C2DMatrix GetWorldMatrix(void);

	void Scaling(float InDeltaX, float InDeltaY);
	void Rotate(float InDeltaZ);
	void Translate(float InDeltaX, float InDeltaY);
	void Translate(const C2DVector& InDeltaXY);

	// 스케일
	void SetScaleX(float InScaleX) { Scale.m_fX = InScaleX; }
	void SetScaleY(float InScaleY) { Scale.m_fY = InScaleY; }
	void SetScaleXY(float ScaleX, float ScaleY) 
	{ 
		SetScaleX(ScaleX); 
		SetScaleY(ScaleY); 
	}
	void SetScaleXY(const C2DVector& InScale) { Scale = InScale; }

	// 회전
	void SetRadianZ(float InRadianZ);

	// 이동/위치
	void SetPosX(float InX) { Position.m_fX = InX; }
	void SetPosY(float InY) { Position.m_fY = InY; }
	void SetPos(float InX, float InY) { SetPos(C2DVector(InX, InY)); }
	void SetPos(const C2DVector& InPos) { Position = InPos; }

	virtual void Update(float InElapsedTime);	
	virtual void Render(HDC hdc, const C2DCamera& InCamera);

protected:
	C2DObject* ParentPtr = nullptr;
	std::vector<C2DObject*> ChildList;
	std::shared_ptr<C2DMesh> MeshPtr;
	C2DVector Scale{ 1.f, 1.f };
	C2DVector Up{ 0.f, 1.f };
	C2DVector Right{ 1.f, 0.f };
	float RadianZ = 0.f;
	C2DVector Position{ 0.f, 0.f };
};
