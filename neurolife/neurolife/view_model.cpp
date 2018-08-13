#include "view_model.h"


GUIContext * BaseViewModel::c = nullptr;

const int elsize = 10;

template<class T>
void ViewModel<T>::render()
{

}

template<>
void ViewModel<Actor>::render()
{
	
	const Field * f = model.get_field();
	int x = model.x()/f->get_width() * c->get_width();
	int y = model.y()/f->get_height() * c->get_height();
	int h = elsize *2* model.get_hp() / default_hp;
	SDL_Rect rect{x, y, elsize, elsize };

	//draw goal
	c->set_color(0, 0, 255);
	vec2d goal = model.get_goal();
	//goal.normalize();
	//goal *= 3;
	int gx = goal.x / f->get_width() * c->get_width();
	int gy = goal.y / f->get_height() * c->get_height();

	c->set_color(255, 0, 0);
	c->draw_arrow({ x, y }, { gx,gy });
	//draw actor
	c->draw_square({ x,y }, elsize);
	
	//draw hp
	c->draw_rect({ x-elsize,y - h + elsize }, elsize * 2, h, true);

	

}

template<>
void ViewModel<Grass>::render()
{
	SDL_SetRenderDrawColor(c->render, 0, 255, 0, 255);
	const Field * f = model.get_field();
	int x = model.x() / f->get_width() * c->get_width();
	int y = model.y() / f->get_height() * c->get_height();;
	
	c->draw_square({ x, y }, elsize * 0.7, true);
}
