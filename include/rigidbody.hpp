#ifndef RIGIDBODY_H
#define RIGIDBODY_H

#include <vector2.hpp>
#include <gameObject.hpp>

class RigidBody : public GameObject
{
protected:
    double mass;
    Vector2<> velocity = Vector2(0.0, 0.0);
    Vector2<> acceleration = Vector2(0.0, 0.0);

public:
    static constexpr double GRAVITIONAL_CONSTANT = 6.67430 * 10e-11; // m^3 kg^-1 s^-2

    static void CalcGravityAttraction(RigidBody *a, RigidBody *b);

    RigidBody(string name = "rigidBody", Vector2<> position = Vector2(), Vector2<> size = Vector2(), double mass = 1.0f);
    
    Vector2<> GetVelocity() const;
    void SetVelocity(Vector2<> velocity);

    Vector2<> GetAcceleration() const;
    void SetAcceleration(Vector2<> acceleration);

    double GetMass() const;
    void SetMass(double mass);

    void UpdateBody(double dt);
};

#endif