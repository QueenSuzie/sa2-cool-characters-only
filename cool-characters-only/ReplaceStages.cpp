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

FastcallFunctionHook<void, int, SeqSection*> hLoadStoryEntry((intptr_t)LoadStoryEntry);
FastcallFunctionHook<NJS_TEXLIST*, const char*> hLoadCharTextures((intptr_t)LoadCharTextures);
FunctionHook<void*> hSummaryBgLoad((intptr_t)0x678BB0);
FunctionHook<void> hProcessWinTime((intptr_t)0x452A00);

SeqAndSummarySection ReplaceStages::FallenHeroStory[] = {
	SeqEvent(Event::FREE_SHADOW, 0, 0),
	SeqStage(Characters_Sonic, LevelIDs_CityEscape, Characters_Shadow, Summary::HOT_SHOT),
	SeqStage(Characters_Sonic, LevelIDs_BigFoot, Characters_Shadow, Summary::HOT_SHOT),
	SeqEvent(Event::BIG_FOOT_SHADOW_SONIC_DARK, Event::MASTER_EMERALD_BREAK_DARK, Characters_Shadow, Summary::HOT_SHOT),
	SeqStage(Characters_Rouge, LevelIDs_WildCanyon, Characters_Rouge, Summary::DRY_LAGOON),
	SeqEvent(Event::TAILS_FINDS_AMY, Characters_Rouge, Summary::DRY_LAGOON),
	SeqStage(Characters_MechTails, LevelIDs_TailsVsEggman1, Characters_MechTails, Summary::EGGMAN_1),
	SeqEvent(Event::TAILS_RESCUED_AMY, Characters_MechTails, Summary::EGGMAN_1),
	SeqStage(Characters_MechTails, LevelIDs_PrisonLane, Characters_MechTails, Summary::PRISON_LANE),
	SeqStage(Characters_Sonic, LevelIDs_MetalHarbor, Characters_Shadow, Summary::WHITE_JUNGLE),
	SeqEvent(Event::ROUGE_REPORTS_PROBLEM, Characters_Shadow, Summary::WHITE_JUNGLE),
	SeqStage(Characters_Shadow, LevelIDs_WhiteJungle, Characters_Shadow, Summary::WHITE_JUNGLE),
	SeqStage(Characters_Sonic, LevelIDs_SonicVsShadow1, Characters_Shadow, Summary::SONIC_1),
	SeqEvent(Event::SHADOW_RESCUES_ROUGE_PT1, Characters_Shadow, Summary::SONIC_1),
	SeqStage(Characters_Sonic, LevelIDs_GreenForest, Characters_Shadow, Summary::SONIC_1),
	SeqEvent(Event::SHADOW_RESCUES_ROUGE_PT2, Event::PRISON_ISLAND_BLOWS_UP, Event::TIMER_FOR_PUMPKIN_HILL, Characters_Shadow, Summary::SONIC_1),
	SeqStage(Characters_Rouge, LevelIDs_PumpkinHill, Characters_Rouge, Summary::DRY_LAGOON),
	SeqEvent(Event::TIMER_FOR_RADICAL_HIGHWAY, Event::SHADOW_REVENGE_MEMORY, Characters_Rouge, Summary::DRY_LAGOON),
	SeqStage(Characters_Shadow, LevelIDs_RadicalHighway, Characters_Shadow, Summary::RADICAL_HIGHWAY),
	SeqEvent(Event::TIMER_FOR_AQUATIC_MINE, Characters_Shadow, Summary::RADICAL_HIGHWAY),
	SeqStage(Characters_Rouge, LevelIDs_AquaticMine, Characters_Rouge, Summary::DRY_LAGOON),
	SeqStage(Characters_Shadow, LevelIDs_SkyRail, Characters_Shadow, Summary::SKY_RAIL),
	SeqEvent(Event::LIMO_SCENE_HERO, Event::DESERT_AREA_ARRIVAL_HERO, Characters_Shadow, Summary::SKY_RAIL),
	SeqStage(Characters_MechTails, LevelIDs_HiddenBase, Characters_MechTails, Summary::HIDDEN_BASE),
	SeqStage(Characters_Sonic, LevelIDs_PyramidCave, Characters_Shadow, Summary::SKY_RAIL),
	SeqStage(Characters_Rouge, LevelIDs_DeathChamber, Characters_Rouge, Summary::EGG_QUARTERS),
	SeqStage(Characters_Rouge, LevelIDs_KingBoomBoo, Characters_Rouge, Summary::EGG_QUARTERS),
	SeqEvent(Event::EGG_GOLEM_ENTRANCE_HERO, Characters_Rouge, Summary::EGG_QUARTERS),
	SeqStage(Characters_Sonic, LevelIDs_EggGolemS, Characters_Shadow, Summary::SKY_RAIL),
	SeqEvent(Event::SHUTTLE_LAUNCH_HERO, Event::TEAM_HERO_ARRIVES_AT_ARK, Characters_Shadow, Summary::SKY_RAIL),
	SeqStage(Characters_MechTails, LevelIDs_EternalEngine, Characters_MechTails, Summary::ETERNAL_ENGINE),
	SeqEvent(Event::ROUGE_HEADS_FOR_SPACE_EMERALDS, Event::AMY_GETS_CAUGHT_HERO, Characters_MechTails, Summary::ETERNAL_ENGINE),
	SeqStage(Characters_Rouge, LevelIDs_MeteorHerd, Characters_Rouge, Summary::MAD_SPACE),
	SeqStage(Characters_Rouge, LevelIDs_KnucklesVsRouge, Characters_Rouge, Summary::KNUCKLES_FIGHT),
	SeqEvent(Event::KNUCKLES_RESCUES_ROUGE_DARK, Event::TIMER_FOR_CRAZY_GADGET, Characters_Rouge, Summary::KNUCKLES_FIGHT),
	SeqStage(Characters_Sonic, LevelIDs_CrazyGadget, Characters_Shadow, Summary::FINAL_CHASE),
	SeqStage(Characters_Shadow, LevelIDs_FinalChase, Characters_Shadow, Summary::FINAL_CHASE),
	SeqEvent(Event::EGGMAN_OUTPLAYS_HEROES, Characters_Shadow, Summary::FINAL_CHASE),
	SeqStage(Characters_MechTails, LevelIDs_TailsVsEggman2, Characters_MechTails, Summary::EGGMAN_2),
	SeqEvent(Event::SHADOW_CONFRONTS_ROUGE, Event::SONIC_SURVIVES_AFTER_CHAOS_CONTROL, Characters_MechTails, Summary::EGGMAN_2),
	SeqStage(Characters_Sonic, LevelIDs_FinalRush, Characters_Shadow, Summary::FINAL_CHASE),
	SeqEvent(Event::SHADOW_VS_SONIC_2_DARK, Characters_Shadow, Summary::FINAL_CHASE),
	SeqStage(Characters_Sonic, LevelIDs_SonicVsShadow2, Characters_Shadow, Summary::SONIC_2),
	SeqEvent(Event::HERO_TEAM_VICTORY, Characters_Shadow, Summary::SONIC_2),
	SeqCredits,
	SeqEvent(Event::DARK_STORY_TRAILER, Characters_Shadow, Summary::SONIC_2),
	SeqTitle
};

SeqAndSummarySection ReplaceStages::FallenDarkStory[] = {
	SeqEvent(Event::MASTER_EMERALD_BREAK_HERO, 0, 0),
	SeqStage(Characters_Knuckles, LevelIDs_DryLagoon, Characters_Knuckles, Summary::WILD_CANYON),
	SeqStage(Characters_Sonic, LevelIDs_HotShot, Characters_Sonic, Summary::BIG_FOOT),
	SeqStage(Characters_Knuckles, LevelIDs_WildCanyon, Characters_Knuckles, Summary::WILD_CANYON),
	SeqEvent(Event::EGGMAN_THREATENS_AMY, Characters_Knuckles, Summary::WILD_CANYON),
	SeqStage(Characters_MechEggman, LevelIDs_TailsVsEggman1, Characters_MechEggman, Summary::TAILS_1),
	SeqEvent(Event::AMY_BREAKS_OUT_SONIC, Characters_MechEggman, Summary::TAILS_1),
	SeqStage(Characters_Sonic, LevelIDs_MetalHarbor, Characters_Sonic, Summary::METAL_HARBOR),
	SeqStage(Characters_MechEggman, LevelIDs_WeaponsBed, Characters_MechEggman, Summary::WEAPONS_BED),
	SeqStage(Characters_Knuckles, LevelIDs_SecurityHall, Characters_Knuckles, Summary::WILD_CANYON),
	SeqStage(Characters_Knuckles, LevelIDs_FlyingDog, Characters_Knuckles, Summary::WILD_CANYON),
	SeqStage(Characters_Knuckles, LevelIDs_PumpkinHill, Characters_Knuckles, Summary::PUMPKIN_HILL),
	SeqStage(Characters_Knuckles, LevelIDs_DeathChamber, Characters_Knuckles, Summary::DEATH_CHAMBER),
	SeqEvent(Event::EGG_GOLEM_ENTRANCE_DARK, Characters_Knuckles, Summary::DEATH_CHAMBER),
	SeqStage(Characters_MechEggman, LevelIDs_EggGolemE, Characters_MechEggman, Summary::EGG_GOLEM_E),
	SeqStage(Characters_Knuckles, LevelIDs_AquaticMine, Characters_Knuckles, Summary::AQUATIC_MINE),
	SeqEvent(Event::SHUTTLE_LAUNCH_DARK, Characters_MechEggman, Summary::EGG_GOLEM_E),
	SeqStage(Characters_MechEggman, LevelIDs_LostColony, Characters_MechEggman, Summary::LOST_COLONY),
	SeqStage(Characters_Knuckles, LevelIDs_MeteorHerd, Characters_Knuckles, Summary::METEOR_HERD),
	SeqStage(Characters_Knuckles, LevelIDs_KnucklesVsRouge, Characters_Knuckles, Summary::ROUGE_FIGHT),
	SeqEvent(Event::EGGMAN_OUTPLAYS_HEROES_DARK, Characters_Knuckles, Summary::ROUGE_FIGHT),
	SeqStage(Characters_MechEggman, LevelIDs_TailsVsEggman2, Characters_MechEggman, Summary::TAILS_2),
	SeqEvent(Event::SONIC_SURVIVES_AFTER_CHAOS_CONTROL, Characters_MechEggman, Summary::TAILS_2),
	SeqStage(Characters_Knuckles, LevelIDs_MadSpace, Characters_Knuckles, Summary::METEOR_HERD),
	SeqEvent(Event::SHADOW_VS_SONIC_2_HERO, Characters_Knuckles, Summary::METEOR_HERD),
	SeqStage(Characters_Sonic, LevelIDs_SonicVsShadow2, Characters_Sonic, Summary::SHADOW_2),
	SeqEvent(Event::DARK_TEAM_VICTORY, Characters_Shadow, Summary::SONIC_2),
	SeqCredits,
	SeqEvent(Event::HERO_STORY_TRAILER, Characters_Shadow, Summary::SONIC_2),
	SeqTitle
};

unsigned short ReplaceStages::FallenHeroStoryLength = (sizeof(ReplaceStages::FallenHeroStory) / sizeof(SeqAndSummarySection));
unsigned short ReplaceStages::FallenHeroStoryLengthNoCredits = ReplaceStages::FallenHeroStoryLength - 3;

unsigned short ReplaceStages::FallenDarkStoryLength = (sizeof(ReplaceStages::FallenHeroStory) / sizeof(SeqAndSummarySection));
unsigned short ReplaceStages::FallenDarkStoryLengthNoCredits = ReplaceStages::FallenHeroStoryLength - 3;

void ReplaceStages::init() {
	hLoadStoryEntry.Hook(LoadSequence);
	hLoadCharTextures.Hook(LoadCharTextures_h);
	hSummaryBgLoad.Hook(SummaryBgLoad);
	hProcessWinTime.Hook(ProcessWinTime);
	PrintDebug("test");
	ReplaceStages::initEventData();
	ReplaceStages::initStorySequence();
	ReplaceStages::replaceStoryStrings();

	WritePointer((void*)0x4586C5, ReplaceStages::FallenHeroSequence);
	WritePointer((void*)0x4586E6, ReplaceStages::FallenDarkSequence);
}

void ReplaceStages::initEventData() {
	// InternalID = (EventID * 1000) + VoiceID
	EventVoiceData[441].InternalID = 133010;
	EventVoiceData[442].InternalID = 133020;
	EventVoiceData[443].InternalID = 134030;
}

void ReplaceStages::initStorySequence() {
	int story_length = sizeof(ReplaceStages::FallenHeroStory) / sizeof(SeqAndSummarySection);
	ReplaceStages::FallenHeroSequence = new SeqSection[story_length];
	for (int i = 0; i < story_length; i++) {
		ReplaceStages::FallenHeroSequence[i] = {
			ReplaceStages::FallenHeroStory[i].type,
			ReplaceStages::FallenHeroStory[i].player_num,
			ReplaceStages::FallenHeroStory[i].stage_num,
			{
				ReplaceStages::FallenHeroStory[i].event_num[0],
				ReplaceStages::FallenHeroStory[i].event_num[1],
				ReplaceStages::FallenHeroStory[i].event_num[2],
				ReplaceStages::FallenHeroStory[i].event_num[3]
			}
		};
	}

	story_length = sizeof(ReplaceStages::FallenDarkStory) / sizeof(SeqAndSummarySection);
	ReplaceStages::FallenDarkSequence = new SeqSection[story_length];
	for (int i = 0; i < story_length; i++) {
		ReplaceStages::FallenDarkSequence[i] = {
			ReplaceStages::FallenDarkStory[i].type,
			ReplaceStages::FallenDarkStory[i].player_num,
			ReplaceStages::FallenDarkStory[i].stage_num,
			{
				ReplaceStages::FallenDarkStory[i].event_num[0],
				ReplaceStages::FallenDarkStory[i].event_num[1],
				ReplaceStages::FallenDarkStory[i].event_num[2],
				ReplaceStages::FallenDarkStory[i].event_num[3]
			}
		};
	}
}

void ReplaceStages::replaceStoryStrings() {
	WritePointer((void*)0xC50F48, ReplaceStages::FallenHeroStoryScenesSelect);
	WritePointer((void*)0xC50F4C, ReplaceStages::FallenHeroStoryBossAttack);
	WritePointer((void*)0xC50F50, ReplaceStages::RisenDarkStoryScenesSelect);
	WritePointer((void*)0xC50F54, ReplaceStages::RisenDarkStoryBossAttack);
}

void __fastcall LoadSequence(int a1, SeqSection* story) {
	if (CurrentSequenceNo == 1 && story->type == SEQ_TYPE_EVENT && story->event_num[0] == Event::FREE_SHADOW) {
		DEBUG_MESSAGE = "Fallen Hero Story: v";
		DEBUG_MESSAGE += CCM_VERSION;
		DEBUG_MESSAGE_TIMER = DEFAULT_MESSAGE_TIME;
	} else if (CurrentSequenceNo == 2 && story->type == SEQ_TYPE_EVENT && story->event_num[0] == Event::MASTER_EMERALD_BREAK_HERO) {
		DEBUG_MESSAGE = "Risen Dark Story: v";
		DEBUG_MESSAGE += CCM_VERSION;
		DEBUG_MESSAGE_TIMER = DEFAULT_MESSAGE_TIME;
	} else if (CurrentSequenceNo == 3 && story->type == SEQ_TYPE_EVENT && story->event_num[0] == Event::ECLIPSE_CANON_DESTRUCTION_SEQUENCE) {
		DEBUG_MESSAGE = "Last Story: v";
		DEBUG_MESSAGE += CCM_VERSION;
		DEBUG_MESSAGE_TIMER = DEFAULT_MESSAGE_TIME;
	}

	if (story && story->type == SEQ_TYPE_EVENT) {
		// InternalID = (EventID * 1000) + VoiceID
		switch (story->event_num[0]) {
			case 118:
				EventVoiceData[441].InternalID = 118010;
				EventVoiceData[442].InternalID = 118020;
				EventVoiceData[443].InternalID = 118030;
				break;
			case 133:
			case 134:
				EventVoiceData[441].InternalID = 133010;
				EventVoiceData[442].InternalID = 133020;
				EventVoiceData[443].InternalID = 134030;
				break;
		}
	}

	hLoadStoryEntry.Original(a1, story);
}

void* SummaryBgLoad() {
	if (CurrentSequenceNo != 1 && CurrentSequenceNo != 2) {
		return hSummaryBgLoad.Original();
	}
	
	SummaryBgCharacterID = CurrentSequenceNo == 1 ? Characters_Shadow : Characters_Sonic;
	SummarySceneID = CurrentSequenceNo == 1 ? Summary::SONIC_2 : Summary::SONIC_2;
	int seq_index = (int)StorySequenceIndex;
	int seq_length = (CurrentSequenceNo == 1 ? ReplaceStages::FallenHeroStoryLengthNoCredits : ReplaceStages::FallenDarkStoryLengthNoCredits);
	if (seq_index >= 0 && seq_index <= seq_length) {
		if (CurrentSequenceNo == 1) {
			SummaryBgCharacterID = ReplaceStages::FallenHeroStory[seq_index].summary_char;
			SummarySceneID = ReplaceStages::FallenHeroStory[seq_index].summary_scene;
		} else {
			SummaryBgCharacterID = ReplaceStages::FallenDarkStory[seq_index].summary_char;
			SummarySceneID = ReplaceStages::FallenDarkStory[seq_index].summary_scene;
		}
	}

	return hSummaryBgLoad.Original();
}

void MemCopyProtected(void* pDst, const void* pSrc, size_t nb) {
	DWORD old_prot;
	VirtualProtect(pDst, nb, PAGE_EXECUTE_READWRITE, &old_prot);
	memcpy(pDst, pSrc, nb);
}

void ProcessWinTime() {
	if (CurrentLevel == LevelIDs_PrisonLane && !TailsBoosterGot) {
		TailsBoosterGot = true;
		MissionStreet_LevelData[0] = 1;
	} else if (CurrentLevel == LevelIDs_DryLagoon && CurrentSequenceNo == 2) {
		IronGate_LevelData[0] = 1;
	} else if (CurrentLevel == LevelIDs_WildCanyon && CurrentSequenceNo == 2 && !KnucklesShovelClawGot) {
		KnucklesShovelClawGot = true;
		SandOcean_LevelData[0] = 1;
		EggQuarters_LevelData[0] = 1;
	} else if (CurrentLevel == LevelIDs_TailsVsEggman1 && CurrentSequenceNo == 2 && !EggmanJetEngineGot) {
		EggmanJetEngineGot = true;
	} else if (CurrentLevel == LevelIDs_TailsVsEggman2 && CurrentSequenceNo == 1 && Route101_LevelData[0] == 0) {
		Route101_LevelData[0] = 1;
	} else if (CurrentLevel == LevelIDs_TailsVsEggman2 && CurrentSequenceNo == 2 && Route280_LevelData[0] == 0) {
		Route280_LevelData[0] = 1;
		CosmicWall_LevelData[0] = 1;
	}

	hProcessWinTime.Original();
}

NJS_TEXLIST* __fastcall LoadCharTextures_h(const char* filename) {
	if (CurrentSequenceNo != 2) {
		return hLoadCharTextures.Original(filename);
	}

	if (strcmp("stg_title10", filename) == 0) {
		return hLoadCharTextures.Original("custom_stage_titles/stg_title_mha_sonic");
	} else if (strcmp("stg_title16", filename) == 0) {
		return hLoadCharTextures.Original("custom_stage_titles/stg_title_wc_knuckles");
	} else if (strcmp("stg_title05", filename) == 0) {
		return hLoadCharTextures.Original("custom_stage_titles/stg_title_ph_knuckles");
	} else if (strcmp("stg_title07", filename) == 0) {
		return hLoadCharTextures.Original("custom_stage_titles/stg_title_am_knuckles");
	} else if (strcmp("stg_title25", filename) == 0) {
		return hLoadCharTextures.Original("custom_stage_titles/stg_title_dc_knuckles");
	} else if (strcmp("stg_title32", filename) == 0) {
		return hLoadCharTextures.Original("custom_stage_titles/stg_title_mhe_knuckles");
	} else if (strcmp("stg_title18", filename) == 0) {
		return hLoadCharTextures.Original("custom_stage_titles/stg_title_dl_knuckles");
	} else if (strcmp("stg_title08", filename) == 0) {
		return hLoadCharTextures.Original("custom_stage_titles/stg_title_sh_knuckles");
	} else if (strcmp("stg_title44", filename) == 0) {
		return hLoadCharTextures.Original("custom_stage_titles/stg_title_msp_knuckles");
	}

	return hLoadCharTextures.Original(filename);
}