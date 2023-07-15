#include <iostream>
#include "FelicoEngine.h"

int main() {
	std::cout << "Hello, world!" << std::endl;
	FelicoEngine::Engine *engine = new FelicoEngine::Engine("My Title",800,600);
	

	return engine->OnExecute();

	
}