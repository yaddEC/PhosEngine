#pragma once
#include "EditorGUI/IEditorGUI.hpp"

namespace EditorGUI
{
	class SceneGUI : public IEditorGUI
	{
	public:
		SceneGUI() : IEditorGUI("Scene") {}

		void DoUpdate() override;
	private:
	};
}


