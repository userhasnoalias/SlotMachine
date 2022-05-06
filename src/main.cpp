#include "engine.h"

int main()
{
	Engine& engine = Engine::get();
	engine.beginPlay();

	while (!engine.getWindow()->isClosed())
	{
		engine.update();
		engine.render();
		engine.lateUpdate();
	}

	return 0;
}