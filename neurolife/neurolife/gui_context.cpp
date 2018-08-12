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

	const Actor& a = w->get_actors().front();
	
	for (auto v : w->get_views()) {
		v.second->render();
	}

	SDL_RenderPresent(render);
	
	/*
	SDL_Event event;
	while (1) {
		if (SDL_PollEvent(&event) && event.type == SDL_QUIT)
			break;
	}*/
}

void GUIContext::init_SDL()
{
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
		std::cout << "SDL_Init Error: " << SDL_GetError() << std::endl;
	}
}

void GUIContext::clear() {
	SDL_SetRenderDrawColor(render, 0, 0, 0, 255);
	SDL_RenderClear(render);
}

