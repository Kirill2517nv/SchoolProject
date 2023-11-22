#include "Interface.hpp"
#include "Application.hpp"
#include <imgui/imgui.h>
#include <imgui_internal.h>
#include <implot/implot.h>
#include <vector>
#include <algorithm>
#include <string>
#include <iostream>

#define _USE_MATH_DEFINES
#include <math.h>


void Interface::onUpdate()
{

}

void Interface::setupDockspaceMenu()
{
	static ImGuiDockNodeFlags dockspace_flags = ImGuiDockNodeFlags_PassthruCentralNode | ImGuiDockNodeFlags_NoWindowMenuButton;
	static ImGuiWindowFlags window_flags = ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking;
	window_flags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;
	window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;
	window_flags |= ImGuiWindowFlags_NoBackground;

	const ImGuiViewport* viewport = ImGui::GetMainViewport();
	ImGui::SetNextWindowPos(viewport->WorkPos);
	ImGui::SetNextWindowSize(viewport->WorkSize);
	ImGui::SetNextWindowViewport(viewport->ID);
	ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
	ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
	ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
	ImGui::Begin("DockSpace", nullptr, window_flags);
	ImGui::PopStyleVar(3);

	ImGuiIO& io = ImGui::GetIO();
	ImGuiID dockspace_id = ImGui::GetID("MyDockSpace");
	
	ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), dockspace_flags);
	if (ImGui::BeginMenuBar())
	{
		if (ImGui::BeginMenu("Modeling parametrs"))
		{
			if (ImGui::MenuItem("Start", NULL))
			{
				calculation = true;
			}
			if (ImGui::MenuItem("Stop", NULL))
			{
				calculation = false;
			}
			if (ImGui::MenuItem("Set initial conditions", NULL))
			{
				time = 0;
				GravityModel->set_initial_conditions();
			}
			ImGui::Separator();
			if (ImGui::MenuItem("Exit", NULL))
			{
				close();
			}
			ImGui::EndMenu();
		}
		ImGui::EndMenuBar();
	}
	ImGui::End();
}

void Interface::beginMenu()
{
	ImGuiIO& io = ImGui::GetIO();
	const float MIN_SCALE = 0.3f;
	const float MAX_SCALE = 2.0f;
	static float scale = 1.4f;
	io.FontGlobalScale = scale;
	//ImGui::SetNextItemWidth(225);
	//ImGui::DragFloat("global scale", &scale, 0.005f, MIN_SCALE, MAX_SCALE, "%.2f", ImGuiSliderFlags_AlwaysClamp); // Scale everything


	ImGui::SameLine();
	ImGui::SetNextItemWidth(255);
	ImGui::InputFloat("time", &time, 0.01f, 1.0f, "%.3f", ImGuiInputTextFlags_ReadOnly);

	ImGui::SameLine();
	ImGui::SetNextItemWidth(255);
	ImGui::InputFloat("dt", &dt, 0.001f, 1.0f, "%.3f");


}

void Interface::Draw_Canvas()
{
	static float scale[4] = { -1.0f, 2.6f, -1.5f, 1.5f };
	ImGui::SliderFloat4("scale", scale, -3.0f, 3.0f);

	static ImVec4 color2 = ImVec4(0, 0, 1, 1);
	static float  alpha = 1.0f;
	static float  thickness = 1;
	static bool   markers = false;
	static bool   shaded = false;
	static bool   markers2 = false;

	Planet A = GravityModel->get_Sun();
	Planet B = GravityModel->get_Earth();


	if (ImPlot::BeginPlot("Earth and Sun", ImVec2(600, 600))) {
		ImPlot::SetupAxes("X-Axis ", "Y-Axis");
		ImPlot::SetupAxesLimits(scale[0], scale[1], scale[2], scale[3], ImPlotCond_Always);

		ImPlot::SetNextMarkerStyle(0, 5, color2, 0);
		ImPlot::PlotLine("Earth", &B.x, &B.y, 1, 0);

		ImPlot::SetNextLineStyle(color2, thickness);
		ImPlot::PlotLine("Earth trace", &B.trace.Data[0].x, &B.trace.Data[0].y, B.trace.Data.size(), 0, B.trace.Offset, 2 * sizeof(float));


		ImPlot::SetNextMarkerStyle(0, 10, ImVec4(1,1,0,1), 0);
		ImPlot::PlotLine("Sun", &A.x, &A.y, 1, 0);

		if (ImPlot::BeginLegendPopup("Earth trace")) {
			ImGui::Separator();
			ImGui::ColorEdit3("Color", &color2.x);
			ImGui::SliderFloat("Thickness", &thickness, 0, 20);
			ImPlot::EndLegendPopup();
		}
		ImPlot::EndPlot();
	}

	ImGui::SameLine();
	if (ImPlot::BeginPlot("Energy", ImVec2(600, 600))) {
		
		ImPlot::SetupAxes("X-Axis ", "Y-Axis");
		ImPlot::SetupAxesLimits(scale[0], scale[1], scale[2], scale[3], ImPlotCond_Always);

		ImPlot::SetNextLineStyle(ImVec4(0,0,0,-1), 3);
		ImPlot::PlotLine("E_k", &B.E_k.Data[0].x, &B.E_k.Data[0].y, B.E_k.Data.size(), 0, B.E_k.Offset, 2 * sizeof(float));
		ImPlot::SetNextLineStyle(ImVec4(0, 0, 0, -1), 3);
		ImPlot::PlotLine("E_p", &B.E_p.Data[0].x, &B.E_p.Data[0].y, B.E_p.Data.size(), 0, B.E_p.Offset, 2 * sizeof(float));
		ImPlot::SetNextLineStyle(ImVec4(0, 0, 0, -1), 3);
		ImPlot::PlotLine("E_f", &B.E_f.Data[0].x, &B.E_f.Data[0].y, B.E_f.Data.size(), 0, B.E_f.Offset, 2 * sizeof(float));

		ImPlot::EndPlot();
	}
}


void Interface::Draw_parametrs()
{
	ImGui::TextColored(ImVec4(0.0f, 0.0f, 0.0f, 1.0f), "Parametrs");

	Planet B = GravityModel->get_Earth();
	
	
	ImGui::SetNextItemWidth(225);
	ImGui::InputFloat("x", &B.x, 0.01f, 1.0f, "%.2f");
	GravityModel->set_Earth_x(B.x);

	ImGui::SameLine();
	ImGui::SetNextItemWidth(225);
	ImGui::InputFloat("y", &B.y, 0.01f, 1.0f, "%.2f");
	GravityModel->set_Earth_y(B.y);

	ImGui::SameLine();
	ImGui::SetNextItemWidth(225);
	ImGui::InputFloat("vx", &B.vx, 0.01f, 1.0f, "%.2f");
	GravityModel->set_Earth_vx(B.vx);

	ImGui::SameLine();
	ImGui::SetNextItemWidth(225);
	ImGui::InputFloat("vy", &B.vy, 0.01f, 1.0f, "%.2f");
	GravityModel->set_Earth_vy(B.vy);

}


void Interface::onUiDraw()
{
	setupDockspaceMenu();
	ImGui::Begin("Gravity Model");
	beginMenu();
	Draw_Canvas();
	Draw_parametrs();
	ImGui::End();
}
