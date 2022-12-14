#include "stdafx.h"
#include "CVectorOperation.h"
#include <math.h>


CVectorOperation::CVectorOperation()
{
}


CVectorOperation::~CVectorOperation()
{
}

void CVectorOperation::C2DIdentify(C2DMatrix* inM)
{
	inM->m_f11 = 1.0f; inM->m_f12 = 0.0f; inM->m_f13 = 0.0f;
	inM->m_f21 = 0.0f; inM->m_f22 = 1.0f; inM->m_f23 = 0.0f;
	inM->m_f31 = 0.0f; inM->m_f32 = 0.0f; inM->m_f33 = 1.0f;
}

void CVectorOperation::C2DTransform(C2DVector* outV, const C2DVector* const inV, const C2DMatrix* const inM)
{
	C2DVector vResult;

	vResult.Set(*inV);

	vResult.m_fX = inV->m_fX * inM->m_f11 + inV->m_fY * inM->m_f21 + inM->m_f31;
	vResult.m_fY = inV->m_fX * inM->m_f12 + inV->m_fY * inM->m_f22 + inM->m_f32;

	outV->Set(vResult);
}

void CVectorOperation::C2DTransform(C2DMatrix* outM, const C2DMatrix* const inM1, const C2DMatrix* const inM2)
{
	C2DMatrix mtxResult;

	mtxResult.m_f11 = inM1->m_f11 * inM2->m_f11 + inM1->m_f12 * inM2->m_f21 + inM1->m_f13 * inM2->m_f31;
	mtxResult.m_f12 = inM1->m_f11 * inM2->m_f12 + inM1->m_f12 * inM2->m_f22 + inM1->m_f13 * inM2->m_f32;
	mtxResult.m_f13 = inM1->m_f11 * inM2->m_f13 + inM1->m_f12 * inM2->m_f23 + inM1->m_f13 * inM2->m_f33;

	mtxResult.m_f21 = inM1->m_f21 * inM2->m_f11 + inM1->m_f22 * inM2->m_f21 + inM1->m_f23 * inM2->m_f31;
	mtxResult.m_f22 = inM1->m_f21 * inM2->m_f12 + inM1->m_f22 * inM2->m_f22 + inM1->m_f23 * inM2->m_f32;
	mtxResult.m_f23 = inM1->m_f21 * inM2->m_f13 + inM1->m_f22 * inM2->m_f23 + inM1->m_f23 * inM2->m_f33;

	mtxResult.m_f31 = inM1->m_f31 * inM2->m_f11 + inM1->m_f32 * inM2->m_f21 + inM1->m_f33 * inM2->m_f31;
	mtxResult.m_f32 = inM1->m_f31 * inM2->m_f12 + inM1->m_f32 * inM2->m_f22 + inM1->m_f33 * inM2->m_f32;
	mtxResult.m_f33 = inM1->m_f31 * inM2->m_f13 + inM1->m_f32 * inM2->m_f23 + inM1->m_f33 * inM2->m_f33;

	outM->Set(mtxResult);
}

void CVectorOperation::C2DScalarProduct(C2DVector* outV, float fS, const C2DVector* const inV)
{
	outV->m_fX = fS * inV->m_fX;
	outV->m_fY = fS * inV->m_fY;
}

void CVectorOperation::C2DScalarProduct(C2DMatrix* outM, float fS, const C2DMatrix* const inM)
{
	outM->m_f11 = fS * inM->m_f11; outM->m_f12 = fS * inM->m_f12; outM->m_f13 = fS * inM->m_f13;
	outM->m_f21 = fS * inM->m_f21; outM->m_f22 = fS * inM->m_f22; outM->m_f23 = fS * inM->m_f23;
	outM->m_f31 = fS * inM->m_f31; outM->m_f32 = fS * inM->m_f32; outM->m_f33 = fS * inM->m_f33;
}

float CVectorOperation::C2DDotProduct(C2DVector* inV1, const C2DVector* const inV2)
{
	return inV1->m_fX * inV2->m_fX + inV1->m_fY * inV2->m_fY;
}

void CVectorOperation::C2DInverse(C2DMatrix* outM, const C2DMatrix* const inM)
{
	C2DMatrix mtxResult;

	float fDet;

	fDet = (inM->m_f11 * inM->m_f22 * inM->m_f33 + inM->m_f21 * inM->m_f32 * inM->m_f13 + inM->m_f31 * inM->m_f12 * inM->m_f23)
		- (inM->m_f11 * inM->m_f32 * inM->m_f23 + inM->m_f31 * inM->m_f22 * inM->m_f13 + inM->m_f21 * inM->m_f12 * inM->m_f33);

	if (!(-0.001f <= fDet && fDet <= 0.001f))		// ???? ???? 1/10^3
	{
		mtxResult.m_f11 = inM->m_f22 * inM->m_f33 - inM->m_f23 * inM->m_f32;
		mtxResult.m_f12 = inM->m_f13 * inM->m_f32 - inM->m_f12 * inM->m_f33;
		mtxResult.m_f13 = inM->m_f12 * inM->m_f23 - inM->m_f13 * inM->m_f22;

		mtxResult.m_f21 = inM->m_f23 * inM->m_f31 - inM->m_f21 * inM->m_f33;
		mtxResult.m_f22 = inM->m_f11 * inM->m_f33 - inM->m_f13 * inM->m_f31;
		mtxResult.m_f23 = inM->m_f13 * inM->m_f21 - inM->m_f11 * inM->m_f23;

		mtxResult.m_f31 = inM->m_f21 * inM->m_f32 - inM->m_f22 * inM->m_f31;
		mtxResult.m_f32 = inM->m_f12 * inM->m_f31 - inM->m_f11 * inM->m_f32;
		mtxResult.m_f33 = inM->m_f11 * inM->m_f22 - inM->m_f12 * inM->m_f21;

		CVectorOperation::C2DScalarProduct(&mtxResult, 1 / fDet, &mtxResult);

		outM->Set(mtxResult);
	}
	else
	{
		// ???????? ???????? ?????? nullptr?? ????????.
		outM = nullptr;
	}
}

float CVectorOperation::C2DLength(const C2DVector* const inV)
{
	return sqrtf(inV->GetX() * inV->GetX() + inV->GetY() * inV->GetY());
}

void CVectorOperation::C2DNormalize(C2DVector* outV, const C2DVector* const inV)
{
	C2DVector vResult;
	float vLen = CVectorOperation::C2DLength(inV);

	if (-0.001f <= vLen && vLen <= 0.001f)
	{
		vResult.Set(0.0f, 0.0f);
	}
	else
	{
		CVectorOperation::C2DScalarProduct(&vResult, 1.0f / vLen, inV);
	}


	outV->Set(vResult);
}

void CVectorOperation::C3DCross(C3DVector* outV, C3DVector* inV1, C3DVector* inV2)
{
	C3DVector vResult;

	vResult.m_fX = inV1->GetY() * inV2->GetZ() - inV1->GetZ() * inV2->GetY();
	vResult.m_fY = inV1->GetZ() * inV2->GetX() - inV1->GetX() * inV2->GetZ();
	vResult.m_fZ = inV1->GetX() * inV2->GetY() - inV1->GetY() * inV2->GetX();

	outV->Set(vResult);
}

C3DVector CVectorOperation::C3DCross(C3DVector* inV1, C3DVector* inV2)
{
	C3DVector vResult;

	CVectorOperation::C3DCross(&vResult, inV1, inV2);

	return vResult;
}

void CVectorOperation::C3DScalarProduct(C3DVector* outV, float fS, C3DVector* inV)
{
	outV->m_fX = fS * inV->m_fX;
	outV->m_fY = fS * inV->m_fY;
	outV->m_fZ = fS * inV->m_fZ;
}

float CVectorOperation::C3DDotProduct(C3DVector* inV1, C3DVector* inV2)
{
	return inV1->m_fX * inV2->m_fX + inV1->m_fY * inV2->m_fY + inV1->m_fZ * inV2->m_fZ;
}

float CVectorOperation::C3DLength(C3DVector* inV)
{
	return sqrtf(inV->GetX() * inV->GetX() + inV->GetY() * inV->GetY() + inV->GetZ() * inV->GetZ());
}

void CVectorOperation::C3DNormalize(C3DVector* outV, C3DVector* inV)
{
	C3DVector vResult;
	float vLen = CVectorOperation::C3DLength(inV);

	if (-0.001f <= vLen && vLen <= 0.001f)
	{
		vResult.Set(0.0f, 0.0f, 0.0f);
	}
	else
	{
		CVectorOperation::C3DScalarProduct(&vResult, 1.0f / vLen, inV);
	}


	outV->Set(vResult);
}

C2DVector::C2DVector() : m_fX(0.0f), m_fY(0.0f)
{

}

C2DVector::C2DVector(float fX, float fY)
{
	m_fX = fX;
	m_fY = fY;
}

C2DVector::~C2DVector()
{

}

void C2DVector::Set(float fX, float fY)
{
	m_fX = fX;
	m_fY = fY;
}

void C2DVector::Set(const C2DVector& vector)
{
	m_fX = vector.m_fX;
	m_fY = vector.m_fY;
}

float C2DVector::GetX(void) const
{
	return m_fX;
}

float C2DVector::GetY(void) const
{
	return m_fY;
}

C2DVector C2DVector::GetXY(void) const
{
	C2DVector vResult;

	vResult.Set(m_fX, m_fY);

	return vResult;
}

C2DVector& C2DVector::operator=(const C2DVector& v)
{
	m_fX = v.m_fX;
	m_fY = v.m_fY;

	return *this;
}

const C2DVector C2DVector::operator-(const C2DVector& v) const
{
	C2DVector vResult;

	vResult.Set(m_fX - v.m_fX, m_fY - v.m_fY);

	return vResult;
}

C2DVector& C2DVector::operator-=(const C2DVector& v)
{
	m_fX -= v.m_fX;
	m_fY -= v.m_fY;

	return *this;
}
const C2DVector C2DVector::operator+(const C2DVector& v) const
{
	C2DVector vResult;

	vResult.Set(m_fX + v.m_fX, m_fY + v.m_fY);

	return vResult;
}


C2DVector& C2DVector::operator+=(const C2DVector& v)
{
	m_fX += v.m_fX;
	m_fY += v.m_fY;

	return *this;
}

const C2DVector C2DVector::operator*(float fS) const
{
	C2DVector vResult;

	vResult.Set(m_fX * fS, m_fY * fS);

	return vResult;
}

const C2DVector C2DVector::operator*(const C2DMatrix& m) const
{
	C2DVector vResult;

	CVectorOperation::C2DTransform(&vResult, this, &m);

	return vResult;
}

C2DVector& C2DVector::operator*=(float fS)
{
	m_fX *= fS; 
	m_fY *= fS;

	return *this;
}

const C2DVector C2DVector::operator/(float fS) const
{
	C2DVector vResult;

	vResult.Set(m_fX / fS, m_fY / fS);

	return vResult;
}

C2DMatrix::C2DMatrix() :
	m_f11(1.0f), m_f12(0.0f), m_f13(0.0f),
	m_f21(0.0f), m_f22(1.0f), m_f23(0.0f),
	m_f31(0.0f), m_f32(0.0f), m_f33(1.0f)
{

}

C2DMatrix::~C2DMatrix()
{

}

void C2DMatrix::Identify(void)
{
	m_f11 = 1.0f;	m_f12 = 0.0f;	m_f13 = 0.0f;
	m_f21 = 0.0f;	m_f22 = 1.0f;	m_f23 = 0.0f;
	m_f31 = 0.0f;	m_f32 = 0.0f;	m_f33 = 1.0f;
}

void C2DMatrix::Set(const C2DMatrix& matrix)
{
	m_f11 = matrix.m_f11;	m_f12 = matrix.m_f12;	m_f13 = matrix.m_f13;
	m_f21 = matrix.m_f21;	m_f22 = matrix.m_f22;	m_f23 = matrix.m_f23;
	m_f31 = matrix.m_f31;	m_f32 = matrix.m_f32;	m_f33 = matrix.m_f33;
}

C2DMatrix& C2DMatrix::operator=(const C2DMatrix& m)
{
	this->Set(m);

	return *this;
}

const C2DMatrix C2DMatrix::operator*(const C2DMatrix& m) const
{
	C2DMatrix mtxResult;

	CVectorOperation::C2DTransform(&mtxResult, this, &m);

	return mtxResult;
}

C2DMatrix& C2DMatrix::operator*=(const C2DMatrix& m)
{
	return *this = (*this) * m;
}

C3DVector::C3DVector() : m_fX(0.0f), m_fY(0.0f), m_fZ(0.0f)
{

}

C3DVector::C3DVector(float fX, float fY, float fZ)
{
	m_fX = fX;
	m_fY = fY;
	m_fZ = fZ;
}

C3DVector::~C3DVector()
{

}

void C3DVector::Set(float fX, float fY, float fZ)
{
	m_fX = fX;
	m_fY = fY;
	m_fZ = fZ;
}

void C3DVector::Set(C3DVector& vector)
{
	m_fX = vector.m_fX;
	m_fY = vector.m_fY;
	m_fZ = vector.m_fZ;
}

float C3DVector::GetX(void)
{
	return m_fX;
}

float C3DVector::GetY(void)
{
	return m_fY;
}

float C3DVector::GetZ(void)
{
	return m_fZ;
}

C3DVector C3DVector::GetXYZ(void)
{
	C3DVector vResult;

	vResult.Set(m_fX, m_fY, m_fZ);

	return vResult;
}

C3DVector& C3DVector::operator=(C3DVector& v)
{
	m_fX = v.m_fX;
	m_fY = v.m_fY;
	m_fZ = v.m_fZ;

	return *this;
}

const C3DVector C3DVector::operator-(C3DVector& v)
{
	C3DVector vResult;

	vResult.Set(m_fX - v.m_fX, m_fY - v.m_fY, m_fZ - v.m_fZ);

	return vResult;
}

C3DVector& C3DVector::operator-=(C3DVector& v)
{
	C3DVector vResult;

	vResult.Set(m_fX -= v.m_fX, m_fY -= v.m_fY, m_fZ -= v.m_fZ);

	return vResult;
}
const C3DVector C3DVector::operator+(C3DVector& v)
{
	C3DVector vResult;

	vResult.Set(m_fX + v.m_fX, m_fY + v.m_fY, m_fZ + v.m_fZ);

	return vResult;
}


C3DVector& C3DVector::operator+=(C3DVector& v)
{
	C3DVector vResult;

	vResult.Set(m_fX += v.m_fX, m_fY += v.m_fY, m_fZ += v.m_fZ);

	return vResult;
}

const C3DVector C3DVector::operator*(float fS)
{
	C3DVector vResult;

	vResult.Set(m_fX * fS, m_fY * fS, m_fZ * fS);

	return vResult;
}

//C3DVector C3DVector::operator*(C2DMatrix& m)
//{
//	C2DVector vResult;
//
//	CVectorOperation::C2DTransform(&vResult, this, &m);
//
//	return vResult;
//}

C3DVector& C3DVector::operator*=(float fS)
{
	C3DVector vResult;

	vResult.Set(m_fX *= fS, m_fY *= fS, m_fZ *= fS);

	return vResult;
}

const C3DVector C3DVector::operator/(float fS)
{
	C3DVector vResult;

	vResult.Set(m_fX / fS, m_fY / fS, m_fZ / fS);

	return vResult;
}