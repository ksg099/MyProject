#include "pch.h"
#include "InputMgr.h"


std::list<sf::Keyboard::Key> InputMgr::downList;
std::list<sf::Keyboard::Key> InputMgr::upList;
std::list<sf::Keyboard::Key> InputMgr::ingList;

void InputMgr::UpdateEvent(const sf::Event& ev)
{
    switch (ev.type)
    {
    case sf::Event::KeyPressed:
        if (!GetKey(ev.key.code))
        {
            ingList.push_back(ev.key.code);
            downList.push_back(ev.key.code);
        }
        break;
    case sf::Event::KeyReleased:
        ingList.remove(ev.key.code);
        upList.push_back(ev.key.code);
        break;
    }
}

void InputMgr::Clear()
{
    downList.clear();
    upList.clear();
}

bool InputMgr::GetKeyDown(sf::Keyboard::Key key)
{
    //std::list<sf::Keyboard::Key>::iterator it = downList.begin

    //for (auto it = downList.begin(); it != downList.end(); ++it)
    //{
    //    if (*it == key)
    //        return true;
    //}

    //for (auto k : downList)
    //{
    //    if (k == key)
    //        return true;
    //}

    return std::find(downList.begin(), downList.end(), key) != downList.end();
}

bool InputMgr::GetKeyUp(sf::Keyboard::Key key)
{
    return std::find(upList.begin(), upList.end(), key) != upList.end();
}

bool InputMgr::GetKey(sf::Keyboard::Key key)
{
    return std::find(ingList.begin(), ingList.end(), key) != ingList.end();
}

//아무키나 눌렀을때
bool InputMgr::AnyKeyDown()
{
    //눌렀을때가 없을경우의 반대!를 해준다.
    return !downList.empty();
}
