#include "Engine/ScreenManager.h"
#include "MarioLike.h"
#include <GL/glew.h>
#include <iostream>

int main()
{
    srand(time(NULL));

    sf::ContextSettings settings;
    settings.depthBits = 24;
    settings.stencilBits = 8;

#ifdef DEBUG
    sf::RenderWindow window(sf::VideoMode(800, 600), "Debug", sf::Style::Close, settings);
#else
//    sf::RenderWindow window(sf::VideoMode(800, 600), "Debug", sf::Style::Close, settings);
    sf::RenderWindow window(sf::VideoMode::getDesktopMode(), "", sf::Style::Fullscreen, settings);
    window.setMouseCursorVisible(false);
#endif // DEBUG
    window.setVerticalSyncEnabled(true);

#ifdef DEBUG
    std::cout << "depth bits:" << window.getSettings().depthBits << std::endl;
    std::cout << "stencil bits:" << window.getSettings().stencilBits << std::endl;
    std::cout << "antialiasing level:" << window.getSettings().antialiasingLevel << std::endl;
    std::cout << "version:" << window.getSettings().majorVersion << "." << window.getSettings().minorVersion << std::endl;
#endif // DEBUG

    glewExperimental = GL_TRUE;
    GLenum err = glewInit();
    if (GLEW_OK != err)
    {
#ifdef DEBUG
        std::cerr << "Error: " << glewGetErrorString(err) << std::endl;
#endif // DEBUG
        return 1;
    }
    if (!GLEW_VERSION_2_1)
    {
#ifdef DEBUG
        std::cerr << "Error: your graphic card does not support OpenGL 2.1" << std::endl;
#endif // DEBUG
        return 1;
    }

    ScreenManager::getInstance().initialize(new MarioLike);
    ScreenManager::getInstance().loadContent(window);

    sf::Clock clock;

    bool running = true;
    while (running)
    {
//        float elapsedTime = clock.getElapsedTime().asSeconds();
        float elapsedTime = clock.restart().asSeconds();

        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                running = false;

            if ((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::Escape))
                running = false;

            ScreenManager::getInstance().update(event, elapsedTime);
        }

        ScreenManager::getInstance().update(window, elapsedTime);

        ScreenManager::getInstance().draw(window);

        window.display();
    }

    return 0;
}
