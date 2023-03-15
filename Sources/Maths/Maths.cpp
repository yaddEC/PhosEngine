// include needed
#include <utility>
#include <limits>
#include "pch.h"
//----------------

#include <math.h>

#define MATHS_EXPORTS
#include "Maths/Maths.hpp"

template <typename T>
void Maths::Swap(T& a, T& b)
{
	T buffer = b;
	b = a;
	a = buffer;
}

/************************\
 *-------VECTOR_2-------*
\************************/
#pragma region Vec2
//CONSTRUCTORS :

Maths::Vec2::Vec2(void) : x(0), y(0) {}
Maths::Vec2::Vec2(float xy) : x(xy), y(xy) {}
Maths::Vec2::Vec2(float x, float y) : x(x), y(y) {}

//DESTRUCTOR :

Maths::Vec2::~Vec2(void) {}

//UTILS :

Maths::Vec2 Maths::Vec2::GetRotated(const Maths::Vec2& origin, float angle) const
{
	Vec2 op = *this - origin;
	Vec2 opP;
	opP.x = cos(angle) * op.x - sin(angle) * op.y;
	opP.y = sin(angle) * op.x + cos(angle) * op.y;
	return opP + origin;
}

float Maths::Vec2::GetMagnitude()												const
{
	return sqrtf((x * x) + (y * y));
}
void Maths::Vec2::Normalize()
{
	if (float i = GetMagnitude() != 0)
	{
		operator/=(i);	
	}
}
Maths::Vec2 Maths::Vec2::GetNormalized()										const
{
	if (float i = GetMagnitude() != 0)
	{
		return operator/(i);
	}
	return *this;
}
float Maths::Vec2::DotProduct(const Vec2& _VecB)								const
{
	return (float)(x * _VecB.x + y * _VecB.y);
}
float Maths::Vec2::DotProduct(const Vec2& _VecA, const Vec2& _VecB)
{
	return (float)(_VecA.x * _VecB.x + _VecA.y * _VecB.y);
}

//ASSINGMENT AND EQUALITY OPERATIONS :

Maths::Vec2 Maths::Vec2::operator = (const Vec2& _Vec)
{
	x = _Vec.x;
	y = _Vec.y;
	return *this;
}
Maths::Vec2 Maths::Vec2::operator = (float _Sca)
{
	x = _Sca;
	y = _Sca;
	return *this;
}

Maths::Vec2 Maths::Vec2::operator - (void)			const
{
	return (Vec2)(-x, -y);
}
bool Maths::Vec2::operator == (const Vec2& _Vec)	const
{
	return (x == _Vec.x) && (y == _Vec.y);
}
bool Maths::Vec2::operator != (const Vec2& _Vec)	const
{
	return (x != _Vec.x) || (y != _Vec.y);
}

//Vec2 TO Vec2 OPERATIONS :

Maths::Vec2 Maths::Vec2::operator + (const Vec2& _Vec)	const
{
	return Vec2(x + _Vec.x, y + _Vec.y);
}
Maths::Vec2 Maths::Vec2::operator - (const Vec2& _Vec)	const
{
	return Vec2(x - _Vec.x, y - _Vec.y);
}
Maths::Vec2 Maths::Vec2::operator * (const Vec2& _Vec)	const
{
	return Vec2(x * _Vec.x, y * _Vec.y);
}
Maths::Vec2 Maths::Vec2::operator / (const Vec2& _Vec)	const
{
	return Vec2(x / _Vec.x, y / _Vec.y);
}

//Vec2 TO THIS OPERATIONS :

Maths::Vec2 Maths::Vec2::operator += (const Vec2& _Vec)
{
	x += _Vec.x;
	y += _Vec.y;
	return *this;
}
Maths::Vec2 Maths::Vec2::operator -= (const Vec2& _Vec)
{
	x -= _Vec.x;
	y -= _Vec.y;
	return *this;
}
Maths::Vec2 Maths::Vec2::operator *= (const Vec2& _Vec)
{
	x *= _Vec.x;
	y *= _Vec.y;
	return *this;
}
Maths::Vec2 Maths::Vec2::operator /= (const Vec2& _Vec)
{
	x /= _Vec.x;
	y /= _Vec.y;
	return *this;
}

//SCALER TO Vec2 OPERATIONS :

Maths::Vec2 Maths::Vec2::operator + (float _Sca)	const
{
	return Vec2(x + _Sca, y + _Sca);
}
Maths::Vec2 Maths::Vec2::operator - (float _Sca)	const
{
	return Vec2(x - _Sca, y - _Sca);
}
Maths::Vec2 Maths::Vec2::operator * (float _Sca)	const
{
	return Vec2(x * _Sca, y * _Sca);
}
Maths::Vec2 Maths::Vec2::operator / (float _Sca)	const
{
	return Vec2(x / _Sca, y / _Sca);
}

//SCALER TO THIS OPERATIONS :

Maths::Vec2 Maths::Vec2::operator += (float _Sca)
{
	x += _Sca;
	y += _Sca;
	return *this;
}
Maths::Vec2 Maths::Vec2::operator -= (float _Sca)
{
	x -= _Sca;
	y -= _Sca;
	return *this;
}
Maths::Vec2 Maths::Vec2::operator *= (float _Sca)
{
	x *= _Sca;
	y *= _Sca;
	return *this;
}
Maths::Vec2 Maths::Vec2::operator /= (float _Sca)
{
	x /= _Sca;
	y /= _Sca;
	return *this;
}
#pragma endregion Vec2

/************************\
 *-------VECTOR_3-------*
\************************/
#pragma region Vec3
//CONSTRUCTORS :

Maths::Vec3::Vec3(void) : x(0), y(0), z(0) {}
Maths::Vec3::Vec3(float xyz) : x(xyz), y(xyz), z(xyz) {}
Maths::Vec3::Vec3(float x, float y, float z) : x(x), y(y), z(z) {}
Maths::Vec3::Vec3(const Vec2& _Vec2, float z) : x(_Vec2.x), y(_Vec2.y), z(z) {}

//DESTRUCTOR :

Maths::Vec3::~Vec3(void) {}

//UTILS :

Maths::Vec2 Maths::Vec3::xy()	const
{
	return Vec2(x, y);
}
Maths::Vec2 Maths::Vec3::xz()	const
{
	return Vec2(x, z);
}
Maths::Vec2 Maths::Vec3::yz()	const
{
	return Vec2(y, z);
}



float Maths::Vec3::GetMagnitude()												const
{
	return sqrtf((x * x) + (y * y) + (z * z));
}
void Maths::Vec3::Normalize()
{
	if (float i = GetMagnitude() != 0)
	{
		operator/=(i);
	}
}
Maths::Vec3 Maths::Vec3::GetNormalized()										const
{
	if (float i = GetMagnitude() != 0)
	{
		return operator/(i);
	}
	return *this;
}
float Maths::Vec3::DotProduct(const Vec3& _VecB)								const
{
	return (float)(x * _VecB.x + y * _VecB.y + z * _VecB.z);
}
float Maths::Vec3::DotProduct(const Vec3& _VecA, const Vec3& _VecB)
{
	return (float)(_VecA.x * _VecB.x + _VecA.y * _VecB.y + _VecA.z * _VecB.z);
}
Maths::Vec3 Maths::Vec3::CrossProduct(const Vec3& _VecB)		const
{
	return { y * _VecB.z - z * _VecB.y, z * _VecB.x - x * _VecB.z, x * _VecB.y - y * _VecB.x };
}
Maths::Vec3 Maths::Vec3::CrossProduct(const Vec3& _VecA, const Vec3& _VecB)
{
	return { _VecA.y * _VecB.z - _VecA.z * _VecB.y, _VecA.z * _VecB.x - _VecA.x * _VecB.z, _VecA.x * _VecB.y - _VecA.y * _VecB.x };
}
//ASSINGMENT AND EQUALITY OPERATIONS :

Maths::Vec3 Maths::Vec3::operator = (const Vec3& _Vec)
{
	x = _Vec.x;
	y = _Vec.y;
	z = _Vec.z;
	return *this;
}
Maths::Vec3 Maths::Vec3::operator = (float _Sca)
{
	x = _Sca;
	y = _Sca;
	z = _Sca;
	return *this;
}

Maths::Vec3 Maths::Vec3::operator - (void)			const
{
	return (Vec3)(-x, -y, -z);
}
bool Maths::Vec3::operator == (const Vec3& _Vec)	const
{
	return (x == _Vec.x) && (y == _Vec.y) && (z == _Vec.z);
}
bool Maths::Vec3::operator != (const Vec3& _Vec)	const
{
	return (x != _Vec.x) || (y != _Vec.y) || (z != _Vec.z);
}

//Vec3 TO Vec3 OPERATIONS :

Maths::Vec3 Maths::Vec3::operator + (const Vec3& _Vec)	const
{
	return Vec3(x + _Vec.x, y + _Vec.y, z + _Vec.z);
}
Maths::Vec3 Maths::Vec3::operator - (const Vec3& _Vec)	const
{
	return Vec3(x - _Vec.x, y - _Vec.y, z - _Vec.z);
}
Maths::Vec3 Maths::Vec3::operator * (const Vec3& _Vec)	const
{
	return Vec3(x * _Vec.x, y * _Vec.y, z * _Vec.z);
}
Maths::Vec3 Maths::Vec3::operator / (const Vec3& _Vec)	const
{
	return Vec3(x / _Vec.x, y / _Vec.y, z / _Vec.z);
}

//Vec3 TO THIS OPERATIONS :

Maths::Vec3 Maths::Vec3::operator += (const Vec3& _Vec)
{
	x += _Vec.x;
	y += _Vec.y;
	z += _Vec.z;
	return *this;
}
Maths::Vec3 Maths::Vec3::operator -= (const Vec3& _Vec)
{
	x -= _Vec.x;
	y -= _Vec.y;
	z -= _Vec.z;
	return *this;
}
Maths::Vec3 Maths::Vec3::operator *= (const Vec3& _Vec)
{
	x *= _Vec.x;
	y *= _Vec.y;
	z *= _Vec.z;
	return *this;
}
Maths::Vec3 Maths::Vec3::operator /= (const Vec3& _Vec)
{
	x /= _Vec.x;
	y /= _Vec.y;
	z /= _Vec.z;
	return *this;
}

//SCALER TO Vec3 OPERATIONS :

Maths::Vec3 Maths::Vec3::operator + (float _Sca)	const
{
	return Vec3(x + _Sca, y + _Sca, z + _Sca);
}
Maths::Vec3 Maths::Vec3::operator - (float _Sca)	const
{
	return Vec3(x - _Sca, y - _Sca, z - _Sca);
}
Maths::Vec3 Maths::Vec3::operator * (float _Sca)	const
{
	return Vec3(x * _Sca, y * _Sca, z * _Sca);
}
Maths::Vec3 Maths::Vec3::operator / (float _Sca)	const
{
	return Vec3(x / _Sca, y / _Sca, z / _Sca);
}

//SCALER TO THIS OPERATIONS :

Maths::Vec3 Maths::Vec3::operator += (float _Sca)
{
	x += _Sca;
	y += _Sca;
	z += _Sca;
	return *this;
}
Maths::Vec3 Maths::Vec3::operator -= (float _Sca)
{
	x -= _Sca;
	y -= _Sca;
	z -= _Sca;
	return *this;
}
Maths::Vec3 Maths::Vec3::operator *= (float _Sca)
{
	x *= _Sca;
	y *= _Sca;
	z *= _Sca;
	return *this;
}
Maths::Vec3 Maths::Vec3::operator /= (float _Sca)
{
	x /= _Sca;
	y /= _Sca;
	z /= _Sca;
	return *this;
}

#pragma endregion Vec3

/************************\
 *-------VECTOR_4-------*
\************************/
#pragma region Vec4
//CONSTRUCTORS :

Maths::Vec4::Vec4(void) : x(0), y(0), z(0), w(0) {}
Maths::Vec4::Vec4(float xyzw) : x(xyzw), y(xyzw), z(xyzw), w(xyzw) {}
Maths::Vec4::Vec4(float x, float y, float z, float w) : x(x), y(y), z(z), w(w) {}

//DESTRUCTOR :

Maths::Vec4::~Vec4(void) { }

//UTILS :

Maths::Vec3 Maths::Vec4::xyz()	const
{
	return Vec3(x, y, z);
}
Maths::Vec3 Maths::Vec4::xzw()	const
{
	return Vec3(x, z, w);
}
Maths::Vec3 Maths::Vec4::xyw()	const
{
	return Vec3(x, y, w);
}
Maths::Vec3 Maths::Vec4::yzw()	const
{
	return Vec3(y, z, w);
}

float Maths::Vec4::GetMagnitude()												const
{
	return sqrtf((x * x) + (y * y) + (z * z) + (w * w));
}
void Maths::Vec4::Normalize()
{
	if (float i = GetMagnitude() != 0)
	{
		operator/=(i);
	}
}
Maths::Vec4 Maths::Vec4::GetNormalized()										const
{
	if (float i = GetMagnitude() != 0)
	{
		return operator/(i);
	}
	return *this;
}
float Maths::Vec4::DotProduct(const Vec4& _VecB)								const
{
	return (float)(x * _VecB.x + y * _VecB.y + z * _VecB.z + w * _VecB.w);
}
float Maths::Vec4::DotProduct(const Vec4& _VecA, const Vec4& _VecB)
{
	return (float)(_VecA.x * _VecB.x + _VecA.y * _VecB.y + _VecA.z * _VecB.z + _VecA.w * _VecB.w);
}
Maths::Vec4 Maths::Vec4::Homogenize()											const
{
	return { x / w, y / w, z / w, 1 };
}

//ASSINGMENT AND EQUALITY OPERATIONS :

Maths::Vec4 Maths::Vec4::operator = (const Vec4& _Vec)
{
	x = _Vec.x;
	y = _Vec.y;
	z = _Vec.z;
	w = _Vec.w;
	return *this;
}
Maths::Vec4 Maths::Vec4::operator = (float _Sca)
{
	x = _Sca;
	y = _Sca;
	z = _Sca;
	w = _Sca;
	return *this;
}

Maths::Vec4 Maths::Vec4::operator - (void)		const
{
	return (Vec4)(-x, -y, -z, -w);
}
bool Maths::Vec4::operator == (const Vec4& _Vec)	const
{
	return (x == _Vec.x) && (y == _Vec.y) && (z == _Vec.z) && (w == _Vec.w);
}
bool Maths::Vec4::operator != (const Vec4& _Vec)	const
{
	return (x != _Vec.x) || (y != _Vec.y) || (z != _Vec.z) || (w != _Vec.w);
}

//Vec4 TO Vec4 OPERATIONS :

Maths::Vec4 Maths::Vec4::operator + (const Vec4& _Vec) const
{
	return Vec4(x + _Vec.x, y + _Vec.y, z + _Vec.z, w + _Vec.w);
}
Maths::Vec4 Maths::Vec4::operator - (const Vec4& _Vec) const
{
	return Vec4(x - _Vec.x, y - _Vec.y, z - _Vec.z, w - _Vec.w);
}
Maths::Vec4 Maths::Vec4::operator * (const Vec4& _Vec) const
{
	return Vec4(x * _Vec.x, y * _Vec.y, z * _Vec.z, w * _Vec.w);
}
Maths::Vec4 Maths::Vec4::operator / (const Vec4& _Vec) const
{
	return Vec4(x / _Vec.x, y / _Vec.y, z / _Vec.z, w / _Vec.w);
}

//Vec4 TO THIS OPERATIONS :

Maths::Vec4 Maths::Vec4::operator += (const Vec4& _Vec)
{
	x += _Vec.x;
	y += _Vec.y;
	z += _Vec.z;
	w += _Vec.w;
	return *this;
}
Maths::Vec4 Maths::Vec4::operator -= (const Vec4& _Vec)
{
	x -= _Vec.x;
	y -= _Vec.y;
	z -= _Vec.z;
	w -= _Vec.w;
	return *this;
}
Maths::Vec4 Maths::Vec4::operator *= (const Vec4& _Vec)
{
	x *= _Vec.x;
	y *= _Vec.y;
	z *= _Vec.z;
	w *= _Vec.w;
	return *this;
}
Maths::Vec4 Maths::Vec4::operator /= (const Vec4& _Vec)
{
	x /= _Vec.x;
	y /= _Vec.y;
	z /= _Vec.z;
	w /= _Vec.w;
	return *this;
}

//SCALER TO Vec4 OPERATIONS :

Maths::Vec4 Maths::Vec4::operator + (float _Sca) const
{
	return Vec4(x + _Sca, y + _Sca, z + _Sca, w + _Sca);
}
Maths::Vec4 Maths::Vec4::operator - (float _Sca) const
{
	return Vec4(x - _Sca, y - _Sca, z - _Sca, w - _Sca);
}
Maths::Vec4 Maths::Vec4::operator * (float _Sca) const
{
	return Vec4(x * _Sca, y * _Sca, z * _Sca, w * _Sca);
}
Maths::Vec4 Maths::Vec4::operator / (float _Sca) const
{
	return Vec4(x / _Sca, y / _Sca, z / _Sca, w / _Sca);
}

//SCALER TO THIS OPERATIONS :

Maths::Vec4 Maths::Vec4::operator += (float _Sca)
{
	x += _Sca;
	y += _Sca;
	z += _Sca;
	w += _Sca;
	return *this;
}
Maths::Vec4 Maths::Vec4::operator -= (float _Sca)
{
	x -= _Sca;
	y -= _Sca;
	z -= _Sca;
	w -= _Sca;
	return *this;
}
Maths::Vec4 Maths::Vec4::operator *= (float _Sca)
{
	x *= _Sca;
	y *= _Sca;
	z *= _Sca;
	w *= _Sca;
	return *this;
}
Maths::Vec4 Maths::Vec4::operator /= (float _Sca)
{
	x /= _Sca;
	y /= _Sca;
	z /= _Sca;
	w /= _Sca;
	return *this;
}
#pragma endregion Vec4

/************************\
 *-------MATRIX_3-------*
\************************/
#pragma region Mat3
//CONSTRUCTORS :

Maths::Mat3::Mat3(void)
{
	for (int i = 0; i < 9; i++)
	{
		data[i] = 0;
	}
}
Maths::Mat3::Mat3(float _data[9])
{
	for (int i = 0; i < 9; i++)
	{
		data[i] = _data[i];
	}
}

//DESTRUCTOR :

Maths::Mat3::~Mat3(void) {}

//UTILS :

//ASSINGMENT AND EQUALITY OPERATIONS :

Maths::Mat3 Maths::Mat3::operator=(float _data[9])
{
	for (int i = 0; i < 9; i++)
	{
		data[i] = _data[i];
	}
	return *this;
}
Maths::Mat3 Maths::Mat3::operator=(Mat3 _Mat)
{
	for (int i = 0; i < 9; i++)
	{
		data[i] = _Mat.data[i];
	}
	return *this;
}

//Mat3 TO Mat3 OPERATIONS :

Maths::Mat3 Maths::Mat3::operator+(Mat3 _Mat) const
{
	Mat3 temp;
	for (int i = 0; i < 9; i++)
	{
		temp.data[i] = data[i] + _Mat.data[i];
	}
	return temp;
}
Maths::Mat3 Maths::Mat3::operator-(Mat3 _Mat) const
{
	Mat3 temp;
	for (int i = 0; i < 9; i++)
	{
		temp.data[i] = data[i] - _Mat.data[i];
	}
	return temp;
}
Maths::Mat3 Maths::Mat3::operator*(Mat3 _Mat) const
{
	Mat3 temp;

	temp.data[0] = data[0] * _Mat.data[0] + data[1] * _Mat.data[3] + data[2] * _Mat.data[6];
	temp.data[1] = data[0] * _Mat.data[1] + data[1] * _Mat.data[4] + data[2] * _Mat.data[7];
	temp.data[2] = data[0] * _Mat.data[2] + data[1] * _Mat.data[5] + data[2] * _Mat.data[8];

	temp.data[3] = data[3] * _Mat.data[0] + data[4] * _Mat.data[3] + data[5] * _Mat.data[6];
	temp.data[4] = data[3] * _Mat.data[1] + data[4] * _Mat.data[4] + data[5] * _Mat.data[7];
	temp.data[5] = data[3] * _Mat.data[2] + data[4] * _Mat.data[5] + data[5] * _Mat.data[8];

	temp.data[6] = data[6] * _Mat.data[0] + data[7] * _Mat.data[3] + data[8] * _Mat.data[6];
	temp.data[7] = data[6] * _Mat.data[1] + data[7] * _Mat.data[4] + data[8] * _Mat.data[7];
	temp.data[8] = data[6] * _Mat.data[2] + data[7] * _Mat.data[5] + data[8] * _Mat.data[8];

	return temp;
}

//Mat3 TO THIS OPERATIONS :

Maths::Mat3 Maths::Mat3::operator+=(Mat3 _Mat)
{
	for (int i = 0; i < 9; i++)
	{
		data[i] += _Mat.data[i];
	}
	return *this;
}
Maths::Mat3 Maths::Mat3::operator-=(Mat3 _Mat)
{
	for (int i = 0; i < 9; i++)
	{
		data[i] -= _Mat.data[i];
	}
	return *this;
}
Maths::Mat3 Maths::Mat3::operator*=(Mat3 _Mat)
{
	Mat3 temp;
	
	temp.data[0] = data[0] * _Mat.data[0] + data[1] * _Mat.data[3] + data[2] * _Mat.data[6];
	temp.data[1] = data[0] * _Mat.data[1] + data[1] * _Mat.data[4] + data[2] * _Mat.data[7];
	temp.data[2] = data[0] * _Mat.data[2] + data[1] * _Mat.data[5] + data[2] * _Mat.data[8];
	
	temp.data[3] = data[3] * _Mat.data[0] + data[4] * _Mat.data[3] + data[5] * _Mat.data[6];
	temp.data[4] = data[3] * _Mat.data[1] + data[4] * _Mat.data[4] + data[5] * _Mat.data[7];
	temp.data[5] = data[3] * _Mat.data[2] + data[4] * _Mat.data[5] + data[5] * _Mat.data[8];
	
	temp.data[6] = data[6] * _Mat.data[0] + data[7] * _Mat.data[3] + data[8] * _Mat.data[6];
	temp.data[7] = data[6] * _Mat.data[1] + data[7] * _Mat.data[4] + data[8] * _Mat.data[7];
	temp.data[8] = data[6] * _Mat.data[2] + data[7] * _Mat.data[5] + data[8] * _Mat.data[8];

	*this = temp;
	return *this;
}
#pragma endregion Mat3

/************************\
 *-------MATRIX_4-------*
\************************/
#pragma region Mat4
//CONSTRUCTORS :

Maths::Mat4::Mat4(void)
{
	for (int i = 0; i < 16; i++)
	{
		data[i] = 0;
	}
}
Maths::Mat4::Mat4(float _data[16])
{
	for (int i = 0; i < 16; i++)
	{
		data[i] = _data[i];
	}
}

//DESTRUCTOR :

Maths::Mat4::~Mat4(void) {}

//UTILS :

Maths::Mat4 Maths::Mat4::CreateDiagonalMatrix(float value)
{
	Mat4 temp;
	temp.data[0] = value;
	temp.data[5] = value;
	temp.data[10] = value;
	temp.data[15] = value;
	return temp;
}
Maths::Mat4 Maths::Mat4::CreateDiagonalMatrix(const Vec4& _Vec)
{
	Mat4 temp;
	temp.data[0] = _Vec.x;
	temp.data[5] = _Vec.y;
	temp.data[10] = _Vec.z;
	temp.data[15] = _Vec.w;
	return temp;
}

Maths::Mat4 Maths::Mat4::CreateTranslationMatrix(const Vec3& _Vec)
{
	Mat4 temp;

	temp.data[0] = 1;
	temp.data[5] = 1;
	temp.data[10] = 1;
	temp.data[15] = 1;

	temp.data[3] = _Vec.x;
	temp.data[7] = _Vec.y;
	temp.data[11] = _Vec.z;

	return temp;
}
Maths::Mat4 Maths::Mat4::CreateScaleMatrix(const Vec3& _Vec)
{
	Mat4 temp;

	temp.data[0] = _Vec.x;
	temp.data[5] = _Vec.y;
	temp.data[10] = _Vec.z;
	temp.data[15] = 1;

	return temp;
}
Maths::Mat4 Maths::Mat4::CreateXRotationMatrix(float x)
{
	float rotationXData[16] =
	{
		1,		0,			0,			0,
		0,		cosf(x),	-sinf(x),	0,
		0,		sinf(x),	cosf(x),	0,
		0,		0,			0,			1
	};
	return Mat4(rotationXData);
}
Maths::Mat4 Maths::Mat4::CreateYRotationMatrix(float y)
{
	float rotationYData[16] =
	{
		cosf(y),	0,		sinf(y),	0,
		0,			1,		0,			0,
		-sinf(y),	0,		cosf(y),	0,
		0,			0,		0,			1
	};
	return Mat4(rotationYData);
}
Maths::Mat4 Maths::Mat4::CreateZRotationMatrix(float z)
{
	float rotationZData[16] =
	{
		cosf(z),	-sinf(z),	0,		0,
		sinf(z),	cosf(z),	0,		0,
		0,			0,			1,		0,
		0,			0,			0,		1
	};
	return Mat4(rotationZData);
}

Maths::Mat4 Maths::Mat4::CreateViewMatrix(const Vec3& position, float pitch, float yaw)
{
	float p = pitch * Maths::M_PI / 180.f;
	float y = yaw * Maths::M_PI / 180.f;
	float cosPitch = cos(p);
	float sinPitch = sin(p);
	float cosYaw = cos(y);
	float sinYaw = sin(y);

	Vec3 xaxis = { cosYaw, 0, -sinYaw };
	Vec3 yaxis = { sinYaw * sinPitch, cosPitch, cosYaw * sinPitch };
	Vec3 zaxis = { sinYaw * cosPitch, -sinPitch, cosPitch * cosYaw };


	float view[16] = {
		xaxis.x, xaxis.y, xaxis.z, -(Maths::Vec3::DotProduct(xaxis, position)),
		yaxis.x, yaxis.y, yaxis.z, -(Maths::Vec3::DotProduct(yaxis, position)),
		zaxis.x, zaxis.y, zaxis.z, -(Maths::Vec3::DotProduct(zaxis, position)),
		0, 0, 0, 1 };

	return Mat4{ view };
}

Maths::Mat4 Maths::Mat4::CreateTransformMatrix(const Vec3& translation, const Vec3& rotation, const Vec3& scale)
{
	return CreateTranslationMatrix(translation) * CreateXRotationMatrix(rotation.x) * CreateYRotationMatrix(rotation.y) * CreateZRotationMatrix(rotation.z) * CreateScaleMatrix(scale);
}

Maths::Mat4 Maths::Mat4::CreateProjectionMatrix(float _fov, float _near, float _far, float _aspectRatio)
{
	float view = tanf((_fov * 0.5f) * (float)DEG2RAD);

	float projectionData[16] =
	{
		(1 / view * (_aspectRatio)),	0,		    0,			0,
		0,						1 / view,		0,			0,
		0,						0,				(_far / (_far - _near)), -((_far * _near) / (_far - _near)),
		0,						0,				1,			0
	};
	return Mat4(projectionData);
}

//ASSINGMENT AND EQUALITY OPERATIONS :

Maths::Mat4 Maths::Mat4::operator=(float _data[16])
{
	for (int i = 0; i < 16; i++)
	{
		data[i] = _data[i];
	}
	return *this;
}
Maths::Mat4 Maths::Mat4::operator=(Mat4 _Mat)
{
	for (int i = 0; i < 16; i++)
	{
		data[i] = _Mat.data[i];
	}
	return *this;
}

//Mat4 TO Mat4 OPERATIONS :

Maths::Mat4 Maths::Mat4::operator+(Mat4 _Mat) const
{
	Mat4 temp;
	for (int i = 0; i < 16; i++)
	{
		temp.data[i] = data[i] + _Mat.data[i];
	}
	return temp;
}
Maths::Mat4 Maths::Mat4::operator-(Mat4 _Mat) const
{
	Mat4 temp;
	for (int i = 0; i < 16; i++)
	{
		temp.data[i] = data[i] - _Mat.data[i];
	}
	return temp;
}
Maths::Mat4 Maths::Mat4::operator*(Mat4 _Mat) const
{
	Mat4 temp;
	
	/*temp.data[0] = data[0] * _Mat.data[0] + data[1] * _Mat.data[4] + data[2] * _Mat.data[8] + data[3] * _Mat.data[12];
	temp.data[1] = data[0] * _Mat.data[1] + data[1] * _Mat.data[5] + data[2] * _Mat.data[9] + data[3] * _Mat.data[13];
	temp.data[2] = data[0] * _Mat.data[2] + data[1] * _Mat.data[6] + data[2] * _Mat.data[10] + data[3] * _Mat.data[14];
	temp.data[3] = data[0] * _Mat.data[3] + data[1] * _Mat.data[7] + data[2] * _Mat.data[11] + data[3] * _Mat.data[15];

	temp.data[4] = data[4] * _Mat.data[0] + data[5] * _Mat.data[4] + data[6] * _Mat.data[8] + data[7] * _Mat.data[12];
	temp.data[5] = data[4] * _Mat.data[1] + data[5] * _Mat.data[5] + data[6] * _Mat.data[9] + data[7] * _Mat.data[13];
	temp.data[6] = data[4] * _Mat.data[2] + data[5] * _Mat.data[6] + data[6] * _Mat.data[10] + data[7] * _Mat.data[14];
	temp.data[7] = data[4] * _Mat.data[3] + data[5] * _Mat.data[7] + data[6] * _Mat.data[11] + data[7] * _Mat.data[15];

	temp.data[8] = data[8] * _Mat.data[0] + data[9] * _Mat.data[4] + data[10] * _Mat.data[8] + data[11] * _Mat.data[12];
	temp.data[9] = data[8] * _Mat.data[1] + data[9] * _Mat.data[5] + data[10] * _Mat.data[9] + data[11] * _Mat.data[13];
	temp.data[10] = data[8] * _Mat.data[2] + data[9] * _Mat.data[6] + data[10] * _Mat.data[10] + data[11] * _Mat.data[14];
	temp.data[11] = data[8] * _Mat.data[3] + data[9] * _Mat.data[7] + data[10] * _Mat.data[11] + data[11] * _Mat.data[15];

	temp.data[12] = data[12] * _Mat.data[0] + data[13] * _Mat.data[4] + data[14] * _Mat.data[8] + data[15] * _Mat.data[12];
	temp.data[13] = data[12] * _Mat.data[1] + data[13] * _Mat.data[5] + data[14] * _Mat.data[9] + data[15] * _Mat.data[13];
	temp.data[14] = data[12] * _Mat.data[2] + data[13] * _Mat.data[6] + data[14] * _Mat.data[10] + data[15] * _Mat.data[14];
	temp.data[15] = data[12] * _Mat.data[3] + data[13] * _Mat.data[7] + data[14] * _Mat.data[11] + data[15] * _Mat.data[15];*/
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			temp.data_4_4[i][j] = data_4_4[0][j] * _Mat.data_4_4[i][0] + data_4_4[1][j] * _Mat.data_4_4[i][1] + data_4_4[2][j] * _Mat.data_4_4[i][2] + data_4_4[3][j] * _Mat.data_4_4[i][3];
		}
	}

	return temp;
}

//Mat4 TO THIS OPERATIONS :

Maths::Mat4 Maths::Mat4::operator+=(Mat4 _Mat)
{
	for (int i = 0; i < 16; i++)
	{
		data[i] += _Mat.data[i];
	}
	return *this;
}
Maths::Mat4 Maths::Mat4::operator-=(Mat4 _Mat)
{
	for (int i = 0; i < 16; i++)
	{
		data[i] -= _Mat.data[i];
	}
	return *this;
}
Maths::Mat4 Maths::Mat4::operator*=(Mat4 _Mat)
{
	Mat4 temp;
	
	temp.data[0] = data[0] * _Mat.data[0] + data[1] * _Mat.data[4] + data[2] * _Mat.data[8] + data[3] * _Mat.data[12];
	temp.data[1] = data[0] * _Mat.data[1] + data[1] * _Mat.data[5] + data[2] * _Mat.data[9] + data[3] * _Mat.data[13];
	temp.data[2] = data[0] * _Mat.data[2] + data[1] * _Mat.data[6] + data[2] * _Mat.data[10] + data[3] * _Mat.data[14];
	temp.data[3] = data[0] * _Mat.data[3] + data[1] * _Mat.data[7] + data[2] * _Mat.data[11] + data[3] * _Mat.data[15];

	temp.data[4] = data[4] * _Mat.data[0] + data[5] * _Mat.data[4] + data[6] * _Mat.data[8] + data[7] * _Mat.data[12];
	temp.data[5] = data[4] * _Mat.data[1] + data[5] * _Mat.data[5] + data[6] * _Mat.data[9] + data[7] * _Mat.data[13];
	temp.data[6] = data[4] * _Mat.data[2] + data[5] * _Mat.data[6] + data[6] * _Mat.data[10] + data[7] * _Mat.data[14];
	temp.data[7] = data[4] * _Mat.data[3] + data[5] * _Mat.data[7] + data[6] * _Mat.data[11] + data[7] * _Mat.data[15];

	temp.data[8] = data[8] * _Mat.data[0] + data[9] * _Mat.data[4] + data[10] * _Mat.data[8] + data[11] * _Mat.data[12];
	temp.data[9] = data[8] * _Mat.data[1] + data[9] * _Mat.data[5] + data[10] * _Mat.data[9] + data[11] * _Mat.data[13];
	temp.data[10] = data[8] * _Mat.data[2] + data[9] * _Mat.data[6] + data[10] * _Mat.data[10] + data[11] * _Mat.data[14];
	temp.data[11] = data[8] * _Mat.data[3] + data[9] * _Mat.data[7] + data[10] * _Mat.data[11] + data[11] * _Mat.data[15];

	temp.data[12] = data[12] * _Mat.data[0] + data[13] * _Mat.data[4] + data[14] * _Mat.data[8] + data[15] * _Mat.data[12];
	temp.data[13] = data[12] * _Mat.data[1] + data[13] * _Mat.data[5] + data[14] * _Mat.data[9] + data[15] * _Mat.data[13];
	temp.data[14] = data[12] * _Mat.data[2] + data[13] * _Mat.data[6] + data[14] * _Mat.data[10] + data[15] * _Mat.data[14];
	temp.data[15] = data[12] * _Mat.data[3] + data[13] * _Mat.data[7] + data[14] * _Mat.data[11] + data[15] * _Mat.data[15];

	*this = temp;
	return *this;
}

#pragma endregion Mat4