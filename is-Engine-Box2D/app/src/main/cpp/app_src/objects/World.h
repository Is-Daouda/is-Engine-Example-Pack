#ifndef WORLD_H_INCLUDED
#define WORLD_H_INCLUDED

#include "../../isEngine/ext_lib/Box2D/Box2D.h"
#include "../../isEngine/system/display/GameDisplay.h"
#include "Box.h"

class World : public is::MainObject
{
public:
    /** Prepare the world */
    b2Vec2 m_gravity;
    b2World m_world;

    World(is::GameDisplay *scene):
        MainObject(),
        m_gravity(0.f, 9.8f),
        m_world(m_gravity),
        m_scene(scene)
    {}

    void step(float const &DELTA_TIME)
    {
        /** When the user left-mouse-click, add a box into the world */
        if (m_scene->getGameSystem().isPressed(is::GameSystem::MOUSE))
        {
            sf::Vector2f pos = m_scene->getCursor();
            m_scene->SDMaddSceneObject(std::make_shared<Box>(pos.x, pos.y, m_world, m_scene)); // add Box object in the scene
        }

        /** Simulate the world */
        m_world.Step(1 / 60.f, 8, 3);
    }

private:
    is::GameDisplay *m_scene;
};

#endif // WORLD_H_INCLUDED
