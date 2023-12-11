/**************************************************************************************
 *   ReplaceCharacters.cpp  --  This file is part of Cool Characters Only.            *
 *                                                                                    *
 *   Copyright (C) 2023 Queen Suzie                                                   *
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
#include "ReplaceCharacters.h"

// Sonic
FunctionHook<void, int> hLoadSonic((intptr_t)LoadSonic);
FunctionHook<int> hLoadSonEffTex((intptr_t)LoadSonEffTex);

// Knuckles
FunctionHook<void, int> hLoadKnuckles((intptr_t)LoadKnuckles);
FunctionHook<void> hLoadAquaticMineCharAnims((intptr_t)LoadAquaticMineCharAnims);

// Fixes
FunctionHook<void> hStageLoad((intptr_t)0x47BB50);
FunctionHook<int, int> hUpgradeGet((intptr_t)LevelItem_Main);
FunctionHook<void, char> hloadResultScreen((intptr_t)LoadResultScreenObjects);
FunctionHook<void> hStageLoadUnloadHandler((intptr_t)0x43D510);

void ReplaceCharacters::init() {
	// Sonic
	hLoadSonic.Hook(LoadShadow);
	hLoadSonEffTex.Hook(LoadShadEffTex);

	// Knuckles
	hLoadKnuckles.Hook(LoadRouge);
	hLoadAquaticMineCharAnims.Hook(LoadDryLagoon2PCharAnims);

	// Fixes
	hStageLoad.Hook(StageLoadHook);
	hUpgradeGet.Hook(UpgradeHook);
	hloadResultScreen.Hook(StageCompletedHook);
	hStageLoadUnloadHandler.Hook(StageLoadUnloadHook);

	this->initCharacterVoices();
	this->initSonicStages();
	this->initKnucklesStages();
}

void ReplaceCharacters::initCharacterVoices() {
	CharacterVoiceBanks1P[Characters_Sonic].Filename_EN = CharacterVoiceBanks1P[Characters_Shadow].Filename_EN;
	CharacterVoiceBanks1P[Characters_Sonic].Filename_JP = CharacterVoiceBanks1P[Characters_Shadow].Filename_JP;
	CharacterVoiceBanks1P[Characters_Sonic].SoundList = CharacterVoiceBanks1P[Characters_Shadow].SoundList;
	CharacterVoiceBanks2P[Characters_Sonic].Filename_EN = CharacterVoiceBanks2P[Characters_Shadow].Filename_EN;
	CharacterVoiceBanks2P[Characters_Sonic].Filename_JP = CharacterVoiceBanks2P[Characters_Shadow].Filename_JP;
	CharacterVoiceBanks2P[Characters_Sonic].SoundList = CharacterVoiceBanks2P[Characters_Shadow].SoundList;

	CharacterVoiceBanks1P[Characters_Knuckles].Filename_EN = CharacterVoiceBanks1P[Characters_Rouge].Filename_EN;
	CharacterVoiceBanks1P[Characters_Knuckles].Filename_JP = CharacterVoiceBanks1P[Characters_Rouge].Filename_JP;
	CharacterVoiceBanks1P[Characters_Knuckles].SoundList = CharacterVoiceBanks1P[Characters_Rouge].SoundList;
	CharacterVoiceBanks2P[Characters_Knuckles].Filename_EN = CharacterVoiceBanks2P[Characters_Rouge].Filename_EN;
	CharacterVoiceBanks2P[Characters_Knuckles].Filename_JP = CharacterVoiceBanks2P[Characters_Rouge].Filename_JP;
	CharacterVoiceBanks2P[Characters_Knuckles].SoundList = CharacterVoiceBanks2P[Characters_Rouge].SoundList;
}

void ReplaceCharacters::initSonicStages() {
	this->sonicStages.push_back(LevelIDs_CityEscape);
	this->sonicStages.push_back(LevelIDs_MetalHarbor);
	this->sonicStages.push_back(LevelIDs_SonicVsShadow1);
	this->sonicStages.push_back(LevelIDs_GreenForest);
	this->sonicStages.push_back(LevelIDs_PyramidCave);
	this->sonicStages.push_back(LevelIDs_EggGolemS);
	this->sonicStages.push_back(LevelIDs_CrazyGadget);
	this->sonicStages.push_back(LevelIDs_FinalRush);
	this->sonicStages.push_back(LevelIDs_SonicVsShadow2);
	this->sonicStages.push_back(LevelIDs_CannonsCoreS);
	this->sonicStages.push_back(LevelIDs_GreenHill);
}

void ReplaceCharacters::initKnucklesStages() {
	this->knucklesStages.push_back(LevelIDs_WildCanyon);
	this->knucklesStages.push_back(LevelIDs_PumpkinHill);
	this->knucklesStages.push_back(LevelIDs_AquaticMine);
	this->knucklesStages.push_back(LevelIDs_DeathChamber);
	this->knucklesStages.push_back(LevelIDs_KingBoomBoo);
	this->knucklesStages.push_back(LevelIDs_MeteorHerd);
	this->knucklesStages.push_back(LevelIDs_CannonsCoreK);
}

void ReplaceCharacters::setStageUpgrades() {
	if (std::find(this->sonicStages.begin(), this->sonicStages.end(), CurrentLevel) != this->sonicStages.end()) {
		this->setSonicUpgrades();
	} else if (std::find(this->knucklesStages.begin(), this->knucklesStages.end(), CurrentLevel) != this->knucklesStages.end()) {
		this->setKnucklesUpgrades();
	}
}

void ReplaceCharacters::setSonicUpgrades() {
	this->originalUpgrades1 = MainCharObj2[0]->Upgrades;
	if (TwoPlayerMode) {
		this->originalUpgrades2 = MainCharObj2[1]->Upgrades;
	}

	if (CurrentLevel == LevelIDs_CityEscape || CurrentLevel == LevelIDs_MetalHarbor) {
		MainCharObj2[0]->Upgrades = 0;
		if (TwoPlayerMode) {
			MainCharObj2[1]->Upgrades = 0;
		}

		return;
	}

	for (int i = 0; i < (TwoPlayerMode == 0 ? 1 : 2); i++) {
		int upgrades = Upgrades_SonicLightShoes | Upgrades_ShadowAirShoes;
		if (CurrentLevel == LevelIDs_GreenHill) {
			upgrades = Upgrades_SonicBounceBracelet;
		} else if (CurrentLevel == LevelIDs_CrazyGadget || CurrentLevel > LevelIDs_PyramidCave) {
			upgrades |= Upgrades_SonicBounceBracelet;
		}

		MainCharObj2[i]->Upgrades = upgrades;
	}
}

void ReplaceCharacters::setKnucklesUpgrades() {
	this->originalUpgrades1 = MainCharObj2[0]->Upgrades;
	if (TwoPlayerMode) {
		this->originalUpgrades2 = MainCharObj2[1]->Upgrades;
	}

	if (CurrentLevel == LevelIDs_WildCanyon || CurrentLevel == LevelIDs_PumpkinHill) {
		MainCharObj2[0]->Upgrades = 0;
		if (TwoPlayerMode) {
			MainCharObj2[1]->Upgrades = 0;
		}

		return;
	}

	for (int i = 0; i < (TwoPlayerMode == 0 ? 1 : 2); i++) {
		int upgrades = Upgrades_KnucklesShovelClaw | Upgrades_RougePickNails;
		if (CurrentLevel >= LevelIDs_MeteorHerd) {
			upgrades |= Upgrades_KnucklesShovelClaw | Upgrades_RougeIronBoots;
		}

		MainCharObj2[i]->Upgrades = upgrades;
	}
}

void ReplaceCharacters::restoreLevelUpgrades() {
	if (this->originalUpgrades1 < 0) {
		return;
	}

	MainCharObj2[0]->Upgrades = this->originalUpgrades1;
	if (TwoPlayerMode) {
		MainCharObj2[1]->Upgrades = this->originalUpgrades2;
	}

	this->originalUpgrades1 = -1;
	this->originalUpgrades2 = -1;
}

void StageLoadHook() {
	hStageLoad.Original();
	ReplaceMod.setStageUpgrades();
}

int UpgradeHook(int upgrade) {
	if (CurrentLevel != LevelIDs_DeathChamber) {
		return hUpgradeGet.Original(upgrade);
	}

	int upgrades = MainCharObj2[0]->Upgrades;
	int ret = hUpgradeGet.Original(upgrade);
	if (MainCharObj2[0]->Upgrades != upgrades) {
		MainCharObj2[0]->Upgrades |= Upgrades_KnucklesShovelClaw | Upgrades_RougeIronBoots;
	}

	return ret;
}

void StageCompletedHook(char player) {
	ReplaceMod.restoreLevelUpgrades();
	hloadResultScreen.Original(player);
}

void StageLoadUnloadHook() {
	// Only on exit game or game over. For cannon's core, also on normal stage exit.
	if (
		(
			GameState == GameStates_Exit_1 &&
			CurrentLevel >= LevelIDs_CannonsCoreS &&
			CurrentLevel <= LevelIDs_CannonsCoreK
		) ||
		GameState == GameStates_NormalExit ||
		GameState == GameStates_Pause
	) {
		ReplaceMod.restoreLevelUpgrades();
	}

	hStageLoadUnloadHandler.Original();
}