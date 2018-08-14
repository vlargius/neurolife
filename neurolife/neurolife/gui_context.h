#pragma once

#include <string>

#include <SDL_ttf.h>
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
	struct Color {
		int r;
		int g;
		int b;
	};

	GUIContext(ViewWorld & view_w, size_t width, size_t height);
	~GUIContext();

	void draw() override {}

	static void init_SDL();

	SDL_Window *window;
	SDL_Renderer *render;

	int get_width() { return width; }
	int get_height() { return height; }

	void set_color(int r, int g, int b);
	Color color() const { return c; }

	void draw_arrow(const Point& p1, const Point& p2);

	void draw_rect(const Point& center, int w, int h, bool filled = false);
	void draw_square(const Point& center, int size, bool filled = false);

	void draw_circle(const Point& center, int radius, bool filled = false);

	void draw_text(const Point& coor, const string text);
	void clear();
	void present();

	static string current_dir;

private:
	int width = 640;
	int height = 480;

	Color c;
	TTF_Font * font;

	void point(int x, int y);
};

inline string get_font_path(const string& path_to_bin) {
	auto ch = path_to_bin.end();
	ch--;
	while (ch != path_to_bin.begin() && *ch != '\\') {
		ch--;
	}
	return string(path_to_bin.begin(), ch) + "\\fonts\\";
}