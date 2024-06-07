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
DataArray(char, Route101_LevelData, 0x1DEF428, 196);

class ReplaceStages {
	public:
		static void init();
		static inline SeqSection* FallenHeroSequence = NULL;
		static SeqAndSummarySection FallenHeroStory[];
		static unsigned short FallenHeroStoryLength;
		static unsigned short FallenHeroStoryLengthNoCredits;
		static inline const char FallenHeroStoryScenesSelect[] = "\tYou can now select scenes\nfrom the Fallen Hero story.";
		static inline const char FallenHeroStoryBossAttack[] = "\tNow select time attack\nboss stages in the Fallen Hero story.";

	private:
		static void initStorySequence();
		static void replaceStoryStrings();
};

void* SummaryBgLoad();
void ProcessWinTime();