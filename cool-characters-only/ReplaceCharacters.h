/**************************************************************************************
 *   ReplaceCharacters.h  --  This file is part of Cool Characters Only.              *
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

#pragma once

#include <vector>
#include <algorithm>

class ReplaceCharacters {
	public:
		void init();
		void setStageUpgrades();
		void restoreLevelUpgrades();

	private:
		void initCharacterVoices();
		void initSonicStages();
		void initKnucklesStages();
		void setSonicUpgrades();
		void setKnucklesUpgrades();
		std::vector<short> sonicStages;
		std::vector<short> knucklesStages;
		int originalUpgrades1 = -1;
		int originalUpgrades2 = -1;
};

void LoadSonic_h(int);
void LoadKnuckles_h(int);
void StageLoadHook();
int UpgradeHook(int);
void StageCompletedHook(char);
void StageLoadUnloadHook();