
#pragma once
#include "stdafx.h"

// This Menu Base is made by maxiZzModz it would be cool if you use this base when you mark me in the Credits as the Base Dev 
// These Base also support the Numpad,Arrow Key and Controller Support Openkey  Numpad * (Controller : Both Shoulderbuttons


//Nano 42 Is am Extension of Virtual base that works for the update 1.42 - Doomsday. All Credits goes to Cretor of MaxxizzModz, and other developer involved in creation of Virtual Base.


bool TestBool = false;
bool godmode = false;
bool neverwanted = false;
bool gangs = false;
bool noclip = false;
int selectedPlayer;

void spawn(std::string vehicle)
{
	Hash model = GAMEPLAY::GET_HASH_KEY((char*)_strdup(vehicle.c_str()));
	if (STREAMING::IS_MODEL_VALID(model))
	{
		STREAMING::REQUEST_MODEL(model);
		while (!STREAMING::HAS_MODEL_LOADED(model)) WAIT(0);
		Vector3 coords = ENTITY::GET_ENTITY_COORDS(PLAYER::PLAYER_PED_ID(), false);
		float heading = ENTITY::GET_ENTITY_HEADING(PLAYER::PLAYER_PED_ID());
		Vehicle vehicle1 = VEHICLE::CREATE_VEHICLE(model, coords.x, coords.y, coords.z, heading, true, true);
		VEHICLE::SET_VEHICLE_ENGINE_ON(vehicle1 , true , true , true);
		VEHICLE::SET_VEHICLE_ON_GROUND_PROPERLY(vehicle1);
	}
}


void tptowaypoint() {
	Vector3 coords;
	Entity e = PLAYER::PLAYER_PED_ID();

	if (PED::IS_PED_IN_ANY_VEHICLE(e, 0)) {
		e = PED::GET_VEHICLE_PED_IS_USING(e);
	}

	int WaypointHandle = UI::GET_FIRST_BLIP_INFO_ID(8);
	if (UI::DOES_BLIP_EXIST)
	{
		Vector3 WaypointPos = UI::GET_BLIP_COORDS(WaypointHandle);
		WaypointPos.z += 5.0;
		int Handle = PLAYER::PLAYER_PED_ID();
		if (PED::IS_PED_IN_ANY_VEHICLE(Handle, 0))
		{
			Handle = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), 0);
		}
			ENTITY::SET_ENTITY_COORDS(Handle , WaypointPos.x , WaypointPos.y , WaypointPos.z , 0 , 0 , 0 , 1);
		
	}
}












char* CharKeyboard(char* windowName = "", int maxInput = 21, char* defaultText = "") {
	GAMEPLAY::DISPLAY_ONSCREEN_KEYBOARD(0, "", "", defaultText, "", "", "", maxInput);
	while (GAMEPLAY::UPDATE_ONSCREEN_KEYBOARD() == 0) WAIT(0);
	if (!GAMEPLAY::GET_ONSCREEN_KEYBOARD_RESULT()) return "";
	return GAMEPLAY::GET_ONSCREEN_KEYBOARD_RESULT();
}
int NumberKeyboard() {
	GAMEPLAY::DISPLAY_ONSCREEN_KEYBOARD(1, "", "", "", "", "", "", 10);
	while (GAMEPLAY::UPDATE_ONSCREEN_KEYBOARD() == 0) WAIT(0);
	if (!GAMEPLAY::GET_ONSCREEN_KEYBOARD_RESULT()) return 0;
	return atof(GAMEPLAY::GET_ONSCREEN_KEYBOARD_RESULT());
}
void notifyleft(char* msg)
{
	UI::_SET_NOTIFICATION_TEXT_ENTRY("STRING");
	UI::ADD_TEXT_COMPONENT_SUBSTRING_PLAYER_NAME(msg);
	UI::_DRAW_NOTIFICATION(2000, 1);
}

Vector3 TPCoords;
void TPto(Vector3 Coords)
{
	int Handle = PLAYER::PLAYER_PED_ID();
	if (PED::IS_PED_IN_ANY_VEHICLE(Handle, 0))
	{
		ENTITY::SET_ENTITY_COORDS(PED::GET_VEHICLE_PED_IS_IN(Handle, false), Coords.x, Coords.y, Coords.z, 0, 0, 0, 1);
	}
	else
		ENTITY::SET_ENTITY_COORDS(Handle, Coords.x, Coords.y, Coords.z, 0, 0, 0, 1);
}
// Skeyoter#0511
// FEATURES
void Features()
{
	Entity player = PLAYER::PLAYER_PED_ID();
	if (godmode)
	{
		ENTITY::SET_ENTITY_INVINCIBLE(PLAYER::PLAYER_PED_ID(), true);
	}
	else { ENTITY::SET_ENTITY_INVINCIBLE(PLAYER::PLAYER_PED_ID(), false); }
	if (neverwanted)
	{
		PLAYER::CLEAR_PLAYER_WANTED_LEVEL(player);
		PLAYER::SET_MAX_WANTED_LEVEL(0);
		PLAYER::SET_POLICE_IGNORE_PLAYER(player, true);
		PLAYER::SET_PLAYER_CAN_BE_HASSLED_BY_GANGS(player, false);
		PLAYER::SET_EVERYONE_IGNORE_PLAYER(player, true);
		PLAYER::SET_IGNORE_LOW_PRIORITY_SHOCKING_EVENTS(player, true);
	}
	else {
		PLAYER::SET_MAX_WANTED_LEVEL(5);
		PLAYER::SET_POLICE_IGNORE_PLAYER(player, false);
		PLAYER::SET_PLAYER_CAN_BE_HASSLED_BY_GANGS(player, true);
		PLAYER::SET_EVERYONE_IGNORE_PLAYER(player, false);
		PLAYER::SET_IGNORE_LOW_PRIORITY_SHOCKING_EVENTS(player, false);
	}
	if (gangs) { PLAYER::SET_PLAYER_CAN_BE_HASSLED_BY_GANGS(player, false); }
	else { PLAYER::SET_PLAYER_CAN_BE_HASSLED_BY_GANGS(player, true); }

	if (noclip)
	{
		Ped playerPed = PLAYER::PLAYER_PED_ID();
		Vector3 pos = ENTITY::GET_ENTITY_COORDS(playerPed, false);
		ENTITY::SET_ENTITY_COORDS_NO_OFFSET(playerPed, pos.x, pos.y, pos.z, false, false, false);
		if (GetAsyncKeyState(0x53) || CONTROLS::IS_DISABLED_CONTROL_JUST_PRESSED(2, 268)) {
			float fivef = 0.5f;
			float heading = ENTITY::GET_ENTITY_HEADING(playerPed);
			float xVec = fivef * sin((heading)) * -1.0f;
			float yVec = fivef * cos((heading));

			ENTITY::GET_ENTITY_HEADING(playerPed);
			pos.x += pos.y += yVec;
			ENTITY::SET_ENTITY_COORDS_NO_OFFSET(playerPed, pos.x, pos.y, pos.z, false, false, false);
		}
		if (GetAsyncKeyState(0x41) || CONTROLS::IS_DISABLED_CONTROL_JUST_PRESSED(2, 266)) {
			float fivef = 0.5f;
			float heading = ENTITY::GET_ENTITY_HEADING(playerPed);
			
			ENTITY::SET_ENTITY_HEADING(playerPed, heading + 0.5);
		}
		if (GetAsyncKeyState(0x44) || CONTROLS::IS_DISABLED_CONTROL_JUST_PRESSED(2, 271)) {
			float fivef = 0.5f;
			float heading = ENTITY::GET_ENTITY_HEADING(playerPed);

			ENTITY::SET_ENTITY_HEADING(playerPed, heading - 0.5);
		}
		if (GetAsyncKeyState(VK_SHIFT) ) {
			float fivef = 0.5f;
			float heading = ENTITY::GET_ENTITY_HEADING(playerPed);
			pos.z = -0.5;
			ENTITY::SET_ENTITY_COORDS_NO_OFFSET(playerPed, pos.x, pos.y, pos.z, false, false, false);
		}
		if (GetAsyncKeyState(VK_SPACE) ) {
			float fivef = 0.5f;
			float heading = ENTITY::GET_ENTITY_HEADING(playerPed);
			pos.z = +0.5;
			ENTITY::SET_ENTITY_COORDS_NO_OFFSET(playerPed, pos.x, pos.y, pos.z, false, false, false);
		}
	}
	else { NULL; }
}
// FEATURES

void main() {

	while (true) {
		Menu::Checks::Controlls();
		Features();
		notifyMap("~f~Nano 42 Loaded!");
		switch (Menu::Settings::currentMenu) {

		case mainmenu:
		{
			Menu::Title("Skey Tutorial");
			if (Menu::Option("Spawn Adder"))
			{
				spawn("adder");
			}
			if (Menu::Option("Teleport to Waypoint"))
			{
				tptowaypoint();
			}
			Menu::MenuOption("Sub Menu ~b~>", sub);
			Menu::MenuOption("Police ~b~>", police);
			Menu::MenuOption("Movement ~b~>", movement);
			Menu::MenuOption("Health ~b~>", health);
			Menu::MenuOption("Player List ~b~>", plist);
			Menu::MenuOption("Settings ~b~>", settings);
		}
		break;
		case movement:
		{
			Menu::Toggle("Noclip", noclip);



		}
		break;
#pragma region Self Menu
		case plist:
		{
			Menu::Title("Player List");
			for (int i{}; i < 32; i++) {
				if (NETWORK::NETWORK_IS_PLAYER_CONNECTED(i)) {
					Menu::PlayerOption(i);
				}
			}
		}
			break;
		case pmenu:
		{
			Menu::Title(PLAYER::GET_PLAYER_NAME(selectedPlayer));
			Menu::Break("It Works!");
		}
			break;
		case sub :
		{
			Menu::Title("Sub Menu");
			Menu::Toggle("Test Bool", TestBool);
			//To use functions do _>
			if (Menu::Option("Toggle Function"))
			{
				teleport_to_marker();
			}
			//SubMenu
		}
		break;
		
#pragma endregion
#pragma region Settings Menu
		case settings:
		{
			Menu::Title("Settings");
			Menu::MenuOption("Colors ~b~>", settingstheme);
			if (Menu::Int("Scroll Delay", Menu::Settings::keyPressDelay2, 1, 200))
			{
				if (IsKeyPressed(VK_NUMPAD5) || CONTROLS::IS_DISABLED_CONTROL_PRESSED(0, ControlFrontendAccept)) {
					Menu::Settings::keyPressDelay2 = NumberKeyboard();
				}
			}
			if (Menu::Int("Int Delay", Menu::Settings::keyPressDelay3, 1, 200))
			{
				if (IsKeyPressed(VK_NUMPAD5) || CONTROLS::IS_DISABLED_CONTROL_PRESSED(0, ControlFrontendAccept)) {
					Menu::Settings::keyPressDelay3 = NumberKeyboard();
				}
			}
			Menu::Option("~HUD_COLOUR_GOLD~Social Club Account:");
			Menu::Option(PLAYER::GET_PLAYER_NAME(PLAYER::PLAYER_ID()));
			Menu::MenuOption("~r~KILL GAME", exitgta);
		}
		break;
		case Credits:
		{
			Menu::Title("Credits");
			Menu::Option("Base : ~r~maxiZzModz");
			Menu::Option("Modified By : ~f~CptShad");
			Menu::Option("Updated By : ~HUD_COLOUR_GOLD~AdryaNN53");
			Menu::Option("Thanks to:");
			Menu::Option("~b~LHDModz");
			Menu::Option("~p~Mike Rohsoft");
			Menu::Option("Taran VG");
			Menu::Option("~r~Name");
			Menu::Option("V. 0.0");
		}
		break;
		case exitgta:
		{
			Menu::Title("Exit GTA V");
			if (Menu::Option("Yes")) exit(0);
		}
		break;
		case settingstheme:
		{
			Menu::Title("Colors");
			Menu::MenuOption("Theme Loader ~b~>", themeloader);
			Menu::MenuOption("Title Background ~b~>", settingstitlerect);
			Menu::MenuOption("Selection Box ~b~>", settingsscroller);
			Menu::MenuOption("Option Text ~b~>", settingsoptiontext);
			if (Menu::Option("MenuX plus")) {
				if (Menu::Settings::menuX < 0.81f) Menu::Settings::menuX += 0.01f;
			}
			if (Menu::Option("MenuX minus")) {
				if (Menu::Settings::menuX > 0.17f) Menu::Settings::menuX -= 0.01f;
			}
		}
		break;
		case themeloader:
		{
			Menu::Title("Theme Colors");
			if (Menu::Option("Red Theme")) {
				Menu::Settings::titleRect = { 100, 0, 0, 255 };
				Menu::Settings::scroller = { 100, 0, 0, 255 };
			}
			if (Menu::Option("Blue Theme")) {
				Menu::Settings::titleRect = { 0, 0, 200, 255 };
				Menu::Settings::scroller = { 0, 0, 200, 255 };
			}
			if (Menu::Option("Green Theme")) {
				Menu::Settings::titleRect = { 0, 180, 0, 255 };
				Menu::Settings::scroller = { 0, 0, 180, 255 };
			}
			if (Menu::Option("Load Default Theme")) {
				Menu::Settings::titleText = { 255, 255, 255, 255, 7 };
				Menu::Settings::titleRect = { 100, 0, 0, 255 };
				Menu::Settings::scroller = { 100, 0, 0, 255 };
				Menu::Settings::optionText = { 255, 255, 255, 255, 0 };
				Menu::Settings::optionRect = { 0, 0, 0, 110 };
			}
		}
		break;
		case settingstitlerect:
		{
			Menu::Title("Title Rect");
			if (Menu::Int("Red", Menu::Settings::titleRect.r, 0, 255))
			{
				if (IsKeyPressed(VK_NUMPAD5) || CONTROLS::IS_DISABLED_CONTROL_PRESSED(0, ControlFrontendAccept)) {
					Menu::Settings::titleRect.r = NumberKeyboard();
				}
			}
			if (Menu::Int("Green", Menu::Settings::titleRect.g, 0, 255))
			{
				if (IsKeyPressed(VK_NUMPAD5) || CONTROLS::IS_DISABLED_CONTROL_PRESSED(0, ControlFrontendAccept)) {
					Menu::Settings::titleRect.g = NumberKeyboard();
				}
			}
			if (Menu::Int("Blue", Menu::Settings::titleRect.b, 0, 255))
			{
				if (IsKeyPressed(VK_NUMPAD5) || CONTROLS::IS_DISABLED_CONTROL_PRESSED(0, ControlFrontendAccept)) {
					Menu::Settings::titleRect.b = NumberKeyboard();
				}
			}
			if (Menu::Int("Opacity", Menu::Settings::titleRect.a, 0, 255))
			{
				if (IsKeyPressed(VK_NUMPAD5) || CONTROLS::IS_DISABLED_CONTROL_PRESSED(0, ControlFrontendAccept)) {
					Menu::Settings::titleRect.a = NumberKeyboard();
				}
			}
		}
		break;
		case settingsoptiontext:
		{
			Menu::Title("Option Text");
			if (Menu::Int("Red", Menu::Settings::optionText.r, 0, 255))
			{
				if (IsKeyPressed(VK_NUMPAD5) || CONTROLS::IS_DISABLED_CONTROL_PRESSED(0, ControlFrontendAccept)) {
					Menu::Settings::optionText.r = NumberKeyboard();
				}
			}
			if (Menu::Int("Green", Menu::Settings::optionText.g, 0, 255))
			{
				if (IsKeyPressed(VK_NUMPAD5) || CONTROLS::IS_DISABLED_CONTROL_PRESSED(0, ControlFrontendAccept)) {
					Menu::Settings::optionText.g = NumberKeyboard();
				}
			}
			if (Menu::Int("Blue", Menu::Settings::optionText.b, 0, 255))
			{
				if (IsKeyPressed(VK_NUMPAD5) || CONTROLS::IS_DISABLED_CONTROL_PRESSED(0, ControlFrontendAccept)) {
					Menu::Settings::optionText.b = NumberKeyboard();
				}
			}
			if (Menu::Int("Opacity", Menu::Settings::optionText.a, 0, 255))
			{
				if (IsKeyPressed(VK_NUMPAD5) || CONTROLS::IS_DISABLED_CONTROL_PRESSED(0, ControlFrontendAccept)) {
					Menu::Settings::optionText.a = NumberKeyboard();
				}
			}
			Menu::MenuOption("Font ~b~>", font);
		}
		break;
		case font:
		{
			Menu::Title("Font");
			if (Menu::Option("Chalet London")) { Menu::Settings::optionText.f = 0; }
			if (Menu::Option("House Script")) { Menu::Settings::optionText.f = 1; }
			if (Menu::Option("Monospace")) { Menu::Settings::optionText.f = 2; }
			if (Menu::Option("Wing Dings")) { Menu::Settings::optionText.f = 3; }
			if (Menu::Option("Chalet Comprime Cologne")) { Menu::Settings::optionText.f = 4; }
			if (Menu::Option("Pricedown")) { Menu::Settings::optionText.f = 7; }
		}
		break;
		case settingsscroller:
		{
			Menu::Title("Scroller");
			if (Menu::Int("Red", Menu::Settings::scroller.r, 0, 255))
			{
				if (IsKeyPressed(VK_NUMPAD5) || CONTROLS::IS_DISABLED_CONTROL_PRESSED(0, ControlFrontendAccept)) {
					Menu::Settings::scroller.r = NumberKeyboard();
				}
			}
			if (Menu::Int("Green", Menu::Settings::scroller.g, 0, 255))
			{
				if (IsKeyPressed(VK_NUMPAD5) || CONTROLS::IS_DISABLED_CONTROL_PRESSED(0, ControlFrontendAccept)) {
					Menu::Settings::scroller.g = NumberKeyboard();
				}
			}
			if (Menu::Int("Blue", Menu::Settings::scroller.b, 0, 255))
			{
				if (IsKeyPressed(VK_NUMPAD5) || CONTROLS::IS_DISABLED_CONTROL_PRESSED(0, ControlFrontendAccept)) {
					Menu::Settings::scroller.b = NumberKeyboard();
				}
			}
			if (Menu::Int("Opacity", Menu::Settings::scroller.a, 0, 255))
			{
				if (IsKeyPressed(VK_NUMPAD5) || CONTROLS::IS_DISABLED_CONTROL_PRESSED(0, ControlFrontendAccept)) {
					Menu::Settings::scroller.a = NumberKeyboard();
				}
			}
		}
		break;
#pragma endregion
#pragma region health
		case health: {
			Menu::Title("Health");
			Menu::Toggle("God Mode", godmode);
			if (Menu::Option("Add Max Health"))
			{
				ENTITY::SET_ENTITY_HEALTH(PLAYER::PLAYER_PED_ID(), 400);
			}
			if (Menu::Option("Add Max Armour"))
			{
				PED::ADD_ARMOUR_TO_PED(PLAYER::PLAYER_PED_ID(), 200);
			}
			if (Menu::Option("1 HP"))
			{
				ENTITY::SET_ENTITY_HEALTH(PLAYER::PLAYER_PED_ID(), 4);
			}
			if (Menu::Option("Suicide"))
			{
				ENTITY::SET_ENTITY_HEALTH(PLAYER::PLAYER_PED_ID(), 0);
			}
			if (Menu::Option("Remove Armour"))
			{
				PED::ADD_ARMOUR_TO_PED(PLAYER::PLAYER_PED_ID(), 0);
			}
		}
#pragma endregion
#pragma region police
		case police:
		{
			Menu::Title("Police");
			Menu::Toggle("Never Wanted", neverwanted);
			if (Menu::Option("Clear Wanted"))
			{
				PLAYER::CLEAR_PLAYER_WANTED_LEVEL(PLAYER::PLAYER_PED_ID());
			}
			Menu::Toggle("Ignored by Gangs", gangs);
			if (Menu::Option("Max Wanted Level 1"))
			{
				PLAYER::SET_MAX_WANTED_LEVEL(1);
			}
		}
#pragma endregion

		}
		Menu::End();
		WAIT(0);
	}
}

void ScriptMain() {
	srand(GetTickCount());

	main();
}