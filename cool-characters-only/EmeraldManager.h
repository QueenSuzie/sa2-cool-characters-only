#pragma once

#include "wincrypt.h"
#include <functional>
#include <random>
#include <unordered_map>

struct Emerald {
	int id;
	NJS_VECTOR v;
};

struct SA2EmeraldManager {
	uint8_t Action;
	uint8_t byte1;
	uint8_t byte2;
	uint8_t HintCount;
	uint8_t Status;
	uint8_t EmeraldsSpawned;
	uint8_t Slot1ArrayLen;
	uint8_t Slot2ArrayLen;
	uint8_t Slot3ArrayLen;
	uint8_t EnemySlotArrayLen;
	uint8_t byteA;
	uint8_t byteB;
	Emerald duplicate_emerald_1;
	Emerald duplicate_emerald_2;
	Emerald Piece1;
	Emerald Piece2;
	Emerald Piece3;
	Emerald* Slot1Emeralds;
	Emerald* Slot2Emeralds;
	Emerald* Slot3Emeralds;
	Emerald* EnemySlotEmeralds;
	uint32_t timer;
	NJS_TEXLIST* TexList;
};

struct Set {
	int p1Id;
	int p2Id;
	int p3Id;
};

class EmeraldManager {
	public:
		static void Init();
		static void LoadEmeraldLocations(SA2EmeraldManager* emManager);
		static void Destroy();

	private:
		static bool AcquireContext(HCRYPTPROV* ctx);
		static Emerald* GetPieceById(SA2EmeraldManager* emManager, int id);
		static void SetSeed();

		static inline bool GOD_SET_ENABLED = false;
		static inline const int PIECE_COLLECTED = 254;
		static inline const int GOD_SET_CHANCE = 2048; // odds of getting are 1 in GOD_SET_CHANCE
		static inline std::mt19937* RandomGenerator = nullptr;
		static inline std::bernoulli_distribution Distribution = std::bernoulli_distribution(1.0f / ((double)EmeraldManager::GOD_SET_CHANCE));
		static inline std::unordered_map<LevelIDs, Set> GodSets = {
			{ LevelIDs_WildCanyon, { 0x0603, 0x0305, 0x0605 } },
			{ LevelIDs_PumpkinHill, { 0x0C01, 0x010A, 0x0704 } },
			{ LevelIDs_AquaticMine, { 0x0008, 0x0108, 0x0208 } },
			{ LevelIDs_DeathChamber, { 0x0405, 0x0100, 0x0107 } },
			{ LevelIDs_MeteorHerd, { 0x0701, 0x000A, 0x0801 } },
			{ LevelIDs_DryLagoon, { 0x0605, 0x0603 , 0x0704 } },
			{ LevelIDs_EggQuarters, { 0x0801, 0x0401, 0x0208  } },
			{ LevelIDs_SecurityHall, { 0x010A, 0x000A, 0x0608 } },
			{ LevelIDs_MadSpace, { 0x1601, 0x0C05, 0x1501 } },
		};
};

