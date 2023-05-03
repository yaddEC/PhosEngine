// include needed
#include <utility>
#include <limits>
#include "pch.h"
//----------------

#include <iostream>

#include "Wrapper/GUI.hpp"
#include "Resource/AnimBone.hpp"
#include "Resource/Animation.hpp"

void Resource::Animation::Load(const std::string& filepath)
{

    Assimp::Importer importer;
    const aiScene* scene = importer.ReadFile(filepath.c_str(), 0);

    if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
    {
        std::cout << "ERROR::ASSIMP::" << importer.GetErrorString() << std::endl;
        return;
    }
    if (!scene->HasAnimations())
        return;

    auto animation = scene->mAnimations[0];
    m_duration = animation->mDuration;
    m_tickRate = animation->mTicksPerSecond;
    ProcessBone(animation, scene);
}

void Resource::Animation::Bind()
{

}

void Resource::Animation::Unload()
{

}

void Resource::Animation::GUIUpdate()
{
    for (auto bone : m_AnimBones)
    {
        if (!bone->GetParent())
            DisplayBoneHierarchy(*bone);
    }
}

void Resource::Animation::DisplayBoneHierarchy(AnimBone& current)
{
    if (Wrapper::GUI::TreeNode(current.GetName(), false, !current.GetChildren().size()))
    {
        for (auto bone : current.GetChildren())
            DisplayBoneHierarchy(*bone);

        Wrapper::GUI::TreePop();
    }
}

void Resource::Animation::ProcessBone(const aiAnimation* anim, const aiScene* scene)
{
    std::unordered_map<std::string, AnimBone*> boneMap;
    for (size_t i = 0; i < anim->mNumChannels; i++)
    {
        
        AnimBone* newBone = new AnimBone();
        newBone->Load(anim->mChannels[i]);
        newBone->SetArmatureIndex(i);
        m_AnimBones.push_back(newBone);
        boneMap.emplace(newBone->GetName(), newBone);
    }

    for (size_t i = 0; i < scene->mRootNode->mNumChildren; i++)
    {
        ProcessHierarchy(scene->mRootNode->mChildren[i], boneMap);
    }
    
}

Resource::AnimBone* Resource::Animation::ProcessHierarchy(const aiNode* node, 
    std::unordered_map<std::string, AnimBone*>& boneMap, AnimBone* parent)
{
    std::string boneName = node->mName.data;
    AnimBone* current = nullptr;
    if (boneMap.find(boneName) != boneMap.end())
    {
        current = boneMap.find(boneName)->second;
        current->SetParent(parent);

        for (size_t i = 0; i < node->mNumChildren; i++)
        {
            AnimBone* child = ProcessHierarchy(node->mChildren[i], boneMap, current);
            if(child)
                current->AddChild(child);
        }

        return current;
    }
    else
    {
        if (node->mNumChildren)
        {
            AnimBone* child = ProcessHierarchy(node->mChildren[0], boneMap, parent);
            if (child)
                return child;
        }
        else
        {
            return nullptr;
        }
        
    }

    
}
