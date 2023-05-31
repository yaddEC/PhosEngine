#pragma once
#include "IResource.hpp"

#include "dllInclude.hpp"

namespace Resource
{
	class Texture;

	class PHOSENGINE_API CubeMap : public IResource
	{
	public:

		CubeMap() : IResource() {};
		~CubeMap() {};

		void Load() override;
		void Bind() override;
		void Unload() override;
		void Save() override;
		void GUIUpdate() override;
		Texture* GenerateFileIcon() override;

		unsigned int GetKey() const { return m_cubeMapKey; }

	private:
		unsigned int m_cubeMapKey;
		Resource::Texture* m_faces[6] = { nullptr };
		unsigned char* m_datas[6];
		void SetProperties(const std::string& filepath);
		void LoadData();
	};
}