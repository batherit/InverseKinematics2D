#include "stdafx.h"
#include "C2DObjectBone.h"
#include "C2DObjectIK.h"
#include "Macro.h"

void C2DObjectBone::Update(float InElapsedTime)
{
	if (!IKPtr)
		return;

	if (ChildList.empty())
	{
		const C2DVector& targetPosition = IKPtr->GetTargetPosition();

		C2DMatrix wMatrix = GetWorldMatrix();
		C2DVector wBeginPoint(wMatrix.m_f31, wMatrix.m_f32);
		C2DVector wEndPoint(wBeginPoint + C2DVector(wMatrix.m_f21, wMatrix.m_f22) * 100.f);

		C2DVector wToTargetVector = targetPosition - wBeginPoint;
		CVectorOperation::C2DNormalize(&wToTargetVector, &wToTargetVector);
		C2DVector wFrontVector = wEndPoint - wBeginPoint;
		CVectorOperation::C2DNormalize(&wFrontVector, &wFrontVector);

		float dot = CVectorOperation::C2DDotProduct(&wToTargetVector, &wFrontVector);
		if (dot < -1.f)
		{
			dot = -1.f;
		}
		else if (dot > 1.f)
		{
			dot = 1.f;
		}
		C3DVector wToTargetVector3D{ wToTargetVector.m_fX, wToTargetVector.m_fY, 0.f };
		C3DVector wFrontVector3D{ wFrontVector.m_fX, wFrontVector.m_fY, 0.f };
		float angleRadian = acosf(dot);

		if (CVectorOperation::C3DCross(&wFrontVector3D, &wToTargetVector3D).m_fZ > 0)
		{
			angleRadian *= 1.f;
		}
		else
		{
			angleRadian *= -1.f;
		}

		float angleDegree = ToDegree(angleRadian);
		Rotate(angleRadian * 10.f * InElapsedTime);

		wMatrix = GetWorldMatrix();
		IKPtr->SetEndPoint(C2DVector(wBeginPoint + C2DVector(wMatrix.m_f21, wMatrix.m_f22) * 100.f));
	}
	else
	{
		for (auto& childPtr : ChildList)
		{
			childPtr->Update(InElapsedTime);
		}
		RotateToTarget(InElapsedTime);
	}
}

void C2DObjectBone::RotateToTarget(float InElapsedTime)
{
	if (!IKPtr)
		return;

	const C2DVector& targetPosition = IKPtr->GetTargetPosition();
	const C2DVector& wIKEndPoint = IKPtr->GetEndPoint();

	C2DMatrix wMatrix = GetWorldMatrix();
	C2DVector wBeginPoint(wMatrix.m_f31, wMatrix.m_f32);
	C2DVector wEndPoint(wBeginPoint + C2DVector(wMatrix.m_f21, wMatrix.m_f22) * 100.f);

	C2DVector wToTargetVector = targetPosition - wBeginPoint;
	CVectorOperation::C2DNormalize(&wToTargetVector, &wToTargetVector);
	C2DVector wFrontVector = wIKEndPoint - wBeginPoint;
	CVectorOperation::C2DNormalize(&wFrontVector, &wFrontVector);

	float dot = CVectorOperation::C2DDotProduct(&wToTargetVector, &wFrontVector);
	if (dot < -1.f)
	{
		dot = -1.f;
	}
	else if(dot > 1.f)
	{
		dot = 1.f;
	}
	C3DVector wToTargetVector3D{ wToTargetVector.m_fX, wToTargetVector.m_fY, 0.f };
	C3DVector wFrontVector3D{ wFrontVector.m_fX, wFrontVector.m_fY, 0.f };
	float angleRadian = acosf(dot);

	if (CVectorOperation::C3DCross(&wFrontVector3D, &wToTargetVector3D).m_fZ > 0)
	{
		angleRadian *= 1.f;
	}
	else
	{
		angleRadian *= -1.f;
	}

	float angleDegree = ToDegree(angleRadian);
	Rotate(angleRadian * 10.f * InElapsedTime);
}
