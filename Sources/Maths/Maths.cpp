// include needed
#include <utility>
#include <limits>
#include "pch.h"
//----------------

#include <math.h>
#include <string>
#include <memory>

#define MATHS_EXPORTS
#include "Maths/Maths.hpp"

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
Maths::Vec3 Maths::Vec3::CrossProduct(const Vec3& _VecA, const Vec3& _VecB)		const
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