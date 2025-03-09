#pragma once 

#include <imgui/imgui.h>
#include <imgui/imgui_impl_opengl3.h>
#include <imgui/imgui_impl_glfw.h>
#include <imgui/imgui_impl_sdl3.h>
#include <imgui/imgui_internal.h>

#include "core.hpp"

namespace TE::App
{
	bool IMGUI_Init(const std::shared_ptr<TE::Core::IWindow> nativeWindow);
	void IMGUI_Quit();

	void IMGUI_UseColorDark();
	void IMGUI_UseColorLight();
}