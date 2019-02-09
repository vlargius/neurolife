#pragma once

#include "render.h"

class CharRender : public Render {
public:
	CharRender(const World* w, ostream& os);
	void flash() override;

private:
	ostream & os;

	void drawStat() const;
	void drawField() const;
};