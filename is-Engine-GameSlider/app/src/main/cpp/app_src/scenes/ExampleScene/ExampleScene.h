#pragma once
#include "../../objects/Player.h"

class ExampleScene : public is::GameDisplay
{
public:
    ExampleScene(sf::RenderWindow &window, sf::View &view, is::Render &surface, is::GameSystemExtended &gameSysExt):
        GameDisplay(window, view, surface, gameSysExt, sf::Color::Black /* => scene color*/)
    {}

    void loadResources()
    {
        // load font and texture
        GameDisplay::loadParentResources(); // allows to load system resource (very important never forgot to call him)
        GRMaddTexture("player", is::GameConfig::SPRITES_DIR + "player.png");
        auto &bg = GRMaddTexture("background", is::GameConfig::SPRITES_DIR + "background.png");

        SDMaddSprite(bg, "background", 0.f, 0.f, false, 1); // We create a sprite for the background

        SDMaddSceneObject(std::make_shared<is::GameSlider>(this)); // We add the object that allows to control the game with slides
        SDMaddSceneObject(std::make_shared<Player>(m_viewW / 2.f, m_viewH / 2.f, this)); // We add the player
    }
};
