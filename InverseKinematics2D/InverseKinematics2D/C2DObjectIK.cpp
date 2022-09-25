#include "stdafx.h"
#include "C2DObjectIK.h"
#include "C2DObjectBone.h"
#include "C2DMesh.h"
#include "Macro.h"

C2DObjectIK::C2DObjectIK()
{
	std::vector<C2DVector> lines{ {0.f, 0.f}, {100.f, 0.f} };
	std::shared_ptr<C2DLines> linesMeshPtr = std::make_shared<C2DLines>(lines);

	SetMesh(linesMeshPtr);

	RootBonePtr = new C2DObjectBone(this);
	RootBonePtr->SetMesh(linesMeshPtr);
	RootBonePtr->SetPosition({ 100.f, 0.f });
	RootBonePtr->SetRadianZ(ToRadian(45.f));
	RootBonePtr->SetParent(this);

	C2DObjectBone* const object0Ptr = new C2DObjectBone(this);
	object0Ptr->SetMesh(linesMeshPtr);
	object0Ptr->SetPosition({ 100.f, 0.f });
	object0Ptr->SetRadianZ(ToRadian(45.f));
	object0Ptr->SetParent(RootBonePtr);

	C2DObjectBone* const object1Ptr = new C2DObjectBone(this);
	object1Ptr->SetMesh(linesMeshPtr);
	object1Ptr->SetPosition({ 100.f, 0.f });
	object1Ptr->SetRadianZ(ToRadian(-30.f));
	object1Ptr->SetParent(object0Ptr);

	C2DObjectBone* const object2Ptr = new C2DObjectBone(this);
	object2Ptr->SetMesh(linesMeshPtr);
	object2Ptr->SetPosition({ 100.f, 0.f });
	object2Ptr->SetRadianZ(ToRadian(45.f));
	object2Ptr->SetParent(object1Ptr);
}

void C2DObjectIK::Update(float InElapsedTime)
{
	C2DObject::Update(InElapsedTime);
}

void C2DObjectIK::Render(HDC hdc, const C2DCamera& InCamera)
{
	C2DObject::Render(hdc, InCamera);
}
