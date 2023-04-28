// include needed
#include <utility>
#include <limits>
#include "pch.h"
//----------------


#include "Resource/ShaderProgram.hpp"
#include "Resource/Texture.hpp"
#include "Resource/Material.hpp"

#include "Wrapper/RHI.hpp"

#include "Resource/SubMesh.hpp"

using namespace std;
using namespace Resource;

SubMesh::SubMesh(vector<Vertex> _vertices, vector<unsigned int> _indices)
{
    vertices = _vertices;
    indices = _indices;
    isSkinned = false;
}

SubMesh::SubMesh(vector<SkinnedVertex> _vertices, vector<unsigned int> _indices)
{
    skninnedVertices = _vertices;
    indices = _indices;
    isSkinned = true;
}

void SubMesh::Render(const ShaderProgram& shaderProgram, const class Material& material) const
{
    material.SendDataToShader();

    Wrapper::RHI::RenderSubMesh(m_VAO, indices);
}

void SubMesh::SetUpSubMesh()
{
        Wrapper::RHI::SetSubMeshData(m_VAO, m_VBO, m_EBO, vertices, indices);

}

void SubMesh::Unload()
{
    Wrapper::RHI::UnloadSubMesh(m_VAO, m_VBO, m_EBO);
}
