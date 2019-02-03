#pragma once

#include "char_render.h"

namespace cmd {

	class BaseViewModel
	{
	public:
		virtual void render() {}

		static CharRender * c;

		virtual  ~BaseViewModel() {
		}

		int elsize() const;

	protected:

	};

	template<class T>
	class ViewModel : public BaseViewModel
	{
	public:
		ViewModel(const T& obj) :
			model(obj) {}
		void render() override;

	protected:
		const T& model;
	};

}
