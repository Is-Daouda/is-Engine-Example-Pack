#pragma once
#include "../../objects/LaunchTransition.h"

class ExampleScene : public is::GameDisplay
{
public:
    ExampleScene(sf::RenderWindow &window, sf::View &view, is::Render &surface, is::GameSystemExtended &gameSysExt):
        GameDisplay(window, view, surface, gameSysExt, sf::Color(0, 128, 255) /* => scene color*/)
    {}

    void loadResources()
    {
        // load font and texture
        GameDisplay::loadParentResources(); // allows to load system resource (very important never forgot to call him)
        auto &bg = GRMaddTexture("is_engine_logo", is::GameConfig::SPRITES_DIR + "is_engine_logo.png");
        SDMaddSprite(bg, "is_engine_logo", 320.f, 240.f, true); // We create a sprite

        // We create the object that is used to make the Fade Out / Fade In transition.
        // /!\ Warning /!\ The Fade Out transition is started when the object is created
        SDMaddSceneObject(std::make_shared<is::TransitionEffect>(this));

        SDMaddSceneObject(std::make_shared<LaunchTransition>(this)); // This object starts the end transition after 3 seconds
                                                                     // and relaunches the scene
    }
};
