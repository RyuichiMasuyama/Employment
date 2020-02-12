#pragma once

#include <Windows.h>

// ImGuiä÷åWÇÃÉwÉbÉ_Å[
#include "imgui.h"
#include "imgui_impl_win32.h"
#include "imgui_impl_dx11.h"

inline void ImGuiSetUp(const HWND& _hwnd,ID3D11Device* _device, ID3D11DeviceContext*_deviceCon) {
#ifndef _DEBUG
#else   
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	ImGui::StyleColorsDark();
	ImGui_ImplWin32_Init(_hwnd);
	ImGui_ImplDX11_Init(_device, _deviceCon);
#endif
}

inline void ImGuiCreanUp() {
#ifndef _DEBUG
#else
	ImGui_ImplDX11_Shutdown();
	ImGui_ImplWin32_Shutdown();
	ImGui::DestroyContext();
#endif
}

