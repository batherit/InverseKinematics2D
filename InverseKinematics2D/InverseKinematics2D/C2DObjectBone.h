#pragma once
#include "C2DObject.h"

class C2DObjectIK;

class C2DObjectBone :
    public C2DObject
{
public:
    C2DObjectBone(C2DObjectIK* const InIKPtr)
        :
        IKPtr(InIKPtr)
    {}

    virtual void Update(float InElapsedTime) override;

private:
    C2DObjectIK* IKPtr = nullptr;
};

