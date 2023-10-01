#include "Dropdown.h"
#include "Image.h"
#include "Label.h"
#include "../Widget.h"
#include "VerticalStack.h"
#include "../UserInterface.h"

class DropdownItem : public Canvas
{
private:
	DropdownList* owner = nullptr;
	class Image* image = nullptr;
	class Label* label = nullptr;
	int index = 0;

	void ReactToClick(Control* Control);
	void ReactToHoverEnter(Control* Control);
	void ReactToHoverExit(Control* Control);

	DropdownItemStyle style;

public:
	DropdownItem(DropdownList* Owner, int Index, const String& Option, const DropdownItemStyle& Style);
};

class DropdownList : public Widget
{
private:
	Dropdown* owner = nullptr;

public:
	DropdownList(Dropdown* Owner, const Array<String>& Options);
	~DropdownList();

	void SetOption(int Index);
};

Dropdown::Dropdown()
{
	image = new Image();
	image->SetHorizontalAlligment(HorizontalAlligment::STRETCH);
	image->SetVerticalAlligment(VerticalAlligment::STRETCH);
	Add(image);

	label = new Label();
	label->SetHorizontalAlligment(HorizontalAlligment::STRETCH);
	label->SetVerticalAlligment(VerticalAlligment::STRETCH);
	label->SetAlligment(TextAlligment::LEFT);
	Add(label);

	OnLeftClick.AddEvent(this, &Dropdown::ReactToClick);
}

class Image* Dropdown::GetBackgroundImage() const
{
	return image;
}

class Label* Dropdown::GetLabel() const
{
	return label;
}

void Dropdown::AddOption(const String& Option)
{
	options.Add(Option);

	if (selectedOption == -1)
	{
		SetOption(0);
	}
}

void Dropdown::ClearOptions()
{
	options.Clear();
}

void Dropdown::SetOption(int Index)
{
	if (Index >= options.Length())
	{
		return;
	}

	selectedOption = Index;
	label->SetText(options[selectedOption]);
	label->Apply();

	if (opened)
	{
		ToggleList(false);
	}

	OnOptionChanged.Broadcast(this, Index);
}

int Dropdown::GetCurrentOption(String& Option)
{
	if (selectedOption >= 0)
	{
		Option = options[selectedOption];
	}
	return selectedOption;
}

void Dropdown::ToggleList(bool Open)
{
	if (Open)
	{
		if (options.Length() == 0)
		{
			return;
		}

		opened = true;
		list = new DropdownList(this, options);
		GetUserInterface()->AddWidget(list);
	}
	else
	{
		opened = false;
		GetUserInterface()->RemoveWidget(list);
		list = nullptr;
	}
}

void Dropdown::ReactToClick(Control* Control)
{
	ToggleList(!opened);
}

void Dropdown::SetDropdownStyle(const DropdownStyle& Style)
{
	dropdownStyle = Style;

	image->SetTexture(dropdownStyle.BackgroundTexture);
	image->SetTextureRect(dropdownStyle.BackgroundTextureRect);
	image->SetColor(dropdownStyle.BackgroundColor);

	label->SetFont(dropdownStyle.TextFont);
	label->SetColor(dropdownStyle.TextColor);
	label->SetTextSize(dropdownStyle.TextSize);
	label->SetPosition({ dropdownStyle.TextPadding.X, dropdownStyle.TextPadding.Y });
	label->SetSize({ dropdownStyle.TextPadding.Z, dropdownStyle.TextPadding.W });
	label->SetAlligment(TextAlligment::LEFT);
}

DropdownStyle Dropdown::GetDropdownStyle() const
{
	return dropdownStyle;
}

void Dropdown::SetDropdownItemStyle(const DropdownItemStyle& Style)
{
	dropdownItemStyle = Style;
}

DropdownItemStyle Dropdown::GetDropdownItemStyle() const
{
	return dropdownItemStyle;
}

DropdownItem::DropdownItem(DropdownList* Owner, int Index, const String& Option, const DropdownItemStyle& Style)
	:owner(Owner), index(Index), style(Style)
{
	image = new Image();
	image->SetHorizontalAlligment(HorizontalAlligment::STRETCH);
	image->SetVerticalAlligment(VerticalAlligment::STRETCH);
	image->SetTexture(style.BackgroundTexture);
	image->SetTextureRect(style.BackgroundTextureRect);
	image->SetColor(style.BackgroundColor);

	Add(image);

	label = new Label();
	label->SetHorizontalAlligment(HorizontalAlligment::STRETCH);
	label->SetVerticalAlligment(VerticalAlligment::STRETCH);
	label->SetPosition({ style.TextPadding.X, style.TextPadding.Y });
	label->SetSize({ style.TextPadding.Z, style.TextPadding.W });
	label->SetFont(style.TextFont);
	label->SetColor(style.TextColor);
	label->SetTextSize(style.TextSize);
	label->SetText(Option);
	label->Apply();
	Add(label);

	OnLeftClick.AddEvent(this, &DropdownItem::ReactToClick);
	OnHoverEnter.AddEvent(this, &DropdownItem::ReactToHoverEnter);
	OnHoverExit.AddEvent(this, &DropdownItem::ReactToHoverExit);
}

void DropdownItem::ReactToClick(Control* Control)
{
	owner->SetOption(index);
}

void DropdownItem::ReactToHoverEnter(Control* Control)
{
	image->SetColor(style.BackgroundHoverColor);
}

void DropdownItem::ReactToHoverExit(Control* Control)
{
	image->SetColor(style.BackgroundColor);
}

DropdownList::DropdownList(Dropdown* Owner, const Array<String>& Options)
	:owner(Owner)
{
	VerticalStack* stack = new VerticalStack();
	Int2 ownerPosition = Owner->GetAbsolutePosition();
	Int2 ownerSize = Owner->GetAbsoluteSize();

	stack->SetPosition({ ownerPosition.X, ownerPosition.Y + ownerSize.Y });
	stack->SetSize({ ownerSize.X, Options.Length() * ownerSize.Y });

	DropdownItemStyle itemStyle = owner->GetDropdownItemStyle();
	for (int i = 0; i < Options.Length(); i++)
	{
		DropdownItem* item = new DropdownItem(this, i, Options[i], itemStyle);
		item->SetSize(ownerSize);
		stack->Add(item);
	}

	GetCanvas()->Add(stack);
}

DropdownList::~DropdownList()
{

}

void DropdownList::SetOption(int Index)
{
	owner->SetOption(Index);
}