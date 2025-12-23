#include "pch.h"
#include "EmeraldManager.h"

FunctionHook<void, SA2EmeraldManager*> hLoadEmeraldLocations((intptr_t)EmeraldLocations_1POr2PGroup3);

void EmeraldManager::Init() {
	hLoadEmeraldLocations.Hook(LoadEmeraldLocations);

	EmeraldManager::SetSeed();
}

bool EmeraldManager::AcquireContext(HCRYPTPROV* ctx) {
	if (!CryptAcquireContext(ctx, nullptr, nullptr, PROV_RSA_FULL, 0)) {
		return CryptAcquireContext(ctx, nullptr, nullptr, PROV_RSA_FULL, CRYPT_NEWKEYSET);
	}

	return true;
}

void EmeraldManager::SetSeed() {
	std::uint_least32_t seed = 0;

	HCRYPTPROV ctx;
	if (!EmeraldManager::AcquireContext(&ctx)) {
		return;
	}

	BYTE* buffer = reinterpret_cast<BYTE*>(&seed);
	if (!CryptGenRandom(ctx, sizeof(seed), buffer) || seed == 0) {
		return;
	}

	if (!CryptReleaseContext(ctx, 0)) {
		return;
	}

	EmeraldManager::RandomGenerator = new std::mt19937(seed);
	EmeraldManager::GOD_SET_ENABLED = true;
}

Emerald* EmeraldManager::GetPieceById(SA2EmeraldManager* emManager, int id) {
	byte idLowByte = id & 0xFF;
	Emerald* emeralds = nullptr;
	int emeraldsLength = 0;
	switch (idLowByte) {
		case 0:
		case 2:
		case 5:
			emeralds = emManager->Slot2Emeralds;
			emeraldsLength = emManager->Slot2ArrayLen;
			break;
		case 1:
		case 3:
			emeralds = emManager->Slot1Emeralds;
			emeraldsLength = emManager->Slot1ArrayLen;
			break;
		case 4:
		case 7:
		case 8:
			emeralds = emManager->Slot3Emeralds;
			emeraldsLength = emManager->Slot3ArrayLen;
			break;
		case 0xA:
			emeralds = emManager->EnemySlotEmeralds;
			emeraldsLength = emManager->EnemySlotArrayLen;
			break;
	}

	for (int i = 0; i < emeraldsLength; i++) {
		if (emeralds[i].id == id) {
			return &emeralds[i];
		}
	}

	return nullptr;
}

void EmeraldManager::LoadEmeraldLocations(SA2EmeraldManager* emManager) {
	if (!EmeraldManager::GOD_SET_ENABLED || !EmeraldManager::RandomGenerator) {
		hLoadEmeraldLocations.Original(emManager);
		return;
	}

	if (EmeraldManager::GodSets.find((LevelIDs)CurrentLevel) == EmeraldManager::GodSets.end()) {
		hLoadEmeraldLocations.Original(emManager);
		return;
	}

	if (EmeraldManager::Distribution(*EmeraldManager::RandomGenerator)) {
		Set godSet = EmeraldManager::GodSets[(LevelIDs)CurrentLevel];
		Emerald* p1 = EmeraldManager::GetPieceById(emManager, godSet.p1Id);
		Emerald* p2 = EmeraldManager::GetPieceById(emManager, godSet.p2Id);
		Emerald* p3 = EmeraldManager::GetPieceById(emManager, godSet.p3Id);
		if (p1 == nullptr || p2 == nullptr || p3 == nullptr) {
			hLoadEmeraldLocations.Original(emManager);
			return;
		}

		if (emManager->Piece1.id != EmeraldManager::PIECE_COLLECTED) {
			*&emManager->Piece1.id = *&p1->id;
			emManager->Piece1.v = p1->v;
			emManager->EmeraldsSpawned++;
		}

		if (emManager->Piece2.id != EmeraldManager::PIECE_COLLECTED) {
			*&emManager->Piece2.id = *&p2->id;
			emManager->Piece2.v = p2->v;
			emManager->EmeraldsSpawned++;
		}

		if (emManager->Piece3.id != EmeraldManager::PIECE_COLLECTED) {
			*&emManager->Piece3.id = *&p3->id;
			emManager->Piece3.v = p3->v;
			emManager->EmeraldsSpawned++;
		}

		return;
	}

	hLoadEmeraldLocations.Original(emManager);
}

void EmeraldManager::Destroy() {
	EmeraldManager::GOD_SET_ENABLED = false;

	if (EmeraldManager::RandomGenerator) {
		delete EmeraldManager::RandomGenerator;
		EmeraldManager::RandomGenerator = nullptr;
	}
}