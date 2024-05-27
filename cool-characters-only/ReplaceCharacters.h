/**************************************************************************************
 *   ReplaceCharacters.h  --  This file is part of Cool Characters Only.              *
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

#pragma once

FunctionPointer(BYTE*, UpgradeDataGet, (ObjectMaster* a1), 0x486520);

class ReplaceCharacters {
	public:
		static void init();
		static void setStageUpgrades();
		static char remapUpgradeMsg(int);

	private:
		static void initCharacterVoices();
		static void setSonicUpgrades();
		static void setKnucklesUpgrades();
		static void remapUpgradeData();
};

void LoadSonic_h(int);
void LoadKnuckles_h(int);
void SetStageUpgrades();
int UpgradeHook(int);
void InputColi_h(ObjectMaster*);
BYTE* UpgradeDataGet_h(ObjectMaster*);