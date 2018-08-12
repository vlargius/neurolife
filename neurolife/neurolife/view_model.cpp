#include "view_model.h"

template<class T>
inline void ViewModel<T>::render()
{
	SDL_SetRenderDrawColor(c.render, 255, 0, 0, 255);
	SDL_Rect rect{100, 100 ,10, 10 };

	SDL_RenderDrawRect(c.render, &rect);
}