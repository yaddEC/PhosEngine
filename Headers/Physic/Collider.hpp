#pragma once
#include <Maths/Maths.hpp>
#include <Engine/MonoBehaviour.hpp>

#ifdef COLLIDER_EXPORTS
#define COLLIDER_API __declspec(dllexport)
#else
#define COLLIDER_API __declspec(dllimport)
#endif


namespace Wrapper
{
	class PhysicsCollider;
}



namespace Physic
{
	class Rigidbody;

	class COLLIDER_API Collider : public Engine::MonoBehaviour
	{
	public:
		bool show = false;
		bool isTrigger = false;
		bool collide = false;
		Maths::Vec3 center;
		Rigidbody* rb;
		Wrapper::PhysicsCollider* physicsCollider;
		void Init();
		void Update() override;

	};

	class BoxCollider : public Collider
	{
	public:
		BoxCollider(Maths::Vec3 _size = Maths::Vec3(1, 1, 1));
		Maths::Vec3 size;
	};

	class COLLIDER_API SphereCollider : public Collider
	{
	public:
		SphereCollider(float _radius = 1);
		float radius;
		float scaledRadius;
	};

	class COLLIDER_API CapsuleCollider : public Collider
	{
	public:
		CapsuleCollider(float _radius = 1, float _height = 1);
		float radius;
		float height;

		float scale = 0;
		float hScale = 0;
		Maths::Vec3 worldScale = Maths::Vec3(1, 1, 1);

	};
}


