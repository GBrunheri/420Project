#include "triggerbottab.h"

void Triggerbot::RenderTab()
{
	ImGui::Checkbox("Enabled", &Settings::Triggerbot::enabled);
	ImGui::Separator();
	ImGui::Columns(2, NULL, true);
	{
		ImGui::BeginChild("TRIG1", ImVec2(0, 0), true);
		{
			ImGui::Text("Keybind");
			ImGui::Separator();
			ImGui::Columns(2, NULL, true);
			{
				ImGui::ItemSize(ImVec2(0.0f, 0.0f), 0.0f);
				ImGui::Text("Trigger Key");
			}
			ImGui::NextColumn();
			{
				UI::KeyBindButton(&Settings::Triggerbot::key);
			}
			ImGui::Columns(1);
			ImGui::Separator();
			ImGui::Text("Random Delay");
			ImGui::Separator();
			ImGui::Columns(2, NULL, true);
			{
				ImGui::Checkbox("Enabled", &Settings::Triggerbot::RandomDelay::enabled);
				SetTooltip("Adiciona um delay aleatório em milissegundos ao Triggerbot");
				if( Settings::Triggerbot::RandomDelay::lastRoll != 0 )
				{
					ImGui::Text("Last delay: %dms", Settings::Triggerbot::RandomDelay::lastRoll);
				}
			}
			ImGui::NextColumn();
			{
				ImGui::Text("Minimum ms");
				ImGui::SliderInt("##TRIGGERRANDOMLOW", &Settings::Triggerbot::RandomDelay::lowBound, 5, 220);
				if( Settings::Triggerbot::RandomDelay::lowBound >= Settings::Triggerbot::RandomDelay::highBound )
				{
					Settings::Triggerbot::RandomDelay::highBound = Settings::Triggerbot::RandomDelay::lowBound + 1;
				}
				ImGui::Text("Maximum ms");
				ImGui::SliderInt("##TRIGGERRANDOMHIGH", &Settings::Triggerbot::RandomDelay::highBound, (Settings::Triggerbot::RandomDelay::lowBound+1), 225);
			}
			ImGui::Columns(1);
			ImGui::Separator();
			ImGui::Text("Auto Knife & Zeus");
			ImGui::Separator();
			ImGui::Columns(2, NULL, true);
			{
					ImGui::PushItemWidth(-1);
					ImGui::Checkbox("Auto Knife", &Settings::AutoKnife::enabled);
					SetTooltip("Ataca inimigos com a faca e zeus ao chegar na distancia correta");
					ImGui::Checkbox("On Key", &Settings::AutoKnife::onKey);
					SetTooltip("Ataca apenas se a tecla do triggerbot está pressionada");

			}
			ImGui::NextColumn();
			{
					ImGui::PushItemWidth(-1);
					ImGui::Checkbox("Enemies", &Settings::AutoKnife::Filters::enemies);
					SetTooltip("Attack enemies");
					ImGui::Checkbox("Allies", &Settings::AutoKnife::Filters::allies);
					SetTooltip("Attack allies");
			}
			ImGui::EndChild();
		}
	}
	ImGui::NextColumn();
	{
		ImGui::BeginChild("TRIG2", ImVec2(0, 0), true);
		{
			ImGui::Text("Minimum Inaccuracy");
			ImGui::Separator();
			ImGui::Columns(2, NULL, true);
			{
				ImGui::Checkbox("Enabled", &Settings::Triggerbot::Inaccuracy::enabled);
				SetTooltip("Adiciona opção para não atirar com o Triggerbot acima de um valor de imprecisão");
			}
			ImGui::NextColumn();
			{
				ImGui::Text("Minimum Value");
				ImGui::SliderFloat("##TRIGGERMININACC", &Settings::Triggerbot::Inaccuracy::minInaccuracy, 0, 1);
			}
			ImGui::Columns(1);
			ImGui::Text("Filter");
			ImGui::Separator();
			ImGui::Columns(2, NULL, true);
			{
				ImGui::Checkbox("Enemies", &Settings::Triggerbot::Filters::enemies);
				SetTooltip("Atira em inimigos");
				ImGui::Checkbox("Walls", &Settings::Triggerbot::Filters::walls);
				SetTooltip("Atira em inimigos atrás de paredes");
				ImGui::Checkbox("Head", &Settings::Triggerbot::Filters::head);
				SetTooltip("Atira na cabeça");
				ImGui::Checkbox("Chest", &Settings::Triggerbot::Filters::chest);
				SetTooltip("Atira no peito");
				ImGui::Checkbox("Legs", &Settings::Triggerbot::Filters::legs);
				SetTooltip("Atira nas pernas");
			}
			ImGui::NextColumn();
			{
				ImGui::Checkbox("Allies", &Settings::Triggerbot::Filters::allies);
				SetTooltip("Atira em aliados");
				ImGui::Checkbox("Smoke check", &Settings::Triggerbot::Filters::smokeCheck);
				SetTooltip("Não atira em inimigos atras de smokes");
				ImGui::Checkbox("Flash check", &Settings::Triggerbot::Filters::flashCheck);
				SetTooltip("Não atira enquanto cego (flashbangs)");
				ImGui::Checkbox("Stomach", &Settings::Triggerbot::Filters::stomach);
				SetTooltip("Atira no estomago");
				ImGui::Checkbox("Arms", &Settings::Triggerbot::Filters::arms);
				SetTooltip("Atira nos braços");
			}
			ImGui::Columns(1);
			ImGui::Separator();
			ImGui::EndChild();
		}
	}
}
