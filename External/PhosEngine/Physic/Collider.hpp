#pragma once
#include <Maths/Maths.hpp>
#include <Engine/MonoBehaviour.hpp>

#include "dllInclude.hpp"


namespace Wrapper
{
	class PhysicsCollider;
	enum MaterialType;
}



namespace Physic
{
	class Rigidbody;

	class PHOSENGINE_API Collider : public Engine::MonoBehaviour
	{
	public:
		Collider();
		bool isTrigger = false;
		Maths::Vec3 center;
		Rigidbody* rb;
		Wrapper::PhysicsCollider* physicsCollider;
		void Init();
		void Update() override;
		void Start() override;
		void GUIUpdate() override {};
		void OnDestroy() override {};
		void Setup(Maths::Vec3 center, Maths::Vec3 size, bool trigger, Wrapper::MaterialType material);
		Reflection::ClassMetaData & GetMetaData() override ;

	};

	class BoxCollider : public Collider
	{
	public:
		BoxCollider(Maths::Vec3 _size = Maths::Vec3(1, 1, 1));
		Reflection::ClassMetaData& GetMetaData() override;
		Maths::Vec3 size;
	};

	class PHOSENGINE_API SphereCollider : public Collider
	{
	public:
		SphereCollider(float _radius = 1);
		Reflection::ClassMetaData& GetMetaData() override;
		float radius;
	};

	class PHOSENGINE_API CapsuleCollider : public Collider
	{
	public:
		CapsuleCollider(float _radius = 1, float _height = 1);
		Reflection::ClassMetaData& GetMetaData() override;
		float radius;
		float height;

	};
}


