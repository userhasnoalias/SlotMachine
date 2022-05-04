#include "engine.h"

#include <iostream>

int main()
{
	Engine& engine = Engine::get();

	while (!engine.getWindow()->isClosed())
	{
		engine.update();
		engine.render();
		engine.lateUpdate();
	}

	return 0;
}