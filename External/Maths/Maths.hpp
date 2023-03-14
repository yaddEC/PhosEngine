#pragma once

#ifdef MATHS_EXPORTS
#define MATHS_API __declspec(dllexport)
#else
#define MATHS_API __declspec(dllimport)
#endif



namespace Maths
{
	constexpr float M_PI = 3.14159265358979323846f;
	constexpr float DEG2RAD = M_PI / 180;

	template <typename T>
	void Swap(T& a, T& b);

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
		Vec2(float xy);
		Vec2(float x, float y);

		//DESTRUCTOR :

		~Vec2(void);

		//UTILS :

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

	class MATHS_API Vec4
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

	class MATHS_API Mat3
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

	class MATHS_API Mat4
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

		static Mat4 CreateTransformMatrix(const Vec3& translation, const Vec3& rotation, const Vec3& scale);

		static Mat4 CreateProjectionMatrix(float _fov, float _near, float _far, float _aspectRatio);

		//ASSINGMENT AND EQUALITY OPERATIONS :

		Mat4 operator=(float p_newData[16]);
		Mat4 operator=(Mat4 _Mat);

		//Mat4 TO Mat4 OPERATIONS :

		Mat4 operator+(Mat4 _Mat) const;
		Mat4 operator-(Mat4 _Mat) const;
		Mat4 operator*(Mat4 _Mat) const;

		//Mat4 TO THIS OPERATIONS :

		Mat4 operator+=(Mat4 _Mat);
		Mat4 operator-=(Mat4 _Mat);
		Mat4 operator*=(Mat4 _Mat);
	};

}