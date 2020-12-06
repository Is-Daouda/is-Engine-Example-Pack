#pragma once
#include "../../objects/tmxExample/TMXLiteExample.h"

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

		SDMaddSceneObject(std::make_shared<TMXLiteExample>(this)); // add TMX object
    }
};
