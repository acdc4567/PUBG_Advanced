#pragma once

UENUM(BlueprintType)
enum class EFashionType : uint8 {
	EFT_ClothTop UMETA(DisplayName = "ClothTop"),
	EFT_ClothBottom UMETA(DisplayName = "ClothBottom"),
	EFT_Whole UMETA(DisplayName = "Whole"),
	EFT_Shoes UMETA(DisplayName = "Shoes"),

	EFT_MAX UMETA(DisplayName = "DefaultMAX")
};


UENUM(BlueprintType)
enum class EWeaponAccType : uint8 {
	EWAT_Sight UMETA(DisplayName = "Sight"),
	EWAT_Muzzle UMETA(DisplayName = "Muzzle"),
	EWAT_Foregrip UMETA(DisplayName = "Foregrip"),
	EWAT_Mag UMETA(DisplayName = "Magazine"),
	EWAT_Buttstock UMETA(DisplayName = "Buttstock"),

	EWAT_MAX UMETA(DisplayName = "DefaultMAX")
};

