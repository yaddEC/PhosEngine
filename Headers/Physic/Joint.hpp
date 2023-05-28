#pragma once
#include <Maths/Maths.hpp>
#include <Engine/MonoBehaviour.hpp>

#include "dllInclude.hpp"

namespace Wrapper
{
    class PhysicsJoint;
}

namespace Engine
{
    class GameObject;
    class Transform;
}

namespace Physic
{
    struct Spring {
        float spring;
        float damper;
        float targetPosition;//optional
    };

    struct Limit {
        float limit;
        float bounciness;
        float contactDistance;
    };

    struct Drive {
        float positionSpring;
        float positionDamper;
        float maximumForce;
    };

    class Rigidbody;

    class PHOSENGINE_API Joint : public Engine::MonoBehaviour
    {
    public:
        Joint();
        ~Joint();

        void Update() override;
        void Start() override;
        void GUIUpdate() override;
        void OnDestroy() override {};
  
        Reflection::ClassMetaData& GetMetaData() override;

        unsigned int GetGameObjectId() const { return p_gameObjectId; }
        Rigidbody* GetSelfRigidbody() const { return p_selfRigidbody; }
        Rigidbody* GetOtherRigidbody() const { return p_otherRigidbody; }
        float GetBreakForce() const { return p_breakForce; }
        float GetBreakTorque() const { return p_breakTorque; }

        void SetGameObjectId(unsigned int gameObjectId) { p_gameObjectId = gameObjectId; }
        void SetSelfRigidbody(Rigidbody* selfRigidbody) { p_selfRigidbody = selfRigidbody; }
        void SetOtherRigidbody(Rigidbody* otherRigidbody) { p_otherRigidbody = otherRigidbody; }
        void SetBreakForce(float breakForce) { p_breakForce = breakForce; }
        void SetBreakTorque(float breakTorque) { p_breakTorque = breakTorque; }

        Wrapper::PhysicsJoint* physicsJoint;
    protected:

        unsigned int p_gameObjectId;
        Rigidbody* p_selfRigidbody;
        Rigidbody* p_otherRigidbody;
        float p_breakForce;
        float p_breakTorque;

    };

    class PHOSENGINE_API FixedJoint : public Joint
    {
    public:
        FixedJoint();
        Reflection::ClassMetaData& GetMetaData() override;
        
    private:
;
    };

    class PHOSENGINE_API HingeJoint : public Joint
    {
    public:
        HingeJoint();
        Reflection::ClassMetaData& GetMetaData() override;
        Maths::Vec3 GetAnchor() const { return m_anchor; }
        Maths::Vec3 GetAxis() const { return m_axis; }
        Maths::Vec3 GetConnectedAnchor() const { return m_connectedAnchor; }
        float GetMotorForce() const { return m_motorForce; }
        float GetMotorSpeed() const { return m_motorSpeed; }

        void SetAnchor(const Maths::Vec3& anchor) { m_anchor = anchor; }
        void SetAxis(const Maths::Vec3& axis) { m_axis = axis; }
        void SetConnectedAnchor(const Maths::Vec3& connectedAnchor) { m_connectedAnchor = connectedAnchor; }
        void SetMotorForce(float motorForce) { m_motorForce = motorForce; }
        void SetMotorSpeed(float motorSpeed) { m_motorSpeed = motorSpeed; }

    private:
        Maths::Vec3 m_anchor;
        Maths::Vec3 m_axis;
        Maths::Vec3 m_connectedAnchor;
        float m_motorForce;
        float m_motorSpeed;
    };

    class PHOSENGINE_API ConfigurableJoint : public Joint
    {
    public:
        ConfigurableJoint();
        Reflection::ClassMetaData& GetMetaData() override;
        Maths::Vec3 GetAnchor() const { return m_anchor; }
        Maths::Vec3 GetAxis() const { return m_axis; }
        Maths::Vec3 GetConnectedAnchor() const { return m_connectedAnchor; }
        Maths::Vec3 GetMotion() const { return m_motion; }
        Maths::Vec3 GetAngularMotion() const { return m_angularMotion; }
        Spring GetLinearLimitSpring() const { return m_linearLimitSpring; }
        Limit GetLinearLimit() const { return m_linearLimit; }
        Drive GetXDrive() const { return m_xDrive; }
        Drive GetYDrive() const { return m_yDrive; }
        Drive GetZDrive() const { return m_zDrive; }
        Drive GetAngularXDrive() const { return m_angularXDrive; }
        Drive GetAngularYDrive() const { return m_angularYDrive; }
        Drive GetAngularZDrive() const { return m_angularZDrive; }
        Drive GetAngularYZDrive() const { return m_angularYZDrive; }
        Maths::Vec3 GetTargetPosition() const { return m_targetPosition; }
        Maths::Quaternion GetTargetRotation() const { return m_targetRotation; }
        Maths::Vec3 GetTargetVelocity() const { return m_targetVelocity; }
        Maths::Vec3 GetTargetAngularVelocity() const { return m_targetAngularVelocity; }

        void SetAnchor(const Maths::Vec3& anchor) { m_anchor = anchor; }
        void SetAxis(const Maths::Vec3& axis) { m_axis = axis; }
        void SetConnectedAnchor(const Maths::Vec3& connectedAnchor) { m_connectedAnchor = connectedAnchor; }
        void SetMotion(const Maths::Vec3& motion) { m_motion = motion; }
        void SetAngularMotion(const Maths::Vec3& angularMotion) { m_angularMotion = angularMotion; }
        void SetLinearLimitSpring(const Spring& linearLimitSpring) { m_linearLimitSpring = linearLimitSpring; }
        void SetLinearLimit(const Limit& linearLimit) { m_linearLimit = linearLimit; }
        void SetXDrive(const Drive& xDrive) { m_xDrive = xDrive; }
        void SetYDrive(const Drive& yDrive) { m_yDrive = yDrive; }
        void SetZDrive(const Drive& zDrive) { m_zDrive = zDrive; }
        void SetAngularXDrive(const Drive& angularXDrive) { m_angularXDrive = angularXDrive; }
        void SetAngularYDrive(const Drive& angularYDrive) { m_angularYDrive = angularYDrive; }
        void SetAngularZDrive(const Drive& angularZDrive) { m_angularZDrive = angularZDrive; }
        void SetAngularYZDrive(const Drive& angularYZDrive) { m_angularYZDrive = angularYZDrive; }
        void SetTargetPosition(const Maths::Vec3& targetPosition) { m_targetPosition = targetPosition; }
        void SetTargetRotation(const Maths::Quaternion& targetRotation) { m_targetRotation = targetRotation; }
        void SetTargetVelocity(const Maths::Vec3& targetVelocity) { m_targetVelocity = targetVelocity; }
        void SetTargetAngularVelocity(const Maths::Vec3& targetAngularVelocity) { m_targetAngularVelocity = targetAngularVelocity; }

    private:
        Maths::Vec3 m_anchor;
        Maths::Vec3 m_axis;
        Maths::Vec3 m_connectedAnchor;
        Maths::Vec3 m_motion;
        Maths::Vec3 m_angularMotion;

        Spring m_linearLimitSpring;
        Limit m_linearLimit;

        Drive m_xDrive;
        Drive m_yDrive;
        Drive m_zDrive;
        Drive m_angularXDrive;
        Drive m_angularYDrive;
        Drive m_angularZDrive;
        Drive m_angularYZDrive;

        Maths::Vec3 m_targetPosition;
        Maths::Quaternion m_targetRotation;
        Maths::Vec3 m_targetVelocity;
        Maths::Vec3 m_targetAngularVelocity;
    };

    class PHOSENGINE_API SpringJoint : public Joint
    {
    public:
        SpringJoint();
        Reflection::ClassMetaData& GetMetaData() override;
        Maths::Vec3 GetAnchor() const { return m_anchor; }
        Maths::Vec3 GetConnectedAnchor() const { return m_connectedAnchor; }
        Spring GetSpring() const { return m_spring; }
        float GetTolerance() const { return m_tolerance; }
        float GetMinDistance() const { return m_minDistance; }
        float GetMaxDistance() const { return m_maxDistance; }

        void SetAnchor(const Maths::Vec3& anchor) { m_anchor = anchor; }
        void SetConnectedAnchor(const Maths::Vec3& connectedAnchor) { m_connectedAnchor = connectedAnchor; }
        void SetSpring(const Spring& spring) { m_spring = spring; }
        void SetTolerance(float tolerance) { m_tolerance = tolerance; }
        void SetMinDistance(float minDistance) { m_minDistance = minDistance; }
        void SetMaxDistance(float maxDistance) { m_maxDistance = maxDistance; }

    private:
        Maths::Vec3 m_anchor;
        Maths::Vec3 m_connectedAnchor;
        Spring m_spring;
        float m_tolerance;
        float m_minDistance; 
        float m_maxDistance;
    };



}