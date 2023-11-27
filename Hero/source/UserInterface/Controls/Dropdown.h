#pragma once

#include "Canvas.h"
#include "../../Graphics/Color.h"
#include "../../Math/Float4.h"
#include "../../Math/Int4.h"
#include <string>

EVENT_DISPATCHER(OptionChangedEvent, class Control*, int);

struct DropdownStyle
{
	class Texture* BackgroundTexture = nullptr;
	Float4 BackgroundTextureRect = { 0.0f, 0.0f, 1.0f, 1.0f };
	Color BackgroundColor = COLOR_GRAY;

	class Font* TextFont = nullptr;
	int TextSize = 10;
	Color TextColor = COLOR_BLACK;
	Int4 TextPadding;
};

struct DropdownItemStyle
{
	class Texture* BackgroundTexture = nullptr;
	Float4 BackgroundTextureRect = { 0.0f, 0.0f, 1.0f, 1.0f };
	Color BackgroundColor = COLOR_GRAY;
	Color BackgroundHoverColor = COLOR_LIGHTGRAY;

	class Font* TextFont = nullptr;
	int TextSize = 10;
	Color TextColor = COLOR_BLACK;
	Int4 TextPadding;
};

class HERO_API Dropdown : public Canvas
{
private:
	class Image* image = nullptr;
	class Label* label = nullptr;

	Array<const char*> options;
	int selectedOption = -1;

public:
	Dropdown();

	class Image* GetBackgroundImage() const;
	class Label* GetLabel() const;

	void AddOption(const char* Option);
	void ClearOptions();
	void SetOption(int Index);
	int GetCurrentOption(const char*& Option);

private:
	bool opened = false;
	void ToggleList(bool Open);

	class DropdownList* list = nullptr;;
	void ReactToClick(Control* Control);

public:
	OptionChangedEvent OnOptionChanged;

private:
	DropdownStyle dropdownStyle;
	DropdownItemStyle dropdownItemStyle;

public:
	void SetDropdownStyle(const DropdownStyle& Style);
	DropdownStyle GetDropdownStyle() const;
	void SetDropdownItemStyle(const DropdownItemStyle& Style);
	DropdownItemStyle GetDropdownItemStyle() const;
};