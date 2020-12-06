/*********************************************************************
(c) Matt Marchant & contributors 2016 - 2019
http://trederia.blogspot.com

tmxlite - Zlib license.

This software is provided 'as-is', without any express or
implied warranty. In no event will the authors be held
liable for any damages arising from the use of this software.

Permission is granted to anyone to use this software for any purpose,
including commercial applications, and to alter it and redistribute
it freely, subject to the following restrictions:

1. The origin of this software must not be misrepresented;
you must not claim that you wrote the original software.
If you use this software in a product, an acknowledgment
in the product documentation would be appreciated but
is not required.

2. Altered source versions must be plainly marked as such,
and must not be misrepresented as being the original software.

3. This notice may not be removed or altered from any
source distribution.
*********************************************************************/

#pragma once

#include "../../../isEngine/system/display/GameDisplay.h"
#include "../../../isEngine/ext_lib/TMXLite/Map.hpp"
#include "SFMLOrthogonalLayer.hpp"

class TMXLiteExample : public is::MainObject
{
public:
    tmx::Map map;
    std::shared_ptr<MapLayer> layerZero;
    std::shared_ptr<MapLayer> layerOne;
    std::shared_ptr<MapLayer> layerTwo;
    sf::Clock globalClock;

    TMXLiteExample(is::GameDisplay *scene):
        MainObject(),
        m_scene(scene)
    {
        m_scene->setWindowSize(sf::Vector2u(800, 600), true);
        map.load(is::GameConfig::TMX_RSC_DIR + "demo.tmx");
        layerZero = std::make_shared<MapLayer>(map, 0);
        layerOne  = std::make_shared<MapLayer>(map, 1);
        layerTwo  = std::make_shared<MapLayer>(map, 2);
    }

    void step(float const &DELTA_TIME)
    {
        sf::Time duration = globalClock.restart();
        layerZero->update(duration);
    }

	void draw(is::Render &surface)
    {
        surface.draw(*layerZero);
        surface.draw(*layerOne);
        surface.draw(*layerTwo);
    }

private:
    is::GameDisplay *m_scene;
};
