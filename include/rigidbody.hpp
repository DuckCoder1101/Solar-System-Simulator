#ifndef RIGIDBODY_H
#define RIGIDBODY_H

#include <vector2.hpp>
#include <gameObject.hpp>
#include <debug.hpp>

class RigidBody : public GameObject
{
protected:
    static double timeScale;

    // Real properties
    double mass;
    double realRadius;
    Vector2 <> realPosition;

    Vector2<> velocity = Vector2(0.0, 0.0);
    Vector2<> acceleration = Vector2(0.0, 0.0);

public:
    static const double G;

    static void CalcGravityAttraction(RigidBody *a, RigidBody *b);

    RigidBody(string name = "rigidbody", Vector2<> realPosition = Vector2<>(), double radius = 0.0f, double mass = 1.0f, Vector2<> v0 = Vector2<>());

    double GetMass() const;
    void SetMass(double mass);

    double GetRealRadius() const;
    void SetRealRadius(double radius);

    Vector2<> GetRealPosition() const;
    void SetRealPosition(Vector2<> position);
    
    Vector2<> GetVelocity() const;
    void SetVelocity(Vector2<> velocity);

    Vector2<> GetAcceleration() const;
    void SetAcceleration(Vector2<> acceleration);

    void UpdateBody(double dt, Debug *debugInterface);

    void Scale(double radiusScale, double positionScale);
};

#endif