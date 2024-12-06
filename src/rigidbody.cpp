#include <rigidbody.hpp>
#include <gameObject.hpp>

// Static methods
void RigidBody::CalcGravityAttraction(RigidBody *a, RigidBody *b) {
    
    double distance = Vector2<>::GetDistance(a->position, b->position);
    double dx = b->position.x - a->position.x;
    double dy = b->position.y - a->position.y;

    if (distance == 0) return;

    // Gravitational force
    int force = GRAVITIONAL_CONSTANT * a->mass * b->mass / distance;

    double fx = force * dx / distance;
    double fy = force * dy / distance;

    // Update acceleration of the bodies
    a->acceleration.x += fx / a->mass;
    a->acceleration.y += fy / a->mass;

    b->acceleration.x -= fx / b->mass;
    b->acceleration.y -= fy / b->mass;
}

// Instance methods
RigidBody::RigidBody(string name, Vector2<> position, Vector2<> size, double mass) {
    this->name = name;
    this->position = position;
    this->size = size;
    this->mass = mass;
}

double RigidBody::GetMass() const {
    return this->mass;
}

void RigidBody::SetMass(double mass) {
    this->mass = mass;
}

Vector2<> RigidBody::GetVelocity() const {
    return this->velocity;
}

void RigidBody::SetVelocity(Vector2<> velocity) {
    this->velocity = velocity;
}

Vector2<> RigidBody::GetAcceleration() const {
    return this->acceleration;
}

void RigidBody::SetAcceleration(Vector2<> acceleration) {
    this->acceleration = acceleration;
}

void RigidBody::UpdateBody(double dt) {
    this->velocity.x += this->acceleration.x * dt;
    this->velocity.y += this->acceleration.y * dt;

    this->position.x += this->velocity.x * dt;
    this->position.y += this->velocity.y * dt;

    this->acceleration = Vector2<double>::zero;
}