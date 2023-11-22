#include "Gravity.hpp"
#define _USE_MATH_DEFINES
#include <math.h>
#include <imgui/imgui.h>

Gravity::Gravity()
{
	set_initial_conditions();
}

void Gravity::calculate(float time, float dt)
{

	Earth.x += Earth.vx * dt;
	Earth.y += Earth.vy * dt;
	double R = sqrt(Earth.x * Earth.x + Earth.y * Earth.y);
	double a = 1. / (R * R);
	Earth.ax = -Earth.x / R * a;
	Earth.ay = -Earth.y / R * a;
	Earth.vx += Earth.ax * dt;
	Earth.vy += Earth.ay * dt;
	Earth.trace.AddPoint(Earth.x, Earth.y);

	double ek = (Earth.vx * Earth.vx + Earth.vy * Earth.vy) / 2.;
	Earth.E_k.AddPoint(Earth.x, ek );
	Earth.E_p.AddPoint(Earth.x, -1. / R);
	Earth.E_f.AddPoint(Earth.x, ek - 1. / R);
}

void Gravity::set_initial_conditions()
{
	Sun.x = 0.;
	Sun.y = 0.;
	Earth.x = 2.5;
	Earth.y = 0.;
	Earth.vx = 0;
	Earth.vy = 0.25;
	Earth.trace.Erase();
	Earth.trace.AddPoint(Earth.x, Earth.y);

	double ek = (Earth.vx * Earth.vx + Earth.vy * Earth.vy) / 2.;
	double R = sqrt(Earth.x * Earth.x + Earth.y * Earth.y);
	Earth.E_k.Erase();
	Earth.E_k.AddPoint(Earth.x, ek);
	Earth.E_p.Erase();
	Earth.E_p.AddPoint(Earth.x, -1. / R);
	Earth.E_f.Erase();
	Earth.E_f.AddPoint(Earth.x, ek - 1. / R);
}
