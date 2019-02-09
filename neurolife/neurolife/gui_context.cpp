#include <vector>
#include <sstream>
#include <iostream>

#include "gui_context.h"

string GUIContext::current_dir;

GUIContext::GUIContext(int width, int height, const string& fontPath):
	width(width),
	height(height)
{
	//Init SDL-------------------------------------------------------//
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
		std::cout << "SDL_Init Error: " << SDL_GetError() << std::endl;
	}

	window = SDL_CreateWindow("Neurolife",
		SDL_WINDOWPOS_UNDEFINED,
		SDL_WINDOWPOS_UNDEFINED,
		width,
		height,
		0
	);

	render = SDL_CreateRenderer(window, -1, 0);

	xs.target = width;
	ys.target = height;
	//----------------------------------------------------------------//

	//Init Text ------------------------------------------------------//
	/*GUIContext::current_dir = fontPath;

	if (TTF_Init() == -1) {
		printf("TTF_Init: %s\n", TTF_GetError());
		exit(2);
	}
	string font_paht = current_dir + "arial.ttf";
	font = TTF_OpenFont(font_paht.c_str(), 80);*/
	//----------------------------------------------------------------//
}

GUIContext::~GUIContext() {
	//TTF_CloseFont(font);

	//TTF_CloseFont(font);
	//SDL_DestroyRenderer(render);
	//SDL_DestroyWindow(window);
	SDL_Quit();
}

void GUIContext::set_color(int r, int g, int b) {
	c = { r, g, b };
	SDL_SetRenderDrawColor(render, r, g, b, 255);
}

void GUIContext::setColor(const Color& color) {
	c = color;
	SDL_SetRenderDrawColor(render, c.r, c.g, c.b, 255);
}

void GUIContext::draw_arrow(const Point & p1, const Point & p2) {
	SDL_RenderDrawLine(render, p1.x, p1.y, p2.x, p2.y);
}

void GUIContext::draw_rect(const Point & lft_tp, int w, int h, bool filled) {
	SDL_Rect r{ lft_tp.x, lft_tp.y, w, h };
	if (!filled) {
		SDL_RenderDrawRect(render, &r);
	}
	else {
		SDL_RenderFillRect(render, &r);
	}
}

void GUIContext::draw_rect(const Point& tl, const Point& dr) {
	SDL_RenderDrawLine(render, tl.x, tl.y, dr.x, tl.y);
	SDL_RenderDrawLine(render, dr.x, tl.y, dr.x, dr.y);
	SDL_RenderDrawLine(render, dr.x, dr.y, tl.x, dr.y);
	SDL_RenderDrawLine(render, tl.x, dr.y, tl.x, tl.y);
}

void GUIContext::draw_square(const Point & center, int size, bool filled) {
	SDL_Rect r{ center.x - size, center.y - size, size * 2, size * 2 };
	if (!filled) {
		SDL_RenderDrawRect(render, &r);
	}
	else {
		SDL_RenderFillRect(render, &r);
	}
}


void GUIContext::draw_circle(const Point & center, int radius, bool filled)
{
	if (!filled) {
		int x = radius;
		int y = 0;

		if (radius > 0)
		{
			point(x + center.x, -y + center.y);
			point(-x + center.x, y + center.y);
			point(-y + center.x, -x + center.y);
		}

		// Initialising the value of P
		int P = 1 - radius;
		while (x > y)
		{
			y++;

			// Mid-point is inside or on the perimeter
			if (P <= 0)
				P = P + 2 * y + 1;

			// Mid-point is outside the perimeter
			else
			{
				x--;
				P = P + 2 * y - 2 * x + 1;
			}

			// All the perimeter points have already been printed
			if (x < y)
				break;

			point(x + center.x, y + center.y);
			point(-x + center.x, y + center.y);
			point(x + center.x, -y + center.y);
			point(-x + center.x, -y + center.y);

			if (x != y)
			{
				point(y + center.x, x + center.y);
				point(-y + center.x, x + center.y);
				point(y + center.x, -x + center.y);
				point(-y + center.x, -x + center.y);
			}
		}
	}
	else {
		for (int i = -radius; i < radius; ++i) {
			for (int j = -radius; j < radius; ++j) {
				if (i*i + j * j < radius * radius) {
					point(i + center.x, j + center.y);
				}
				if (i*i + j * j == radius * radius) {
					Color old = color();
					set_color(old.r / 2, old.g / 2, old.b / 2);
					point(i + center.x, j + center.y);
					set_color(old.r, old.g, old.b);
				}

			}
		}
	}
}

void GUIContext::draw_text(const Point & coor, const string text)
{
	static const int letter_w = 10;
	//SDL_Color White = { 255, 255, 255 }; 
	
	/*if (font) {

		SDL_Surface* surfaceMessage = TTF_RenderText_Solid(font, text.c_str(), White);

		SDL_Texture* Message = SDL_CreateTextureFromSurface(render, surfaceMessage);

		SDL_Rect Message_rect{ coor.x, coor.y, letter_w*text.size(), 20 };

		SDL_RenderCopy(render, Message, NULL, &Message_rect);
		SDL_DestroyTexture(Message);
		SDL_FreeSurface(surfaceMessage);

	}
	else {
		cout << "cant open font" << endl;
	}*/
}

void GUIContext::point(int x, int y) {
	SDL_RenderDrawPoint(render, x, y);
}

void GUIContext::clear() {
	setColor(clearC);
	SDL_RenderClear(render);
}

void GUIContext::present() {
	SDL_RenderPresent(render);
}

