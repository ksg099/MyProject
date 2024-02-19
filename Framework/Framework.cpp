#include "pch.h"
#include "Framework.h"

void Framework::Init(int width, int height, const std::string& name)
{
    bgm.openFromFile("sound/bgm.wav");
    bgm.setLoop(true);
    bgm.setVolume(25);
    //bgm.play();
    srand(std::time(NULL));

    windowSize.x = width;
    windowSize.y = height;

    window.create(sf::VideoMode(windowSize.x, windowSize.y), name);
    sf::View viewReset({ (float)windowSize.x * 0.5f, (float)windowSize.y * 0.5f }, { (float)windowSize.x, (float)windowSize.y });
    viewReset.setViewport({ 0.f, 0.f, 1.f, 1.f });
    window.setView(sf::View({ 0.f, 0.f, (float)width, (float)height }));
    SCENE_MGR.Init();
}

void Framework::Do()
{
    while (window.isOpen())
    {
        deltaTime = realDeltaTime = clock.restart();
        deltaTime *= timeScale;

        time += deltaTime;
        realTime += realDeltaTime;

        InputMgr::Clear();
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();

            InputMgr::UpdateEvent(event);
        }

        SCENE_MGR.Update(GetDT());
        window.clear();
        SCENE_MGR.Draw(window);
        window.display();
    }
}

void Framework::Release()
{
    SCENE_MGR.Release();
}
