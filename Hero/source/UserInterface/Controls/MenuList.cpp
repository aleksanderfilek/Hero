#include "MenuList.h"
#include "../Widget.h"
#include "../UserInterface.h"
#include "Image.h"
#include "Label.h"
#include "VerticalStack.h"
#include "../../Resources/Font.h"
#include "../../Math/Math.h"

class MenuItemWidget : public Widget
{
private:
	MenuButton* owner = nullptr;

	void ReactToMenuItemClicked(Control* Control);

public:
	MenuItemWidget(MenuButton* Owner, Array<MenuItem*>& Options, const MenuOptionStyle& Style);
};

MenuButton::MenuButton()
{
	backgroundImage = new Image();
	backgroundImage->SetHorizontalAlligment(HorizontalAlligment::STRETCH);
	backgroundImage->SetVerticalAlligment(VerticalAlligment::STRETCH);
	Add(backgroundImage);

	label = new Label();
	label->SetHorizontalAlligment(HorizontalAlligment::STRETCH);
	label->SetVerticalAlligment(VerticalAlligment::STRETCH);
	label->SetAlligment(TextAlligment::LEFT);
	Add(label);

	OnLeftClick.AddEvent(this, &MenuButton::ReactToClick);
}

void MenuButton::AddOption(MenuItem* Option)
{
	options.Add(Option);
}

void MenuButton::Clear()
{
	options.Clear();
}

void MenuButton::ToggleList(bool Open)
{
	if (Open)
	{
		if (options.Length() == 0)
		{
			return;
		}

		opened = true;
		widget = new MenuItemWidget(this, options, style.OptionStyle);
		GetUserInterface()->AddWidget(widget);
	}
	else
	{
		opened = false;
		GetUserInterface()->RemoveWidget(widget);
		widget = nullptr;
	}
}

void MenuButton::ReactToClick(Control* Control)
{
	ToggleList(!opened);
}

void MenuButton::SetMenuButtonStyle(const MenuButtonStyle& Style)
{
	style = Style;

	backgroundImage->SetImageStyle(style.BackgroundStyle);
	label->SetLabelStyle(style.TextStyle);
}

MenuButtonStyle MenuButton::GetMenuButtonStyle() const
{
	return style;
}

MenuItemWidget::MenuItemWidget(MenuButton* Owner, Array<MenuItem*>& Options, const MenuOptionStyle& Style)
	:owner(Owner)
{
	VerticalStack* stack = new VerticalStack();

	int width = 0;
	for (int i = 0; i < Options.Length(); i++)
	{
		Options[i]->SetMenuItemStyle(Style);
		width = max(width, Options[i]->GetWidth());
		Options[i]->OnLeftClick.AddEvent(this, &MenuItemWidget::ReactToMenuItemClicked);
		stack->Add(Options[i]);
	}

	stack->SetPosition({Owner->GetAbsolutePosition().X, Owner->GetAbsolutePosition().Y + Owner->GetAbsoluteSize().Y });
	stack->SetSize({width, Options.Length() * Owner->GetAbsoluteSize().Y});

	for (int i = 0; i < Options.Length(); i++)
	{
		Options[i]->SetSize({ width, Owner->GetAbsoluteSize().Y });
	}

	GetCanvas()->Add(stack);
}

void MenuItemWidget::ReactToMenuItemClicked(Control* Control)
{
	owner->ToggleList(false);
}

MenuItem::MenuItem()
{
	backgroundImage = new Image();
	backgroundImage->SetHorizontalAlligment(HorizontalAlligment::STRETCH);
	backgroundImage->SetVerticalAlligment(VerticalAlligment::STRETCH);
	Add(backgroundImage);

	label = new Label();
	label->SetHorizontalAlligment(HorizontalAlligment::STRETCH);
	label->SetVerticalAlligment(VerticalAlligment::STRETCH);
	label->SetAlligment(TextAlligment::LEFT);
	Add(label);
}

void MenuItem::SetText(const char* Text)
{
	label->SetText(Text);
	label->Apply();
}

int MenuItem::GetWidth() const
{
	if (!label->GetFont())
		return 0;
	return label->GetFont()->GetTextWidth(label->GetText(), label->GeTextSize());
}

void MenuItem::SetMenuItemStyle(const MenuOptionStyle& Style)
{
	backgroundImage->SetImageStyle(Style.BackgroundStyle);
	label->SetLabelStyle(Style.TextStyle);
}