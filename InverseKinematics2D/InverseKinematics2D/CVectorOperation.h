#pragma once
#pragma once

class C2DVector;
class C2DMatrix;
class C3DVector;

class CVectorOperation
{
public:
	CVectorOperation();
	~CVectorOperation();

	static void C2DIdentify(C2DMatrix* inM);
	static void C2DTransform(C2DVector* outV, const C2DVector* const inV, const C2DMatrix* const inM);
	static void C2DTransform(C2DMatrix* outM, const C2DMatrix* const inM1, const C2DMatrix* const inM2);
	static void C2DScalarProduct(C2DVector* outV, float fS, const C2DVector* const inV);
	static void C2DScalarProduct(C2DMatrix* outM, float fS, const C2DMatrix* const inM);
	static float C2DDotProduct(C2DVector* inV1, const C2DVector* const inV2);
	static void C2DInverse(C2DMatrix* outM, const C2DMatrix* const inM);
	static float C2DLength(const C2DVector* const inV);
	static void C2DNormalize(C2DVector* outV, const C2DVector* const inV);

	static void C3DCross(C3DVector* outV, C3DVector* inV1, C3DVector* inV2);
	static C3DVector C3DCross(C3DVector* inV1, C3DVector* inV2);
	static void C3DScalarProduct(C3DVector* outV, float fS, C3DVector* inV);
	static float C3DDotProduct(C3DVector* inV1, C3DVector* inV2);
	static float C3DLength(C3DVector* inV);
	static void C3DNormalize(C3DVector* outV, C3DVector* inV);
};

class C2DVector
{
public:
	float m_fX;
	float m_fY;

public:
	C2DVector();
	C2DVector(float, float);
	~C2DVector();

	void Set(float fX, float fY);
	void Set(const C2DVector& vector);
	float GetX() const;
	float GetY() const;
	C2DVector GetXY(void) const;

	C2DVector& operator=(const C2DVector& v);
	const C2DVector operator-(const C2DVector& v) const;
	C2DVector& operator-=(const C2DVector& v);
	const C2DVector operator+(const C2DVector& v) const;
	C2DVector& operator+=(const C2DVector& v);
	const C2DVector operator*(float fS) const;
	const C2DVector operator*(const C2DMatrix& m) const;
	C2DVector& operator*=(float fS);
	const C2DVector operator/(float fS) const;
};

class C2DMatrix
{
public:
	float m_f11, m_f12, m_f13;
	float m_f21, m_f22, m_f23;
	float m_f31, m_f32, m_f33;

public:
	C2DMatrix();
	~C2DMatrix();

	void Identify(void);
	void Set(const C2DMatrix& matrix);

	C2DMatrix& operator=(const C2DMatrix& m);
	const C2DMatrix operator*(const C2DMatrix& m) const;
	C2DMatrix& operator*=(const C2DMatrix& m);
};

class C3DVector
{
public:
	float m_fX;
	float m_fY;
	float m_fZ;

public:
	C3DVector();
	C3DVector(float, float, float);
	~C3DVector();

	void Set(float fX, float fY, float fZ);
	void Set(C3DVector& vector);
	float GetX(void);
	float GetY(void);
	float GetZ(void);
	C3DVector GetXYZ(void);

	C3DVector& operator=(C3DVector& v);
	const C3DVector operator-(C3DVector& v);
	C3DVector& operator-=(C3DVector& v);
	const C3DVector operator+(C3DVector& v);
	C3DVector& operator+=(C3DVector& v);
	const C3DVector operator*(float fS);
	//C3DVector operator*(C3DMatrix& m);
	C3DVector& operator*=(float fS);
	const C3DVector operator/(float fS);
};