#pragma once
#include <cmath>
#include <iostream>
#include "Canon.h"
#include <Box2D/Box2D.h>
#include "Box2DHelper.h"
#include "Ragdoll.h"

class Cannon
{
public:
    Cannon(b2World* world, b2Vec2 position);
    void AimAt(b2Vec2 target);
    std::pair<b2Vec2, float> Fire(b2Vec2 target);
    b2Body* GetBase() const;

private:
    b2Body* base;
    b2Body* barrel;
    b2RevoluteJoint* joint;


};


