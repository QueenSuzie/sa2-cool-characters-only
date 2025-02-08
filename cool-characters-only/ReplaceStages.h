/**************************************************************************************
 *   ReplaceStages.h  --  This file is part of Cool Characters Only.                  *
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

void MemCopyProtected(void*, const void*, size_t);

#define WriteMemory(waddr, daddr, size) MemCopyProtected((void*)(waddr), (void*)(daddr), (size_t)(size))

#define WritePData(addr, data, type) { type _v_ = (type)(data); WriteMemory((addr), &_v_, sizeof(type)); }
#define WritePointer(addr, ptr) WritePData((addr), (ptr), void*)

DataArray(char, MissionStreet_LevelData, 0x1DED33C, 196);
DataArray(char, IronGate_LevelData, 0x1DECEA4, 196);
DataArray(char, SandOcean_LevelData, 0x1DED64C, 196);
DataArray(char, EggQuarters_LevelData, 0x1DEDA20, 196);
DataArray(char, CosmicWall_LevelData, 0x1DEE724, 196);
DataArray(char, Route101_LevelData, 0x1DEF428, 196);
DataArray(char, Route280_LevelData, 0x1DEF4EC, 196);
DataArray(CutsceneVoices, EventVoiceData, 0x1716720, 720);

class ReplaceStages {
	public:
		static void init();
		static inline SeqSection* FallenHeroSequence = NULL;
		static inline SeqSection* FallenDarkSequence = NULL;
		static SeqAndSummarySection FallenHeroStory[];
		static SeqAndSummarySection FallenDarkStory[];
		static unsigned short FallenHeroStoryLength;
		static unsigned short FallenHeroStoryLengthNoCredits;
		static unsigned short FallenDarkStoryLength;
		static unsigned short FallenDarkStoryLengthNoCredits;
		static inline const char FallenHeroStoryScenesSelect[] = "\tYou can now select scenes\nfrom the Fallen Hero story.";
		static inline const char FallenHeroStoryBossAttack[] = "\tNow select time attack\nboss stages in the Fallen Hero story.";
		static inline const char RisenDarkStoryScenesSelect[] = "\tYou can now select scenes\nfrom the Risen Dark story.";
		static inline const char RisenDarkStoryBossAttack[] = "\tNow select time attack\nboss stages in the Risen Dark story.";

	private:
		static void initEventData();
		static void initStorySequence();
		static void replaceStoryStrings();
};

void __fastcall LoadSequence(int a1, SeqSection* story);
void* SummaryBgLoad();
void ProcessWinTime();
NJS_TEXLIST* __fastcall LoadCharTextures_h(const char *filename);