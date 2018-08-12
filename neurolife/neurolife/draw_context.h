#pragma once
#include <iostream>

using namespace std;

class World;

class DrawContext {
public:
	virtual void draw() = 0;
	virtual void init(World * world) {
		w = world;
	}
	virtual void dipose() {}

protected:
	World * w;
};

class ConsoleContext : public DrawContext {
public:
	ConsoleContext(ostream& os) :
		os(os) {}

	void draw() override;

private:
	ostream & os;

	void draw_head() const;
	void draw_field() const;
};