#include "TextInput.h"
#include "Label.h"
#include "../../Core.h"
#include "../UserInterface.h"
#include "../../Resources/Font.h"
#include "../../Subsystems/Window/WindowObject.h"

TextInput::TextInput()
{
	background = new Image();
	background->SetHorizontalAlligment(HorizontalAlligment::STRETCH);
	background->SetVerticalAlligment(VerticalAlligment::STRETCH);

	Add(background);

	label = new Label();
	label->SetHorizontalAlligment(HorizontalAlligment::STRETCH);
	label->SetVerticalAlligment(VerticalAlligment::STRETCH);
	label->SetAlligment(TextAlligment::LEFT);
	label->SetColor(COLOR_BLACK);
	Add(label);

	cursor = new Image();
	cursor->SetSize({5, 0});
	cursor->SetHorizontalAlligment(HorizontalAlligment::LEFT);
	cursor->SetVerticalAlligment(VerticalAlligment::STRETCH);
	cursor->SetColor(COLOR_BLACK);
	cursor->SetVisibility(VisibilityState::HIDDEN);
	Add(cursor);

	OnLeftClick.AddEvent(this, &TextInput::OnClick);
}

void TextInput::OnInputText(const void* Event)
{
	bool render = false;
	SDL_Event* event = (SDL_Event*)Event;

	if (event->type == SDL_KEYDOWN)
	{
		//Handle backspace
		if (event->key.keysym.sym == SDLK_BACKSPACE && text.Length() > 0)
		{
			//lop off character
			if (text.Length() > 0)
			{
				text.PopBack();
			}
			render = true;
		}
		//Handle copy
		else if (event->key.keysym.sym == SDLK_c && SDL_GetModState() & KMOD_CTRL)
		{
			SDL_SetClipboardText(*text);
		}
		//Handle paste
		else if (event->key.keysym.sym == SDLK_v && SDL_GetModState() & KMOD_CTRL)
		{
			text = SDL_GetClipboardText();
			render = true;
		}
		else if (event->key.keysym.sym == SDLK_RETURN)
		{
			Cancel();
			return;
		}
	}
	else if (event->type == SDL_TEXTINPUT)
	{
		if (!(SDL_GetModState() & KMOD_CTRL && (event->text.text[0] == 'c' || event->text.text[0] == 'C' || event->text.text[0] == 'v' || event->text.text[0] == 'V')))
		{
			text += event->text.text[0];
			render = true;
		}
	}

	if (render)
	{
		label->SetText(*text);
		cursor->SetPosition({ label->GetFont()->GetTextWidth(label->GetText(), label->GeTextSize()), 0 });
		label->Apply();
	}
}

void TextInput::OnClick(class Control* Control)
{
	if (inputEnabled)
	{
		return;
	}

	inputEnabled = true;
	SDL_StartTextInput();
	cursor->SetVisibility(VisibilityState::VISIBLE);
	cursor->SetPosition({ label->GetFont()->GetTextWidth(label->GetText(), label->GeTextSize()), 0 });

	GetUserInterface()->GetWindow()->OnWindowEventCustom.AddEvent(this, &TextInput::OnInputText);
}

void TextInput::SetText(const String& Text)
{
	text = Text;
	label->SetText(text);
	label->Apply();
}

void TextInput::Cancel()
{
	inputEnabled = false;
	SDL_StopTextInput();
	cursor->SetVisibility(VisibilityState::HIDDEN);

	GetUserInterface()->GetWindow()->OnWindowEventCustom.RemoveEvent(this, &TextInput::OnInputText);
	OnTextInputFinished.Broadcast(text);
}

void TextInput::OnCancel(class Control* context)
{
	if (this == context)
	{
		return;
	}

	if (inputEnabled)
	{
		Cancel();
	}
}

class Image* TextInput::GetCursorImage() const
{
	return cursor;
}

class Image* TextInput::GetBackgroundImage() const
{
	return background;
}

class Label* TextInput::GetLabel() const
{
	return label;
}