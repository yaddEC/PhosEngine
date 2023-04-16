#pragma once
#include <Maths/Maths.hpp>
#include <Engine/MonoBehaviour.hpp>

#include "dllInclude.hpp"

namespace Wrapper
{
	class PhysicsRigidbody;
}

namespace Physic
{
	class PHOSENGINE_API Rigidbody : public Engine::MonoBehaviour
	{
	public:
		Rigidbody();
		~Rigidbody() {};
		void Init();
		void Update() override;
		void Start() override {};
		void GUIUpdate() override {};
		void OnDestroy() override {};
		Reflection::ClassMetaData& GetMetaData() override;

		Maths::Vec3 gravity = Maths::Vec3(0, -20, 0);
		Maths::Vec3 velocity;
		float mass = 1;
		bool reset = false;

		Wrapper::PhysicsRigidbody* physicsRigidbody;

	};
}