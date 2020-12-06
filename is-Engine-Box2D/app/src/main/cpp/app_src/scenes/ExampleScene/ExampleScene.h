#pragma once
#include "../../objects/World.h"
#include "../../objects/Ground.h"

class ExampleScene : public is::GameDisplay
{
public:
    ExampleScene(sf::RenderWindow &window, sf::View &view, is::Render &surface, is::GameSystemExtended &gameSysExt):
        GameDisplay(window, view, surface, gameSysExt, sf::Color::White /* => scene color*/)
    {}

    void loadResources()
    {
        // load font and texture
        GameDisplay::loadParentResources(); // allows to load system resource (very important never forgot to call him)
        GRMaddTexture("box", is::GameConfig::SPRITES_DIR + "box.png");
        GRMaddTexture("ground", is::GameConfig::SPRITES_DIR + "ground.png");

        // add an Box 2D world object
        auto worldObj = std::make_shared<World>(this);
        SDMaddSceneObject(worldObj);

        // add an Box 2D ground object at position x = 400, y = 500
        SDMaddSceneObject(std::make_shared<Ground>(400.f, 500.f, worldObj->m_world, this));
    }
};
