#pragma once

#include "gui_context.h"
#include "actor.h"
#include "grass.h"

class BaseViewModel
{
public:
	virtual void render() = 0;

protected:
	static GUIContext c;
};


template<class T>
class ViewModel : public BaseViewModel
{
public:
	void render() override;

protected:
	const T& model;
};


