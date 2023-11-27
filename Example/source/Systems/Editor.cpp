#include "Editor.hpp"
#include "../Hero/Core/Core.hpp"
#include "../Hero/Systems/ActorScene/Scene.hpp"
#include "../Hero/Actors/Systems/ForwardRenderer.hpp"
#include "MainEditorWidget.hpp"
#include "../Hero/Systems/Resources.hpp"
#include "../Hero/Graphics/Shader.hpp"
#include "../Hero/Core/Math.hpp"
#include "../Actors/Cliff.hpp"

#include <iostream>

#define ROT_SPEED 5.0f
#define Move_SPEED 5.0f

Editor::Editor(const Hero::Sid& sid) : Hero::ISystem(sid)
{

}

Editor::~Editor()
{

}

void Editor::init()
{
    Hero::ISystem::init();

    input = Hero::Core::getSystem<Hero::System::Input>(SID("input"));
    sceneSystem = Hero::Core::getSystem<Hero::SceneSystem>(SID("scene"));
    ui = Hero::Core::getSystem<Hero::System::UserInterface>(SID("ui"));

    Hero::Resources* resources = Hero::Core::getSystem<Hero::Resources>(SID("resources"));
    resources->Add(SID("uiShader"), "bin/assets/spritebatch.he");

    ui->setShader((Hero::Shader*)resources->Get(SID("uiShader")));
    editorWidget = new MainEditorWidget();
    editorWidget->setVisibility(false);
    ui->add("main", editorWidget);
}

void Editor::update()
{
    Hero::ISystem::update();

    if(input->keyDown(Hero::System::Input::KeyCode::F1))
    {
        ((Hero::ForwardRenderer*)sceneSystem->GetCurrentScene()->GetActor(SID("Renderer")))->SetCurrentVisibleBuffer(0);
    }

    if(input->keyDown(Hero::System::Input::KeyCode::F2))
    {
        ((Hero::ForwardRenderer*)sceneSystem->GetCurrentScene()->GetActor(SID("Renderer")))->SetCurrentVisibleBuffer(1);
    }

    if(input->keyDown(Hero::System::Input::KeyCode::F12))
    {
        active = !active;
        editorWidget->setVisibility(active);
    }

    if(!active)
    {
        return;
    }

    if(input->mouseButtonDown(Hero::System::Input::Mouse::Left))
    {
        Hero::Int2 position = input->getMousePosition();
        position.y = 720 - position.y;
        Hero::Actor* selected = sceneSystem->GetCurrentScene()->GetActorUnderCursor(position);
        if(selected)
        {
            std::cout<<"Selected: "<<selected->GetName()<<std::endl;
        }
        selectedActor = selected;
    }


    if(selectedActor)
    {
        if(input->keyDown(Hero::System::Input::KeyCode::DELETE))
        {
            selectedActor->Destroy();
            selectedActor = nullptr;
        }

        if(input->keyDown(Hero::System::Input::KeyCode::KP_4))
        {
            Hero::Float3 rightVec = selectedActor->GetRotation().GetRightVector();
            Hero::Float3 position = selectedActor->GetPosition();
            position -= rightVec * Move_SPEED;
            selectedActor->SetPosition(position);
        }

        if(input->keyDown(Hero::System::Input::KeyCode::KP_6))
        {
            Hero::Float3 rightVec = selectedActor->GetRotation().GetRightVector();
            Hero::Float3 position = selectedActor->GetPosition();
            position += rightVec * Move_SPEED;
            selectedActor->SetPosition(position);
        }

        if(input->keyDown(Hero::System::Input::KeyCode::KP_8))
        {
            Hero::Float3 forwardVec = selectedActor->GetRotation().GetForwardVector();
            Hero::Float3 position = selectedActor->GetPosition();
            position += forwardVec * Move_SPEED;
            selectedActor->SetPosition(position);
        }

        if(input->keyDown(Hero::System::Input::KeyCode::KP_2))
        {
            Hero::Float3 forwardVec = selectedActor->GetRotation().GetForwardVector();
            Hero::Float3 position = selectedActor->GetPosition();
            position -= forwardVec * Move_SPEED;
            selectedActor->SetPosition(position);
        }

        if(input->keyDown(Hero::System::Input::KeyCode::KP_7))
        {
            Hero::Quaternion rotation = selectedActor->GetRotation();
            rotation *= Hero::Quaternion(Hero::deg2rad(-ROT_SPEED), Hero::Float3::up());
            selectedActor->SetRotation(rotation);
        }

        if(input->keyDown(Hero::System::Input::KeyCode::KP_9))
        {
            Hero::Quaternion rotation = selectedActor->GetRotation();
            rotation *= Hero::Quaternion(Hero::deg2rad(ROT_SPEED), Hero::Float3::up());
            selectedActor->SetRotation(rotation);
        }

        if(input->keyDown(Hero::System::Input::KeyCode::KP_0))
        {
            selectedActor->SetTransform(Hero::Transform());
        }

        if(input->keyDown(Hero::System::Input::KeyCode::RETURN))
        {
            static int spawnedNum = 0;
            spawnedNum++;
            std::string name = "Cliff_" + std::to_string(spawnedNum);
            selectedActor = sceneSystem->GetCurrentScene()->Spawn<Cliff>(SID(name.c_str()));
            sceneSystem->GetCurrentScene()->AddActor(selectedActor);
        }
    }
}

void Editor::close()
{
    Hero::ISystem::close();

}