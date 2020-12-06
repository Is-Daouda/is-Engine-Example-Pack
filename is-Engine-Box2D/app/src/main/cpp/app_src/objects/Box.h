#ifndef BOX_H_INCLUDED
#define BOX_H_INCLUDED

#include "../../isEngine/ext_lib/Box2D/Box2D.h"
#include "../../isEngine/system/display/GameDisplay.h"

class Box : public is::MainObject
{
public:
    float const SCALE = 30.f; /** We need this to easily convert between pixel and real-world coordinates*/
    b2BodyDef m_bodyDef;
    b2PolygonShape m_shape;
    b2FixtureDef m_fixtureDef;
    b2Body* m_body;

    Box(float x, float y, b2World& world, is::GameDisplay *scene):
        MainObject(x, y)
    {
        // We define the parameters to create the Box2d physical object
        m_bodyDef.position = b2Vec2(x / SCALE, y / SCALE);
        m_bodyDef.type = b2_dynamicBody;
        m_body = world.CreateBody(&m_bodyDef);

        m_shape.SetAsBox((32.f / 2) / SCALE, (32.f / 2) / SCALE);

        m_fixtureDef.density = 1.f;
        m_fixtureDef.friction = 0.7f;
        m_fixtureDef.shape = &m_shape;
        m_body->CreateFixture(&m_fixtureDef);

        // Define the parameters of the object sprite
        is::createSprite(scene->GRMgetTexture("box"), m_sprParent, sf::Vector2f(0.f, 0.f), sf::Vector2f(16.f, 16.f));
    }

    void step(float const &DELTA_TIME)
    {
        // Update the sprite with Box 2D data
        updateSprite(SCALE * m_body->GetPosition().x, SCALE * m_body->GetPosition().y, m_body->GetAngle() * 180 / b2_pi, 255, 1.f, 1.f, 0.f, 0.f);
    }
};

#endif // BOX_H_INCLUDED
