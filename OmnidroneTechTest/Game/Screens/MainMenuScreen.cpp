#include "stdafx.h"
#include <Game/Screens/MainMenuScreen.h>
#include <Engine/UI/ButtonObject.h>

CMainMenuScreen::CMainMenuScreen()
	: CScreenBase("data/Screens/MainMenu.xml")
{
	CButtonObject* buttonTest = GetObjectById<CButtonObject>(CStringID("test1"));
	//buttonTest->GetTransform().setRotation(10);
	//buttonTest->GetTransform().setPosition(100.0f, 200.0f);


}

