#include "gui_render.h"
#include <cstdint>

GuiRender::GuiRender(const GuiRender::CreateConf& conf):
    windowBox(conf.outBox) {
    xs.target = windowBox.width;
    ys.target = windowBox.height;

    if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
	{
		std::cout << "SDL_Init Error: " << SDL_GetError() << std::endl;
	}

	SdlWindow = SDL_CreateWindow("Neurolife",
							  SDL_WINDOWPOS_UNDEFINED,
							  SDL_WINDOWPOS_UNDEFINED,
							  windowBox.width,
							  windowBox.height,
							  0);

	SdlRender = SDL_CreateRenderer(SdlWindow, -1, 0);
}

struct Color {
    int8_t r;
    int8_t g;
    int8_t b;

	const static Color red;
	const static Color green;
	const static Color blue;
	const static Color black;
	const static Color white;
};

const Color Color::red = {static_cast<int8_t>(255), 0, 0};
const Color Color::green = {0, static_cast<int8_t>(255), 0};
const Color Color::blue = {0, 0, static_cast<int8_t>(255)};
const Color Color::black = {0, 0, 0};
const Color Color::white = {static_cast<int8_t>(255), static_cast<int8_t>(255), static_cast<int8_t>(255)};

void GuiRender::render(const World& world) {
	setInBox(world.size);

	SDL_SetRenderDrawColor(SdlRender, Color::black.r, Color::black.g, Color::black.b, 255);
	SDL_RenderClear(SdlRender);

	Color c = Color::green;

	for (const Actor& actor : world.actors) {
		SDL_SetRenderDrawColor(SdlRender, c.r, c.g, c.b, 255);
		SDL_Rect r{ xs(actor.pos.x), ys(actor.pos.y), 15, 15 };

		SDL_RenderFillRect(SdlRender, &r);
	}

	SDL_RenderPresent(SdlRender);
}