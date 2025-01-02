#include <iostream>
#include "application.hpp"

int main(int argc, char** argv)
{
	TE::App::Application* app = new TE::App::Application();
	app->Run();
	delete app;


	std::cin.get();
	return 0;
}