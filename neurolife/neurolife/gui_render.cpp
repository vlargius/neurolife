#include "mutil.h"

#include "gui_render.h"

GUIRender::GUIRender(const World * w, int with, int height) :
	Render(w),
	c(with, height, "") {
	c.xs.source = w->getField().getWidth();
	c.ys.source = w->getField().getHeight();
}

void GUIRender::flash() {
	c.clear();
	for (auto& a : w->getActors()) {
		render(a);
	}
	c.present();
}

void GUIRender::render(const Actor& a) {

	const Field & f = w->getField();
	vec2d pos = a.getPosComp().getPos();
	int x = c.xs(pos.x);
	int y = c.ys(pos.y);
	x = clamp(x, 0, c.xs(f.getWidth()));
	y = clamp(y, 0, c.ys(f.getHeight()));
	//draw actor
	c.set_color(255, 0, 0);
	c.draw_square({ x,y }, actorSize);
}
