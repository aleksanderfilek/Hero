#include "MainEditorWidget.hpp"
#include "../Hero/UserInterface/Canvas.hpp"
#include "../Hero/UserInterface/Image.hpp"
#include "../Hero/Systems/Resources.hpp"
#include "../Hero/Core/Core.hpp"
#include "../Hero/Graphics/Texture.hpp"

MainEditorWidget::MainEditorWidget()
{
    Hero::Resources* resources = Hero::Core::getSystem<Hero::Resources>(SID("resources"));

    Hero::UI::Canvas* panel = new Hero::UI::Canvas();
    Hero::UI::Image* background = new Hero::UI::Image();

    resources->Add(SID("EditorBackground"), "bin/assets/EditorBackground.he");
    background->setTexture((Hero::Texture*)resources->Get(SID("EditorBackground")), false);
    // background->SetRelativeTransform(Hero::Int4::zero(), 
    //     Hero::UI::HorizontalAnchor::STRETCH,
    //     Hero::UI::VerticalAnchor::STRETCH);

    panel->add("background", background);
    add("panel", panel);
}