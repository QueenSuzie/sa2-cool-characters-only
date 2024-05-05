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

DataPointer(byte, CurrentStoryLevelCount, 0x1DEB31E);
DataPointer(WORD, AllStoriesLevelCount, 0x1DEB31F);
DataPointer(DWORD, SummaryBgCharacterID, 0x1D1C1B0);
DataPointer(DWORD, SummarySceneID, 0x1D1C1B4);

class ReplaceStages {
	public:
		static inline short LAST_LEVEL = 0;
		static inline bool FINAL_CHASE_COMPLETE = false;
		static inline bool WHITE_JUNGLE_COMPLETE = false;
		static void init();
};

void StageLoadUnloadHook();
signed int GameModeHandler_h();
void* SummaryBgLoad();