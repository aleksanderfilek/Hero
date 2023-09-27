#pragma once

#include "Canvas.h"
#include "../../GenericTypes/String.h"
#include "../../ThirdParty/SDL2/SDL.h"

EVENT_DISPATCHER(TextInputFinished, const String&)

class HERO_API TextInput : public Canvas
{
private:
	class Image* cursor = nullptr;
	class Image* background = nullptr;
	class Label* label = nullptr;
	String text;
	bool inputEnabled = false;
	void OnInputText(const void* Event);

	void OnClick(class Control* Control);
	void Cancel();
	void OnCancel(class Control* context);
public:
	TextInput();

	TextInputFinished OnTextInputFinished;

	String GetText() const { return text; }
	void SetText(const String& Text);

	class Image* GetCursorImage() const;
	class Image* GetBackgroundImage() const;
	class Label* GetLabel() const;
};
