#pragma once
#include <Application.hpp>


#pragma warning(disable: 6386)

class Interface : public Engine::Application {

	virtual void onUpdate() override;

	void setupDockspaceMenu();

	void beginMenu();

	void Draw_Canvas();

	void Draw_parametrs();

	virtual void onUiDraw() override; //main
};

