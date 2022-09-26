#pragma once
#include "Engine/DataTable.h"
#include "PUBGA_Enums.h"
#include "PUBGA_Structs.generated.h"


USTRUCT(BlueprintType)
struct FSTR_ProneTimes : public FTableRowBase {
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Sec;


};


USTRUCT(BlueprintType)
struct FSTR_CameraHeight : public FTableRowBase {
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Height;


};

USTRUCT(BlueprintType)
struct FSTR_WalkSpeed : public FTableRowBase {
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float Forward;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float Other;

};



USTRUCT(BlueprintType)
struct FSTR_ItemFashion : public FTableRowBase {
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		EFashionType Type;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FName Name;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UTexture2D* Icon;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		USkeletalMesh* SkeletalMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UStaticMesh* StaticMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UTexture* MaskTexture;


};

USTRUCT(BlueprintType)
struct FSTR_ItemWeapon : public FTableRowBase {
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FName Name;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UTexture2D* Icon;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UTexture2D* BigIcon;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UTexture2D* Thumbnail;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FName UseAmmoID;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int32 ClipSize;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int32 Damage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float FiringInterval;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float ReplaceClipTime;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float ReplaceBulletTime;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool bAutoMode;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UStaticMesh* StaticMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		USkeletalMesh* SkeletalMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UStaticMesh* DefaultMag;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UStaticMesh* DefaultSight;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UStaticMesh* DefaultButtstock;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		USoundBase* FireSound;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		USoundBase* FireSoundSuppressor;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool bCanSight;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool bCanMuzzle;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool bCanClip;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool bCanButtStock;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool bCanGrip;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float CrossOffset_Min_Stillness;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float CrossOffset_Max_Stillness;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float CrossOffset_Min_Move;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float CrossOffset_Max_Move;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float CrossOffset_Min_AimStillness;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float CrossOffset_Max_AimStillness;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float CrossOffset_Min_AimMove;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float CrossOffset_Max_AimMove;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float VerticalOffset;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float HorizontalOffset;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float InitVelocity;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float f100MVelocity;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float f300MVelocity;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float f500MVelocity;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float WalkSpeedPer;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UParticleSystem* FireFlashParticles;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int32 ProbabilityPercent;

};


USTRUCT(BlueprintType)
struct FSTR_ItemAmmo : public FTableRowBase {
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FName Name;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UStaticMesh* PickupMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int32 PickupAmount;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UTexture2D* Icon;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int32 Weight;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int32 ProbabilityPercent;

};

USTRUCT(BlueprintType)
struct FSTR_ItemWeaponAcc : public FTableRowBase {
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FName Name;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		EWeaponAccType Type;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TArray<FName> WeaponIDs;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int32 Weight;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UStaticMesh* StaticMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UStaticMesh* StaticMesh2;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UTexture2D* Icon;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int32 SightMultiple;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool bIsSuppressor;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool bIsNotFlash;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float ClipRate;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int32 ClipCapacity;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float VerticalAdjPer;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float HorizontalAdjPer;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FName SocketName;

};

USTRUCT(BlueprintType)
struct FSTR_ItemEquipment : public FTableRowBase {
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FName Name;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		EItemType Type;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UStaticMesh* StaticMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UTexture2D* Icon;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UTexture2D* Thumbnail;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int32 Capacity;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int32 ProbabilityPercent;

	

};


USTRUCT(BlueprintType)
struct FSTR_ItemHealth : public FTableRowBase {
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FName Name;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UStaticMesh* StaticMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UTexture2D* Icon;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int32 Weight;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float UseTime;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float Value;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float Limit;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int32 ProbabilityPercent;

};


USTRUCT(BlueprintType)
struct FSTR_ItemBoost : public FTableRowBase {
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FName Name;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UStaticMesh* StaticMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UTexture2D* Icon;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int32 Weight;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float UseTime;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float BoostValue;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int32 ProbabilityPercent;

};



USTRUCT(BlueprintType)
struct FSTR_NumberProbability : public FTableRowBase {
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int32 Percent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int32 Number;

	
};


USTRUCT(BlueprintType)
struct FSTR_ItemTypeProbability : public FTableRowBase {
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int32 Percent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		EItemType Type;


};



USTRUCT(BlueprintType)
struct FSTR_ArmsLocation : public FTableRowBase {
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FVector Location;

};

USTRUCT(BlueprintType)
struct FSTR_AimAccurately : public FTableRowBase {
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float ArmsNormalRate;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float ArmsAccuratelyRate;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float Duration;

};





USTRUCT(BlueprintType)
struct FGate {
	GENERATED_BODY()
public:
	FORCEINLINE void Open() { bIsGateOpen = true; }

	FORCEINLINE void Close() { bIsGateOpen = false; }

	FORCEINLINE void Toggle() { bIsGateOpen = !bIsGateOpen; }

	FORCEINLINE bool IsGateOpen() const { return bIsGateOpen; }

private:
	UPROPERTY(VisibleAnywhere)
		bool bIsGateOpen = true;


};





