/**************************************************************************************
 *   ReplaceCharacters.cpp  --  This file is part of Cool Characters Only.            *
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
#include "ReplaceCharacters.h"

// Sonic
FunctionHook<void, int> hLoadSonic((intptr_t)LoadSonic);
FunctionHook<void, int> hLoadShadow((intptr_t)LoadShadow);

// Knuckles
FunctionHook<void, int> hLoadKnuckles((intptr_t)LoadKnuckles);
FunctionHook<void, int> hLoadRouge((intptr_t)LoadRouge);
FunctionHook<void> hLoadAquaticMineCharAnims((intptr_t)LoadAquaticMineCharAnims);
FunctionHook<void> hLoadCannonsCoreKCharAnims((intptr_t)LoadCannonsCoreKCharAnims);

// Fixes
FunctionHook<void> hStageLoad((intptr_t)0x439610);
FunctionHook<int, int> hUpgradeGet((intptr_t)LevelItem_Main);
FunctionHook<void, ObjectMaster*> hInputColi((intptr_t)InputColi);

FunctionHook<BYTE*, ObjectMaster*> hUpgradeDataGet((intptr_t)UpgradeDataGet);

void ReplaceCharacters::init() {
	// Sonic
	hLoadSonic.Hook(LoadSonic_h);
	hLoadShadow.Hook(LoadSonic_h);

	// Knuckles
	hLoadKnuckles.Hook(LoadKnuckles_h);
	hLoadRouge.Hook(LoadKnuckles_h);
	hLoadAquaticMineCharAnims.Hook(LoadDryLagoon2PCharAnims);
	hLoadCannonsCoreKCharAnims.Hook(LoadDryLagoon2PCharAnims);

	// Fixes
	hStageLoad.Hook(SetStageUpgrades);
	hUpgradeGet.Hook(UpgradeHook);
	hInputColi.Hook(InputColi_h);
	hUpgradeDataGet.Hook(UpgradeDataGet_h);

	// PC HourGlass Fix
	WriteData<char>((char*)0x7083F6, 0xEBu);

	// Air Necklace Fix
	WriteData<char>((char*)0x459FA5, 0x90u);
	WriteData<char>((char*)0x459FA6, 0x90u);

	// BB Box Break Fix
	uint8_t opcode = 0x3Cu;
	uint8_t value = 0x48u;
	WriteData((void*)0x46ECF8, { opcode, value});

	ReplaceCharacters::initCharacterVoices();
	ReplaceCharacters::remapUpgradeData();
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
		ReplaceCharacters::setSonicUpgrades();
	} else if (CurrentCharacter == Characters_Knuckles) {
		ReplaceCharacters::setKnucklesUpgrades();
	} else if (CurrentCharacter == Characters_Rouge && KnucklesAirNecklaceGot) {
		MainCharObj2[0]->Upgrades |= Upgrades_KnucklesAirNecklace;
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

void ReplaceCharacters::remapUpgradeData() {
	LevelItems[0].Character = Characters_Shadow; // Bounce
	LevelItems[25].Character = Characters_Shadow; // Magic Gloves
	LevelItems[14].Character = Characters_Rouge; // Air Necklace

	// Idea is to override upgrade data but then restore actual upgrade values to not break upgrade handling.
	// This should let upgrades show up in levelup object but not break how everything has worked up to now.

	// Light Shows -> Air Shoes
	LevelItems[1] = LevelItems[3];
	LevelItems[1].Mask = Upgrades_SonicLightShoes;
	LevelItems[1].Index = 0;

	// Flame Ring
	LevelItems[2] = LevelItems[4];
	LevelItems[2].Mask = Upgrades_SonicFlameRing;
	LevelItems[2].Index = 3;

	// Sonic Mystic Melody
	LevelItems[18] = LevelItems[19];
	LevelItems[18].Mask = Upgrades_SonicMysticMelody;
	LevelItems[18].Index = 5;

	// Ancient Light
	LevelItems[24] = LevelItems[27];
	LevelItems[24].Mask = Upgrades_SonicAncientLight;
	LevelItems[24].Index = 1;

	// Shovel Claws -> Pick Nails
	LevelItems[12] = LevelItems[16];
	LevelItems[12].Mask = Upgrades_KnucklesShovelClaw;
	LevelItems[12].Index = 0xA;

	// Hammer Gloves -> Iron Boots
	LevelItems[13] = LevelItems[17];
	LevelItems[13].Mask = Upgrades_KnucklesHammerGloves;
	LevelItems[13].Index = 0xC;

	// Knuckles Mystic Melody
	LevelItems[22] = LevelItems[23];
	LevelItems[22].Mask = Upgrades_KnucklesMysticMelody;
	LevelItems[22].Index = 0xE;

	// Sunglasses -> Treasure Scope
	LevelItems[26] = LevelItems[15];
	LevelItems[26].Mask = Upgrades_KnucklesSunglasses;
	LevelItems[26].Index = 0xB;
}

char ReplaceCharacters::remapUpgradeMsg(int msgID) {
	switch (msgID) {
		case 1: // Light Shoes
			return (char)3;

		case 2: // Flame Ring
			return (char)4;

		case 12: // Shovel Claws
			return (char)16;

		case 13: // Hammer Gloves
			return (char)17;

		case 18: // Sonic Mystic Melody
			return (char)19;

		case 22: // Knuckles Mystic Melody
			return (char)23;

		case 24: // Ancient Light
			return (char)27;

		case 26: // Sunglasses
			return (char)15;
	}

	return (char)msgID;
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
	ReplaceCharacters::setStageUpgrades();
}

int UpgradeHook(int upgrade) {
	ReplaceCharacters::CAN_MANIPULATE_ACTION_DATA = true;
	int upgrades = MainCharObj2[0]->Upgrades;
	int ret = hUpgradeGet.Original(upgrade);
	ReplaceCharacters::CAN_MANIPULATE_ACTION_DATA = false;

	if (upgrades != MainCharObj2[0]->Upgrades) {
		ReplaceCharacters::setStageUpgrades();
	}

	return ret;
}

void __cdecl InputColi_h(ObjectMaster* obj) {
	hInputColi.Original(obj);
	if (CurrentLevel == LevelIDs_CannonsCoreS) {
		ControllerEnabled[0] = 1; // Allow Shadow to move in Cannon's Core
	}
}

BYTE* UpgradeDataGet_h(ObjectMaster* a1) {
	BYTE* ret = hUpgradeDataGet.Original(a1);
	if (ret && ReplaceCharacters::CAN_MANIPULATE_ACTION_DATA) {
		ObjectMaster* v9 = (ObjectMaster*)*((_DWORD*)ret + 1);
		if (v9) {
			a1->Data1.Entity->NextAction = ReplaceCharacters::remapUpgradeMsg((int)a1->Data1.Entity->NextAction);
		}
	}

	return ret;
}