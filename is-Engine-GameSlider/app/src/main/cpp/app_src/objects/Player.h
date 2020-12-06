#ifndef PLAYER_H_INCLUDED
#define PLAYER_H_INCLUDED

#include "../../isEngine/system/function/GameSlider.h"

class Player :  public is::MainObject
{
public:
    Player(float x, float y, is::GameDisplay *scene):
        MainObject(x, y),
        m_scene(scene),
        SUB_IMAGE_WIDTH(48) // Represents the size of a sub-image
    {
        // We define the properties of the object's sprite
        is::createSprite(scene->GRMgetTexture("player"), m_sprParent, sf::Vector2f(m_x, m_y), sf::Vector2f(0.f, 0.f));
    }

    void step(float const &DELTA_TIME)
    {
        // We call the GameSlider object from the scene to use it
        if (auto gameSlider = static_cast<is::GameSlider*>(m_scene->SDMgetObject("GameSlider")); gameSlider != nullptr)
        {
            int subImage(12); // Represents the number of sub pictures to use for an animation.
                              // It varies depending on the animation to be performed
            m_frame += 0.3f * is::VALUE_CONVERSION * DELTA_TIME; // Animation speed

            switch (gameSlider->getSlideDirection()) // Allows to know the action that the user has performed
            {
                case is::GameSlider::SlideDirection::SLIDE_RIGHT: // Slide right
                    m_frameStart = 0.f; // Represents the first sub-image to be used for animation
                    m_strAnimation = "move_right";
                    m_x += 2.f * is::VALUE_CONVERSION * DELTA_TIME; // Move object 2 pixels to the right
                break;

                case is::GameSlider::SlideDirection::SLIDE_LEFT:  // Slide left
                    m_frameStart = getSpriteNumberSubImage(SUB_IMAGE_WIDTH); // Represents the first sub-image to be used for animation
                    m_strAnimation = "move_left";
                    m_x -= 2.f * is::VALUE_CONVERSION * DELTA_TIME; // Move object 2 pixels to the left
                break;

                case is::GameSlider::SlideDirection::SLIDE_DOWN:  // Slide down
                    subImage = 9; // Number of subpictures to use for animation
                    m_frameStart = getSpriteNumberSubImage(SUB_IMAGE_WIDTH) * 2.f; // Represents the first sub-image to be used for animation
                    m_strAnimation = "move_down";
                    m_y += 2.f * is::VALUE_CONVERSION * DELTA_TIME; // Move object 2 pixels to the bottom
                break;

                case is::GameSlider::SlideDirection::SLIDE_UP:  // Slide up
                    subImage = 9; // Number of subpictures to use for animation
                    m_frameStart = getSpriteNumberSubImage(SUB_IMAGE_WIDTH) * 3.f; // Represents the first sub-image to be used for animation
                    m_strAnimation = "move_up";
                    m_y -= 2.f * is::VALUE_CONVERSION * DELTA_TIME; // Move object 2 pixels to the top
                break;

                default: break;
            }

            // This allows to control the image slice to be used to make an animation
            setFrameLimit(m_frameStart, m_frameStart + subImage);

            // When the user has not taken any action
            if (gameSlider->getSlideDirection() == is::GameSlider::SlideDirection::SLIDE_NONE)
            {
                if (m_strAnimation == "move_left") m_frame = getSpriteNumberSubImage(SUB_IMAGE_WIDTH);
                else if (m_strAnimation == "move_down") m_frame = getSpriteNumberSubImage(SUB_IMAGE_WIDTH) * 2.f;
                else if (m_strAnimation == "move_up") m_frame = getSpriteNumberSubImage(SUB_IMAGE_WIDTH) * 3.f;
                else m_frame = 0.f;
            }
        }

        // This allows to define the sub-picture to use to make the animation
        is::setFrame(m_sprParent, m_frame, getSpriteNumberSubImage(SUB_IMAGE_WIDTH), SUB_IMAGE_WIDTH);
        updateSprite();
    }

private:
    is::GameDisplay *m_scene;
    std::string m_strAnimation; // Allows to determine the sub-image to use to make an animation when the player is not moving
    int const SUB_IMAGE_WIDTH;
};

#endif // PLAYER_H_INCLUDED
