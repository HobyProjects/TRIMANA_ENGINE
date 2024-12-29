#include <iostream>
#include "application.hpp"

int main(int argc, char** argv)
{
	TE::app::application* app = new TE::app::application();
	app->run();
	delete app;


	std::cin.get();
	return 0;
}