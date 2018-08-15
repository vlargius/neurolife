#pragma once

#include "gui_context.h"
#include "actor.h"
#include "grass.h"

class BaseViewModel
{
public:
	virtual void render() {}

	static GUIContext * c;

	virtual  ~BaseViewModel() {
	}

	double elsize() const;

protected:
	
};

template<class T>
class ViewModel : public BaseViewModel
{
public:
	ViewModel(const T& obj):
		model(obj) {}
	void render() override;

protected:
	const T& model;
};


