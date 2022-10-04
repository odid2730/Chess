#include "pch.h"
#include "Core/EntryPoint.h"
#include "Core/Application.h"

#include "Game/SettingsLayer.h"
#include "Game/StartLayer.h"
#include "Game/UILayer.h"
#include "Game/GameLayer.h"

class SandboxApp : public Application
{
public:
	SandboxApp()
	{
		PushLayer(new GameLayer());			//0
		PushLayer(new UILayer());			//1
		PushLayer(new StartLayer());		//2
		PushLayer(new SettingsLayer());		//3
	}

	~SandboxApp()
	{

	}
};

Application* CreateApp()
{
	return new SandboxApp();
}