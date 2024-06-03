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

class ReplaceStages {
	public:
		static void init();
		static void initStorySequence();
		static inline SeqSection* FallenHeroSequence = NULL;
        static SeqAndSummarySection FallenHeroStory[];
};

void StageLoadUnloadHook();
void* SummaryBgLoad();