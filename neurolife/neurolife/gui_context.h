#pragma once

#include <SDL.h>
#undef main
#include <SDL_main.h>

#include "draw_context.h"

struct Point {
	int x;
	int y;
};

class GUIContext : public DrawContext {
public:
	
	GUIContext(size_t width, size_t height);
	
	void draw() override;

	static void init_SDL();

	SDL_Window *window;
	SDL_Renderer *render;

	int get_width() { return width; }
	int get_height() { return height; }

	void set_color(int r, int g, int b);

	void draw_arrow(const Point& p1, const Point& p2);

	void draw_rect(const Point& center, int w, int h, bool is_fill = false);
	void draw_square(const Point& center, int size, bool is_fill = false);

	void draw_circle(const Point& center, int radius);

private:
	int width = 640;
	int height = 480;

	void clear();
};
