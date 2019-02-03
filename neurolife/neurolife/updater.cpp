
#include "my_utils.h"
#include "updater.h"

#include "gui_context.h"

Updater::Updater(World & w, Render* render):
	world(w),
	render(render),
	stepSize(1) {

}

void Updater::setStepSize(int size) {
	stepSize = size;
}

void Updater::run() {
	double dt = 1;

	//GUIContext context(1200, 600, "run");

	/*chrono::steady_clock::time_point from, to;

	for (size_t i = 0; i < time_to_live; ++i) {
		while (!is_active) {
			std::unique_lock<std::mutex> lock(com_lock);
			cond.wait(lock);
		}
		double dt = chrono::duration_cast<chrono::milliseconds>(to - from).count();
		from = chrono::steady_clock::now();
		tick(dt);

		handle_event();

		my::sleep(step_size);
		to = chrono::steady_clock::now();
	}
	cout << "closing" << endl;*/

	do{
		render->flash();
		world.tick(dt);
		utils::sleep(stepSize);
	} while (world.alive());
}

//
//void World::handle_event() {
//	//while (SDL_PollEvent(&e)) {
//	//	//If user closes the window
//	//	if (e.type == SDL_QUIT) {
//	//		is_active = false;
//	//	}
//	//	//If user presses any key
//	//	if (e.type == SDL_KEYDOWN) {
//	//		switch (e.key.keysym.sym) {
//	//		case SDLK_LEFT:
//	//			context->xs.pos += cam_speed;
//	//			cout << "l";
//	//			break;
//	//		case SDLK_RIGHT:
//	//			context->xs.pos -= cam_speed;
//	//			cout << "r";
//	//			break;
//	//		case SDLK_UP:
//	//			context->ys.pos += cam_speed;
//	//			cout << "u";
//	//			break;
//	//		case SDLK_DOWN:
//	//			context->ys.pos -= cam_speed;
//	//			cout << "d";
//	//			break;
//	//		case SDLK_ESCAPE:
//	//			is_active = false;
//	//		default:
//	//			break;
//	//		}
//	//	}
//	//	if (e.type == SDL_MOUSEWHEEL)
//	//	{
//	//		if (e.wheel.y > 0)
//	//		{
//	//			context->scale() *= scroll_speed;
//	//		}
//	//		else if (e.wheel.y < 0)
//	//		{
//	//			context->scale() /= scroll_speed;
//	//		}
//	//	}
//	//	
//
//	//	
//	//}
//}