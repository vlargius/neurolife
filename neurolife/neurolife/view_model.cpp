#include "view_model.h"


GUIContext * BaseViewModel::c = nullptr;

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
	SDL_Rect rect{ model.get_x(), model.get_y() ,10, 10 };

	SDL_RenderDrawRect(c->render, &rect);
}

template<>
void ViewModel<Grass>::render()
{
	SDL_SetRenderDrawColor(c->render, 0, 255, 0, 255);
	SDL_Rect rect{ model.get_x(), model.get_y(), 10, 10 };

	SDL_RenderDrawRect(c->render, &rect);
}
