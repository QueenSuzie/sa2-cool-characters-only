/**************************************************************************************
 *   SequenceData.h  --  This file is part of Cool Characters Only.                   *
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

#pragma once

DataPointer(byte, StorySequenceIndex, 0x1DEB31E);
DataPointer(uint8_t, CurrentSequenceNo, 0x1DEB320);
DataPointer(DWORD, SummaryBgCharacterID, 0x1D1C1B0);
DataPointer(DWORD, SummarySceneID, 0x1D1C1B4);

typedef struct {
    uint8_t type;
    uint8_t player_num;
    uint8_t stage_num;
    int16_t event_num[4];
} SeqSection;

typedef struct {
    uint8_t type;
    uint8_t player_num;
    uint8_t stage_num;
    int16_t event_num[4];
    DWORD summary_char;
    DWORD summary_scene;
} SeqAndSummarySection;

enum {
    SEQ_TYPE_EVENT,
    SEQ_TYPE_STAGE,
    SEQ_TYPE_TITLE,
    SEQ_TYPE_ENDING,
};

enum Event {
    NO_EVENT = -1,
    TAILS_FINDS_AMY = 4,
    TAILS_RESCUED_AMY = 5,
    AMY_BREAKS_OUT_SONIC = 6,
    LIMO_SCENE_HERO = 15,
    DESERT_AREA_ARRIVAL_HERO = 16,
    DEATH_CHAMBER_ENTRANCE = 17,
    EGG_GOLEM_ENTRANCE_HERO = 19,
    TEAM_HERO_ARRIVES_AT_ARK = 21,
    AMY_GETS_CAUGHT_HERO = 22,
    EGGMAN_OUTPLAYS_HEROES = 25,
    SONIC_SURVIVES_AFTER_CHAOS_CONTROL = 26,
    HERO_TEAM_VICTORY = 28,
    TIMER_FOR_PUMPKIN_HILL = 50,
    TIMER_FOR_RADICAL_HIGHWAY = 51,
    TIMER_FOR_AQUATIC_MINE = 52,
    TIMER_FOR_CRAZY_GADGET = 54,
    FREE_SHADOW = 101,
    MASTER_EMERALD_BREAK_DARK = 103,
    SHADOW_REVENGE_MEMORY = 106,
    BIG_FOOT_SHADOW_SONIC_DARK = 107,
    ROUGE_REPORTS_PROBLEM = 116,
    SHADOW_RESCUES_ROUGE = 118,
    ROUGE_HEADS_FOR_SPACE_EMERALDS = 124,
    KNUCKLES_RESCUES_ROUGE_DARK = 126,
    SHADOW_CONFRONTS_ROUGE = 129,
    SHADOW_VS_SONIC_2_DARK = 130,
    PRISON_ISLAND_BLOWS_UP = 409,
    SHUTTLE_LAUNCH_HERO = 420,
    DARK_STORY_TRAILER = 429,
};

enum Summary {
    EGGMAN_1 = 3,
    PRISON_LANE = 4,
    HIDDEN_BASE = 12,
    ETERNAL_ENGINE = 17,
    EGGMAN_2 = 21,
    HOT_SHOT = 25,
    DRY_LAGOON = 26,
    RADICAL_HIGHWAY = 28,
    EGG_QUARTERS = 29,
    WHITE_JUNGLE = 35,
    SONIC_1 = 36,
    SKY_RAIL = 38,
    MAD_SPACE = 40,
    KNUCKLES_FIGHT = 41,
    FINAL_CHASE = 44,
    SONIC_2 = 45
};

#define FUNC_CHOOSER(_f0, _f1, _f2, _f3, _f4, _f5, _f6, _f7, _f8, _f9, _f10, _f11, _f12, _f13, _f14, _f15, _f16, ...) _f16
#define FUNC_RECOMPOSER(argsWithParentheses) FUNC_CHOOSER argsWithParentheses
#define CHOOSE_FROM_ARG_COUNT(F, ...) FUNC_RECOMPOSER((__VA_ARGS__, \
            F##_16, F##_15, F##_14, F##_13, F##_12, F##_11, F##_10, F##_9, F##_8,\
            F##_7, F##_6, F##_5, F##_4, F##_3, F##_2, F##_1, ))
#define NO_ARG_EXPANDER(FUNC) ,,,,,,,,,,,,,,,,FUNC ## _0
#define MACRO_CHOOSER(FUNC, ...) CHOOSE_FROM_ARG_COUNT(FUNC, NO_ARG_EXPANDER __VA_ARGS__ (FUNC))
#define MULTI_MACRO(FUNC, ...) MACRO_CHOOSER(FUNC, __VA_ARGS__)(__VA_ARGS__)

#define SeqEvent(...) MULTI_MACRO(SEQEVENT, __VA_ARGS__)
#define SEQEVENT_2(SummaryCharID, SummaryBgSceneID) SEQEVENT_3(Event::NO_EVENT, SummaryCharID, SummaryBgSceneID)
#define SEQEVENT_3(EventOne, SummaryCharID, SummaryBgSceneID) SEQEVENT_4(EventOne, Event::NO_EVENT, SummaryCharID, SummaryBgSceneID)
#define SEQEVENT_4(EventOne, EventTwo, SummaryCharID, SummaryBgSceneID) \
			SEQEVENT_5(EventOne, EventTwo, Event::NO_EVENT, SummaryCharID, SummaryBgSceneID)
#define SEQEVENT_5(EventOne, EventTwo, EventThree, SummaryCharID, SummaryBgSceneID) \
			SEQEVENT_6(EventOne, EventTwo, EventThree, Event::NO_EVENT, SummaryCharID, SummaryBgSceneID)
#define SEQEVENT_6(EventOne, EventTwo, EventThree, EventFour, SummaryCharID, SummaryBgSceneID) \
			{ SEQ_TYPE_EVENT, Characters_Sonic, LevelIDs_BasicTest, { EventOne, EventTwo, EventThree, EventFour }, SummaryCharID, SummaryBgSceneID }

#define SeqStage(CharacterID, StageID, SummaryCharID, SummaryBgSceneID) { SEQ_TYPE_STAGE, CharacterID, StageID, { -1, -1, -1, -1 }, SummaryCharID, SummaryBgSceneID }
#define SeqCredits { SEQ_TYPE_ENDING, Characters_Sonic, LevelIDs_BasicTest, { -1, -1, -1, -1 }, 0, 0 }
#define SeqTitle { SEQ_TYPE_TITLE }