#include <vector>

#include "gui_context.h"
#include "world.h"

using namespace std;

GUIContext::GUIContext(size_t width, size_t height):
	width(width),
	height(height) {
	SDL_CreateWindowAndRenderer(width, height, 0, &window, &render);
}

void GUIContext::draw() {
	clear();
	for (auto v : w->get_views()) {
		v.second->render();
	}

	SDL_RenderPresent(render);
}

void GUIContext::init_SDL()
{
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
		std::cout << "SDL_Init Error: " << SDL_GetError() << std::endl;
	}
}

void GUIContext::set_color(int r, int g, int b) {
	SDL_SetRenderDrawColor(render, r, g, b, 255);
}

void GUIContext::draw_arrow(const Point & p1, const Point & p2)
{
	SDL_RenderDrawLine(render, p1.x, p1.y, p2.x, p2.y);
}

void GUIContext::draw_rect(const Point & center, int w, int h, bool filled)
{
	SDL_Rect r{ center.x, center.y, w, h };
	if (!filled) {
		SDL_RenderDrawRect(render, &r);
	}
	else {
		SDL_RenderFillRect(render, &r);
	}
}

void GUIContext::draw_square(const Point & center, int size, bool filled)
{
	SDL_Rect r{ center.x - size, center.y - size, size * 2, size * 2 };
	if (!filled) {
		SDL_RenderDrawRect(render, &r);
	}
	else {
		SDL_RenderFillRect(render, &r);
	}
}


void GUIContext::draw_circle(const Point & center, int radius)
{
}

void GUIContext::clear() {
	SDL_SetRenderDrawColor(render, 0, 0, 0, 255);
	SDL_RenderClear(render);
}

