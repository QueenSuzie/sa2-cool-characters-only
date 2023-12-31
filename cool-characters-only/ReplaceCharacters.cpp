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
FunctionHook<void, int> hLoadShadow((intptr_t)LoadShadow);

// Knuckles
FunctionHook<void, int> hLoadKnuckles((intptr_t)LoadKnuckles);
FunctionHook<void, int> hLoadRouge((intptr_t)LoadRouge);
FunctionHook<void> hLoadAquaticMineCharAnims((intptr_t)LoadAquaticMineCharAnims);

// Fixes
FunctionHook<void> hStageLoad((intptr_t)0x439610);
FunctionHook<int, int> hUpgradeGet((intptr_t)LevelItem_Main);

void ReplaceCharacters::init() {
	// Sonic
	hLoadSonic.Hook(LoadSonic_h);
	hLoadShadow.Hook(LoadSonic_h);

	// Knuckles
	hLoadKnuckles.Hook(LoadKnuckles_h);
	hLoadRouge.Hook(LoadKnuckles_h);
	hLoadAquaticMineCharAnims.Hook(LoadDryLagoon2PCharAnims);

	// Fixes
	hStageLoad.Hook(SetStageUpgrades);
	hUpgradeGet.Hook(UpgradeHook);

	this->initCharacterVoices();
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

void ReplaceCharacters::setStageUpgrades() {
	if (CurrentCharacter == Characters_Sonic) {
		this->setSonicUpgrades();
	} else if (CurrentCharacter == Characters_Knuckles) {
		this->setKnucklesUpgrades();
	}
}

void ReplaceCharacters::setSonicUpgrades() {
	if (SonicLightShoesGot) {
		MainCharObj2[0]->Upgrades |= Upgrades_ShadowAirShoes;
	}

	if (SonicAncientLightGot) {
		MainCharObj2[0]->Upgrades |= Upgrades_ShadowAncientLight;
	}

	if (SonicMagicGlovesGot) {
		MainCharObj2[0]->Upgrades |= Upgrades_SonicMagicGloves;
	}

	if (SonicFlameRingGot) {
		MainCharObj2[0]->Upgrades |= Upgrades_ShadowFlameRing;
	}

	if (SonicBounceBraceletGot) {
		MainCharObj2[0]->Upgrades |= Upgrades_SonicBounceBracelet;
	}

	if (SonicMysticMelodyGot) {
		MainCharObj2[0]->Upgrades |= Upgrades_ShadowMysticMelody;
	}
}

void ReplaceCharacters::setKnucklesUpgrades() {
	if (KnucklesShovelClawGot) {
		MainCharObj2[0]->Upgrades |= Upgrades_RougePickNails;
	}

	if (KnucklesSunglassesGot) {
		MainCharObj2[0]->Upgrades |= Upgrades_RougeTreasureScope;
	}

	if (KnucklesHammerGlovesGot) {
		MainCharObj2[0]->Upgrades |= Upgrades_RougeIronBoots;
	}

	if (KnucklesAirNecklaceGot) {
		MainCharObj2[0]->Upgrades |= Upgrades_KnucklesAirNecklace;
	}

	if (KnucklesMysticMelodyGot) {
		MainCharObj2[0]->Upgrades |= Upgrades_RougeMysticMelody;
	}
}

void LoadSonic_h(int player) {
	if (player == 0) {
		hLoadShadow.Original(0);
	} else {
		hLoadSonic.Original(player);
	}
}

void LoadKnuckles_h(int player) {
	if (player == 0) {
		hLoadRouge.Original(0);
	} else {
		hLoadKnuckles.Original(player);
	}
}

void SetStageUpgrades() {
	hStageLoad.Original();
	ReplaceMod.setStageUpgrades();
}

int UpgradeHook(int upgrade) {
	int upgrades = MainCharObj2[0]->Upgrades;
	int ret = hUpgradeGet.Original(upgrade);
	if (CurrentLevel != LevelIDs_DeathChamber) {
		return ret;
	}

	if (MainCharObj2[0]->Upgrades != upgrades) {
		MainCharObj2[0]->Upgrades |= Upgrades_RougeIronBoots;
	}

	return ret;
}