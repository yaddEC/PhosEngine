#pragma once
#include <Maths/Maths.hpp>
#include <Engine/MonoBehaviour.hpp>

#include "dllInclude.hpp"

namespace Wrapper
{
	class PhysicsRigidbody;
	enum MaterialType;
}

namespace Physic
{
	class PHOSENGINE_API Rigidbody : public Engine::MonoBehaviour
	{
	public:
		Rigidbody();
		Rigidbody(Wrapper::MaterialType type);
		~Rigidbody() {};
		void Init();
		void Update() override;

		Maths::Vec3 gravity = Maths::Vec3(0, -20, 0);
		Maths::Vec3 velocity;
		bool isStatic = false;
		float mass = 1;
		bool reset = false;

		Wrapper::PhysicsRigidbody* physicsRigidbody;

	};
}