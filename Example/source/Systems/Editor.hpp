#pragma once

#include "../Hero/Systems/Input.hpp"
#include "../Hero/Core/ISystem.hpp"
#include "../Hero/Systems/ActorScene/Actor.hpp"
#include "../Hero/Systems/ActorScene/SceneSystem.hpp"
#include "../Hero/Systems/UserInterface.hpp"

class Editor : public Hero::ISystem
{
private:
    Hero::System::Input* input;
    Hero::SceneSystem* sceneSystem;
    Hero::System::UserInterface* ui;

    class MainEditorWidget* editorWidget;
    bool active = false;

    Hero::Actor* selectedActor = nullptr;

public:
    Editor(const Hero::Sid& sid);
    ~Editor();

    void init();
    void update();
    void close();
};