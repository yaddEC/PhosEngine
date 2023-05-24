/*#pragma once
#include <Maths/Maths.hpp>
#include <Engine/MonoBehaviour.hpp>

#include "dllInclude.hpp"

namespace Wrapper
{
    class PhysicsCollider;
    enum class MaterialType;
}

namespace Engine
{
    class GameObject;
    class Transform;
}

namespace Physic
{
    class Rigidbody;

    class PHOSENGINE_API Joint : public Engine::MonoBehaviour
    {
    public:
        Joint();

        void Update() override;
        void Start() override;
        void GUIUpdate() override;
        void OnDestroy() override {};
  
        Reflection::ClassMetaData& GetMetaData() override;
    protected:

    };

    class PHOSENGINE_API FixedJoint : public Joint
    {
    public:
        FixedJoint();
        Reflection::ClassMetaData& GetMetaData() override;
        
    private:
       
    };

    class PHOSENGINE_API HingeJoint : public Joint
    {
    public:
        HingeJoint();
        Reflection::ClassMetaData& GetMetaData() override;

    private:

    };

    class PHOSENGINE_API CharacterJoint : public Joint
    {
    public:
        CharacterJoint();
        Reflection::ClassMetaData& GetMetaData() override;

    private:

    };

    class PHOSENGINE_API SpringJoint : public Joint
    {
    public:
        SpringJoint();
        Reflection::ClassMetaData& GetMetaData() override;

    private:

    };



}*/