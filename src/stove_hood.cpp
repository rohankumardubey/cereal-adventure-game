#include "../include/stove_hood.h"

#include "../include/world.h"
#include "../include/colors.h"

dbasic::ModelAsset *c_adv::StoveHood::m_stoveHoodAsset = nullptr;

c_adv::StoveHood::StoveHood() {
    m_clock.setLowTime(10.0f);
    m_clock.setHighTime(10.0f);

    m_currentPower = 0.0f;
    m_maxPower = 25.0f;
}

c_adv::StoveHood::~StoveHood() {
    /* void */
}

void c_adv::StoveHood::initialize() {
    GameObject::initialize();

    RigidBody.SetHint(dphysics::RigidBody::RigidBodyHint::Dynamic);
    RigidBody.SetInverseMass(0.0f);
    RigidBody.SetAlwaysAwake(true);
    RigidBody.SetRequestsInformation(true);

    dphysics::CollisionObject *bounds;
    RigidBody.CollisionGeometry.NewCircleObject(&bounds);
    bounds->SetMode(dphysics::CollisionObject::Mode::Sensor);
    bounds->GetAsCircle()->Radius = 4.0f;
    bounds->GetAsCircle()->Position = ysMath::Constants::Zero;
    bounds->SetRelativePosition(ysMath::LoadVector(0.0f, -10.0f, 0.0f));

    RigidBody.CollisionGeometry.NewBoxObject(&bounds);
    bounds->SetMode(dphysics::CollisionObject::Mode::Fine);
    bounds->GetAsBox()->HalfWidth = 1.0f;
    bounds->GetAsBox()->HalfHeight = 31.2f / 2.0f;
    bounds->SetRelativePosition(ysMath::LoadVector(0.0f, 15.381f, 0.0f));
}

void c_adv::StoveHood::render() {
    m_world->getShaders().ResetBrdfParameters();

    ysVector color = ysMath::Lerp(ObjectColor, DebugRed, m_currentPower / m_maxPower);
    m_world->getShaders().SetBaseColor(color);

    m_world->getShaders().SetObjectTransform(RigidBody.Transform.GetWorldTransform());
    m_world->getShaders().ConfigureModel(1.0f, m_stoveHoodAsset);
    m_world->getEngine().DrawModel(m_world->getShaders().GetRegularFlags(), m_stoveHoodAsset);
}

void c_adv::StoveHood::process(float dt) {
    GameObject::process(dt);

    m_clock.update(dt);

    if (m_clock.getState()) {
        m_currentPower += dt * 7.0f;
        m_currentPower = min(m_currentPower, m_maxPower);
    }
    else {
        m_currentPower -= dt * 15.0f;
        m_currentPower = max(m_currentPower, 0.0f);
    }

    const int collisionCount = RigidBody.GetCollisionCount();
    for (int i = 0; i < collisionCount; ++i) {
        dphysics::Collision *col = RigidBody.GetCollision(i);

        if (col->m_sensor) {
            GameObject *obj = getCollidingObject(col);

            float obj_x = ysMath::GetX(obj->RigidBody.Transform.GetWorldPosition());
            float hood_x = ysMath::GetX(RigidBody.Transform.GetWorldPosition());

            if (std::abs(obj_x - hood_x) < 1.5f) {
                if (!obj->hasTag(GameObject::Tag::Dynamic)) continue;
                if (ysMath::GetY(obj->RigidBody.GetVelocity()) > 7.5f) continue;

                obj->RigidBody.AddForceLocalSpace(
                    ysMath::LoadVector(0.0f, m_currentPower, 0.0f), ysMath::Constants::Zero);
            }
        }
    }
}

void c_adv::StoveHood::getAssets(dbasic::AssetManager *am) {
    m_stoveHoodAsset = am->GetModelAsset("StoveHood");
}
