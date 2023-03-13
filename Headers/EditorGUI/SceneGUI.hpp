#pragma once
#include "EditorGUI/IEditorGUI.h"

class SceneGUI : public IEditorGUI
{
public:
	SceneGUI() : IEditorGUI("Scene") {}

	void DoUpdate() override;
private:
};
