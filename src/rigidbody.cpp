#include <rigidbody.hpp>
#include <gameObject.hpp>
#include <iostream>
#include <chrono>
#include <vector>

#include <debug.hpp>

using std::cerr;
using std::cout;
using std::endl;
using std::vector;

const double RigidBody::G = 6.67430e-11; // m^3 kg^-1 s^-2
double RigidBody::timeScale = 1;

// Static methods
void RigidBody::CalcGravityAttraction(RigidBody *a, RigidBody *b)
{
    Vector2<> direction = a->realPosition - b->realPosition;
    double distance = direction.GetMagnitude();

    if (distance == 0)
    {
        cerr << "Error: distance is 0" << endl;
        return;
    }

    if (distance < 1e-10) distance = 1e-10; 

    double forceMagnitude = G * ((a->mass * b->mass) / (distance * distance));

    // cout << "Massa 1: " << a->mass << endl;
    // cout << "Massa 2: " << b->mass << endl;
    // cout << "Distancia: " << distance << endl;

    if (std::isnan(forceMagnitude) || std::isinf(forceMagnitude)) {
        cerr << "Error: Invalid force magnitude" << endl;
        return;
    }

    Vector2<> force = direction.Normalize() * forceMagnitude;

    // cout << "Forca resultante: " << force.ToString() << endl;

    a->acceleration = force;
    b->acceleration -= force;
}

// Instance methods
RigidBody::RigidBody(string name, Vector2<> realPosition, double radius, double mass, Vector2<> v0)
{
    this->name = name;
    this->realPosition = realPosition;
    this->radius = radius;
    this->mass = mass;
    this->velocity = v0;
}

double RigidBody::GetMass() const
{
    return this->mass;
}

void RigidBody::SetMass(double mass)
{
    this->mass = mass;
}

double RigidBody::GetRealRadius() const
{
    return this->realRadius;
}

void RigidBody::SetRealRadius(double radius)
{
    this->realRadius = radius;
}

Vector2<> RigidBody::GetRealPosition() const
{
    return this->realPosition;
}

void RigidBody::SetRealPosition(Vector2<> position)
{
    this->realPosition = position;
}

Vector2<> RigidBody::GetVelocity() const
{
    return this->velocity;
}

void RigidBody::SetVelocity(Vector2<> velocity)
{
    this->velocity = velocity;
}

Vector2<> RigidBody::GetAcceleration() const
{
    return this->acceleration;
}

void RigidBody::SetAcceleration(Vector2<> acceleration)
{
    this->acceleration = acceleration;
}

void RigidBody::UpdateBody(double dt, Debug *debug)
{
    // Atualiza a velocidade
    this->velocity.x += this->acceleration.x * dt;
    this->velocity.y += this->acceleration.y * dt;

    // Atualiza a posição real
    this->realPosition.x += this->velocity.x * dt;
    this->realPosition.y += this->velocity.y * dt;

    double timeInSeconds = std::chrono::duration<double>(std::chrono::system_clock::now().time_since_epoch()).count();

    // cout << this->name << endl;
    // cout << "Real position: " << this->realPosition.x << ", " << this->realPosition.y << endl;
    // cout << "Acceleration: " << this->acceleration.x << ", " << this->acceleration.y << endl;
    // cout << "Velocity: " << this->velocity.x << ", " << this->velocity.y << endl;
}

void RigidBody::Scale(double radiusScale, double positionScale)
{
    this->radius = this->realRadius * radiusScale;

    this->position = Vector2<int>(
        round(this->realPosition.x * positionScale),
        round(this->realPosition.y * positionScale)
    );

    // cout << "Position: " << this->position.x << ", " << this->position.y << endl;
}
