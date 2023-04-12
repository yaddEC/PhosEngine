// include needed
#include <utility>
#include <limits>
#include "pch.h"

#include <iostream>

#include "Resource/Texture.hpp"
#include "Resource/SubMesh.hpp"
#include "Resource/ResourceManager.hpp"
#include "Resource/ShaderProgram.hpp"
#include "Resource/Material.hpp"
#include "Resource/CubeMap.hpp"

#define MESH_EXPORTS
#include "Resource/Mesh.hpp"

using namespace Maths;
using namespace Resource;

void Mesh::Load(const std::string& filepath)
{
    SetFileInfo(filepath);

    Assimp::Importer importer;
    const aiScene* scene = importer.ReadFile(filepath.c_str(), aiProcess_Triangulate | aiProcess_CalcTangentSpace);

    if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
    {
        std::cout << "ERROR::ASSIMP::" << importer.GetErrorString() << std::endl;
        return;
    }

    ProcessNode(scene->mRootNode, scene, filepath);
    return;
}

void Mesh::Bind()
{
    for (SubMesh& mesh : m_subMeshes)
    {
        mesh.SetUpSubMesh();
    }
    p_isLoaded = true;
}

void Mesh::Unload()
{
    for (SubMesh& mesh : m_subMeshes)
    {
        mesh.Unload();
    }
}

Mesh::~Mesh()
{
    Unload();
}

void Mesh::Render(const ShaderProgram& shaderProgram, const class Material& material) const
{
    for (SubMesh mesh : m_subMeshes)
    {
        mesh.Render(shaderProgram, material);
    }
}

Texture* Mesh::GenerateFileIcon()
{
    /*unsigned char image[] = { 0, 255, 15, 255, 0, 20, 255, 0, 32, 0, 21, 255 };
    unsigned char* data = new unsigned char[12]();
    for (size_t i = 0; i < 12; i++)
    {
        data[i] = image[i];
    }*/
    /*Transform modelTransform, camTransform;
    camTransform.position = Vec3(0, 1, -7);

    modelTransform.ComputeGlobalMatrix();
    camTransform.ComputeGlobalMatrix();
    ShaderProgram* shaderProgram = ResourceManager::GetInstance().GetResource<ShaderProgram>("Resources\\Shader\\BasicShader.prog");
    Texture* tex = Camera::TakePhoto(*this, modelTransform, camTransform, *shaderProgram);*/



    return nullptr;
}

void Mesh::ProcessNode(aiNode* node, const aiScene* scene, const std::string& filepath)
{
    // process all the node's meshes (if any)
    for (unsigned int i = 0; i < node->mNumMeshes; i++)
    {
        aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
        m_subMeshes.push_back(ProcessMesh(mesh, scene, filepath));
    }
    // then do the same for each of its children
    for (unsigned int i = 0; i < node->mNumChildren; i++)
    {
        ProcessNode(node->mChildren[i], scene, filepath);
    }
}

SubMesh Mesh::ProcessMesh(aiMesh* mesh, const aiScene* scene, const std::string& filepath)
{
    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;

    for (unsigned int i = 0; i < mesh->mNumVertices; i++)
    {
        Vertex vertex;
        // process vertex positions, normals and texture coordinates
        vertex.position = Vec3(mesh->mVertices[i].x, mesh->mVertices[i].y, mesh->mVertices[i].z);
        vertex.normal = Vec3(mesh->mNormals[i].x, mesh->mNormals[i].y, mesh->mNormals[i].z);

        if (mesh->mTextureCoords[0])
        {
            vertex.UVCoords = Vec2(mesh->mTextureCoords[0][i].x, mesh->mTextureCoords[0][i].y);
        }

        vertices.push_back(vertex);

        if (vertex.position.x < m_boundingBoxMin.x) m_boundingBoxMin.x = vertex.position.x;
        if (vertex.position.y < m_boundingBoxMin.y) m_boundingBoxMin.y = vertex.position.y;
        if (vertex.position.z < m_boundingBoxMin.z) m_boundingBoxMin.z = vertex.position.z;

        if (vertex.position.x > m_boundingBoxMax.x) m_boundingBoxMax.x = vertex.position.x;
        if (vertex.position.y > m_boundingBoxMax.y) m_boundingBoxMax.y = vertex.position.y;
        if (vertex.position.z > m_boundingBoxMax.z) m_boundingBoxMax.z = vertex.position.z;
    }

    // process indices
    for (unsigned int i = 0; i < mesh->mNumFaces; i++)
    {
        aiFace face = mesh->mFaces[i];
        for (unsigned int j = 0; j < face.mNumIndices; j++)
            indices.push_back(face.mIndices[j]);
    }

    // process materials (textures for now)
    Texture* texture = nullptr;
    if (mesh->mMaterialIndex >= 0)
    {
        aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];
        //GenerateMaterial(material);
        texture = ProcessTexture(material, aiTextureType_DIFFUSE, filepath);
    }

    return SubMesh(vertices, indices, texture);
}

Texture* Mesh::ProcessTexture(aiMaterial* mat, aiTextureType type, const std::string& filepath)
{
    aiString str;
    mat->GetTexture(type, 0, &str);
    ResourceManager& rm = ResourceManager::GetInstance();
    Texture* tex = rm.GetResource<Texture>(p_directory + "\\" + str.C_Str());
    return tex;
}

void Resource::Mesh::GenerateMaterial(aiMaterial* mat)
{
    
    aiString name;
    mat->Get(AI_MATKEY_NAME, name);
    

    aiColor3D albedoCol, specCol;
    mat->Get(AI_MATKEY_COLOR_DIFFUSE, albedoCol);
    mat->Get(AI_MATKEY_COLOR_SPECULAR, specCol);

    aiString albedoTex, specTex;
    mat->GetTexture(aiTextureType_DIFFUSE, 0, &albedoTex);
    mat->GetTexture(aiTextureType_SPECULAR, 0, &specTex);

    float shininess;
    mat->Get(AI_MATKEY_SHININESS, shininess);

    Material* material = Resource::ResourceManager::GetInstance().CreateResource<Material>(p_directory + "\\" + name.C_Str() + ".phmat");

    ColorMap albedo;
    albedo.texture = ResourceManager::GetInstance().GetResource<Texture>(p_directory + "\\" + albedoTex.C_Str());
    albedo.useTexture = albedo.texture;
    if (!albedo.useTexture)
        albedo.color = Maths::Vec3(albedoCol.r, albedoCol.g, albedoCol.b);

    ColorMap spec;
    spec.texture = ResourceManager::GetInstance().GetResource<Texture>(p_directory + "\\" + specTex.C_Str());
    spec.useTexture = spec.texture;
    if (!spec.useTexture)
        spec.color = Maths::Vec3(specCol.r, specCol.g, specCol.b);
    ShaderProgram* shader = ResourceManager::GetInstance().GetResource<ShaderProgram>("Assets\\Shader\\MainShader.prog");
    material->SetProperties(albedo, spec, shininess, shader);
    material->SetFileInfo(p_directory + "\\" + name.C_Str() + ".phmat");
    material->Save();
}
