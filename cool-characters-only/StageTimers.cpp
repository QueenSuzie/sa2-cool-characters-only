/**************************************************************************************
 *   StageTimers.cpp  --  This file is part of Cool Characters Only.                  *
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
#include "StageTimers.h"

void StageTimers::init() {
	StageTimers::initGreenForestTimer();
	StageTimers::initMission4Timers();
}

void StageTimers::initGreenForestTimer() {
	WriteJump((void*)0x452073, &StageTimers::setGreentForestTimer);
	WriteJump((void*)0x45208B, &StageTimers::setWhiteJungleTimer);

	for (unsigned short i = 0; i < 6; i++) {
		WriteData<char>((char*)(0x452078 + i), 0x90u);
		WriteData<char>((char*)(0x452090 + i), 0x90u);
	}
}

void StageTimers::initMission4Timers() {
	for (unsigned short i = 0; i < Mission4Times.size(); i++) {
		switch (Mission4Times[i].LevelID) {
			case LevelIDs_GreenForest:
				Mission4Times[i].Minutes = 1;
				Mission4Times[i].Seconds = 50;
				break;
			case LevelIDs_WhiteJungle:
				Mission4Times[i].Minutes = 2;
				Mission4Times[i].Seconds = 15;
				break;
		}
	}
}

__declspec(naked) void StageTimers::setGreentForestTimer() {
	__asm {
		cmp     al, 0
		je		SET_TIMER
		cmp		al, 4
		je		SET_HARD_TIMER
		jmp		StageTimers::JumpToAbortTimer

SET_TIMER:
		mov		cl, StageTimers::GreenForestMinutes
		mov		byte ptr[esp + 4], cl
		mov		cl, StageTimers::GreenForestSeconds
		jmp		RETURN

SET_HARD_TIMER:
		mov		cl, StageTimers::GreenForestHardMinutes
		mov		byte ptr[esp + 4], cl
		mov		cl, StageTimers::GreenForestHardSeconds

RETURN:
		jmp		StageTimers::JumpToSetTimer
	}
}

__declspec(naked) void StageTimers::setWhiteJungleTimer() {
	__asm {
		cmp     al, 0
		je		SET_TIMER
		cmp		al, 4
		je		SET_HARD_TIMER
		jmp		StageTimers::JumpToAbortTimer

SET_TIMER:
		mov		cl, StageTimers::WhiteJungleMinutes
		mov		byte ptr[esp + 4], cl
		mov		cl, StageTimers::WhiteJungleSeconds
		jmp		RETURN

SET_HARD_TIMER:
		mov		cl, StageTimers::WhiteJungleHardMinutes
		mov		byte ptr[esp + 4], cl
		mov		cl, StageTimers::WhiteJungleHardSeconds

RETURN:
		jmp		StageTimers::JumpToSetTimer
	}
}