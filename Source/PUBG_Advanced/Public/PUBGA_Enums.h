#pragma once

UENUM(BlueprintType)
enum class EFashionType : uint8 {
	EFT_ClothTop UMETA(DisplayName = "ClothTop"),
	EFT_ClothBottom UMETA(DisplayName = "ClothBottom"),
	EFT_Whole UMETA(DisplayName = "Whole"),
	EFT_Shoes UMETA(DisplayName = "Shoes"),

	EFT_MAX UMETA(DisplayName = "DefaultMAX")
};