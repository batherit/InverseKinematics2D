#include "stdafx.h"
#include "C2DObjectBone.h"
#include "C2DObjectIK.h"

void C2DObjectBone::Update(float InElapsedTime)
{
	if (!IKPtr)
		return;

	const C2DVector& TargetPositon = IKPtr->GetTargetPosition();

	if (ChildList.empty())
	{

	}
	else
	{

	}
}
