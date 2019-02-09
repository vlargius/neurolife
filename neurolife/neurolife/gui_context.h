#pragma once

#include <string>

using namespace std;

//#include <SDL_ttf.h>
#include <SDL.h>
#undef main
#include <SDL_main.h>

class Scale {
public:

	int operator()(double x) {
		return ((x-source/2) /source * target *scale + target/2 + pos);
	}

	double scale = 1;
	double pos = 0;

	double target;
	double source;

protected:
};

struct Point {
	int x;
	int y;
};

class GUIContext {
public:
	struct Color {
		int r;
		int g;
		int b;
	};

	GUIContext(int width, int height, const string& font_path);
	~GUIContext();

	void draw() {}

	SDL_Window *window;
	SDL_Renderer *render;

	int get_width() { return width; }
	int get_height() { return height; }

	void set_color(int r, int g, int b);
	void setColor(const Color& color);
	Color color() const { return c; }

	void draw_arrow(const Point& p1, const Point& p2);

	void draw_rect(const Point& center, int w, int h, bool filled = false);
	void draw_rect(const Point& tl, const Point& dr);
	void draw_square(const Point& center, int size, bool filled = false);

	void draw_circle(const Point& center, int radius, bool filled = false);

	void draw_text(const Point& coor, const string text);
	void clear();
	void present();

	double & scale() {
		xs.scale = current_scale;
		ys.scale = current_scale;
		return current_scale;
	}

	Scale xs;
	Scale ys;

	static string current_dir;

	GUIContext(const GUIContext&) = delete;
	GUIContext& operator=(const GUIContext&) = delete;

private:
	int width = 640;
	int height = 480;

	double current_scale = 1;

	Color c;
	Color clearC = { 0, 0, 0 };
	//TTF_Font * font;

	void point(int x, int y);
};

