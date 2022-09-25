#pragma once
#include "C2DObject.h"
#include <vector>
#include "CVectorOperation.h"

class C2DObjectBone;

class C2DObjectIK :
    public C2DObject
{
public:
    C2DObjectIK();

    virtual void Update(float InElapsedTime) override;
    virtual void Render(HDC hdc, const C2DCamera& InCamera) override;

    void SetTargetPosition(const C2DVector& InTargetPosition) { TargetPosition = InTargetPosition; }
    const C2DVector& GetTargetPosition() const { return TargetPosition; }

private:
    C2DVector TargetPosition;
    C2DObjectBone* RootBonePtr = nullptr;
};

