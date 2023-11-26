#pragma once

#include "Canvas.h"
#include "../../ThirdParty/SDL2/SDL.h"

EVENT_DISPATCHER(TextInputFinished, const char*)

class HERO_API TextInput : public Canvas
{
private:
	class Image* cursor = nullptr;
	class Image* background = nullptr;
	class Label* label = nullptr;
	char* text = nullptr;
	bool inputEnabled = false;
	void OnInputText(const void* Event);

	void OnClick(class Control* Control);
	void Cancel();
	void OnCancel(class Control* context);
public:
	TextInput();
	~TextInput();

	TextInputFinished OnTextInputFinished;

	const char* GetText() const { return text; }
	void SetText(const char* Text);

	class Image* GetCursorImage() const;
	class Image* GetBackgroundImage() const;
	class Label* GetLabel() const;
};
