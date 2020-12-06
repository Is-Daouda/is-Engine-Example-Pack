#ifndef LAUNCHTRANSITION_H_INCLUDED
#define LAUNCHTRANSITION_H_INCLUDED

#include "../../isEngine/system/graphic/TransitionEffect.h"
#include "../../isEngine/system/function/GameTime.h"

class LaunchTransition : public is::MainObject
{
public:
    LaunchTransition(is::GameDisplay *scene):
        MainObject(),
        m_scene(scene),
        m_gameTime(0, 3, 0) // We define the time (3 seconds) that will elapse before the end transition starts
    {}

    void step(float const &DELTA_TIME)
    {
        // We start the stopwatch
        m_gameTime.step(DELTA_TIME);

        // We call the Transition object from the scene to use it
        if (auto transition = static_cast<is::TransitionEffect*>(m_scene->SDMgetObject("TransitionEffect")); transition != nullptr)
        {
            // If the stopwatch counter reaches zero (0)
            if (m_gameTime.compareTime(0, 0, 0)) transition->setType(is::TransitionEffect::Transition::FADE_IN); // We launch the end transition

            // At the end of the Fade In transition we restart the scene
            if (transition->getTransitionEnd(is::TransitionEffect::Transition::FADE_IN)) m_scene->quitScene(is::DisplayOption::EXAMPLE_SCENE);
        }
    }

private:
    is::GameDisplay *m_scene;
    is::GameTime m_gameTime; // Allows to use a stopwatch
};

#endif // LAUNCHTRANSITION_H_INCLUDED
