/**************************************************************************************
 *   main.cpp  --  This file is part of Cool Characters Only.                         *
 *                                                                                    *
 *   Copyright (C) 2023 - 2024 Queen Suzie                                            *
 *                                                                                    *
 *   Cool Characters Only is free software: you can redistribute it and/or modify     *
 *   it under the terms of the GNU General Public License as published                *
 *   by the Free Software Foundation, either version 3 of the License,                *
 *   or (at your option) any later version.                                           *
 *                                                                                    *
 *   Cool Characters Only is distributed in the hope that it will be useful,          *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty                      *
 *   of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.                          *
 *   See the GNU General Public License for more details.                             *
 *                                                                                    *
 *   You should have received a copy of the GNU General Public License                *
 *   along with this program.  If not, see http://www.gnu.org/licenses/.              *
 *                                                                                    *
 *************************************************************************************/

#include "pch.h"
#include <vector>

HelperFunctions HelperFunctionsGlobal;
const char* CCM_VERSION = "1.3.0-rc.1";
std::string DEBUG_MESSAGE = "";
int DEBUG_MESSAGE_TIMER = 0;
int DEFAULT_MESSAGE_TIME = 300;
float SCALE_MULTIPLIER = 2.0;
int DEBUG_FONT_SCALE = 10;
int DEBUG_FONT_COLOR = 0xFF7D3C98; // Purple AARRGGBB

extern "C" {
	__declspec(dllexport) void __cdecl Init(const char* path, const HelperFunctions& helperFunctions) {
		if (helperFunctions.Mods->find("sa2.queensuzie.storystyleupgrades") != NULL) {
			ReplaceCharacters::SSU_DETECTED = true;
		}

		ReplaceCharacters::init();
		ReplaceStages::init();
		StageTimers::init();
		Animations anims;
		StartingPositions pos;

		anims.init();
		pos.init();

		HelperFunctionsGlobal = helperFunctions;
		helperFunctions.SetWindowTitle(L"SONIC ADVENTURE 2 - FALLEN HERO\n");
		SCALE_MULTIPLIER = (float)HorizontalResolution / (float)VerticalResolution > 1.33f ? floor((float)VerticalResolution / 480.0f) : floor((float)HorizontalResolution / 640.0f);
		DEBUG_FONT_SCALE *= SCALE_MULTIPLIER;
	}

	__declspec(dllexport) void __cdecl OnFrame() {
		if (DEBUG_MESSAGE_TIMER > 0) {
			SetDebugInfo();
			HelperFunctionsGlobal.DisplayDebugString(NJM_LOCATION(1, 1), DEBUG_MESSAGE.c_str());
			DEBUG_MESSAGE_TIMER--;
		}
	}

	__declspec(dllexport) void __cdecl OnExit() {
		if (ReplaceStages::FallenHeroSequence) {
			delete ReplaceStages::FallenHeroSequence;
		}
	}

	__declspec(dllexport) ModInfo SA2ModInfo = { ModLoaderVer }; // This is needed for the Mod Loader to recognize the DLL.
}

void SetDebugInfo() {
	HelperFunctionsGlobal.SetDebugFontSize(DEBUG_FONT_SCALE);
	HelperFunctionsGlobal.SetDebugFontColor(DEBUG_FONT_COLOR);
}