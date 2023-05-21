// include needed
#include <utility>
#include <limits>
#include "pch.h"
//----------------

#include "Resource/Parser.hpp"
#include "Resource/AnimBone.hpp"

void Resource::AnimBone::Load(const aiNodeAnim* channel)
{
	
	m_name = channel->mNodeName.data;

	for (size_t i = 0; i < channel->mNumPositionKeys; i++)
	{
		AnimBonePosition pos;
		aiVector3D aiPosition = channel->mPositionKeys[i].mValue;
		pos.position = Maths::Vec3(aiPosition.x, aiPosition.y, aiPosition.z);
		pos.timeStamp = channel->mPositionKeys[i].mTime;
		m_positionList.push_back(pos);
	}

	for (size_t i = 0; i < channel->mNumRotationKeys; i++)
	{
		AnimBoneRotation rot;
		rot.rotation.a = channel->mRotationKeys[i].mValue.w;
		rot.rotation.b = channel->mRotationKeys[i].mValue.x;
		rot.rotation.c = channel->mRotationKeys[i].mValue.y;
		rot.rotation.d = channel->mRotationKeys[i].mValue.z;
		rot.timeStamp = channel->mRotationKeys[i].mTime;
		m_rotationList.push_back(rot);
	}

	for (size_t i = 0; i < channel->mNumScalingKeys; i++)
	{
		AnimBoneScale scale;
		aiVector3D aiScale = channel->mScalingKeys[i].mValue;
		scale.scale = Maths::Vec3(aiScale.x, aiScale.y, aiScale.z);
		scale.timeStamp = channel->mScalingKeys[i].mTime;
		m_scaleList.push_back(scale);
	}
}

Maths::Mat4 Resource::AnimBone::GetGlobalMatrix(float animationTime, const Maths::Mat4& parentMatrix) const
{
	int posIndex = 0; int rotIndex = 0; int scaleIndex = 0;

	for (size_t i = 0; i < m_positionList.size(); i++)
	{
		if (m_positionList.at(i).timeStamp < animationTime)
			posIndex++;
		else
			break;
	}

	for (size_t i = 0; i < m_rotationList.size(); i++)
	{
		if (m_rotationList.at(i).timeStamp < animationTime)
			rotIndex++;
		else
			break;
	}

	for (size_t i = 0; i < m_scaleList.size(); i++)
	{
		if (m_scaleList.at(i).timeStamp < animationTime)
			scaleIndex++;
		else
			break;
	}

	return parentMatrix * Maths::Mat4::CreateTransformMatrix(
		m_positionList.at(posIndex).position,
		m_rotationList.at(rotIndex).rotation.ToEulerAngles(),
		m_scaleList.at(scaleIndex).scale);
	
}

Maths::Vec3 Resource::AnimBone::GetInterpolationPosition(float animationTime) const
{
	int posIndex = 0;

	for (size_t i = 0; i < m_positionList.size(); i++)
	{
		if (m_positionList.at(i).timeStamp < animationTime)
			posIndex++;
		else
			break;
	}

	return m_positionList.at(posIndex).position;
}

Maths::Quaternion Resource::AnimBone::GetInterpolationRotation(float animationTime) const
{
	int rotIndex = 0;

	for (size_t i = 0; i < m_rotationList.size(); i++)
	{
		if (m_rotationList.at(i).timeStamp < animationTime)
			rotIndex++;
		else
			break;
	}

	return m_rotationList.at(rotIndex).rotation;
}

Maths::Vec3 Resource::AnimBone::GetInterpolationScale(float animationTime) const
{
	int scaleIndex = 0;

	for (size_t i = 0; i < m_scaleList.size(); i++)
	{
		if (m_scaleList.at(i).timeStamp < animationTime)
			scaleIndex++;
		else
			break;
	}

	return m_scaleList.at(scaleIndex).scale;
}



