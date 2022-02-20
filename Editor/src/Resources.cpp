#include"Resources.hpp"

Resources::Resources(const Hero::Sid& sid)
    :ISystem(sid)
{

}

Resources::~Resources()
{

}

void Resources::init()
{
    ISystem::init();
}

void Resources::update()
{

}

void Resources::close()
{
    ISystem::close();
}