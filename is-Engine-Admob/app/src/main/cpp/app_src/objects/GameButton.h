#ifndef GAMEBUTTON_H_INCLUDED
#define GAMEBUTTON_H_INCLUDED

#include "../../isEngine/system/entity/Button.h"

class GameButton : public is::Button
{
public:
    GameButton(float x, float y, std::string const &title, std::string const &name, is::GameDisplay *scene):
        Button(scene->GRMgetTexture("button"), x, y, title, name, true, scene) {}

    void onClick()
    {
        // We wait a few seconds for the request to load properly before displaying an ad.
        // This helps to avoid errors because not all users have a fast internet connection!
        // You can change the number of seconds to make the ad appear faster.
        m_scene->showTempLoading(3.f * is::SECOND);

        int answer = m_scene->getGameSystem().m_admobManager->showRewardVideo(); // Return 1 when the video has been loaded and 0 otherwise
        if (answer) m_scene->showMessageBox("Reward video has been loaded!\n"
                                            "As a reward you deserved\n"
                                            "applause!", false);
        else m_scene->showMessageBox("Cannot load video rewards!\n"
                                     "Maybe the internet connection is\n"
                                     "not working.", false);
    }
};

#endif // GAMEBUTTON_H_INCLUDED
