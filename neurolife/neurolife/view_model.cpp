#include "view_model.h"


GUIContext * BaseViewModel::c = nullptr;

const int elsize = 15;

template<class T>
void ViewModel<T>::render()
{
	//SDL_SetRenderDrawColor(c.render, 255, 0, 0, 255);
	//SDL_Rect rect{100, 100 ,10, 10 };

	//SDL_RenderDrawRect(c.render, &rect);
}

template<>
void ViewModel<Actor>::render()
{
	SDL_SetRenderDrawColor(c->render, 255, 0, 0, 255);
	const Field * f = model.get_field();
	int x = model.x()/f->get_width() * c->get_width();
	int y = model.y()/f->get_height() * c->get_height();
	int h = elsize * model.get_hp() / default_hp;
	SDL_Rect rect{x, y, elsize, elsize };

	//draw actor
	SDL_RenderDrawRect(c->render, &rect);
	
	//draw hp
	rect.y = y + (elsize - h);
	rect.h = h;
	SDL_RenderFillRect(c->render, &rect);

	//draw goal
	if (model.g != nullptr) {
		SDL_SetRenderDrawColor(c->render, 0, 0, 255, 255);
		int x = model.g->x() / f->get_width() * c->get_width();
		int y = model.g->y() / f->get_height() * c->get_height();

		SDL_Rect goal{ x-1, y-1, elsize + 2, elsize + 2 };
		SDL_RenderDrawRect(c->render, &goal);
	}
}

template<>
void ViewModel<Grass>::render()
{
	SDL_SetRenderDrawColor(c->render, 0, 255, 0, 255);
	const Field * f = model.get_field();
	int x = model.x() / f->get_width() * c->get_width();
	int y = model.y() / f->get_height() * c->get_height();;
	SDL_Rect rect{ x, y, elsize, elsize };

	SDL_RenderDrawRect(c->render, &rect);
}
