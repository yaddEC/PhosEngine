#pragma once
#include "Resource/IResource.hpp"
#include "Maths/Maths.hpp"
#include <string>


#include "dllInclude.hpp"


namespace Resource
{
	class Texture;
	class ShaderProgram;

	struct ColorMap
	{
		ColorMap() {}
		~ColorMap() {}

		union
		{
			Texture* texture;
			Maths::Vec3 color;
		};

		bool useTexture = false;


		void GUIUpdate(const std::string& label);
	};

	struct ValueMap
	{
		ValueMap() {}
		~ValueMap() {}

		union
		{
			Texture* texture;
			float value;
		};

		bool useTexture = false;

		void GUIUpdate(const std::string& label);
	};

	class PHOSENGINE_API Material : public IResource
	{
	public:

		Material() : IResource() {}
		~Material() {}

		void Load(const std::string& filepath) override;
		void Bind() override;
		void Unload() override;
		void Save() override;
		void GUIUpdate() override;

		std::string GetTypeName() { return "Material"; }

		Texture* GenerateFileIcon() override;

		void SendDataToShader() const;

		ShaderProgram* GetShader() const { return m_shader; } 
		void SetProperties(const ColorMap& albedo, const ColorMap& specular, float shininess, ShaderProgram* shader);



		static Material DefaultMaterial();

	private:
		ShaderProgram* m_shader = nullptr;
		
		Texture* m_normalMap;

		ColorMap m_albedo;
		ColorMap m_specular;
		float m_shininess = 1;

		ValueMap m_roughness;
		ValueMap m_metallic;

		void SetProperties(const std::string& filepath);
	};
}