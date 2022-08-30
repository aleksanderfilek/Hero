#include"Player.hpp"

// #include"../Hero/Core/Math.hpp"
// #include"../Hero/Components/Actor.hpp"
// #include"../Hero/Core/Time.hpp"
// #include"../Hero/Core/Core.hpp"
// #include"../Hero/ThirdParty/SDL2/SDL.h"
// #include"../Hero/Components/Transform.hpp"
// #include"../Hero/Systems/Input.hpp"

// #include<iostream>

// #define SPEED 50.0f

// void Player::dataInit(PlayerData* data)
// {
//     data->transform = (Hero::TransformData*)data->actor->GetComponent(SID("Transform"));
//     data->input = Hero::Core::getSystem<Hero::System::Input>(SID("input"));
// }

// void Player::dataUpdate(PlayerData* data)
// {
//   if(data->input->keyDown(Hero::System::Input::KeyCode::ESCAPE))
//   {
//     SDL_SetRelativeMouseMode((SDL_GetRelativeMouseMode() == SDL_TRUE)?SDL_FALSE:SDL_TRUE);
//   }

//     int x=0, y=0;
//     SDL_GetRelativeMouseState(&x, &y);
//     //input->getMousePosition(&x, &y);

//     float xpos = (float)x;
//     float ypos = (float)y;

//     float xoffset = xpos/320.0f;
//     float yoffset = ypos/240.0f; // reversed since y-coordinates go from bottom to top

//     float sensitivity = 10.0f; // change this value to your liking
//     xoffset *= sensitivity;
//     yoffset *= sensitivity;

//     data->yaw += xoffset;
//     data->pitch += yoffset;

//     // make sure that when pitch is out of bounds, screen doesn't get flipped
//     if (data->pitch > 89.0f)
//         data->pitch = 89.0f;
//     if (data->pitch < -89.0f)
//         data->pitch = -89.0f;

//     data->transform->setRotation({
//         Hero::deg2rad(data->pitch),
//         Hero::deg2rad(data->yaw),
//         0.0f}
//         );

//     Hero::Float3 forward = data->transform->forward();
//     Hero::Float3 right = data->transform->right();
//     Hero::Float3 up = data->transform->up();

//     Hero::Float3 newPosition = data->transform->getLocalPosition();

//     if(data->input->keyPressed(Hero::System::Input::KeyCode::W))
//     {
//         newPosition += forward * SPEED * Hero::Time::getDeltaTime();
//     }
//     else if(data->input->keyPressed(Hero::System::Input::KeyCode::S))
//     {
//         newPosition -= forward * SPEED * Hero::Time::getDeltaTime();
//     }

//     if(data->input->keyPressed(Hero::System::Input::KeyCode::A))
//     {
//         newPosition -= right * SPEED * Hero::Time::getDeltaTime();
//     }
//     else if(data->input->keyPressed(Hero::System::Input::KeyCode::D))
//     {
//         newPosition += right * SPEED * Hero::Time::getDeltaTime();    
//     }

//     if(data->input->keyPressed(Hero::System::Input::KeyCode::SPACE))
//     {
//         newPosition += up * SPEED * Hero::Time::getDeltaTime();
//     }
//     else if(data->input->keyPressed(Hero::System::Input::KeyCode::LCTRL))
//     {
//         newPosition -= up * SPEED * Hero::Time::getDeltaTime();
//     }


//     data->transform->setPosition(newPosition);
// }

// void Player::dataDestroy(PlayerData* data)
// {

// }