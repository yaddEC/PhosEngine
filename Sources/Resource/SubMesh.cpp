// include needed
#include <utility>
#include <limits>
#include "pch.h"
//----------------


#include "Resource/ShaderProgram.hpp"
#include "Resource/Texture.hpp"

#include "Wrapper/RHI.hpp"

#define VERTEX_EXPORTS
#define SUBMESH_EXPORTS
#include "Resource/SubMesh.hpp"

using namespace std;
using namespace Resource;

SubMesh::SubMesh(vector<Vertex> _vertices, vector<unsigned int> _indices, Texture* _texture)
{
    vertices = _vertices;
    indices = _indices;
    texture = _texture;
}

void SubMesh::Render(const ShaderProgram& shaderProgram) const
{
    if (texture)
    {
        shaderProgram.SetTexture("albedoTexture", 0, *texture);
    }

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
