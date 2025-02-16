#include "pch.h"
#include "Animations.h"

std::pair<short, short> Animations::KnucklesAnimReplacements[] = {
	{ 190, 75 },
	{ 192, 105 },
	{ 193, 105 },
	{ 194, 15 },
	{ 195, 15 },
	{ 196, 15 },
	{ 197, 15 },
	{ 198, 15 },
	{ 211, 1 },
	{ 212, 77 },
	{ 215, 15 }
};

FunctionHook<void> hLoadCharacters((intptr_t)0x43D630);

void Animations::init() {
	unsigned __int8 shortjmp[] = { 0xEB };

	hLoadCharacters.Hook(LoadAnimations);
	WriteData((void*)0x7374E4, shortjmp); // Dry Lagoon Turtle Grab Patch
	WriteData((void*)0x749921, shortjmp); // Mech Boss Special Patch
	WriteData((void*)0x724261, shortjmp); // Sonic Boss Special Patch
	WriteData((void*)0x736211, shortjmp); // Knuckles Boss Special Patch
	WriteJump((void*)0x744E02, EggmanLargeCannonFix);
	WriteJump((void*)0x744914, EggmanLaserBlasterFix);
	WriteJump((void*)0x72F531, KnucklesAirNecklaceFix);
	WriteJump((void*)0x72F4D6, KnucklesSunglassesFix);
}

// Eggman Large Cannon
static const int loc_744E59 = 0x744E59;
static const int loc_744E08 = 0x744E08;
static NJS_OBJECT** const EggmanLargeCannonModel1 = &CharacterModels[262].Model;
static NJS_OBJECT** const EggmanLargeCannonModel2 = &CharacterModels[263].Model;
static const float* const flt_8AF004 = (const float*)0x8AF004;
__declspec(naked) void EggmanLargeCannonFix()
{
	__asm
	{
		mov eax, EggmanLargeCannonModel1
		mov eax, [eax]
		test eax, eax
		jz label
		mov eax, EggmanLargeCannonModel2
		mov eax, [eax]
		test eax, eax
		jz label
		mov eax, flt_8AF004
		fld[eax]
		jmp loc_744E08
		label :
		jmp loc_744E59
	}
}

// Eggman Laser Blaster
static const int loc_74496B = 0x74496B;
static const int loc_74491A = 0x74491A;
static NJS_OBJECT** const EggmanLaserBlasterModel = &CharacterModels[260].Model;
__declspec(naked) void EggmanLaserBlasterFix()
{
	__asm
	{
		mov edx, EggmanLaserBlasterModel
		mov edx, [edx]
		test edx, edx
		jz label
		jmp loc_74491A
		label :
		jmp loc_74496B
	}
}

// Knuckles Air Necklase
static const int loc_72F564 = 0x72F564;
static const int loc_72F537 = 0x72F537;
static NJS_OBJECT** const KnucklesAirNecklaceModel = &CharacterModels[168].Model;
__declspec(naked) void KnucklesAirNecklaceFix()
{
	__asm
	{
		mov ecx, KnucklesAirNecklaceModel
		mov ecx, [ecx]
		test ecx, ecx
		jz label
		jmp loc_72F537
		label :
		jmp loc_72F564
	}
}

// Knuckles Sunglasses
static const int loc_72F528 = 0x72F528;
static const int loc_72F4DB = 0x72F4DB;
static NJS_OBJECT** const KnucklesSunglassesModel = &CharacterModels[161].Model;
__declspec(naked) void KnucklesSunglassesFix()
{
	__asm
	{
		mov eax, KnucklesSunglassesModel
		mov eax, [eax]
		test eax, eax
		jz label
		jmp loc_72F4DB
		label :
		jmp loc_72F528
	}
}

void LoadAnimations() {
	ReplaceCharacters::remapUpgradeDataDynamic();
	hLoadCharacters.Original();

	for (int playerNum = 0; playerNum < 2; playerNum++) {
		int character = playerNum == 0 ? CurrentCharacter : CurrentCharacter2P;
		if (character == Characters_Knuckles) {
			int repcnt = (int)LengthOfArray(Animations::KnucklesAnimReplacements);
			std::pair<short, short>* replst = Animations::KnucklesAnimReplacements;
			AnimationInfo* anilst = MainCharObj2[playerNum]->AnimInfo.Animations;
			for (int i = 0; i < repcnt; i++) {
				if (!CharacterAnimations[anilst[replst[i].first].AnimNum].Animation) {
					anilst[replst[i].first] = anilst[replst[i].second];
				}
			}
		}
	}
}