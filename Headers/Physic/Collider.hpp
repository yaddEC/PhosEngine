#pragma once
#include <Maths/Maths.hpp>
#include <Engine/MonoBehaviour.hpp>
#include <Engine/GameObject.hpp>
#include <Physic/PhysXManager.hpp>
#include <Physic/Rigidbody.hpp>
#include <vector>

#ifdef COLLIDER_EXPORTS
#define COLLIDER_API __declspec(dllexport)
#else
#define COLLIDER_API __declspec(dllimport)
#endif


using namespace Maths;
using namespace Engine;

namespace Physic
{
	class Collider : public MonoBehaviour
	{
	public:
		bool show = false;
		bool isTrigger = false;
		bool collide = false;
		Vec3 center;
		Rigidbody* rb;
		PxShape* shape;

		virtual void setShape(PxMaterial& material) = 0;
		void Init(PxPhysics& physics, PxMaterial& material, PxScene& scene);
		void Update() override;

	};

	class BoxCollider : public Collider
	{
	public:
		BoxCollider(Vec3 _size = Vec3(1, 1, 1));
		void setShape(PxMaterial& material) override;
		Vec3 size;
		std::vector<Vec3> vertices;
		PxBoxGeometry geometry;
	};

	class SphereCollider : public Collider
	{
	public:
		SphereCollider(float _radius = 1);
		void setShape(PxMaterial& material) override;
		float radius;
		float scaledRadius;
		PxSphereGeometry geometry;
	};

	class CapsuleCollider : public Collider
	{
	public:
		CapsuleCollider(float _radius = 1, float _height = 1);
		void setShape(PxMaterial& material) override;
		float radius;
		float height;

		float scale = 0;
		float hScale = 0;
		Vec3 worldScale = Vec3(1, 1, 1);

		PxCapsuleGeometry geometry;
	};
}


