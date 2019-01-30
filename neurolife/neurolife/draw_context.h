#pragma once
#include <iostream>

using namespace std;

#include "world.h";

class DrawContext {
public:
	virtual void draw() = 0;
	DrawContext(){}

	virtual void dipose() {}

protected:
};

class CharRender {
public:
	CharRender(ostream& os);

	void flash(const World& w);

private:
	ostream & os;

	void drawHead(const World& w) const;
	void drawField(const World& w) const;
};