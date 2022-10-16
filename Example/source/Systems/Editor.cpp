#include "Editor.hpp"
#include "../Hero/Core/Core.hpp"
#include "../Hero/Systems/ActorScene/Scene.hpp"
#include "../Hero/Actors/Systems/ForwardRenderer.hpp"
#include "MainEditorWidget.hpp"
#include "../Hero/Systems/Resources.hpp"
#include "../Hero/Graphics/Shader.hpp"

#include <iostream>

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
            std::cout<<selected->GetName()<<std::endl;
        }
        selectedActor = selected;
    }

}

void Editor::close()
{
    Hero::ISystem::close();

}