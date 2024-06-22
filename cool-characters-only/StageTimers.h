/**************************************************************************************
 *   StageTimers.h  --  This file is part of Cool Characters Only.                    *
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

struct Mission4Time {
	uint8_t LevelID;
	uint8_t Minutes;
	uint8_t Seconds;
};

DataArray(Mission4Time, Mission4Times, 0x173B318, 31);

class StageTimers {
	public:
		static void init();
		static void setGreentForestTimer();
		static void setWhiteJungleTimer();
		static inline uint8_t GreenForestMinutes = 2;
		static inline uint8_t GreenForestSeconds = 10;
		static inline uint8_t GreenForestHardMinutes = 2;
		static inline uint8_t GreenForestHardSeconds = 20;
		static inline uint8_t WhiteJungleMinutes = 2;
		static inline uint8_t WhiteJungleSeconds = 30;
		static inline uint8_t WhiteJungleHardMinutes = 3;
		static inline uint8_t WhiteJungleHardSeconds = 0;
		static inline void* JumpToSetTimer = (void*)0x4520AC;
		static inline void* JumpToAbortTimer = (void*)0x4520C0;

	private:
		static void initGreenForestTimer();
		static void initMission4Timers();
};

