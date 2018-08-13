#pragma once

#include <SDL.h>
#undef main
#include <SDL_main.h>

#include "draw_context.h"

class GUIContext : public DrawContext {
public:
	
	GUIContext(size_t width, size_t height);
	
	void draw() override;

	static void init_SDL();

	SDL_Window *window;
	SDL_Renderer *render;

	int get_width() { return width; }
	int get_height() { return height; }

private:
	int width = 640;
	int height = 480;

	void clear();
};
