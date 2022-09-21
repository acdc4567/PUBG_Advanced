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

UENUM(BlueprintType)
enum class EItemType : uint8 {
	EIT_Weapon UMETA(DisplayName = "Weapon"),
	EIT_Accessories UMETA(DisplayName = "Accessories"),
	EIT_Ammo UMETA(DisplayName = "Ammo"),
	EIT_Health UMETA(DisplayName = "Health"),
	EIT_Boost UMETA(DisplayName = "Boost"),
	EIT_Helmet UMETA(DisplayName = "Helmet"),
	EIT_Vest UMETA(DisplayName = "Vest"),
	EIT_Backpack UMETA(DisplayName = "Backpack"),
	EIT_Fashion UMETA(DisplayName = "Fashion"),
	
	EIT_MAX UMETA(DisplayName = "DefaultMAX")
};


UENUM(BlueprintType)
enum class EWeaponPosition : uint8 {
	EWP_Left UMETA(DisplayName = "Left"),
	EWP_Right UMETA(DisplayName = "Right"),

	EWP_MAX UMETA(DisplayName = "DefaultMAX")
};











