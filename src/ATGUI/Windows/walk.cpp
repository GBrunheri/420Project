#include "walk.h"

bool Walk::showWindow = false;


void Walk::RenderWindow()
{
	if( !Walk::showWindow )
		return;

	ImGui::SetNextWindowSize(ImVec2(320, 240), ImGuiSetCond_Always);
	if (ImGui::Begin("Walkbot", &Walk::showWindow, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_ShowBorders | ImGuiWindowFlags_NoResize))
	{
		ImGui::Text("Dust 2 Walkbot");

		if (ImGui::Checkbox("Enable", &Settings::WalkBot::enabled)){
			cvar->ConsoleDPrintf("\n---WalkBot %s---\n", Settings::WalkBot::enabled ? "ON" : "OFF");
		}
		SetTooltip("Liga o bot de movimento automatico para Dust 2");

		ImGui::SameLine();
		if (ImGui::Button("Reset")){
			Settings::WalkBot::forceReset = true;
		}
		SetTooltip("Reseta a movimentação (se ficar preso em algum canto)");

		ImGui::Separator();

		if (ImGui::Checkbox("Autobuy", &Settings::WalkBot::autobuy)){
			cvar->ConsoleColorPrintf(ColorRGBA(100, 150, 90), "\n---WalkBot-AutoBuy %s---\n", Settings::WalkBot::autobuy ? "ON" : "OFF");
		}
		ImGui::SameLine();
		ImGui::SliderInt("autobuyAt", &Settings::WalkBot::autobuyAt, 0, 16000, "Autobuy At $%0.f");
		SetTooltip("Quanto de dinheiro você vai acumular até comprar armas automaticamente\n (Ctrl-Click) para escrever");

		ImGui::End();
	}
}
