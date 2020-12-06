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
        // The texture of the Virtual Game Pad is loaded in its class

        SDMaddSprite(bg, "background", 0.f, 0.f, false, 1); // We create a sprite for the background

        //////////////////////////////////////////////////////
        // These data are used to configure the Virtual Game Pad
        // You can modify them if you wish
        //////////////////////////////////////////////////////
        // Position of directional keys (UP, DOWN, LEFT, RIGHT)
        getGameSystem().m_padDirXPos = -250.f;
        getGameSystem().m_padDirYPos = 170.f;

        // Position of keys A and B
        getGameSystem().m_padActionXPos = 245.f;
        getGameSystem().m_padActionYPos = 200.f;

        // Swap keys A and B
        getGameSystem().m_permutePadAB = false;

        // Transparency of the Virtual Game Pad
        getGameSystem().m_padAlpha = 255;
        //////////////////////////////////////////////////////

        SDMaddSceneObject(std::make_shared<is::GameKeyData>(this)); // We add the object that allows to control the game with virtual key
        SDMaddSceneObject(std::make_shared<Player>(m_viewW / 2.f, m_viewH / 2.f, this)); // We add the player
    }
};
