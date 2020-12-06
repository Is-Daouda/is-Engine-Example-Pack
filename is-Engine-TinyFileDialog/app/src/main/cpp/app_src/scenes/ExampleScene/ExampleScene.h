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

        // Creation of buttons that display dialog boxes to save / load files
        SDMaddSceneObject(std::make_shared<GameButton>((m_viewW / 2.f) - 96.f, (m_viewH / 2.f) - 96.f, "Save File", "save_file", this));
        SDMaddSceneObject(std::make_shared<GameButton>((m_viewW / 2.f) + 96.f, (m_viewH / 2.f) - 96.f, "Load File", "load_file", this));

        // Creation of buttons that display dialog boxes to inform / request
        SDMaddSceneObject(std::make_shared<GameButton>((m_viewW / 2.f) - 192.f, (m_viewH / 2.f), "OK Dialog", "ok_dialog", this));
        SDMaddSceneObject(std::make_shared<GameButton>((m_viewW / 2.f), (m_viewH / 2.f), "YES-NO Dialog", "yesno_dialog", this));
        SDMaddSceneObject(std::make_shared<GameButton>((m_viewW / 2.f) + 192.f, (m_viewH / 2.f), "OK-CANCEL Dialog", "okcancel_dialog", this));

        // Creation of the button that display dialog boxes to open a folder
        SDMaddSceneObject(std::make_shared<GameButton>((m_viewW / 2.f), (m_viewH / 2.f) + 96.f, "Folder Dialog", "folder", this));
    }
};
