#include "Canon.h"


Cannon::Cannon(b2World* world, b2Vec2 position)
{

    base = Box2DHelper::CreateRectangularStaticBody(world, 5.0f, 2.0f);
    base->SetTransform(position, 0.0f);


    barrel = Box2DHelper::CreateRectangularDynamicBody(world, 4.0f, 0.5f, 1.0f, 0.5f, 0.5f);
    barrel->SetTransform(position + b2Vec2(2.0f, 0.0f), 0.0f);


    b2RevoluteJointDef jointDef;
    jointDef.bodyA = base;
    jointDef.bodyB = barrel;
    jointDef.localAnchorA.Set(1.0f, 0.0f);
    jointDef.localAnchorB.Set(-2.0f, 0.0f);
    jointDef.enableLimit = true;
    jointDef.lowerAngle = -b2_pi / 4;  
    jointDef.upperAngle = b2_pi / 4;   

    joint = (b2RevoluteJoint*)world->CreateJoint(&jointDef);
}

void Cannon::AimAt(b2Vec2 target)
{
    b2Vec2 direction = target - base->GetWorldCenter();
    float angle = atan2(direction.y, direction.x);
    joint->SetMotorSpeed(10.0f * (angle - joint->GetJointAngle()));
    joint->EnableMotor(true);
}

std::pair<b2Vec2, float> Cannon::Fire(b2Vec2 target) {
    b2Vec2 direction = target - (base->GetWorldCenter() + b2Vec2(1.0f, 0.0f));
    direction.Normalize();
    float distance = (target - base->GetWorldCenter()).Length();
    float force = distance * 100.0f; 

    return { direction, force };
}

b2Body* Cannon::GetBase() const
{
    return base;
}
