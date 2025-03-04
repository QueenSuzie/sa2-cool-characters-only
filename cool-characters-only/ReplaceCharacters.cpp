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
FunctionHook<void> hLoadAquaticMineCharAnims((intptr_t)LoadAquaticMineCharAnims);
FunctionHook<void> hLoadCannonsCoreKCharAnims((intptr_t)LoadCannonsCoreKCharAnims);
FunctionHook<void> hLoadDryLagoonCharAnims((intptr_t)LoadDryLagoonCharAnims);

// Fixes
FunctionHook<void> hStageLoad((intptr_t)0x439610);
FunctionHook<int, int> hUpgradeGet((intptr_t)LevelItem_Main);
FunctionHook<void, ObjectMaster*> hInputColi((intptr_t)InputColi);

FunctionHook<BYTE*, ObjectMaster*> hUpgradeDataGet((intptr_t)UpgradeDataGet);
static CharacterSoundBank SoundBanksCopy[12];
static CharacterVoiceBank VoiceBanksCopy[10];
static LevelItemData LevelItemsCopy[28];

void ReplaceCharacters::init() {
	// Sonic
	hLoadSonic.Hook(LoadSonic_h);
	hLoadShadow.Hook(LoadSonic_h);
	
	// Knuckles
	hLoadAquaticMineCharAnims.Hook(LoadDryLagoon2PCharAnims);
	hLoadCannonsCoreKCharAnims.Hook(LoadDryLagoon2PCharAnims);
	hLoadDryLagoonCharAnims.Hook(LoadDryLagoonAnims);

	// Fixes
	if (!ReplaceCharacters::SSU_DETECTED) {
		hStageLoad.Hook(SetStageUpgrades);
	}

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
	WriteData((void*)0x46ECF8, { opcode, value });

	ReplaceCharacters::initCharacterVoices();
	ReplaceCharacters::remapUpgradeData();
	ReplaceCharacters::remapMiniCutscenes();
	ReplaceCharacters::remapStageSelectLevels();
}

void ReplaceCharacters::initCharacterVoices() {
	for (int i = 0; i < 12; i++) {
		SoundBanksCopy[i] = CharacterSoundBanks1P[i];
	}

	for (int i = 0; i < 10; i++) {
		VoiceBanksCopy[i] = CharacterVoiceBanks1P[i];
	}
}

void ReplaceCharacters::setStageUpgrades() {
	if (CurrentCharacter == Characters_Sonic) {
		ReplaceCharacters::setSonicUpgrades();
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

void ReplaceCharacters::remapUpgradeData() {
	for (int i = 0; i < 28; i++) {
		LevelItemsCopy[i] = {
			LevelItems[i].Character,
			LevelItems[i].Name,
			LevelItems[i].Mask,
			LevelItems[i].Index,
			LevelItems[i].field_10,
			LevelItems[i].anonymous_1,
			LevelItems[i].anonymous_2,
			LevelItems[i].anonymous_3,
			LevelItems[i].field_20
		};
	}

	LevelItems[0].Character = Characters_Shadow; // Bounce
	LevelItems[25].Character = Characters_Shadow; // Magic Gloves
	LevelItems[14].Character = Characters_Rouge; // Air Necklace

	// Idea is to override upgrade data but then restore actual upgrade values to not break upgrade handling.
	// This should let upgrades show up in levelup object but not break how everything has worked up to now.

	// Light Shoes -> Air Shoes
	ReplaceCharacters::copyLevelItem(&LevelItems[1], &LevelItemsCopy[3]);
	LevelItems[1].Mask = Upgrades_SonicLightShoes;
	LevelItems[1].Index = 0;

	// Flame Ring
	ReplaceCharacters::copyLevelItem(&LevelItems[2], &LevelItemsCopy[4]);
	LevelItems[2].Mask = Upgrades_SonicFlameRing;
	LevelItems[2].Index = 3;

	// Sonic Mystic Melody
	ReplaceCharacters::copyLevelItem(&LevelItems[18], &LevelItemsCopy[19]);
	LevelItems[18].Mask = Upgrades_SonicMysticMelody;
	LevelItems[18].Index = 5;

	// Ancient Light
	ReplaceCharacters::copyLevelItem(&LevelItems[24], &LevelItemsCopy[27]);
	LevelItems[24].Mask = Upgrades_SonicAncientLight;
	LevelItems[24].Index = 1;
}

void ReplaceCharacters::remapUpgradeDataDynamic() {
	LevelItems[14].Character = CurrentSequenceNo == 2 ? Characters_Knuckles : Characters_Rouge; // Air Necklace
	ReplaceCharacters::copyLevelItem(&LevelItems[17], &LevelItemsCopy[17]);

	if (CurrentCharacter == Characters_Knuckles) {
		// Restore Originals
		ReplaceCharacters::copyLevelItem(&LevelItems[12], &LevelItemsCopy[12]);
		ReplaceCharacters::copyLevelItem(&LevelItems[13], &LevelItemsCopy[13]);
		ReplaceCharacters::copyLevelItem(&LevelItems[22], &LevelItemsCopy[22]);
		ReplaceCharacters::copyLevelItem(&LevelItems[26], &LevelItemsCopy[26]);

		if (CurrentSequenceNo == 2 && KnucklesHammerGlovesGot && CurrentLevel == LevelIDs_MadSpace) {
			ReplaceCharacters::copyLevelItem(&LevelItems[17], NULL);
		}
	} else if (CurrentCharacter == Characters_Rouge) {
		// Shovel Claws -> Pick Nails
		ReplaceCharacters::copyLevelItem(&LevelItems[12], &LevelItemsCopy[16]);

		// Hammer Gloves -> Iron Boots
		ReplaceCharacters::copyLevelItem(&LevelItems[13], &LevelItemsCopy[17]);

		// Knuckles Mystic Melody
		ReplaceCharacters::copyLevelItem(&LevelItems[22], &LevelItemsCopy[23]);

		// Sunglasses -> Treasure Scope
		ReplaceCharacters::copyLevelItem(&LevelItems[26], &LevelItemsCopy[15]);

		// Restore Iron Boots
		ReplaceCharacters::copyLevelItem(&LevelItems[17], &LevelItemsCopy[17]);
	}

	if (CurrentCharacter == Characters_Sonic && CurrentSequenceNo == 2) {
		// Restore Originals
		LevelItems[0].Character = Characters_Sonic;
		ReplaceCharacters::copyLevelItem(&LevelItems[1], &LevelItemsCopy[1]);
		ReplaceCharacters::copyLevelItem(&LevelItems[2], &LevelItemsCopy[2]);
		ReplaceCharacters::copyLevelItem(&LevelItems[18], &LevelItemsCopy[18]);
		ReplaceCharacters::copyLevelItem(&LevelItems[24], &LevelItemsCopy[24]);
		LevelItems[25].Character = Characters_Sonic;
	} else if (CurrentSequenceNo != 2 && (CurrentCharacter == Characters_Shadow || CurrentCharacter == Characters_Sonic)) {
		LevelItems[0].Character = Characters_Shadow; // Bounce
		LevelItems[25].Character = Characters_Shadow; // Magic Gloves

		// Light Shoes -> Air Shoes
		ReplaceCharacters::copyLevelItem(&LevelItems[1], &LevelItemsCopy[3]);
		LevelItems[1].Mask = Upgrades_SonicLightShoes;
		LevelItems[1].Index = 0;

		// Flame Ring
		ReplaceCharacters::copyLevelItem(&LevelItems[2], &LevelItemsCopy[4]);
		LevelItems[2].Mask = Upgrades_SonicFlameRing;
		LevelItems[2].Index = 3;

		// Sonic Mystic Melody
		ReplaceCharacters::copyLevelItem(&LevelItems[18], &LevelItemsCopy[19]);
		LevelItems[18].Mask = Upgrades_SonicMysticMelody;
		LevelItems[18].Index = 5;

		// Ancient Light
		ReplaceCharacters::copyLevelItem(&LevelItems[24], &LevelItemsCopy[27]);
		LevelItems[24].Mask = Upgrades_SonicAncientLight;
		LevelItems[24].Index = 1;
	}
}

void ReplaceCharacters::copyLevelItem(LevelItemData* dest, LevelItemData* source) {
	if (dest == NULL) {
		return;
	}

	if (source == NULL) {
		dest->anonymous_1 = NULL;
		dest->anonymous_2 = NULL;
		dest->anonymous_3 = NULL;
		dest->Character = NULL;
		dest->Name = NULL;
		dest->Mask = NULL;
		dest->Index = NULL;
		dest->field_10 = NULL;
		dest->field_20 = NULL;
	} else {
		dest->anonymous_1 = source->anonymous_1;
		dest->anonymous_2 = source->anonymous_2;
		dest->anonymous_3 = source->anonymous_3;
		dest->Character = source->Character;
		dest->Name = source->Name;
		dest->Mask = source->Mask;
		dest->Index = source->Index;
		dest->field_10 = source->field_10;
		dest->field_20 = source->field_20;
	}
}

char ReplaceCharacters::remapUpgradeMsg(int msgID) {
	switch (msgID) {
		case 1: // Light Shoes
			return CurrentSequenceNo == 2 ? (char)1 : (char)3;

		case 2: // Flame Ring
			return CurrentSequenceNo == 2 ? (char)2 : (char)4;

		case 12: // Shovel Claws
			return CurrentCharacter == Characters_Knuckles ? (char)12 : (char)16;

		case 13: // Hammer Gloves
			return CurrentCharacter == Characters_Knuckles ? (char)13 : (char)17;

		case 18: // Sonic Mystic Melody
			return CurrentSequenceNo == 2 ? (char)18 : (char)19;

		case 22: // Knuckles Mystic Melody
			return CurrentCharacter == Characters_Knuckles ? (char)22 : (char)23;

		case 24: // Ancient Light
			return CurrentSequenceNo == 2 ? (char)24 : (char)27;

		case 26: // Sunglasses
			return CurrentCharacter == Characters_Knuckles ? (char)26 : (char)15;
	}

	if (msgID == 17 && CurrentSequenceNo == 2 && !KnucklesHammerGlovesGot) {
		// Troll message
		return (char)65;
	}

	return (char)msgID;
}

void ReplaceCharacters::remapMiniCutscenes() {
	LevelCutscenes[1].Level = LevelIDs_DeathChamber;
	LevelCutscenes[1].Character = Characters_Rouge;
	LevelCutscenes[1].Cutscene = 108;
}

void ReplaceCharacters::remapStageSelectLevels() {
	for (int i = 0; i < StageSelectLevels.size(); i++) {
		StageSelectLevel t = StageSelectLevels[i];
		if (StageSelectLevels[i].Character == Characters_Knuckles) {
			StageSelectLevels[i].Character = Characters_Rouge;
		}
	}
}

void LoadSonic_h(int player) {
	CharacterVoiceBanks1P[Characters_Sonic].Filename_EN = VoiceBanksCopy[Characters_Sonic].Filename_EN;
	CharacterVoiceBanks1P[Characters_Sonic].Filename_JP = VoiceBanksCopy[Characters_Sonic].Filename_JP;
	CharacterVoiceBanks1P[Characters_Sonic].SoundList = VoiceBanksCopy[Characters_Sonic].SoundList;
	CharacterSoundBanks1P[Characters_Sonic].SoundList = SoundBanksCopy[Characters_Sonic].SoundList;

	if (CurrentSequenceNo && CurrentSequenceNo == 2 && player == 0) {
		hLoadSonic.Original(player);
	} else if ((CurrentSequenceNo && CurrentSequenceNo == 2) || player == 0) {
		hLoadShadow.Original(player);
		CharacterVoiceBanks1P[Characters_Sonic].Filename_EN = VoiceBanksCopy[Characters_Shadow].Filename_EN;
		CharacterVoiceBanks1P[Characters_Sonic].Filename_JP = VoiceBanksCopy[Characters_Shadow].Filename_JP;
		CharacterVoiceBanks1P[Characters_Sonic].SoundList = VoiceBanksCopy[Characters_Shadow].SoundList;
		CharacterSoundBanks1P[Characters_Sonic].SoundList = SoundBanksCopy[Characters_Shadow].SoundList;
	} else {
		hLoadSonic.Original(player);
	}
}

void LoadDryLagoonAnims() {
	if (CurrentSequenceNo && CurrentSequenceNo == 2) {
		LoadDryLagoon2PCharAnims();
	} else {
		hLoadDryLagoonCharAnims.Original();
	}
}

void SetStageUpgrades() {
	hStageLoad.Original();
	ReplaceCharacters::setStageUpgrades();
}

int UpgradeHook(int upgrade) {
	char ironBootsOrig = RougeIronBootsGot;
	ReplaceCharacters::CAN_MANIPULATE_ACTION_DATA = true;
	int upgrades = MainCharObj2[0]->Upgrades;
	int ret = hUpgradeGet.Original(upgrade);
	ReplaceCharacters::CAN_MANIPULATE_ACTION_DATA = false;

	if (!ReplaceCharacters::SSU_DETECTED && upgrades != MainCharObj2[0]->Upgrades) {
		ReplaceCharacters::setStageUpgrades();
	}

	if (CurrentSequenceNo == 2 && !KnucklesHammerGlovesGot && CurrentLevel == LevelIDs_MadSpace) {
		RougeIronBootsGot = ironBootsOrig;
		MainCharObj2[0]->Upgrades = upgrades;
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