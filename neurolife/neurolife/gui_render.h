#pragma once

#include "render.h"
#include "gui_context.h"

class GUIRender : public Render {
public:
	GUIRender(const World* w, int with, int height);

	void flash() override;

protected:

	GUIContext c;
	int actorSize = 20;

	void render(const Actor& a);
};