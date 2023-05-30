#pragma once

#include "Engine/MonoBehaviour.hpp"

namespace Script
{
	class PHOSENGINE_API PlayerMouvement : public Engine::MonoBehaviour
	{
	public:
		PlayerMouvement();
		~PlayerMouvement();
		void Start() override;
		void Update() override;
		void GUIUpdate() override;
		void OnInspector() override;
		void OnDestroy() override;
		Reflection::ClassMetaData& GetMetaData() override;
	private:
		float m_playerSpeed;
		float m_idUser;
		int user; //temp
		bool up;
		bool right;
		bool down;
		bool left;

	};


}