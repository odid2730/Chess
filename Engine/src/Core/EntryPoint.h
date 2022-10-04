#pragma once

#include "Application.h"

int main()
{
	Application* app = CreateApp();
	app->Run();
	delete app;
}