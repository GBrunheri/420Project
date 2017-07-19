#include "visualstab.h"

static char skyName[127] = "";

void Visuals::RenderTab()
{
	const char* BoxTypes[] = { "Flat 2D", "Frame 2D", "Box 3D", "Hitboxes" };
	const char* TracerTypes[] = { "Bottom", "Cursor" };
	const char* BarTypes[] = { "Vertical Left", "Vertical Right", "Horizontal Below", "Horizontal Above", "Interwebz" };
	const char* BarColorTypes[] = { "Static", "Health Based" };
	const char* TeamColorTypes[] = { "Absolute", "Relative" };
	const char* ChamsTypes[] = { "Normal", "Normal - XQZ", "Flat", "Flat - XQZ" };
	const char* ArmsTypes[] = { "Default", "Wireframe", "None" };

	ImGui::Columns(2, NULL, true);
	{
		ImGui::Checkbox("Enabled", &Settings::ESP::enabled);
		ImGui::NextColumn();
		ImGui::Text("Only on Key");
		UI::KeyBindButton(&Settings::ESP::key);
	}
	ImGui::Separator();

	ImGui::Columns(2, NULL, true);
	{
		ImGui::BeginChild("COL1", ImVec2(0, 0), true);
		{
			ImGui::Text("ESP");
			ImGui::BeginChild("ESP", ImVec2(0, 0), true);
			ImGui::Text("Type");
			ImGui::Separator();
			ImGui::Columns(2, NULL, true);
			{
				ImGui::Checkbox("Outline Box", &Settings::ESP::Boxes::enabled);
				SetTooltip("Desenha um retângulo em volta dos players");
				ImGui::Checkbox("Chams", &Settings::ESP::Chams::enabled);
				SetTooltip("Muda a textura do modelo dos players");
				ImGui::Checkbox("Health", &Settings::ESP::Bars::enabled);
				SetTooltip("Mostra a vida dos players em uma 'barra'");
				ImGui::Checkbox("Tracers", &Settings::ESP::Tracers::enabled);
				SetTooltip("Desenha uma linha até os players");
				ImGui::ItemSize(ImVec2(0.0f, 0.0f), 0.0f);
				ImGui::Text("Bar Color");
				ImGui::ItemSize(ImVec2(0.0f, 0.0f), 0.0f);
				ImGui::Text("Team Color");
				ImGui::ItemSize(ImVec2(0.0f, 0.0f), 0.0f);
				ImGui::Checkbox("Bullet Tracers", &Settings::ESP::BulletTracers::enabled);
				SetTooltip("Desenha uma linha mostrando onde os players estao mirando");
				ImGui::Checkbox("Head Dot", &Settings::ESP::HeadDot::enabled);
				SetTooltip("Desenha um ponto na cabeça dos players");
			}
			ImGui::NextColumn();
			{
				ImGui::PushItemWidth(-1);
				ImGui::Combo("##BOXTYPE", (int*)& Settings::ESP::Boxes::type, BoxTypes, IM_ARRAYSIZE(BoxTypes));
				ImGui::Combo("##CHAMSTYPE", (int*)& Settings::ESP::Chams::type, ChamsTypes, IM_ARRAYSIZE(ChamsTypes));
				ImGui::Combo("##BARTYPE", (int*)& Settings::ESP::Bars::type, BarTypes, IM_ARRAYSIZE(BarTypes));
				ImGui::Combo("##TRACERTYPE", (int*)& Settings::ESP::Tracers::type, TracerTypes, IM_ARRAYSIZE(TracerTypes));
				ImGui::Combo("##BARCOLTYPE", (int*)& Settings::ESP::Bars::colorType, BarColorTypes, IM_ARRAYSIZE(BarColorTypes));
				ImGui::Combo("##TEAMCOLTYPE", (int*)& Settings::ESP::teamColorType, TeamColorTypes, IM_ARRAYSIZE(TeamColorTypes));
				ImGui::PopItemWidth();
				ImGui::Checkbox("Skeleton", &Settings::ESP::Skeleton::enabled);
				SetTooltip("Show a players skeleton");
				ImGui::PushItemWidth(-1);
				ImGui::SliderFloat("##HDOTSIZE", &Settings::ESP::HeadDot::size, 1.f, 10.f, "Size: %0.3f");
				ImGui::PopItemWidth();
			}
			ImGui::Columns(1);
			ImGui::Separator();
			ImGui::Text("Filter");
			ImGui::Separator();
			ImGui::Columns(2, NULL, true);
			{
				ImGui::Checkbox("Enemies", &Settings::ESP::Filters::enemies);
				SetTooltip("Mostrar inimigos");
				ImGui::Checkbox("Chickens", &Settings::ESP::Filters::chickens);
				SetTooltip("Mostrar Galinhas");
				ImGui::Checkbox("LocalPlayer", &Settings::ESP::Filters::localplayer);
				SetTooltip("Mostrar você mesmo (terceira pessoa)");
				ImGui::Checkbox("Legit Mode", &Settings::ESP::Filters::legit);
				SetTooltip("Não mostra inimigos que não estão visiveis");
			}
			ImGui::NextColumn();
			{
				ImGui::Checkbox("Allies", &Settings::ESP::Filters::allies);
				SetTooltip("Mostra aliados");
				ImGui::Checkbox("Fish", &Settings::ESP::Filters::fishes);
				SetTooltip("Mostra peixes");
				ImGui::Checkbox("Smoke Check", &Settings::ESP::Filters::smokeCheck);
				SetTooltip("Marca players atras/dentro de smokes como invisiveis");
				ImGui::Checkbox("Visiblity Check", &Settings::ESP::Filters::visibilityCheck);
				SetTooltip("Muda a cor do retangulo se você consegue ver o player ou não.");
			}
			ImGui::Columns(1);
			ImGui::Separator();
			ImGui::Text("Player Information");
			ImGui::Separator();
			ImGui::Columns(2, NULL, true);
			{
				ImGui::Checkbox("Clan", &Settings::ESP::Info::clan);
				SetTooltip("Mostra o clan do player");
				ImGui::Checkbox("Rank", &Settings::ESP::Info::rank);
				SetTooltip("Mostra a patente do player");
				ImGui::PushID(1);
				ImGui::Checkbox("Health", &Settings::ESP::Info::health);
				SetTooltip("Mostra a vida do player");
				ImGui::PopID();
				ImGui::Checkbox("Scoped", &Settings::ESP::Info::scoped);
				SetTooltip("Mostra se estão com a mira aberta");
				ImGui::Checkbox("Flashed", &Settings::ESP::Info::flashed);
				SetTooltip("Mostra se o player está cego");
				ImGui::Checkbox("Defuse Kit", &Settings::ESP::Info::hasDefuser);
				SetTooltip("Mostra se o player tem defuse");
				ImGui::Checkbox("Grabbing Hostage", &Settings::ESP::Info::grabbingHostage);
				SetTooltip("Mostra se o player está pegando o refém");
				ImGui::Checkbox("Location", &Settings::ESP::Info::location);
				SetTooltip("Mostra a localização(call) do player");
			}
			ImGui::NextColumn();
			{
				ImGui::Checkbox("Name", &Settings::ESP::Info::name);
				SetTooltip("Mostra o nome do player");
				ImGui::Checkbox("Steam ID", &Settings::ESP::Info::steamId);
				SetTooltip("Mostra a Steam ID do player");
				ImGui::Checkbox("Weapon", &Settings::ESP::Info::weapon);
				SetTooltip("Mostra qual arma o player está segurando");
				ImGui::Checkbox("Reloading", &Settings::ESP::Info::reloading);
				SetTooltip("Mostra se o player está recarregando");
				ImGui::Checkbox("Planting", &Settings::ESP::Info::planting);
				SetTooltip("Mostra se o player está plantando a bomba");
				ImGui::Checkbox("Defusing", &Settings::ESP::Info::defusing);
				SetTooltip("Mostra se o player está defusando a bomba");
				ImGui::Checkbox("Rescuing Hostage", &Settings::ESP::Info::rescuing);
				SetTooltip("Mostra se o player está segurando um refém");
			}

			ImGui::Columns(1);
			ImGui::Separator();
			ImGui::Text("World");
			ImGui::Separator();
			ImGui::Columns(2, NULL, true);
			{
				ImGui::Checkbox("Weapons", &Settings::ESP::Filters::weapons);
				SetTooltip("Mostra armas dropadas no mapa");
				ImGui::Checkbox("Throwables", &Settings::ESP::Filters::throwables);
				SetTooltip("Mostra granadas");
				ImGui::Checkbox("Entity Glow", &Settings::ESP::Glow::enabled);
				SetTooltip("Wallhack de Glow (igual no modo espectador)");
			}
			ImGui::NextColumn();
			{
				ImGui::Checkbox("Bomb", &Settings::ESP::Filters::bomb);
				SetTooltip("Mostra a bomba plantada");
				ImGui::Checkbox("Defuse Kits", &Settings::ESP::Filters::defusers);
				SetTooltip("Mostra kits de defuse dropados no mapa");
				ImGui::Checkbox("Hostages", &Settings::ESP::Filters::hostages);
				SetTooltip("Mostra reféns");
			}
			ImGui::Columns(1);
			ImGui::EndChild();
			ImGui::EndChild();
		}
	}

	ImGui::NextColumn();
	{
		ImGui::BeginChild("Chams", ImVec2(0, 0), true);
		{
			ImGui::Text("Crosshair");
			ImGui::Separator();
			ImGui::Columns(2, NULL, true);
			{
				ImGui::Checkbox("Recoil Crosshair", &Settings::Recoilcrosshair::enabled);
				SetTooltip("Desenha um crosshair baseado em recuo");
				ImGui::Checkbox("FOV Circle", &Settings::ESP::FOVCrosshair::enabled);
				SetTooltip("Desenha um circulo representando o FOV do aimbot");
				ImGui::Checkbox("Show Spread", &Settings::ESP::Spread::enabled);
				SetTooltip("Mostra onde suas balas possivelmente vão atingir");
			}
			ImGui::NextColumn();
			{
				ImGui::Checkbox("Only When Shooting", &Settings::Recoilcrosshair::showOnlyWhenShooting);
				SetTooltip("Mostra o crosshair de recuo apenas enquanto atirando");
				ImGui::Checkbox("Filled", &Settings::ESP::FOVCrosshair::filled);
				SetTooltip("O circulo de fov não é transparente no seu centro");
				ImGui::Checkbox("Show SpreadLimit", &Settings::ESP::Spread::spreadLimit);
				SetTooltip("Mostra a porcentagem de limite de spread");
			}
			ImGui::Columns(1);
			ImGui::Separator();
			ImGui::Text("Other Visual Settings");
			ImGui::Separator();
			ImGui::Columns(2, NULL, true);
			{
				ImGui::Checkbox("Arms", &Settings::ESP::Chams::Arms::enabled);
				SetTooltip("Muda a textura dos braços");
				ImGui::Checkbox("Dlights", &Settings::Dlights::enabled);
				SetTooltip("Adiciona uma fonte de luz nos players, brilham no escuro.");
				ImGui::Checkbox("No Flash", &Settings::Noflash::enabled);
				SetTooltip("Não fica cego com flashbangs");
				ImGui::Checkbox("Show Footsteps", &Settings::ESP::Sounds::enabled);
				SetTooltip("Mostra o local de origem dos barulhos de passos dos players");
				ImGui::Checkbox("No View Punch", &Settings::View::NoViewPunch::enabled);
				SetTooltip("Desativa o recuo visual enquanto atira");
				ImGui::Checkbox("Weapons", &Settings::ESP::Chams::Weapon::enabled);
				SetTooltip("Muda a textura da arma");
				ImGui::Checkbox("No Sky", &Settings::NoSky::enabled);
				SetTooltip("Muda a cor do céu, ou o desativa completamente");
				ImGui::Checkbox("No Smoke", &Settings::NoSmoke::enabled);
				SetTooltip("Não mostra smokes no mapa.");
			}
			ImGui::NextColumn();
			{
				ImGui::PushItemWidth(-1);
				ImGui::Combo("##ARMSTYPE", (int*)& Settings::ESP::Chams::Arms::type, ArmsTypes, IM_ARRAYSIZE(ArmsTypes));
				ImGui::SliderFloat("##DLIGHTRADIUS", &Settings::Dlights::radius, 0, 1000, "Radius: %0.f");
				ImGui::SliderFloat("##NOFLASHAMOUNT", &Settings::Noflash::value, 0, 255, "Amount: %0.f");
				ImGui::SliderInt("##SOUNDSTIME", &Settings::ESP::Sounds::time, 250, 5000, "Timeout: %0.f");
				ImGui::PopItemWidth();
				ImGui::Checkbox("No Aim Punch", &Settings::View::NoAimPunch::enabled);
				SetTooltip("Desativa o recuo VISUAL da arma enquantoa atira");
				ImGui::Checkbox("ASUS Walls", &Settings::ASUSWalls::enabled);
				SetTooltip("Deixa a textura das paredes transparente");
				if (ImGui::InputText("##SKYNAME", skyName, 127, ImGuiInputTextFlags_EnterReturnsTrue))
					Skychanger::SetSky(std::string(skyName).c_str());
				SetTooltip("Nome do céu customizado");
				ImGui::Checkbox("No Scope Border", &Settings::NoScopeBorder::enabled);
				SetTooltip("Desativa a parte preta do scope nas armas");
				ImGui::Checkbox("Autowall Debug", &Settings::ESP::AutoWall::debugView);
				SetTooltip("Mostra o dano possivel do autowall nos players\nAtive os visuais e cheque os filtros para usar (DEBUG)");
			}
			ImGui::Columns(1);
			ImGui::Separator();
			ImGui::Text("Radar");
			ImGui::Separator();
			ImGui::Columns(2, NULL, true);
			{
				ImGui::Checkbox("Radar", &Settings::Radar::enabled);
				SetTooltip("Mostra os players em um radar customizado");
				ImGui::PushItemWidth(-1);
				ImGui::Combo("##RADARTEAMCOLTYPE", (int*)& Settings::Radar::teamColorType, TeamColorTypes, IM_ARRAYSIZE(TeamColorTypes));
				ImGui::PopItemWidth();
				ImGui::Checkbox("Enemies", &Settings::Radar::enemies);
				ImGui::Checkbox("Bomb", &Settings::Radar::bomb);
				ImGui::Checkbox("Legit", &Settings::Radar::legit);
				ImGui::Checkbox("In-game Radar", &Settings::Radar::InGame::enabled);
				SetTooltip("Mostra os players no radar do jogo, mesmo sem ter sido vistos por outros players");
			}
			ImGui::NextColumn();
			{
				ImGui::PushItemWidth(-1);
				ImGui::SliderFloat("##RADARZOOM", &Settings::Radar::zoom, 0.f, 100.f, "Zoom: %0.f");
				ImGui::SliderFloat("##RADARICONSSCALE", &Settings::Radar::iconsScale, 2, 16, "Icons Scale: %0.1f");
				ImGui::PopItemWidth();
				ImGui::Checkbox("Allies", &Settings::Radar::allies);
				ImGui::Checkbox("Defuser", &Settings::Radar::defuser);
				ImGui::Checkbox("Visibility Check", &Settings::Radar::visibilityCheck);
				ImGui::Checkbox("Smoke Check", &Settings::Radar::smokeCheck);
			}
			ImGui::Columns(1);
			ImGui::Separator();

			ImGui::Text("Hitmarkers");
			ImGui::Separator();
			ImGui::Columns(2, NULL, true);
			{
				ImGui::Checkbox("Hitmarkers", &Settings::ESP::Hitmarker::enabled);
				SetTooltip("Mostra quando você acerta um tiro em algum player");

				ImGui::Checkbox("Enemies##HITMARKERS", &Settings::ESP::Hitmarker::enemies);
				ImGui::Checkbox("Allies##HITMARKERS", &Settings::ESP::Hitmarker::allies);
				ImGui::Checkbox("Damage##HITMARKERS", &Settings::ESP::Hitmarker::Damage::enabled);
				SetTooltip("Mostra o dano causado próximo ao hitmarker");
			}
			ImGui::NextColumn();
			{
				ImGui::PushItemWidth(-1);
				ImGui::SliderInt("##HITMARKERDUR", &Settings::ESP::Hitmarker::duration, 250, 3000, "Timeout: %0.f");
				ImGui::SliderInt("##HITMARKERSIZE", &Settings::ESP::Hitmarker::size, 1, 32, "Size: %0.f");
				ImGui::SliderInt("##HITMARKERGAP", &Settings::ESP::Hitmarker::innerGap, 1, 16, "Gap: %0.f");
				ImGui::PopItemWidth();
			}
			ImGui::Columns(1);
			ImGui::Separator();

			ImGui::EndChild();
		}
	}
	ImGui::Columns(1);
}
