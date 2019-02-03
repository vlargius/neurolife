#include <algorithm>
#include <sstream>
#include <iomanip>

#include "view_model.h"
#include "constants.h"
#include "buckets.h"


template<class T>
void ViewModel<T>::render()
{

}

template<>
void ViewModel<Actor>::render() {	
	//const Field * f = model.get_field();
	//int x = c->xs(model.x());
	//int y = c->ys(model.y());

	//int h = elsize() *2* model.get_hp() / default_hp;

	//vec2d goal = model.get_goal();

	//int gx = c->xs(goal.x);
	//int gy = c->ys(goal.y);

	////draw goal
	//c->set_color(0, 0, 255);	
	//c->draw_arrow({ x, y }, { gx,gy });

	////draw actor
	//c->set_color(255, 0, 0);
	//c->draw_square({ x,y }, elsize());
	//
	////draw hp
	//c->draw_rect({ x- elsize(),y - h + elsize() }, elsize() * 2, h, true);

	//const Buckets&  b = model.get_controller().get_buckets();
	//
	////draw buckets
	//{

	//	c->set_color(100, 100, 100);
	//	int x = model.x() - b.param.bucket_size * b.param.width / 2.;
	//	int y = model.y() - b.param.bucket_size * b.param.height / 2.;

	//	
	//	for (int i = 0; i < b.param.width; ++i) {
	//		for (int j = 0; j < b.param.height; ++j) {
	//			c->draw_rect({ c->xs(x), c->ys(y) }, { c->xs(x+ b.param.bucket_size), c->ys(y+ b.param.bucket_size) });
	//			x += b.param.bucket_size;
	//		}
	//		y += b.param.bucket_size;
	//		x = model.x() - b.param.bucket_size * b.param.width / 2.;
	//	}
	//}

	////draw norm 
	//{
	//	c->set_color(255, 255, 255);
	//	
	//	stringstream ss;
	//	ss << setprecision(3) << model.get_controller().get_input().length;

	//	//c->draw_text({ x,y+20 }, ss.str());
	//}
}

//template<>
//void ViewModel<Grass>::render()
//{	
//	//const Field * f = model.get_field();
//	//int x = c->xs(model.x());
//	//int y = c->ys(model.y());
//
//	//if (!model.is_in_bucket) {
//	//	c->set_color(0, 255, 0);
//	//}
//	//else {
//	//	c->set_color(0, 255, 200);
//	//}
//	//c->draw_circle({ x, y }, elsize() * 0.7, true);
//}
#undef max

int BaseViewModel::elsize() const
{
	return 0;// std::max(default_elsize * c->scale(), 2.);
}
