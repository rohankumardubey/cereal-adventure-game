#include "../include/shelves.h"

#include "../include/world.h"

dbasic::ModelAsset *c_adv::Shelves::m_shelvesAsset = nullptr;

c_adv::Shelves::Shelves() {
    /* void */
}

c_adv::Shelves::~Shelves() {
    /* void */
}

void c_adv::Shelves::initialize() {
    GameObject::initialize();

    RigidBody.SetHint(dphysics::RigidBody::RigidBodyHint::Dynamic);
    RigidBody.SetInverseMass(0.0f);

    dphysics::CollisionObject *bounds;
    RigidBody.CollisionGeometry.NewBoxObject(&bounds);
    bounds->SetMode(dphysics::CollisionObject::Mode::Fine);
    bounds->GetAsBox()->HalfHeight = 2.0f;
    bounds->GetAsBox()->HalfWidth = 1.0f;
    bounds->GetAsBox()->Orientation = ysMath::Constants::QuatIdentity;
    bounds->GetAsBox()->Position = ysMath::Constants::Zero;
}

void c_adv::Shelves::render() {
    m_world->getEngine().SetObjectTransform(RigidBody.Transform.GetWorldTransform());
    m_world->getEngine().SetMultiplyColor(ysVector4(1.0f, 1.0f, 1.0f, 1.0f));
    m_world->getEngine().DrawModel(m_shelvesAsset, RigidBody.Transform.GetWorldTransform(), 1.0f, nullptr);
}

void c_adv::Shelves::process() {
    GameObject::process();
}

void c_adv::Shelves::configureAssets(dbasic::AssetManager *am) {
    m_shelvesAsset = am->GetModelAsset("Shelves");
}