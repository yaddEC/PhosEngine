#pragma once



#include "dllInclude.hpp"



namespace Maths
{
	constexpr float M_PI = 3.14159265358979323846f;
	constexpr float DEG2RAD = M_PI / 180.f;
	constexpr float RAD2DEG = 180.f / M_PI;

	template <typename T>
	void Swap(T& a, T& b)
	{
		T buffer = b;
		b = a;
		a = buffer;
	}

	template <typename T>
	T Lerp(const T& a, const T& b, float t)
	{
		return a * (1 - t) + b * t;
	}

	template <typename T>
	T Min(const T& a, const T& b)
	{
		return a < b ? a : b;
	}

	template <typename T>
	T Max(const T& a, const T& b)
	{
		return a > b ? a : b;
	}

	template <typename T>
	T Clamp(const T& value, const T& min, const T& max)
	{
		return value < min ? min : value > max ? max : value;
	}

	class PHOSENGINE_API Vec2
	{
	public:
		//MEMBERS :

		union
		{
			struct
			{
				float x, y;
			};
			float xy[2];
		};

		//CONSTRUCTORS :

		Vec2();
		Vec2(float xy);
		Vec2(float x, float y);

		//DESTRUCTOR :

		~Vec2(void);

		//UTILS :
		Vec2 GetRotated(const Vec2& origin, float angle) const;
		float GetMagnitude()											const;
		void Normalize();
		Vec2 GetNormalized()											const;
		float DotProduct(const Vec2& _VecB)								const;
		static float DotProduct(const Vec2& _VecA, const Vec2& _VecB);

		//ASSINGMENT AND EQUALITY OPERATIONS :

		Vec2 operator = (const Vec2& _Vec);
		Vec2 operator = (float _Sca);

		Vec2 operator - (void)               const;
		bool operator == (const Vec2& _Vec)  const;
		bool operator != (const Vec2& _Vec)  const;

		//Vec2 TO Vec2 OPERATIONS :

		Vec2 operator + (const Vec2& _Vec)   const;
		Vec2 operator - (const Vec2& _Vecv)  const;
		Vec2 operator * (const Vec2& _Vec)   const;
		Vec2 operator / (const Vec2& _Vec)   const;

		//Vec2 TO THIS OPERATIONS :

		Vec2 operator += (const Vec2& _Vec);
		Vec2 operator -= (const Vec2& _Vec);
		Vec2 operator *= (const Vec2& _Vec);
		Vec2 operator /= (const Vec2& _Vec);

		//SCALER TO Vec2 OPERATIONS :

		Vec2 operator + (float _Sca) const;
		Vec2 operator - (float _Sca) const;
		Vec2 operator * (float _Sca) const;
		Vec2 operator / (float _Sca) const;

		//SCALER TO THIS OPERATIONS :

		Vec2 operator += (float _Sca);
		Vec2 operator -= (float _Sca);
		Vec2 operator *= (float _Sca);
		Vec2 operator /= (float _Sca);
	};

	class PHOSENGINE_API Vec3
	{
	public:
		//MEMBERS :

		union
		{
			struct
			{
				float x, y, z;
			};
			float xyz[3];
		};

		//CONSTRUCTORS :

		Vec3(void);
		Vec3(float xyz);
		Vec3(float x, float y, float z);
		Vec3(const Vec2& _Vec2, float z);

		//DESTRUCTOR :

		~Vec3(void);

		//UTILS :

		Vec2 xy()	const;
		Vec2 xz()	const;
		Vec2 yz()	const;

		
		float GetMagnitude()											const;
		void Normalize();
		Vec3 GetNormalized()											const;
		float DotProduct(const Vec3& _VecB)								const;
		static float DotProduct(const Vec3& _VecA, const Vec3& _VecB);
		Vec3 CrossProduct(const Vec3& _VecB)							const;
		static Vec3 CrossProduct(const Vec3& _VecA, const Vec3& _VecB);

		//ASSINGMENT AND EQUALITY OPERATIONS :

		Vec3 operator = (const Vec3& _Vec);
		Vec3 operator = (float _Sca);

		Vec3 operator - (void)				const;
		bool operator == (const Vec3& _Vec)	const;
		bool operator != (const Vec3& _Vec)	const;

		//Vec3 TO Vec3 OPERATIONS :

		Vec3 operator + (const Vec3& _Vec)	const;
		Vec3 operator - (const Vec3& _Vec)	const;
		Vec3 operator * (const Vec3& _Vec)	const;
		Vec3 operator / (const Vec3& _Vec)	const;

		//Vec3 TO THIS OPERATIONS :

		Vec3 operator += (const Vec3& _Vec);
		Vec3 operator -= (const Vec3& _Vec);
		Vec3 operator *= (const Vec3& _Vec);
		Vec3 operator /= (const Vec3& _Vec);

		//SCALER TO Vec3 OPERATIONS :

		Vec3 operator + (float _Sca)	const;
		Vec3 operator - (float _Sca)	const;
		Vec3 operator * (float _Sca)	const;
		Vec3 operator / (float _Sca)	const;

		//SCALER TO THIS OPERATIONS :

		Vec3 operator += (float _Sca);
		Vec3 operator -= (float _Sca);
		Vec3 operator *= (float _Sca);
		Vec3 operator /= (float _Sca);
	};

	class PHOSENGINE_API Vec4
	{
	public:
		//MEMBERS :

		union
		{
			struct
			{
				float x, y, z, w;
			};
			float xyzw[4];
		};

		//CONSTRUCTORS :

		Vec4(void);
		Vec4(float xyzw);
		Vec4(float x, float y, float z, float w);

		//DESTRUCTOR :

		~Vec4(void);

		//UTILS :

		Vec3 xyz()	const;
		Vec3 xzw()	const;
		Vec3 xyw()	const;
		Vec3 yzw()	const;

		float GetMagnitude()											const;
		void Normalize();
		Vec4 GetNormalized()											const;
		float DotProduct(const Vec4& _VecB)								const;
		static float DotProduct(const Vec4& _VecA, const Vec4& _VecB);
		Vec4 Homogenize()												const;

		//ASSINGMENT AND EQUALITY OPERATIONS :

		Vec4 operator = (const Vec4& _Vec);
		Vec4 operator = (float _Sca);

		Vec4 operator - (void)               const;
		bool operator == (const Vec4& _Vec)  const;
		bool operator != (const Vec4& _Vec)  const;

		//Vec4 TO Vec4 OPERATIONS :

		Vec4 operator + (const Vec4& _Vec) const;
		Vec4 operator - (const Vec4& _Vec) const;
		Vec4 operator * (const Vec4& _Vec) const;
		Vec4 operator / (const Vec4& _Vec) const;

		//Vec4 TO THIS OPERATIONS :

		Vec4 operator += (const Vec4& _Vec);
		Vec4 operator -= (const Vec4& _Vec);
		Vec4 operator *= (const Vec4& _Vec);
		Vec4 operator /= (const Vec4& _Vec);

		//SCALER TO Vec4 OPERATIONS :

		Vec4 operator + (float _Sca) const;
		Vec4 operator - (float _Sca) const;
		Vec4 operator * (float _Sca) const;
		Vec4 operator / (float _Sca) const;

		//SCALER TO THIS OPERATIONS :

		Vec4 operator += (float _Sca);
		Vec4 operator -= (float _Sca);
		Vec4 operator *= (float _Sca);
		Vec4 operator /= (float _Sca);
	};

	class PHOSENGINE_API Mat3
	{
	public:
		//MEMBERS :

		union
		{
			struct
			{
				float data[9];
			};
			Vec3 data3V[3];
			float data_3_3[3][3];
		};

		//CONSTRUCTORS :

		Mat3(void);
		Mat3(float data[9]);

		//DESTRUCTOR :

		~Mat3(void);

		//UTILS :
		
		//ASSINGMENT AND EQUALITY OPERATIONS :

		Mat3 operator=(float _data[9]);
		Mat3 operator=(Mat3 _Mat);

		//Mat3 TO Mat3 OPERATIONS :

		Mat3 operator+(Mat3 _Mat) const;
		Mat3 operator-(Mat3 _Mat) const;
		Mat3 operator*(Mat3 _Mat) const;

		//Mat3 TO THIS OPERATIONS :

		Mat3 operator+=(Mat3 _Mat);
		Mat3 operator-=(Mat3 _Mat);
		Mat3 operator*=(Mat3 _Mat);

	};

	class PHOSENGINE_API Mat4
	{
	public:
		//MEMBERS :

		union
		{
			struct
			{
				float data[16];
			};
			Vec4 data4V[4];
			float data_4_4[4][4];
		};

		//CONSTRUCTORS :

		Mat4(void);
		Mat4(float _data[16]);

		//DESTRUCTOR :

		~Mat4(void);

		//UTILS :

		//Create a matrix similar to identity matrix
		static Mat4 CreateDiagonalMatrix(float value = 1);
		static Mat4 CreateDiagonalMatrix(const Vec4& _Vec);

		static Mat4 CreateTranslationMatrix(const Vec3& _Vec);
		static Mat4 CreateScaleMatrix(const Vec3& _Vec);
		static Mat4 CreateXRotationMatrix(float x);
		static Mat4 CreateYRotationMatrix(float y);
		static Mat4 CreateZRotationMatrix(float z);
		static Mat4 CreateViewMatrix(const Vec3& position, float pitch, float yaw);
		static Mat4 LookAt(const Vec3& pos, const Vec3& point, const Vec3& up);


		static Mat4 CreateTransformMatrix(const Vec3& translation, const Vec3& rotation, const Vec3& scale);


		static Mat4 CreateProjectionMatrix(float _fov, float _near, float _far, float _aspectRatio);

		Mat4 GetTranspose() const;

		//ASSINGMENT AND EQUALITY OPERATIONS :

		Mat4 operator=(float p_newData[16]);
		Mat4 operator=(Mat4 _Mat);

		//Mat4 TO Mat4 OPERATIONS :

		Mat4 operator+(Mat4 _Mat) const;
		Mat4 operator-(Mat4 _Mat) const;
		Mat4 operator*(Mat4 _Mat) const;
		Vec4 operator*(Vec4 _vec) const;
		

		//Mat4 TO THIS OPERATIONS :

		Mat4 operator+=(Mat4 _Mat);
		Mat4 operator-=(Mat4 _Mat);
		Mat4 operator*=(Mat4 _Mat);
	};

	class PHOSENGINE_API Quaternion
	{
	public:
		
		//MEMBRES
		union
		{
			struct
			{
				float a, b, c, d;
			};
			float abcd[4];
		};

		//CONSTRUCTORS :

		// _a is real part / _b, _c, _d is imaginary  part
		Quaternion(float _a = 1, float _b = 0, float _c = 0, float _d = 0);
		Quaternion(const Quaternion& copied);

		//DESTRUCTOR :

		~Quaternion();

		//UTILS :

		void Print() const;
		void Normalize();
		void Conjugate();
		float DotProduct(const Quaternion& quat2) const;
		float Lenght() const;
		Quaternion GetNormalized() const;
		Quaternion GetConjugate() const;
		Quaternion Negated() const;
		static Quaternion Slerp(Quaternion q1, Quaternion q2, float time);
		//OPERATOR

		void		operator= (const Quaternion& v);
		bool		operator==(const Quaternion& v);
		Quaternion	operator+ (const Quaternion& v);
		Quaternion	operator+=(const Quaternion& v);
		Quaternion	operator- (const Quaternion& v);
		Quaternion	operator-=(const Quaternion& v);
		Quaternion	operator* (const Quaternion& v);
		Quaternion	operator*=(const Quaternion& v);
		bool		operator!=(const Quaternion& v);
		Quaternion	operator* (const float v);
		Quaternion	operator*=(const float v);		
		Quaternion	operator/ (const float v);
		Quaternion	operator/=(const float v);

		//CONVERSION
		Mat4 ToRotationMatrix()  const;
		Vec3 ToEulerAngles()  const;
		static Mat4 CreateTransformMatrix(const Vec3& translation, const Quaternion& quaternion, const Vec3& scale);
		static Quaternion ToQuaternion(const Vec3& eulerAngle);
		static Quaternion fromAngleAxis(float angle, const Vec3& axis);
	};
}