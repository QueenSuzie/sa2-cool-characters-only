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

#ifdef CASUAL_MODE
		// Casual Times
		static inline int32_t TempStorage = 0;
		static inline uint8_t GreenForestMinutes = 2;
		static inline uint8_t GreenForestSeconds = 5;
		static inline uint8_t GreenForestM4Minutes = 1;
		static inline uint8_t GreenForestM4Seconds = 55;
		static inline uint8_t GreenForestHardMinutes = 2;
		static inline uint8_t GreenForestHardSeconds = 0;
		static inline uint8_t WhiteJungleMinutes = 2;
		static inline uint8_t WhiteJungleSeconds = 5;
		static inline uint8_t WhiteJungleM4Minutes = 1;
		static inline uint8_t WhiteJungleM4Seconds = 55;
		static inline uint8_t WhiteJungleHardMinutes = 2;
		static inline uint8_t WhiteJungleHardSeconds = 0;
#else
		// Speedrun Times
		static inline uint8_t GreenForestMinutes = 1;
		static inline uint8_t GreenForestSeconds = 45;
		static inline uint8_t GreenForestM4Minutes = 1;
		static inline uint8_t GreenForestM4Seconds = 25;
		static inline uint8_t GreenForestHardMinutes = 1;
		static inline uint8_t GreenForestHardSeconds = 40;
		static inline uint8_t WhiteJungleMinutes = 1;
		static inline uint8_t WhiteJungleSeconds = 50;
		static inline uint8_t WhiteJungleM4Minutes = 1;
		static inline uint8_t WhiteJungleM4Seconds = 32;
		static inline uint8_t WhiteJungleHardMinutes = 1;
		static inline uint8_t WhiteJungleHardSeconds = 45;
#endif

		static inline void* JumpToSetTimer = (void*)0x4520AC;
		static inline void* JumpToAbortTimer = (void*)0x4520C0;

	private:
		static void initJungleTimer();
		static void initMission4Timers();
};

