#include "isEngine/core/GameEngine.h"

namespace is
{
bool GameEngine::basicSFMLmain()
{
////////////////////////////////////////////////////////////
//                    WINDOW CREATION
////////////////////////////////////////////////////////////
#if defined(__ANDROID__)
    m_window.create(sf::VideoMode::getDesktopMode(), "");

#if defined(IS_ENGINE_USE_ADMOB)
    ANativeActivity* activity = sf::getNativeActivity();
    JNIEnv* env = activity->env;
    JavaVM* vm = activity->vm;
    vm->AttachCurrentThread(&env, NULL);

    m_gameSysExt.m_admobManager = std::make_shared<AdmobManager>(m_window, activity, env, vm);
    m_gameSysExt.m_admobManager->checkAdObjInit();
#endif // definded
#else
    #if !defined(IS_ENGINE_HTML_5)
    m_window.create(sf::VideoMode(is::GameConfig::WINDOW_WIDTH,
                                  is::GameConfig::WINDOW_HEIGHT),
                                  is::GameConfig::GAME_NAME,
                                  is::getWindowStyle());

    // load application icon
    sf::Image iconTex;
    if (!iconTex.loadFromFile(is::GameConfig::GUI_DIR + "icon.png")) return false;
    m_window.setIcon(32, 32, iconTex.getPixelsPtr());
    #else // using the SFML library (Web development)
    m_window = sf::RenderWindow(is::GameConfig::WINDOW_WIDTH, is::GameConfig::WINDOW_HEIGHT, is::GameConfig::GAME_NAME);
    #endif // defined
#endif // defined
    setFPS(m_window, is::GameConfig::FPS); // set frames per second (FPS)
    sf::View m_view(sf::Vector2f(is::GameConfig::VIEW_WIDTH / 2.f, is::GameConfig::VIEW_HEIGHT / 2.f), sf::Vector2f(is::GameConfig::VIEW_WIDTH, is::GameConfig::VIEW_HEIGHT));
    m_window.setView(m_view);

////////////////////////////////////////////////////////////
//                    INITIALIZATION
////////////////////////////////////////////////////////////

    sf::Font font;
    is::loadSFMLFont(font, is::GameConfig::FONT_DIR + "font_system.ttf");

    sf::Text text;
    is::createText(font, text, "is::Engine Admob", 320.f, 240.f, sf::Color::White, true);

    m_gameSysExt.m_admobManager->loadBannerAd(); // Launches the request that allows to load banner ads
    m_gameSysExt.m_admobManager->loadRewardVideo(); // Launches the request that allows to load video reward ads

    sf::Clock clock;
    float time(0.f); // Millisecond counter
    bool showAd = false; // Allows to display the ad only once (avoid repetition)

////////////////////////////////////////////////////////////
//                    RENDER LOOP                         //
////////////////////////////////////////////////////////////
// This starts the render loop.                           //
// Don't touch unless you know what you're doing.         //
    #if !defined(IS_ENGINE_HTML_5)                        //
    while (m_window.isOpen())                             //
    #else                                                 //
    m_window.ExecuteMainLoop([&]                          //
    #endif                                                //
    {                                                     //
////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////
//                       EVENT
////////////////////////////////////////////////////////////

        ////////////////////////////////////////////////////////////
        //                       SFML
        ////////////////////////////////////////////////////////////
        #if !defined(IS_ENGINE_HTML_5) // using the SFML library
        sf::Event event;
        while (m_window.pollEvent(event))
        {
            switch (event.type)
            {
                case sf::Event::Closed:
                    m_window.close();
                break;

                default: break;
            }
        }

        ////////////////////////////////////////////////////////////
        //                 SMK (Web Development)
        ////////////////////////////////////////////////////////////
        #else
        m_window.PoolEvents(); // Allows to update events
        #endif // defined

////////////////////////////////////////////////////////////
//                    UPDATE OBJECTS
////////////////////////////////////////////////////////////
        float deltaTime = clock.restart().asSeconds();
        time += is::getMSecond(deltaTime);

        // We wait a few seconds for the request to load properly before displaying an ad.
        // This helps to avoid errors because not all users have a fast internet connection!
        // You can change the number of seconds to make the ad appear faster.
        if (time > 4.f * is::SECOND)
        {
            if (!showAd)
            {
                m_gameSysExt.m_admobManager->showRewardVideo();
                showAd = true;
            }
        }

        m_gameSysExt.m_admobManager->showBannerAd();

////////////////////////////////////////////////////////////
//                     DRAW OBJECTS
////////////////////////////////////////////////////////////

        // Clear the window
        m_window.clear(sf::Color::Blue);
        m_window.draw(text);
        m_window.display();
    }

////////////////////////////////////////////////////////////
// Don't touch unless you know what you're doing.         //
    #if defined(IS_ENGINE_HTML_5)                         //
    );                                                    //
    #endif                                                //
////////////////////////////////////////////////////////////
    return true;
}
}
