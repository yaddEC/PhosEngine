// include needed
#include <utility>
#include <limits>
#include "pch.h"
//----------------

#include <iostream>
#include <algorithm>

#include "Wrapper/GUI.hpp"
#include "Resource/AnimBone.hpp"
#include "Resource/Animation.hpp"

void Resource::Animation::Load()
{
    std::string filepath = GetFilePath();

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
    static float timeline;
    Wrapper::GUI::EditFloat("timeline", &timeline, true, 0.01f, 0, m_duration / m_tickRate);
    for (auto bone : m_AnimBones)
    {
        DisplayBoneKeyFrame(*bone, timeline);
    }
}


void Resource::Animation::DisplayBoneKeyFrame(AnimBone& current, float timeline)
{
    if (Wrapper::GUI::TreeNode(current.GetName() + " " + std::to_string(current.GetArmatureIndex()), false, false))
    {
        Wrapper::GUI::DisplayVec3("Position", current.GetInterpolationPosition(timeline * m_tickRate));
        Wrapper::GUI::DisplayVec3("Rotation", current.GetInterpolationRotation(timeline * m_tickRate).ToEulerAngles());
        Wrapper::GUI::DisplayVec3("Scale", current.GetInterpolationScale(timeline * m_tickRate));
        Wrapper::GUI::TreePop();
    }
}

void Resource::Animation::ProcessBone(const aiAnimation* anim, const aiScene* scene)
{
    std::unordered_map<std::string, AnimBone*> boneMap;
    for (size_t i = 1; i < anim->mNumChannels; i++)
    {
        AnimBone* newBone = new AnimBone();
        newBone->Load(anim->mChannels[i]);
        m_AnimBones.push_back(newBone);
        boneMap.emplace(newBone->GetName(), newBone);
    }

    int index = -1;
    for (size_t i = 0; i < scene->mRootNode->mNumChildren; i++)
    {
        ProcessHierarchy(scene->mRootNode->mChildren[i], boneMap, nullptr, ++index);
    }
    std::sort(m_AnimBones.begin(), m_AnimBones.end(), [](const AnimBone* a, const AnimBone* b) { return a->GetArmatureIndex() < b->GetArmatureIndex(); });
}

Resource::AnimBone* Resource::Animation::ProcessHierarchy(const aiNode* node, 
    std::unordered_map<std::string, AnimBone*>& boneMap, AnimBone* parent, int& index)
{
    std::string boneName = node->mName.data;
    AnimBone* current = nullptr;
    if (boneMap.find(boneName) != boneMap.end())
    {
        current = boneMap.find(boneName)->second;
        current->SetArmatureIndex(index);

        for (size_t i = 0; i < node->mNumChildren; i++)
        {
            AnimBone* child = ProcessHierarchy(node->mChildren[i], boneMap, current, ++index);
            if(!child)
                index--;
        }

        return current;
    }
    else
    {
        if (node->mNumChildren)
        {
            AnimBone* child = ProcessHierarchy(node->mChildren[0], boneMap, parent, index);
            if (child)
                return child;
        }
        else
        {
            return nullptr;
        }
        
    }

    
}
