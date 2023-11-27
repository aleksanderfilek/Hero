#pragma once

#include "Canvas.h"
#include "../../Graphics/Color.h"
#include "../../Math/Float4.h"
#include "../../Math/Int4.h"

#include "Image.h"
#include "Label.h"

struct MenuOptionStyle
{
	ImageStyle BackgroundStyle;
	LabelStyle TextStyle;
};

struct MenuButtonStyle
{
	ImageStyle BackgroundStyle;
	LabelStyle TextStyle;

	MenuOptionStyle OptionStyle;
};

class HERO_API MenuButton : public Canvas
{
private:
	class Image* backgroundImage = nullptr;
	class Label* label = nullptr;

	class MenuItemWidget* widget = nullptr;
	bool opened = false;
	void ReactToClick(Control* Control);

	Array<class MenuItem*> options;

public:
	MenuButton();

	void AddOption(class MenuItem* Option);
	void Clear();

	void ToggleList(bool Open);

private:
	MenuButtonStyle style;

public:
	void SetMenuButtonStyle(const MenuButtonStyle& Style);
	MenuButtonStyle GetMenuButtonStyle() const;
};

class MenuItem : public Canvas
{
private:
	class Image* backgroundImage = nullptr;
	class Label* label = nullptr;

public:
	MenuItem();

	void SetText(const char* Text);
	int GetWidth() const;

public:
	void SetMenuItemStyle(const MenuOptionStyle& Style);
};