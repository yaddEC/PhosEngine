#pragma once
#include "Resource/IResource.hpp"
#include "Maths/Maths.hpp"
#include <unordered_map>
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

	class PHOSENGINE_API Material : public IResource
	{
	public:

		Material() : IResource() {}
		~Material() {}

		void Load(const std::string& filepath) override;
		void Bind() override;
		void Unload() override;
		void Save() override;
		void GUIUpdate();

		std::string GetTypeName() { return "Material"; }

		Texture* GenerateFileIcon() override;

		void SendDataToShader() const;

		ShaderProgram* GetShader() const { return m_shader; } 
		void SetProperties(const ColorMap& albedo, const ColorMap& specular, float shininess, ShaderProgram* shader);



		static Material DefaultMaterial();

	private:
		ShaderProgram* m_shader = nullptr;

		ColorMap m_albedo;
		ColorMap m_specular;
		float m_shininess = 1;


		void SetProperties(const std::string& filepath);
		
	};
}