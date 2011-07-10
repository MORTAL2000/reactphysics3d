/********************************************************************************
* ReactPhysics3D physics library, http://code.google.com/p/reactphysics3d/      *
* Copyright (c) 2010 Daniel Chappuis                                            *
*********************************************************************************
*                                                                               *
* Permission is hereby granted, free of charge, to any person obtaining a copy  *
* of this software and associated documentation files (the "Software"), to deal *
* in the Software without restriction, including without limitation the rights  *
* to use, copy, modify, merge, publish, distribute, sublicense, and/or sell     *
* copies of the Software, and to permit persons to whom the Software is         *
* furnished to do so, subject to the following conditions:                      *
*                                                                               *
* The above copyright notice and this permission notice shall be included in    *
* all copies or substantial portions of the Software.                           *
*                                                                               *
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR    *
* IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,      *
* FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE   *
* AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER        *
* LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, *
* OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN     *
* THE SOFTWARE.                                                                 *
********************************************************************************/

#ifndef RIGIDBODY_H
#define RIGIDBODY_H

// Libraries
#include <cassert>
#include "Body.h"
#include "../shapes/Shape.h"
#include "../mathematics/mathematics.h"

// Namespace reactphysics3d
namespace reactphysics3d {

/*  -------------------------------------------------------------------
    Class RigidBody :
        This class represents a rigid body of the physics
        engine. A rigid body is a non-deformable body that
        has a constant mass.
    -------------------------------------------------------------------
*/
class RigidBody : public Body {
    protected :
        Vector3D linearVelocity;                    // Linear velocity of the body
        Vector3D angularVelocity;                   // Angular velocity of the body
        Vector3D externalForce;                     // Current external force on the body
        Vector3D externalTorque;                    // Current external torque on the body
        Matrix3x3 inertiaTensorLocal;               // Local inertia tensor of the body (in body coordinates)
        Matrix3x3 inertiaTensorLocalInverse;        // Inverse of the inertia tensor of the body (in body coordinates)
        double massInverse;                         // Inverse of the mass of the body
        double restitution;                         // Coefficient of restitution (between 0 and 1), 1 for a very boucing body

    public :
        RigidBody(const Transform& transform, double mass,
                  const Matrix3x3& inertiaTensorLocal, Shape* shape);           // Constructor                                                                                                         // Copy-constructor
        virtual ~RigidBody();                                                   // Destructor

        Vector3D getLinearVelocity() const;                                     // Return the linear velocity
        void setLinearVelocity(const Vector3D& linearVelocity);                 // Set the linear velocity of the body
        Vector3D getAngularVelocity() const;                                    // Return the angular velocity
        void setAngularVelocity(const Vector3D& angularVelocity);               // Set the angular velocity
        void setMassInverse(double massInverse);                                // Set the inverse of the mass
        Vector3D getExternalForce() const;                                      // Return the current external force of the body
        void setExternalForce(const Vector3D& force);                           // Set the current external force on the body
        Vector3D getExternalTorque() const;                                     // Return the current external torque of the body
        void setExternalTorque(const Vector3D& torque);                         // Set the current external torque of the body
        double getMassInverse() const;                                          // Return the inverse of the mass of the body
        Matrix3x3 getInertiaTensorLocal() const;                                // Return the local inertia tensor of the body (in body coordinates)
        void setInertiaTensorLocal(const Matrix3x3& inertiaTensorLocal);        // Set the local inertia tensor of the body (in body coordinates)
        Matrix3x3 getInertiaTensorLocalInverse() const;                         // Get the inverse of the inertia tensor
        Matrix3x3 getInertiaTensorWorld() const;                                // Return the inertia tensor in world coordinates
        Matrix3x3 getInertiaTensorInverseWorld() const;                         // Return the inverse of the inertia tensor in world coordinates
        
        double getRestitution() const;                                          // Get the restitution coefficient
        void setRestitution(double restitution) throw(std::invalid_argument);   // Set the restitution coefficient
};

// Return the linear velocity
inline Vector3D RigidBody::getLinearVelocity() const {
    return linearVelocity;
}

// Return the angular velocity of the body
inline Vector3D RigidBody::getAngularVelocity() const {
    return angularVelocity;
}

inline void RigidBody::setAngularVelocity(const Vector3D& angularVelocity) {
     this->angularVelocity = angularVelocity;
}

// Set the inverse of the mass
inline void RigidBody::setMassInverse(double massInverse) {
    this->massInverse = massInverse;
}

// Get the inverse of the inertia tensor
inline Matrix3x3 RigidBody::getInertiaTensorLocalInverse() const {
    return inertiaTensorLocalInverse;
}

// Return the external force on the body
inline Vector3D RigidBody::getExternalForce() const {
    return externalForce;
}

// Set the external force on the body
inline void RigidBody::setExternalForce(const Vector3D& force) {
    this->externalForce = force;
}

// Return the current external torque on the body
inline Vector3D RigidBody::getExternalTorque() const {
    return externalTorque;
}

 // Set the current external torque on the body
inline void RigidBody::setExternalTorque(const Vector3D& torque) {
    this->externalTorque = torque;
}

// Return the inverse of the mass of the body
inline double RigidBody::getMassInverse() const {
    return massInverse;
}

// Return the local inertia tensor of the body (in body coordinates)
inline Matrix3x3 RigidBody::getInertiaTensorLocal() const {
    return inertiaTensorLocal;
}

// Set the local inertia tensor of the body (in body coordinates)
inline void RigidBody::setInertiaTensorLocal(const Matrix3x3& inertiaTensorLocal) {
    this->inertiaTensorLocal = inertiaTensorLocal;
}

// Return the inertia tensor in world coordinates
// The inertia tensor I_w in world coordinates in computed with the local inertia tensor I_b in body coordinates
// by I_w = R * I_b * R^T
// where R is the rotation matrix (and R^T its transpose) of the current orientation quaternion of the body
inline Matrix3x3 RigidBody::getInertiaTensorWorld() const {
    // Compute and return the inertia tensor in world coordinates
    return transform.getOrientation() * inertiaTensorLocal * transform.getOrientation().getTranspose();
}

// Return the inverse of the inertia tensor in world coordinates
// The inertia tensor I_w in world coordinates in computed with the local inverse inertia tensor I_b^-1 in body coordinates
// by I_w = R * I_b^-1 * R^T
// where R is the rotation matrix (and R^T its transpose) of the current orientation quaternion of the body
inline Matrix3x3 RigidBody::getInertiaTensorInverseWorld() const {
    // Compute and return the inertia tensor in world coordinates
    return transform.getOrientation() * inertiaTensorLocalInverse * transform.getOrientation().getTranspose();
}

// Set the linear velocity of the rigid body
inline void RigidBody::setLinearVelocity(const Vector3D& linearVelocity) {
    // If the body is able to move
    if (isMotionEnabled) {
        // Update the linear velocity of the current body state
        this->linearVelocity = linearVelocity;
    }
}

// Get the restitution coeffficient of the rigid body
inline double RigidBody::getRestitution() const {
    return restitution;
}

// Set the restitution coefficient
inline void RigidBody::setRestitution(double restitution) throw(std::invalid_argument) {
    // Check if the restitution coefficient is between 0 and 1
    if (restitution >= 0.0 && restitution <= 1.0) {
        this->restitution = restitution;
    }
    else {
        throw std::invalid_argument("Error : the restitution coefficent must be between 0 and 1");
    }
}


} // End of the ReactPhyscis3D namespace

 #endif
