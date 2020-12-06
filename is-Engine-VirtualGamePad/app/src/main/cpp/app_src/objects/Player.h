#ifndef PLAYER_H_INCLUDED
#define PLAYER_H_INCLUDED

#include "../../isEngine/system/function/GameKeyData.h"

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
        // We call the GameKeyData object from the scene to use it
        if (auto gameKeyData = static_cast<is::GameKeyData*>(m_scene->SDMgetObject("GameKeyData")); gameKeyData != nullptr)
        {
            int subImage(12); // Represents the number of sub pictures to use for an animation.
                              // It varies depending on the animation to be performed

            float frameSpeed(0.3f); // Allows to change the animation speed
            float moveSpeed(2.f); // Displacement speed of the object

            if (gameKeyData->keyAPressed()) // Speed up the player
            {
                moveSpeed *= 2.f;
                frameSpeed = 1.f;
            }
            if (gameKeyData->keyBPressed()) // Slow down the player
            {
                moveSpeed /= 2.f;
                frameSpeed = 0.1f;
            }

            m_frame += frameSpeed * is::VALUE_CONVERSION * DELTA_TIME; // Animation speed

            if (gameKeyData->keyRightPressed())
            {
                m_frameStart = 0.f; // Represents the first sub-image to be used for animation
                m_strAnimation = "move_right";
                m_x += moveSpeed * is::VALUE_CONVERSION * DELTA_TIME; // Move object to the right
            }
            else if (gameKeyData->keyLeftPressed())
            {
                m_frameStart = getSpriteNumberSubImage(SUB_IMAGE_WIDTH); // Represents the first sub-image to be used for animation
                m_strAnimation = "move_left";
                m_x -= moveSpeed * is::VALUE_CONVERSION * DELTA_TIME; // Move object to the left
            }
            else if (gameKeyData->keyDownPressed())
            {
                subImage = 9; // Number of subpictures to use for animation
                m_frameStart = getSpriteNumberSubImage(SUB_IMAGE_WIDTH) * 2.f; // Represents the first sub-image to be used for animation
                m_strAnimation = "move_down";
                m_y += moveSpeed * is::VALUE_CONVERSION * DELTA_TIME; // Move object to the bottom
            }
            else if (gameKeyData->keyUpPressed())
            {
                subImage = 9; // Number of subpictures to use for animation
                m_frameStart = getSpriteNumberSubImage(SUB_IMAGE_WIDTH) * 3.f; // Represents the first sub-image to be used for animation
                m_strAnimation = "move_up";
                m_y -= moveSpeed * is::VALUE_CONVERSION * DELTA_TIME; // Move object to the top
            }

            // This allows to control the image slice to be used to make an animation
            setFrameLimit(m_frameStart, m_frameStart + subImage);

            // When the user has not taken any action
            if (gameKeyData->m_moveKeyPressed == is::GameKeyData::VirtualKeyIndex::V_KEY_NONE)
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
