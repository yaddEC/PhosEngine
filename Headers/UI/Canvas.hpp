#pragma once
#include "Resource/IResource.hpp"


namespace Resource
{
	class Texture;
}

namespace UI
{
	class Canvas : public Resource::IResource
	{
	public:
		void Load() override;
		void Unload() override;
		void Save() override;
		void GUIUpdate() override;
		Texture* GenerateFileIcon() override;
	};
}