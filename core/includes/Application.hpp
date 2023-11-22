#pragma once

#include <memory>
#include "Event.hpp"
#include "Gravity.hpp"


namespace Engine {
	class Application {
	public:
		Application();
		virtual ~Application();

		Application(const Application&) = delete;
		Application(Application&&) = delete;
		Application& operator=(const Application&) = delete;
		Application& operator=(Application&&) = delete;


		virtual int start(unsigned int window_width = 1250, unsigned int window_height = 900, const char* title = "GravityModel");
		
		void close() { mbCloseWindow = true; };

		virtual void onUpdate() {
		};

		virtual void onUiDraw() {};

	private:
		void draw();
		std::shared_ptr<class Window> mpWindow;
		EventDispatcher mEventDispatcher;
		bool mbCloseWindow = false;
	protected:
		std::shared_ptr<Gravity> GravityModel;
		float time = 0;
		float dt = 0.001;
		bool calculation = false;
	};
}