#pragma once
#include "../../objects/GameButton.h"

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
        GRMaddTexture("button", is::GameConfig::GUI_DIR + "button.png");
        auto &bg = GRMaddTexture("is_engine_logo", is::GameConfig::SPRITES_DIR + "is_engine_logo.png");
        SDMaddSprite(bg, "is_engine_logo", 320.f, 240.f, true); // We create a sprite

        getGameSystem().m_admobManager->loadBannerAd(); // Launches the request that allows to load banner ads
        getGameSystem().m_admobManager->loadRewardVideo(); // Launches the request that allows to load video reward ads

        getGameSystem().m_admobManager->showBannerAd(); // Displays the banner provided that the request has been successfully executed
        SDMaddSceneObject(std::make_shared<GameButton>(320.f, 300.f, "Show Reward Video", "show_video", this)); // This object allows to launch video reward ads
    }
};
