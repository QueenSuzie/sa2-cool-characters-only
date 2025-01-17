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
	}

	__declspec(dllexport) void __cdecl OnFrame() {
		if (CurrentSequenceNo) {
			PrintDebug("CurrentSeq: %d", CurrentSequenceNo);
		}
	}

	__declspec(dllexport) void __cdecl OnExit() {
		if (ReplaceStages::FallenHeroSequence) {
			delete ReplaceStages::FallenHeroSequence;
		}
	}

	__declspec(dllexport) ModInfo SA2ModInfo = { ModLoaderVer }; // This is needed for the Mod Loader to recognize the DLL.
}