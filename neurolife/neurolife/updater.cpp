#include <Windows.h>

#include "updater.h"

#include "gui_context.h"

Updater::Updater(World & w, CharRender& r):
	world(w),
	render(r),
	stepSize(1) {

}

void Updater::setStepSize(int size) {
	stepSize = size;
}

void Updater::run() {
	double dt = 1;

	GUIContext context(1200, 600, "run");

	do{
		render.flash(world);
		world.tick(dt);
		Sleep(stepSize);
	} while (world.isAlive());
}
