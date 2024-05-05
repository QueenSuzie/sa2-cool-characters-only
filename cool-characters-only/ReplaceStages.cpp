/**************************************************************************************
 *   ReplaceStages.cpp  --  This file is part of Cool Characters Only.                *
 *                                                                                    *
 *   Copyright (C) 2024 Queen Suzie                                                   *
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
#include "ReplaceStages.h"

FunctionHook<void> hStageLoadUnloadHandler((intptr_t)0x43D510);
FunctionHook<signed int> hGameModeHandler((intptr_t)GameModeHandler);
FunctionHook<void*> hSummaryBgLoad((intptr_t)0x678BB0);

void ReplaceStages::init() {
	hStageLoadUnloadHandler.Hook(StageLoadUnloadHook);
	hGameModeHandler.Hook(GameModeHandler_h);
	hSummaryBgLoad.Hook(SummaryBgLoad);
}

void StageLoadUnloadHook() {
	if (GameState == GameStates_NormalExit || GameState == GameStates_Pause) {
		ReplaceStages::LAST_LEVEL = 0;
	}

	if (!TailsBoosterGot && GameState == GameStates_Exit_1 && CurrentLevel == LevelIDs_PrisonLane) {
		TailsBoosterGot = '1';
	}

	hStageLoadUnloadHandler.Original();
}

signed int GameModeHandler_h() {
	bool settingLevel = GameMode == GameMode_LoadStory;
	signed int ret = hGameModeHandler.Original();

	if (settingLevel) {
		if (CurrentLevel == LevelIDs_MissionStreet) {
			CurrentLevel = LevelIDs_RadicalHighway;
			CurrentCharacter = Characters_Shadow;
		} else if (CurrentLevel == LevelIDs_Route101280 && CurrentCharacter == Characters_MechTails) {
			CurrentLevel = LevelIDs_SkyRail;
			CurrentCharacter = Characters_Shadow;
		} else if (CurrentLevel == LevelIDs_SonicVsShadow1) {
			if (!ReplaceStages::WHITE_JUNGLE_COMPLETE && (ReplaceStages::LAST_LEVEL == LevelIDs_MetalHarbor || ReplaceStages::LAST_LEVEL == 0)) {
				CurrentLevel = LevelIDs_WhiteJungle;
				CurrentCharacter = Characters_Shadow;
				CurrentStoryLevelCount -= 1;
				AllStoriesLevelCount -= 1;
			} else {
				ReplaceStages::WHITE_JUNGLE_COMPLETE = true;
			}
		} else if (CurrentLevel == LevelIDs_TailsVsEggman2) {
			if (!ReplaceStages::FINAL_CHASE_COMPLETE && (ReplaceStages::LAST_LEVEL == LevelIDs_CrazyGadget || ReplaceStages::LAST_LEVEL == 0)) {
				CurrentLevel = LevelIDs_FinalChase;
				CurrentCharacter = Characters_Shadow;
				CurrentStoryLevelCount -= 2;
				AllStoriesLevelCount -= 2;
			} else {
				ReplaceStages::FINAL_CHASE_COMPLETE = true;
			}
		}

		if (CurrentLevel != 0) {
			ReplaceStages::LAST_LEVEL = CurrentLevel;
		}
	}

	return ret;
}

void* SummaryBgLoad() {
	if (SummaryBgCharacterID == Characters_Sonic) {
		SummaryBgCharacterID = Characters_Shadow;
		switch (SummarySceneID) {
			case 1: // Big Foot
				SummarySceneID = 25; // Hot Shot
				break;
			case 6: // Shadow 1
				if (ReplaceStages::WHITE_JUNGLE_COMPLETE) {
					SummarySceneID = 36; // Sonic 1
				} else {
					SummarySceneID = 35; // White Jungle
				}

				break;
			case 23: // Shadow 2
				SummarySceneID = 45; // Sonic 2
				break;
		}
	} else if (SummaryBgCharacterID == Characters_Knuckles) {
		SummaryBgCharacterID = Characters_Rouge;
		switch (SummarySceneID) {
			case 2: // Wild Canyon
				SummarySceneID = 26; // Dry Lagoon
				break;
			case 14: // Death Chamber
				SummarySceneID = 29; // Egg Quarters
				break;
			case 18: // Meteor Herd
				SummarySceneID = 40; // Mad Space
				break;
			case 19: // Rouge Fight
				SummarySceneID = 41; // Knuckles Fight
				break;
		}
	} else {
		switch (SummarySceneID) {
			case 9: // Mission Street
				SummaryBgCharacterID = Characters_Shadow;
				SummarySceneID = 28; // Radical Highway
				break;
			case 11: // Route 101
				SummaryBgCharacterID = Characters_Shadow;
				SummarySceneID = 38; // Sky Rail
				break;
			case 21: // Eggman 2
				if (!ReplaceStages::FINAL_CHASE_COMPLETE) {
					SummaryBgCharacterID = Characters_Shadow;
					SummarySceneID = 44; // Final Chase
				}

				break;
		}
	}

	return hSummaryBgLoad.Original();
}