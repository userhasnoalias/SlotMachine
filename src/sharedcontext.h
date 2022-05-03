#pragma once

#include "eventmanager.h"
#include "fontmanager.h"
#include "slot.h"
#include "texturemanager.h"
#include "window.h"

struct SharedContext
{
	EventManager* m_event_manager = nullptr;

	TextureManager* m_texture_manager = nullptr;

	FontManager* m_font_manager = nullptr;

	Window* m_window = nullptr;

	Slot* m_slot = nullptr;

	SharedContext() {}
};