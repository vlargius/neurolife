#include <algorithm>

#include "view_model.h"
#include "constants.h"

GUIContext * BaseViewModel::c = nullptr;

template<class T>
void ViewModel<T>::render()
{

}

template<>
void ViewModel<Actor>::render() {	
	const Field * f = model.get_field();
	int x = c->xs(model.x());
	int y = c->ys(model.y());

	int h = elsize() *2* model.get_hp() / default_hp;

	vec2d goal = model.get_goal();

	int gx = c->xs(goal.x);
	int gy = c->ys(goal.y);

	//draw goal
	c->set_color(0, 0, 255);	
	c->draw_arrow({ x, y }, { gx,gy });

	//draw actor
	c->set_color(255, 0, 0);
	c->draw_square({ x,y }, elsize());
	
	//draw hp
	c->draw_rect({ x- (int)elsize(),y - h + (int)elsize() }, elsize() * 2, h, true);
}

template<>
void ViewModel<Grass>::render()
{	
	const Field * f = model.get_field();
	int x = c->xs(model.x());
	int y = c->ys(model.y());

	c->set_color(0, 255, 0);
	c->draw_circle({ x, y }, elsize() * 0.7, true);
}
#undef max

double BaseViewModel::elsize() const
{
	 return std::max(default_elsize * c->scale(), 2.) ;
}
