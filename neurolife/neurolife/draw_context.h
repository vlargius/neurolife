#pragma once
#include <iostream>

using namespace std;

class ViewWorld;

class DrawContext {
public:
	virtual void draw() = 0;
	DrawContext(ViewWorld & view_w):
		view_w(view_w) {}

	virtual void dipose() {}

protected:
	ViewWorld& view_w;
};

class ConsoleContext : public DrawContext {
public:
	ConsoleContext(ViewWorld & view_w, ostream& os) :
		DrawContext(view_w),
		os(os) {}

	void draw() override;

private:
	ostream & os;

	void draw_head() const;
	void draw_field() const;
};