#pragma once
#include <Maths/Maths.hpp>
#include <Engine/MonoBehaviour.hpp>
#include <Physic/PhysXManager.hpp>

#ifdef RIGIDBODY_EXPORTS
#define RIGIDBODY_API __declspec(dllexport)
#else
#define RIGIDBODY_API __declspec(dllimport)
#endif

using namespace Maths;
using namespace Engine;

namespace Physic
{
	class Rigidbody : public MonoBehaviour
	{
	public:
		Rigidbody();
		~Rigidbody() {};
		void Init();
		void Update() override;

		Vec3 gravity = Vec3(0, -20, 0);
		Vec3 velocity;
		bool isStatic = false;
		float mass = 1;
		bool reset = false;

		PxRigidActor* PhysxActor;

	};
}