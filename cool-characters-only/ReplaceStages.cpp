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
FunctionHook<void*> hSummaryBgLoad((intptr_t)0x678BB0);
FunctionHook<void> hProcessWinTime((intptr_t)0x452A00);

SeqAndSummarySection ReplaceStages::FallenHeroStory[] = {
	SeqEvent(Event::FREE_SHADOW, 0, 0),
	SeqStage(Characters_Sonic, LevelIDs_CityEscape, Characters_Shadow, Summary::HOT_SHOT),
	SeqStage(Characters_Sonic, LevelIDs_BigFoot, Characters_Shadow, Summary::HOT_SHOT),
	SeqEvent(Event::BIG_FOOT_SHADOW_SONIC_DARK, Event::MASTER_EMERALD_BREAK_DARK, Characters_Shadow, Summary::HOT_SHOT),
	SeqStage(Characters_Knuckles, LevelIDs_WildCanyon, Characters_Rouge, Summary::DRY_LAGOON),
	SeqEvent(Event::TAILS_FINDS_AMY, Characters_Rouge, Summary::DRY_LAGOON),
	SeqStage(Characters_MechTails, LevelIDs_TailsVsEggman1, Characters_MechTails, Summary::EGGMAN_1),
	SeqEvent(Event::TAILS_RESCUED_AMY, Characters_MechTails, Summary::EGGMAN_1),
	SeqStage(Characters_MechTails, LevelIDs_PrisonLane, Characters_MechTails, Summary::PRISON_LANE),
	SeqEvent(Event::AMY_BREAKS_OUT_SONIC, Characters_MechTails, Summary::PRISON_LANE),
	SeqStage(Characters_Sonic, LevelIDs_MetalHarbor, Characters_Shadow, Summary::WHITE_JUNGLE),
	SeqEvent(Event::ROUGE_REPORTS_PROBLEM, Characters_Shadow, Summary::WHITE_JUNGLE),
	SeqStage(Characters_Shadow, LevelIDs_WhiteJungle, Characters_Shadow, Summary::WHITE_JUNGLE),
	SeqStage(Characters_Sonic, LevelIDs_SonicVsShadow1, Characters_Shadow, Summary::SONIC_1),
	SeqEvent(Event::SHADOW_RESCUES_ROUGE_PT1, Characters_Shadow, Summary::SONIC_1),
	SeqStage(Characters_Sonic, LevelIDs_GreenForest, Characters_Shadow, Summary::SONIC_1),
	SeqEvent(Event::SHADOW_RESCUES_ROUGE_PT2, Event::PRISON_ISLAND_BLOWS_UP, Event::TIMER_FOR_PUMPKIN_HILL, Characters_Shadow, Summary::SONIC_1),
	SeqStage(Characters_Knuckles, LevelIDs_PumpkinHill, Characters_Rouge, Summary::DRY_LAGOON),
	SeqEvent(Event::TIMER_FOR_RADICAL_HIGHWAY, Event::SHADOW_REVENGE_MEMORY, Characters_Rouge, Summary::DRY_LAGOON),
	SeqStage(Characters_Shadow, LevelIDs_RadicalHighway, Characters_Shadow, Summary::RADICAL_HIGHWAY),
	SeqEvent(Event::TIMER_FOR_AQUATIC_MINE, Characters_Shadow, Summary::RADICAL_HIGHWAY),
	SeqStage(Characters_Knuckles, LevelIDs_AquaticMine, Characters_Rouge, Summary::DRY_LAGOON),
	SeqStage(Characters_Shadow, LevelIDs_SkyRail, Characters_Shadow, Summary::SKY_RAIL),
	SeqEvent(Event::LIMO_SCENE_HERO, Event::DESERT_AREA_ARRIVAL_HERO, Characters_Shadow, Summary::SKY_RAIL),
	SeqStage(Characters_MechTails, LevelIDs_HiddenBase, Characters_MechTails, Summary::HIDDEN_BASE),
	SeqStage(Characters_Sonic, LevelIDs_PyramidCave, Characters_Shadow, Summary::SKY_RAIL),
	SeqStage(Characters_Knuckles, LevelIDs_DeathChamber, Characters_Rouge, Summary::EGG_QUARTERS),
	SeqStage(Characters_Knuckles, LevelIDs_KingBoomBoo, Characters_Rouge, Summary::EGG_QUARTERS),
	SeqEvent(Event::EGG_GOLEM_ENTRANCE_HERO, Characters_Rouge, Summary::EGG_QUARTERS),
	SeqStage(Characters_Sonic, LevelIDs_EggGolemS, Characters_Shadow, Summary::SKY_RAIL),
	SeqEvent(Event::SHUTTLE_LAUNCH_HERO, Event::TEAM_HERO_ARRIVES_AT_ARK, Characters_Shadow, Summary::SKY_RAIL),
	SeqStage(Characters_MechTails, LevelIDs_EternalEngine, Characters_MechTails, Summary::ETERNAL_ENGINE),
	SeqEvent(Event::ROUGE_HEADS_FOR_SPACE_EMERALDS, Event::AMY_GETS_CAUGHT_HERO, Characters_MechTails, Summary::ETERNAL_ENGINE),
	SeqStage(Characters_Knuckles, LevelIDs_MeteorHerd, Characters_Rouge, Summary::MAD_SPACE),
	SeqStage(Characters_Knuckles, LevelIDs_KnucklesVsRouge, Characters_Rouge, Summary::KNUCKLES_FIGHT),
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

unsigned short ReplaceStages::FallenHeroStoryLength = (sizeof(ReplaceStages::FallenHeroStory) / sizeof(SeqAndSummarySection));
unsigned short ReplaceStages::FallenHeroStoryLengthNoCredits = ReplaceStages::FallenHeroStoryLength - 3;

void ReplaceStages::init() {
	hLoadStoryEntry.Hook(LoadSequence);
	hSummaryBgLoad.Hook(SummaryBgLoad);
	hProcessWinTime.Hook(ProcessWinTime);

	ReplaceStages::initEventData();
	ReplaceStages::initStorySequence();
	ReplaceStages::replaceStoryStrings();

	WritePointer((void*)0x4586C5, ReplaceStages::FallenHeroSequence);
}

void ReplaceStages::initEventData() {
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
}

void ReplaceStages::replaceStoryStrings() {
	WritePointer((void*)0xC50F48, ReplaceStages::FallenHeroStoryScenesSelect);
	WritePointer((void*)0xC50F4C, ReplaceStages::FallenHeroStoryBossAttack);
}

void __fastcall LoadSequence(int a1, SeqSection* story) {
	if (story && story->type == SEQ_TYPE_EVENT) {
		// InternalID = (EventID * 1000) + VoiceID
		switch (story->event_num[0]) {
			case 118:
				EventVoiceData[441].InternalID = 118010;
				EventVoiceData[442].InternalID = 118020;
				EventVoiceData[443].InternalID = 118030;
				break;
			case 133:
				EventVoiceData[441].InternalID = 133010;
				EventVoiceData[442].InternalID = 133020;
				EventVoiceData[443].InternalID = 134030;
				break;
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
	if (CurrentSequenceNo != 1) {
		return hSummaryBgLoad.Original();
	}
	
	SummaryBgCharacterID = Characters_Shadow;
	SummarySceneID = Summary::SONIC_2;
	int seq_index = (int)StorySequenceIndex;
	if (seq_index >= 0 && seq_index <= ReplaceStages::FallenHeroStoryLengthNoCredits) {
		SummaryBgCharacterID = ReplaceStages::FallenHeroStory[seq_index].summary_char;
		SummarySceneID = ReplaceStages::FallenHeroStory[seq_index].summary_scene;
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
	} else if (CurrentLevel == LevelIDs_TailsVsEggman2 && CurrentSequenceNo == 1 && Route101_LevelData[0] == 0) {
		Route101_LevelData[0] = 1;
	}

	hProcessWinTime.Original();
}