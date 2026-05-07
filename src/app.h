#pragma once
#include "gfx/renderer.h"
#include "gfx/window.h"

class app
{
public:
	app();

	void run();

	inline float get_dt() const
	{
		return dt;
	}

private:
	window window;
	renderer renderer;
	float dt;
};