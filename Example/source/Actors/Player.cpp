#include "Player.hpp"

#include<iostream>

Player::Player(const Hero::Sid& NewId) : Hero::Actor(NewId)
{
  
}

void Player::Start()
{
  std::cout<<"player start"<<std::endl;
}

void Player::Update()
{
  std::cout<<"player update"<<std::endl;
}

void Player::End()
{
  std::cout<<"player end"<<std::endl;
}