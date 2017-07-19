#include "../atgui.h"

static ItemDefinitionIndex currentWeapon = ItemDefinitionIndex::INVALID;
static bool enabled = false;
static bool silent = false;
static bool pSilent = false;
static bool friendly = false;
static bool moveMouse = false;
static bool closestBone = false;
static bool desiredBones[] = {true, true, true, true, true, true, true, // center mass
							  false, false, false, false, false, false, false, // left arm
							  false, false, false, false, false, false, false, // right arm
							  false, false, false, false, false, // left leg
							  false, false, false, false, false  // right leg
							 };
static bool engageLock = false;
static bool engageLockTR = false; // Target Reacquisition
static int engageLockTTR = 700; // Time to Target Reacquisition ( in ms )
static Bone bone = Bone::BONE_HEAD;
static ButtonCode_t aimkey = ButtonCode_t::MOUSE_MIDDLE;
static bool aimkeyOnly = false;
static bool smoothEnabled = false;
static float smoothValue = 0.5f;
static SmoothType smoothType = SmoothType::SLOW_END;
static bool smoothSaltEnabled = false;
static float smoothSaltMultiplier = 0.0f;
static bool errorMarginEnabled = false;
static float errorMarginValue = 0.0f;
static bool curveEnabled = false;
static float curveAmount = 0.5f;
static bool autoAimEnabled = false;
static float autoAimValue = 180.0f;
static bool aimStepEnabled = false;
static float aimStepValue = 25.0f;
static bool rcsEnabled = false;
static bool rcsAlwaysOn = false;
static float rcsAmountX = 2.0f;
static float rcsAmountY = 2.0f;
static bool autoCockRevolver = false;
static bool autoPistolEnabled = false;
static bool autoShootEnabled = false;
static bool autoScopeEnabled = false;
static bool noShootEnabled = false;
static bool ignoreJumpEnabled = false;
static bool smokeCheck = false;
static bool flashCheck = false;
static bool spreadLimitEnabled = false;
static bool spreadLimitDistance = false;
static float spreadLimit = 0.1f;
static bool autoWallEnabled = false;
static float autoWallValue = 10.0f;
static bool autoWallBones[] = { true, false, false, false, false, false };
static bool autoAimRealDistance = false;
static bool autoSlow = false;
static bool predEnabled = false;
static bool hitChanceEnabled = false;
static int hitChanceRays = 100;
static float hitChanceValue = 0.5f;

void UI::ReloadWeaponSettings()
{
	ItemDefinitionIndex index = ItemDefinitionIndex::INVALID;
	if (Settings::Aimbot::weapons.find(currentWeapon) != Settings::Aimbot::weapons.end())
		index = currentWeapon;

	enabled = Settings::Aimbot::weapons.at(index).enabled;
	silent = Settings::Aimbot::weapons.at(index).silent;
	pSilent = Settings::Aimbot::weapons.at(index).pSilent;
	friendly = Settings::Aimbot::weapons.at(index).friendly;
	moveMouse = Settings::Aimbot::weapons.at(index).moveMouse;
	closestBone = Settings::Aimbot::weapons.at(index).closestBone;
	engageLock = Settings::Aimbot::weapons.at(index).engageLock;
	engageLockTR = Settings::Aimbot::weapons.at(index).engageLockTR;
	engageLockTTR = Settings::Aimbot::weapons.at(index).engageLockTTR;
	bone = Settings::Aimbot::weapons.at(index).bone;
	aimkey = Settings::Aimbot::weapons.at(index).aimkey;
	aimkeyOnly = Settings::Aimbot::weapons.at(index).aimkeyOnly;
	smoothEnabled = Settings::Aimbot::weapons.at(index).smoothEnabled;
	smoothValue = Settings::Aimbot::weapons.at(index).smoothAmount;
	smoothType = Settings::Aimbot::weapons.at(index).smoothType;
	smoothSaltEnabled = Settings::Aimbot::weapons.at(index).smoothSaltEnabled;
	smoothSaltMultiplier = Settings::Aimbot::weapons.at(index).smoothSaltMultiplier;
	errorMarginEnabled = Settings::Aimbot::weapons.at(index).errorMarginEnabled;
	errorMarginValue = Settings::Aimbot::weapons.at(index).errorMarginValue;
	curveEnabled = Settings::Aimbot::weapons.at(index).curveAmount;
	curveAmount = Settings::Aimbot::weapons.at(index).curveAmount;
	autoAimEnabled = Settings::Aimbot::weapons.at(index).autoAimEnabled;
	autoAimValue = Settings::Aimbot::weapons.at(index).autoAimFov;
	aimStepEnabled = Settings::Aimbot::weapons.at(index).aimStepEnabled;
	aimStepValue = Settings::Aimbot::weapons.at(index).aimStepValue;
	rcsEnabled = Settings::Aimbot::weapons.at(index).rcsEnabled;
	rcsAlwaysOn = Settings::Aimbot::weapons.at(index).rcsAlwaysOn;
	rcsAmountX = Settings::Aimbot::weapons.at(index).rcsAmountX;
	rcsAmountY = Settings::Aimbot::weapons.at(index).rcsAmountY;
	autoCockRevolver = Settings::Aimbot::weapons.at(index).autoCockRevolver;
	autoPistolEnabled = Settings::Aimbot::weapons.at(index).autoPistolEnabled;
	autoShootEnabled = Settings::Aimbot::weapons.at(index).autoShootEnabled;
	autoScopeEnabled = Settings::Aimbot::weapons.at(index).autoScopeEnabled;
	noShootEnabled = Settings::Aimbot::weapons.at(index).noShootEnabled;
	ignoreJumpEnabled = Settings::Aimbot::weapons.at(index).ignoreJumpEnabled;
	smokeCheck = Settings::Aimbot::weapons.at(index).smokeCheck;
	flashCheck = Settings::Aimbot::weapons.at(index).flashCheck;
	spreadLimitEnabled = Settings::Aimbot::weapons.at(index).spreadLimitEnabled;
	spreadLimitDistance = Settings::Aimbot::weapons.at(index).spreadLimitDistance;
	spreadLimit = Settings::Aimbot::weapons.at(index).spreadLimit;
	autoWallEnabled = Settings::Aimbot::weapons.at(index).autoWallEnabled;
	autoWallValue = Settings::Aimbot::weapons.at(index).autoWallValue;
	autoAimRealDistance = Settings::Aimbot::weapons.at(index).autoAimRealDistance;
	autoSlow = Settings::Aimbot::weapons.at(index).autoSlow;
	predEnabled = Settings::Aimbot::weapons.at(index).predEnabled;
	hitChanceEnabled = Settings::Aimbot::weapons.at(index).hitChanceEnabled;
	hitChanceRays = Settings::Aimbot::weapons.at(index).hitChanceRays;
	hitChanceValue = Settings::Aimbot::weapons.at(index).hitChanceValue;

	for (int bone = (int) Hitbox::HITBOX_HEAD; bone <= (int) Hitbox::HITBOX_ARMS; bone++)
		autoWallBones[bone] = Settings::Aimbot::weapons.at(index).autoWallBones[bone];
	for (int bone = (int) DesiredBones::BONE_PELVIS; bone <= (int) DesiredBones::BONE_RIGHT_SOLE; bone++)
		desiredBones[bone] = Settings::Aimbot::weapons.at(index).desiredBones[bone];
}

void UI::UpdateWeaponSettings()
{
	if (Settings::Aimbot::weapons.find(currentWeapon) == Settings::Aimbot::weapons.end())
		Settings::Aimbot::weapons[currentWeapon] = AimbotWeapon_t();

	AimbotWeapon_t settings = {
			enabled, silent, pSilent, friendly, closestBone, engageLock, engageLockTR, engageLockTTR, bone, aimkey, aimkeyOnly,
			smoothEnabled, smoothValue, smoothType, smoothSaltEnabled, smoothSaltMultiplier,
			errorMarginEnabled, errorMarginValue,
			curveEnabled, curveAmount,
			autoAimEnabled, autoAimValue, aimStepEnabled, aimStepValue,
			rcsEnabled, rcsAlwaysOn, rcsAmountX, rcsAmountY,
			autoCockRevolver, autoPistolEnabled, autoShootEnabled, autoScopeEnabled,
			noShootEnabled, ignoreJumpEnabled, smokeCheck, flashCheck, spreadLimitEnabled, spreadLimitDistance, spreadLimit, autoWallEnabled, autoWallValue, autoAimRealDistance, autoSlow, predEnabled, moveMouse, hitChanceEnabled, hitChanceRays, hitChanceValue
	};

	for (int bone = (int) Hitbox::HITBOX_HEAD; bone <= (int) Hitbox::HITBOX_ARMS; bone++)
		settings.autoWallBones[bone] = autoWallBones[bone];

	for (int bone = (int) DesiredBones::BONE_PELVIS; bone <= (int) DesiredBones::BONE_RIGHT_SOLE; bone++)
		settings.desiredBones[bone] = desiredBones[bone];

	Settings::Aimbot::weapons.at(currentWeapon) = settings;

	if (Settings::Aimbot::weapons.at(currentWeapon) == Settings::Aimbot::weapons.at(ItemDefinitionIndex::INVALID) &&
		currentWeapon != ItemDefinitionIndex::INVALID)
	{
		Settings::Aimbot::weapons.erase(currentWeapon);
		UI::ReloadWeaponSettings();
	}
}

void Aimbot::RenderTab()
{
	const char* targets[] = { "PELVIS", "", "", "HIP", "LOWER SPINE", "MIDDLE SPINE", "UPPER SPINE", "NECK", "HEAD" };
	const char* smoothTypes[] = { "Slow Near End", "Constant Speed", "Fast Near End" };
	static char filterWeapons[32];

	if (ImGui::Checkbox("Enabled", &enabled))
		UI::UpdateWeaponSettings();
	ImGui::Separator();

	ImGui::Columns(3, NULL, true);
	{
		ImGui::SetColumnOffset(1, 200);
		ImGui::PushItemWidth(-1);
		ImGui::InputText("##FILTERWEAPONS", filterWeapons, IM_ARRAYSIZE(filterWeapons));
		ImGui::PopItemWidth();
		ImGui::ListBoxHeader("##GUNS", ImVec2(-1, -1));
		for (auto it : ItemDefinitionIndexMap)
		{
			bool isDefault = (int) it.first < 0;
			if (!isDefault && !Util::Contains(Util::ToLower(std::string(filterWeapons)), Util::ToLower(Util::Items::GetItemDisplayName(it.first).c_str())))
				continue;

			if (Util::Items::IsKnife(it.first) || Util::Items::IsGlove(it.first) || Util::Items::IsUtility(it.first))
				continue;

			const bool item_selected = ((int) it.first == (int) currentWeapon);
			ImGui::PushID((int) it.first);
			std::string formattedName;
			char changeIndicator = ' ';
			bool isChanged = Settings::Aimbot::weapons.find(it.first) != Settings::Aimbot::weapons.end();
			if (!isDefault && isChanged)
				changeIndicator = '*';
			formattedName = changeIndicator + (isDefault ? Util::Items::GetItemDisplayName(it.first).c_str() : Util::Items::GetItemDisplayName(it.first));
			if (ImGui::Selectable(formattedName.c_str(), item_selected))
			{
				currentWeapon = it.first;
				UI::ReloadWeaponSettings();
			}
			ImGui::PopID();
		}
		ImGui::ListBoxFooter();
	}
	ImGui::NextColumn();
	{
		ImGui::SetColumnOffset(2, ImGui::GetWindowWidth() / 2 + 75);
		ImGui::BeginChild("COL1", ImVec2(0, 0), true);
		{
			ImGui::Text("Target");
			ImGui::Separator();
			ImGui::Columns(2, NULL, false);
			{
				if (ImGui::Checkbox("FriendlyFire", &friendly))
					UI::UpdateWeaponSettings();
				SetTooltip("Mira em aliados se ativado.");
			}
			ImGui::NextColumn();
			{
				ImGui::PushItemWidth(-1);
				ImGui::Text("Aimbot Target");
				if(!closestBone){
					if (ImGui::Combo("##AIMTARGET", (int*)& bone, targets, IM_ARRAYSIZE(targets)))
						UI::UpdateWeaponSettings();
				}
				if( closestBone )
				{
					if(ImGui::Button("Bones", ImVec2(-1, 0)))
						ImGui::OpenPopup("optionBones");
					ImGui::SetNextWindowSize(ImVec2((ImGui::GetWindowWidth()/1.25f),ImGui::GetWindowHeight()), ImGuiSetCond_Always);
					if( ImGui::BeginPopup("optionBones") )
					{
						ImGui::PushItemWidth(-1);
						ImGui::Text("Center Mass\n");
						if( ImGui::Checkbox("Head", &desiredBones[(int)DesiredBones::BONE_HEAD]) )
							UI::UpdateWeaponSettings();
						if( ImGui::Checkbox("Neck", &desiredBones[(int)DesiredBones::BONE_NECK]) )
							UI::UpdateWeaponSettings();
						if( ImGui::Checkbox("Upper Spine", &desiredBones[(int)DesiredBones::BONE_UPPER_SPINAL_COLUMN]) )
							UI::UpdateWeaponSettings();
						if( ImGui::Checkbox("Middle Spine", &desiredBones[(int)DesiredBones::BONE_MIDDLE_SPINAL_COLUMN]) )
							UI::UpdateWeaponSettings();
						if( ImGui::Checkbox("Lower Spine", &desiredBones[(int)DesiredBones::BONE_LOWER_SPINAL_COLUMN]) )
							UI::UpdateWeaponSettings();
						if( ImGui::Checkbox("Pelvis", &desiredBones[(int)DesiredBones::BONE_PELVIS]) )
							UI::UpdateWeaponSettings();
						if( ImGui::Checkbox("Hip", &desiredBones[(int)DesiredBones::BONE_HIP]) )
							UI::UpdateWeaponSettings();
						ImGui::Separator();

						ImGui::Columns(2, NULL, false);
						{
							ImGui::Text("Player's Right Arm\n");
							if( ImGui::Checkbox("Collarbone", &desiredBones[(int)DesiredBones::BONE_RIGHT_COLLARBONE]) )
								UI::UpdateWeaponSettings();
							if( ImGui::Checkbox("Shoulder", &desiredBones[(int)DesiredBones::BONE_RIGHT_SHOULDER]) )
								UI::UpdateWeaponSettings();
							if( ImGui::Checkbox("Armpit", &desiredBones[(int)DesiredBones::BONE_RIGHT_ARMPIT]) )
								UI::UpdateWeaponSettings();
							if( ImGui::Checkbox("Bicep", &desiredBones[(int)DesiredBones::BONE_RIGHT_BICEP]) )
								UI::UpdateWeaponSettings();
							if( ImGui::Checkbox("Elbow", &desiredBones[(int)DesiredBones::BONE_RIGHT_ELBOW]) )
								UI::UpdateWeaponSettings();
							if( ImGui::Checkbox("Forearm", &desiredBones[(int)DesiredBones::BONE_RIGHT_FOREARM]) )
								UI::UpdateWeaponSettings();
							if( ImGui::Checkbox("Wrist", &desiredBones[(int)DesiredBones::BONE_RIGHT_WRIST]) )
								UI::UpdateWeaponSettings();
							ImGui::Text("Player's Right Leg\n");
							if( ImGui::Checkbox("Buttcheek", &desiredBones[(int)DesiredBones::BONE_RIGHT_BUTTCHEEK]) )
								UI::UpdateWeaponSettings();
							if( ImGui::Checkbox("Thigh", &desiredBones[(int)DesiredBones::BONE_RIGHT_THIGH]) )
								UI::UpdateWeaponSettings();
							if( ImGui::Checkbox("Knee", &desiredBones[(int)DesiredBones::BONE_RIGHT_KNEE]) )
								UI::UpdateWeaponSettings();
							if( ImGui::Checkbox("Ankle", &desiredBones[(int)DesiredBones::BONE_RIGHT_ANKLE]) )
								UI::UpdateWeaponSettings();
							if( ImGui::Checkbox("Sole", &desiredBones[(int)DesiredBones::BONE_RIGHT_SOLE]) )
								UI::UpdateWeaponSettings();
						}
						ImGui::NextColumn();
						{
							ImGui::Text("Player's Left Arm\n");
							if( ImGui::Checkbox("Collarbone ", &desiredBones[(int)DesiredBones::BONE_LEFT_COLLARBONE]) )
								UI::UpdateWeaponSettings();
							if( ImGui::Checkbox("Shoulder ", &desiredBones[(int)DesiredBones::BONE_LEFT_SHOULDER]) )
								UI::UpdateWeaponSettings();
							if( ImGui::Checkbox("Armpit ", &desiredBones[(int)DesiredBones::BONE_LEFT_ARMPIT]) )
								UI::UpdateWeaponSettings();
							if( ImGui::Checkbox("Bicep ", &desiredBones[(int)DesiredBones::BONE_LEFT_BICEP]) )
								UI::UpdateWeaponSettings();
							if( ImGui::Checkbox("Elbow ", &desiredBones[(int)DesiredBones::BONE_LEFT_ELBOW]) )
								UI::UpdateWeaponSettings();
							if( ImGui::Checkbox("Forearm ", &desiredBones[(int)DesiredBones::BONE_LEFT_FOREARM]) )
								UI::UpdateWeaponSettings();
							if( ImGui::Checkbox("Wrist ", &desiredBones[(int)DesiredBones::BONE_LEFT_WRIST]) )
								UI::UpdateWeaponSettings();

							ImGui::Text("Player's Left Leg\n");
							if( ImGui::Checkbox("Buttcheek ", &desiredBones[(int)DesiredBones::BONE_LEFT_BUTTCHEEK]) )
								UI::UpdateWeaponSettings();
							if( ImGui::Checkbox("Thigh ", &desiredBones[(int)DesiredBones::BONE_LEFT_THIGH]) )
								UI::UpdateWeaponSettings();
							if( ImGui::Checkbox("Knee ", &desiredBones[(int)DesiredBones::BONE_LEFT_KNEE]) )
								UI::UpdateWeaponSettings();
							if( ImGui::Checkbox("Ankle ", &desiredBones[(int)DesiredBones::BONE_LEFT_ANKLE]) )
								UI::UpdateWeaponSettings();
							if( ImGui::Checkbox("Sole ", &desiredBones[(int)DesiredBones::BONE_LEFT_SOLE]) )
								UI::UpdateWeaponSettings();
						}
						ImGui::PopItemWidth();
						ImGui::EndPopup();
					}
				}
				if(ImGui::Checkbox("ClosestBone", &closestBone))
					UI::UpdateWeaponSettings();
				SetTooltip("Mira no Bone mais perto da mira\nAo inves de mirar em determinado bone.");

				if(ImGui::Checkbox("EngageLock", &engageLock))
					UI::UpdateWeaponSettings();
				SetTooltip("Trava a mira no alvo do aimbot até soltar o trigger\nDepois de mata-lo, o Aimbot é desativado ate você re-pressionar o trigger.");
				if(engageLock)
				{
					if(ImGui::Checkbox("Target Reacquisition", &engageLockTR))
						UI::UpdateWeaponSettings();
					SetTooltip("Depois de matar atirando em spray 'n' pray, \n Adquirir ou não novo alvo.");
					if( engageLockTR )
					{
						if(ImGui::SliderInt("##TTR", &engageLockTTR, 0, 1000))
							UI::UpdateWeaponSettings();
						SetTooltip("Delay em ms para adquirir novo alvo");
					}
				}
				ImGui::PopItemWidth();
			}
			ImGui::Columns(1);
			ImGui::Separator();
			ImGui::Text("Accuracy");
			ImGui::Separator();
			ImGui::Columns(2, NULL, true);
			{
				if (ImGui::Checkbox("Auto Aim", &autoAimEnabled))
					UI::UpdateWeaponSettings();
				SetTooltip("Trava a mira em inimigos presentes em determinado FOV");
				if (ImGui::Checkbox("Recoil Control", &rcsEnabled))
					UI::UpdateWeaponSettings();
				SetTooltip("Controla o recoil automaticamente");
				if (ImGui::Checkbox("Distance-Based FOV", &autoAimRealDistance))
					UI::UpdateWeaponSettings();
				SetTooltip("Leva a perspectiva em conta quando calculando o FOV");
			}
			ImGui::NextColumn();
			{
				ImGui::PushItemWidth(-1);
				if (ImGui::SliderFloat("##AA", &autoAimValue, 0, 180))
					UI::UpdateWeaponSettings();
				SetTooltip("FOV em volta da mira usada para o AutoAim.\nCtrl+Click para escrever valores precisos");
				ImGui::PopItemWidth();
				if (ImGui::Button("RCS Settings", ImVec2(-1, 0)))
					ImGui::OpenPopup("optionRCSAmount");
				ImGui::SetNextWindowSize(ImVec2(200, 100), ImGuiSetCond_Always);
				if (ImGui::BeginPopup("optionRCSAmount"))
				{
					ImGui::PushItemWidth(-1);
					if (ImGui::Checkbox("RCS Always on", &rcsAlwaysOn))
						UI::UpdateWeaponSettings();
					SetTooltip("Se ativado o RCS sempre controlará o recoil (mesmo sem alvo no aimbot)");
					if (ImGui::SliderFloat("##RCSX", &rcsAmountX, 0, 2, "X: %0.3f"))
						UI::UpdateWeaponSettings();
					if (ImGui::SliderFloat("##RCSY", &rcsAmountY, 0, 2, "Y: %0.3f"))
						UI::UpdateWeaponSettings();
					ImGui::PopItemWidth();

					ImGui::EndPopup();
				}
			}
			ImGui::Columns(1);
			ImGui::Separator();
			ImGui::Text("Humanizing");
			ImGui::Separator();
			ImGui::Columns(2, NULL, true);
			{
				if (ImGui::Checkbox("Curve", &curveEnabled))
					UI::UpdateWeaponSettings();
				SetTooltip("Curve faz a mira não ir em linha reta. Usado com smoothing");
				if (ImGui::Checkbox("Smoothing", &smoothEnabled))
					UI::UpdateWeaponSettings();
				SetTooltip("Smoothing reduz o \"flick\" do aimbot. 0 para flicks. 1 para suavização total");
				if (ImGui::Checkbox("Smooth Salting", &smoothSaltEnabled))
					UI::UpdateWeaponSettings();
				SetTooltip("Divide a suavização em passos menores, alto smooth + baixo salt fica meio tremido.");
				if (ImGui::Checkbox("Error Margin", &errorMarginEnabled))
					UI::UpdateWeaponSettings();
				SetTooltip("Adiciona uma margem de erro ao aimbot, o que a função faz fica óbvio quando usado.");
				ImGui::PushItemWidth(-1);
				if (ImGui::Combo("##SMOOTHTYPE", (int*)& smoothType, smoothTypes, IM_ARRAYSIZE(smoothTypes)))
					UI::UpdateWeaponSettings();
				ImGui::PopItemWidth();
			}
			ImGui::NextColumn();
			{
				ImGui::PushItemWidth(-1);
				if (ImGui::SliderFloat("##CURVE", &curveAmount, 0, 2))
					UI::UpdateWeaponSettings();
				if (ImGui::SliderFloat("##SMOOTH", &smoothValue, 0, 1))
					UI::UpdateWeaponSettings();
				if (ImGui::SliderFloat("##SALT", &smoothSaltMultiplier, 0, smoothValue))
					UI::UpdateWeaponSettings();
				if (ImGui::SliderFloat("##ERROR", &errorMarginValue, 0, 2))
					UI::UpdateWeaponSettings();
				ImGui::PopItemWidth();
			}
			ImGui::Columns(1);
			ImGui::Separator();
			ImGui::EndChild();
		}
	}
	ImGui::NextColumn();
	{
		ImGui::BeginChild("COL2", ImVec2(0, 0), true);
		{
			ImGui::Text("Aimkey Only");
			ImGui::Separator();
			ImGui::Columns(2, NULL, true);
			{
				if (ImGui::Checkbox("Enabled", &aimkeyOnly))
					UI::UpdateWeaponSettings();
				SetTooltip("Ativar isso significa que você terá que apertar a tecla definida para usar o aimbot");
			}
			ImGui::NextColumn();
			{
				UI::KeyBindButton(&aimkey);
			}
			ImGui::Columns(1);
			ImGui::Separator();
			ImGui::Text("Casual / DM Only");
			ImGui::Separator();
			ImGui::Columns(2, NULL, true);
			{
				if (ImGui::Checkbox("Aim Step", &aimStepEnabled))
					UI::UpdateWeaponSettings();
				SetTooltip("Evita os kicks por VAC auth no Casual / DM");
			}
			ImGui::NextColumn();
			{
				ImGui::PushItemWidth(-1);
				if (ImGui::SliderFloat("##STEP", &aimStepValue, 0, 45))
					UI::UpdateWeaponSettings();
				ImGui::PopItemWidth();
			}
			ImGui::Columns(1);
			ImGui::Separator();
			ImGui::Text("Other");
			ImGui::Separator();
			ImGui::Columns(2, NULL, true);
			{
				if (ImGui::Checkbox("Mouse Movement", &moveMouse))
					UI::UpdateWeaponSettings();
				SetTooltip("Emula movimento de mouse ao invés de definir angulos. Recomendado para servidores do Face-It. (Não funciona com silent aim)");

				switch (currentWeapon)
				{
					case ItemDefinitionIndex::INVALID:
					case ItemDefinitionIndex::WEAPON_DEAGLE:
					case ItemDefinitionIndex::WEAPON_ELITE:
					case ItemDefinitionIndex::WEAPON_FIVESEVEN:
					case ItemDefinitionIndex::WEAPON_GLOCK:
					case ItemDefinitionIndex::WEAPON_TEC9:
					case ItemDefinitionIndex::WEAPON_HKP2000:
					case ItemDefinitionIndex::WEAPON_USP_SILENCER:
					case ItemDefinitionIndex::WEAPON_P250:
					case ItemDefinitionIndex::WEAPON_CZ75A:
					case ItemDefinitionIndex::WEAPON_REVOLVER:
						if (ImGui::Checkbox("Auto Cock Revolver", &autoCockRevolver))
							UI::UpdateWeaponSettings();
						SetTooltip("Pressiona o gatilho do revolver automaticamente, assim atirando instantaneamente.");
						if (ImGui::Checkbox("Auto Pistol", &autoPistolEnabled))
							UI::UpdateWeaponSettings();
						SetTooltip("Automaticamente atira com a pistola enquanto segurando o botao de atirar.");
						break;
					default:
						break;
				}

				if (ImGui::Checkbox("Auto Shoot", &autoShootEnabled))
					UI::UpdateWeaponSettings();
				SetTooltip("Atira automaticamente quando há inimigos.");
				ImGui::Checkbox("^Velocity Check", &Settings::Aimbot::AutoShoot::velocityCheck);
				SetTooltip("Atira automaticamente apenas quando a precisão não é afetada pelo movimento.\nUso recomendad em conjunto com Auto-Slow");
				if( ImGui::Checkbox("Spread Limit", &spreadLimitEnabled) )
					UI::UpdateWeaponSettings();
				SetTooltip("Auto Shoot apenas quando a precisão está dentro do limite definido.\nBom para armas como Desert Eagle.");
				if( ImGui::SliderFloat("##SPREADLIMIT", &spreadLimit, 0, 0.1) )
					UI::UpdateWeaponSettings();
				SetTooltip(" Ative Spreadlimit na aba de Visuals para ver o quão grande está");
				if( ImGui::Checkbox("Distance-Based Limit", &spreadLimitDistance) )
					UI::UpdateWeaponSettings();
				SetTooltip("Limite de inprecisão baseado na distância.\nDefine o limite menor se o alvo está mais distante.");
				if (ImGui::Checkbox("Silent Aim", &silent))
					UI::UpdateWeaponSettings();
				SetTooltip("Mira não meche na sua visão, não funciona em demos (overwatch)");
				if (ImGui::Checkbox("pSilent", &pSilent))
					UI::UpdateWeaponSettings();
				SetTooltip("Mesma função do Silent Aim, porém funciona em demos.\nporém, Funciona apenas em servidores da comunidade");
			}
			ImGui::NextColumn();
			{
				if (ImGui::Checkbox("No Shoot", &noShootEnabled))
					UI::UpdateWeaponSettings();
				SetTooltip("Para de atirar quando travado em um alvo");
				if (ImGui::Checkbox("Auto Scope", &autoScopeEnabled))
					UI::UpdateWeaponSettings();
				SetTooltip("Abre o scope da arma automaticamente para melhor precisão, se disponivel.");
				if (ImGui::Checkbox("Ignore Jump", &ignoreJumpEnabled))
					UI::UpdateWeaponSettings();
				SetTooltip("Desativa o aimbot enquanto está no ar.");
				if (ImGui::Checkbox("Flash Check", &flashCheck))
					UI::UpdateWeaponSettings();
				SetTooltip("Desativa o aimbot quando está cego (flashbang)");
				if (ImGui::Checkbox("Smoke Check", &smokeCheck))
					UI::UpdateWeaponSettings();
				SetTooltip("Ignora players que não estão visiveis devido a Smokes.");
				if (ImGui::Checkbox("Prediction", &predEnabled))
					UI::UpdateWeaponSettings();
				SetTooltip("Calcula a velocidade para prever a posição do player.");
				if( ImGui::Checkbox("Hit Chance", &hitChanceEnabled) )
					UI::UpdateWeaponSettings();
				SetTooltip("Spread limit, calculado simulando o spread da arma.");
				if( ImGui::SliderFloat("##HITCHANCEVALUE", &hitChanceValue, 0, 1) )
					UI::UpdateWeaponSettings();
				SetTooltip("Abaixo desse valor, autoshoot não atira \nUsado para melhor precisão, evitar atirar sem chance de acertar.");
				if( ImGui::SliderInt("##HITCHANCERAYS", &hitChanceRays, 1, 250) )
					UI::UpdateWeaponSettings();
				SetTooltip("Quantidade de raios de probabilidade usados pelo Hitchance, maior melhor.");
			}


			ImGui::Columns(1);
			ImGui::Separator();
			ImGui::Text("AutoSlow");
			ImGui::Separator();
			if (ImGui::Checkbox("Enabled##AUTOSLOW", &autoSlow))
				UI::UpdateWeaponSettings();
			SetTooltip("Automaticamente aperta shift quando há inimigos atingiveis");

			ImGui::Columns(1);
			ImGui::Separator();
			ImGui::Text("AutoWall");
			ImGui::Separator();
			ImGui::Columns(2, NULL, true);
			{
				if (ImGui::Checkbox("Enabled##AUTOWALL", &autoWallEnabled))
					UI::UpdateWeaponSettings();
				SetTooltip("Atira em inimigos atrás de paredes se for possivel causar X ou mais de dano.");
				if(ImGui::Button("Autowall Bones", ImVec2(-1, 0)))
					ImGui::OpenPopup("optionBones");
				ImGui::SetNextWindowSize(ImVec2((ImGui::GetWindowWidth()/1.25f),ImGui::GetWindowHeight()), ImGuiSetCond_Always);
				if( ImGui::BeginPopup("optionBones") )
				{
					ImGui::PushItemWidth(-1);
					ImGui::Text("Center Mass\n");
					if( ImGui::Checkbox("Head", &desiredBones[(int)DesiredBones::BONE_HEAD]) )
						UI::UpdateWeaponSettings();
					if( ImGui::Checkbox("Neck", &desiredBones[(int)DesiredBones::BONE_NECK]) )
						UI::UpdateWeaponSettings();
					if( ImGui::Checkbox("Upper Spine", &desiredBones[(int)DesiredBones::BONE_UPPER_SPINAL_COLUMN]) )
						UI::UpdateWeaponSettings();
					if( ImGui::Checkbox("Middle Spine", &desiredBones[(int)DesiredBones::BONE_MIDDLE_SPINAL_COLUMN]) )
						UI::UpdateWeaponSettings();
					if( ImGui::Checkbox("Lower Spine", &desiredBones[(int)DesiredBones::BONE_LOWER_SPINAL_COLUMN]) )
						UI::UpdateWeaponSettings();
					if( ImGui::Checkbox("Pelvis", &desiredBones[(int)DesiredBones::BONE_PELVIS]) )
						UI::UpdateWeaponSettings();
					if( ImGui::Checkbox("Hip", &desiredBones[(int)DesiredBones::BONE_HIP]) )
						UI::UpdateWeaponSettings();
					ImGui::Separator();

					ImGui::Columns(2, NULL, false);
					{
						ImGui::Text("Player's Right Arm\n");
						if( ImGui::Checkbox("Collarbone", &desiredBones[(int)DesiredBones::BONE_RIGHT_COLLARBONE]) )
							UI::UpdateWeaponSettings();
						if( ImGui::Checkbox("Shoulder", &desiredBones[(int)DesiredBones::BONE_RIGHT_SHOULDER]) )
							UI::UpdateWeaponSettings();
						if( ImGui::Checkbox("Armpit", &desiredBones[(int)DesiredBones::BONE_RIGHT_ARMPIT]) )
							UI::UpdateWeaponSettings();
						if( ImGui::Checkbox("Bicep", &desiredBones[(int)DesiredBones::BONE_RIGHT_BICEP]) )
							UI::UpdateWeaponSettings();
						if( ImGui::Checkbox("Elbow", &desiredBones[(int)DesiredBones::BONE_RIGHT_ELBOW]) )
							UI::UpdateWeaponSettings();
						if( ImGui::Checkbox("Forearm", &desiredBones[(int)DesiredBones::BONE_RIGHT_FOREARM]) )
							UI::UpdateWeaponSettings();
						if( ImGui::Checkbox("Wrist", &desiredBones[(int)DesiredBones::BONE_RIGHT_WRIST]) )
							UI::UpdateWeaponSettings();
						ImGui::Text("Player's Right Leg\n");
						if( ImGui::Checkbox("Buttcheek", &desiredBones[(int)DesiredBones::BONE_RIGHT_BUTTCHEEK]) )
							UI::UpdateWeaponSettings();
						if( ImGui::Checkbox("Thigh", &desiredBones[(int)DesiredBones::BONE_RIGHT_THIGH]) )
							UI::UpdateWeaponSettings();
						if( ImGui::Checkbox("Knee", &desiredBones[(int)DesiredBones::BONE_RIGHT_KNEE]) )
							UI::UpdateWeaponSettings();
						if( ImGui::Checkbox("Ankle", &desiredBones[(int)DesiredBones::BONE_RIGHT_ANKLE]) )
							UI::UpdateWeaponSettings();
						if( ImGui::Checkbox("Sole", &desiredBones[(int)DesiredBones::BONE_RIGHT_SOLE]) )
							UI::UpdateWeaponSettings();
					}
					ImGui::NextColumn();
					{
						ImGui::Text("Player's Left Arm\n");
						if( ImGui::Checkbox("Collarbone ", &desiredBones[(int)DesiredBones::BONE_LEFT_COLLARBONE]) )
							UI::UpdateWeaponSettings();
						if( ImGui::Checkbox("Shoulder ", &desiredBones[(int)DesiredBones::BONE_LEFT_SHOULDER]) )
							UI::UpdateWeaponSettings();
						if( ImGui::Checkbox("Armpit ", &desiredBones[(int)DesiredBones::BONE_LEFT_ARMPIT]) )
							UI::UpdateWeaponSettings();
						if( ImGui::Checkbox("Bicep ", &desiredBones[(int)DesiredBones::BONE_LEFT_BICEP]) )
							UI::UpdateWeaponSettings();
						if( ImGui::Checkbox("Elbow ", &desiredBones[(int)DesiredBones::BONE_LEFT_ELBOW]) )
							UI::UpdateWeaponSettings();
						if( ImGui::Checkbox("Forearm ", &desiredBones[(int)DesiredBones::BONE_LEFT_FOREARM]) )
							UI::UpdateWeaponSettings();
						if( ImGui::Checkbox("Wrist ", &desiredBones[(int)DesiredBones::BONE_LEFT_WRIST]) )
							UI::UpdateWeaponSettings();

						ImGui::Text("Player's Left Leg\n");
						if( ImGui::Checkbox("Buttcheek ", &desiredBones[(int)DesiredBones::BONE_LEFT_BUTTCHEEK]) )
							UI::UpdateWeaponSettings();
						if( ImGui::Checkbox("Thigh ", &desiredBones[(int)DesiredBones::BONE_LEFT_THIGH]) )
							UI::UpdateWeaponSettings();
						if( ImGui::Checkbox("Knee ", &desiredBones[(int)DesiredBones::BONE_LEFT_KNEE]) )
							UI::UpdateWeaponSettings();
						if( ImGui::Checkbox("Ankle ", &desiredBones[(int)DesiredBones::BONE_LEFT_ANKLE]) )
							UI::UpdateWeaponSettings();
						if( ImGui::Checkbox("Sole ", &desiredBones[(int)DesiredBones::BONE_LEFT_SOLE]) )
							UI::UpdateWeaponSettings();
					}
					ImGui::PopItemWidth();
					ImGui::EndPopup();
				}
			}
			ImGui::NextColumn();
			{
				ImGui::PushItemWidth(-1);
				if (ImGui::SliderFloat("##AUTOWALLDMG", &autoWallValue, 0, 100, "Min Damage: %f"))
					UI::UpdateWeaponSettings();
				ImGui::PopItemWidth();
			}


			ImGui::Columns(1);
			ImGui::Separator();
			if (currentWeapon > ItemDefinitionIndex::INVALID && Settings::Aimbot::weapons.find(currentWeapon) != Settings::Aimbot::weapons.end())
			{
				if (ImGui::Button("Clear Weapon Settings", ImVec2(-1, 0)))
				{
					Settings::Aimbot::weapons.erase(currentWeapon);
					UI::ReloadWeaponSettings();
				}
			}
			ImGui::EndChild();
		}
	}
}
