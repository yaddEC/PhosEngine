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
		void SetIdUser(int ID);
		int GetIdUser() { return m_idUser; }
		Reflection::ClassMetaData& GetMetaData() override;
	private:
		float m_playerSpeed;
		int m_idUser;

	};


}