#pragma once

#ifdef MATHS_EXPORTS
#define MATHS_API __declspec(dllexport)
#else
#define MATHS_API __declspec(dllimport)
#endif

namespace Maths
{
	class MATHS_API Vec2
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
		Vec2(const float xy);
		Vec2(const float x, const float y);

		//DESTRUCTOR :

		~Vec2(void);

		//UTILS :

		float GetMagnitude();
		void Normalize();
		float DotProduct(const Vec2& _VecB);
		static float DotProduct(const Vec2& _VecA, const Vec2& _VecB);

		//ASSINGMENT AND EQUALITY OPERATIONS :

		Vec2 operator = (const Vec2& _Vec);
		Vec2 operator = (const float _Sca);

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

		Vec2 operator + (const float _Sca) const;
		Vec2 operator - (const float _Sca) const;
		Vec2 operator * (const float _Sca) const;
		Vec2 operator / (const float _Sca) const;

		//SCALER TO THIS OPERATIONS :

		Vec2 operator += (const float _Sca);
		Vec2 operator -= (const float _Sca);
		Vec2 operator *= (const float _Sca);
		Vec2 operator /= (const float _Sca);
	};

	class MATHS_API Vec3
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
		Vec3(const float xyz);
		Vec3(const float x, const float y, const float z);

		//DESTRUCTOR :

		~Vec3(void);

		//UTILS :

		float GetMagnitude();
		void Normalize();
		float DotProduct(const Vec3& _VecB);
		float DotProduct(const Vec3& _VecA, const Vec3& _VecB);
		Vec3 CrossProduct(const Vec3& _VecA, const Vec3& _VecB);

		//ASSINGMENT AND EQUALITY OPERATIONS :

		Vec3 operator = (const Vec3& _Vec);
		Vec3 operator = (const float _Sca);

		Vec3 operator - (void)              const;
		bool operator == (const Vec3& _Vec) const;
		bool operator != (const Vec3& _Vec) const;

		//Vec3 TO Vec3 OPERATIONS :

		Vec3 operator + (const Vec3& _Vec) const;
		Vec3 operator - (const Vec3& _Vec) const;
		Vec3 operator * (const Vec3& _Vec) const;
		Vec3 operator / (const Vec3& _Vec) const;

		//Vec3 TO THIS OPERATIONS :

		Vec3 operator += (const Vec3& _Vec);
		Vec3 operator -= (const Vec3& _Vec);
		Vec3 operator *= (const Vec3& _Vec);
		Vec3 operator /= (const Vec3& _Vec);

		//SCALER TO Vec3 OPERATIONS :

		Vec3 operator + (float _Sca) const;
		Vec3 operator - (float _Sca) const;
		Vec3 operator * (float _Sca) const;
		Vec3 operator / (float _Sca) const;

		//SCALER TO THIS OPERATIONS :

		Vec3 operator += (float _Sca);
		Vec3 operator -= (float _Sca);
		Vec3 operator *= (float _Sca);
		Vec3 operator /= (float _Sca);
	};

	class Vec4
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
		Vec4(const float xyzw);
		Vec4(const float x, const float y, const float z, const float w);

		//DESTRUCTOR :

		~Vec4(void);

		//UTILS :

		float GetMagnitude();
		void Normalize();
		float DotProduct(const Vec4& _VecB);
		float DotProduct(const Vec4& _VecA, const Vec4& _VecB);
		Vec4 Homogenize();

		//ASSINGMENT AND EQUALITY OPERATIONS :

		Vec4 operator = (const Vec4& _Vec);
		Vec4 operator = (const float _Sca);

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

		Vec4 operator + (const float _Sca) const;
		Vec4 operator - (const float _Sca) const;
		Vec4 operator * (const float _Sca) const;
		Vec4 operator / (const float _Sca) const;

		//SCALER TO THIS OPERATIONS :

		Vec4 operator += (const float _Sca);
		Vec4 operator -= (const float _Sca);
		Vec4 operator *= (const float _Sca);
		Vec4 operator /= (const float _Sca);
	};
}