// PUBG Advanced Tutorial. Blueprint To C++!!

#pragma once

#include "CoreMinimal.h"
#include "Engine/SceneCapture2D.h"
#include "PUBGA_Enums.h"
#include "Engine/DataTable.h"

#include "Capture_Actor_Cpp.generated.h"


class USkeletalMeshComponent;
class APUBGA_PlayerController;
class APUBGA_PlayerState;
class AItemBase;
class APUBGA_Character;



/**
 * 
 */
UCLASS()
class PUBG_ADVANCED_API ACapture_Actor_Cpp : public ASceneCapture2D
{
	GENERATED_BODY()
	
public:
	ACapture_Actor_Cpp();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Meshes)
		bool bHoldWeapon = 0;

	UFUNCTION(BlueprintImplementableEvent)
		void PlayHoldGunAnim();

	UFUNCTION(BlueprintImplementableEvent)
		void PlayNoGunAnim();

protected:
	
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void Destroyed() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Components)
		USkeletalMeshComponent* SkeletalMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = PlayerControllers)
		APUBGA_PlayerController* PlayerControllerRef;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = PlayerControllers)
		APUBGA_PlayerState* PlayerStateRef;

	UFUNCTION()
		void UpdateEquipment(AItemBase* Equipment, bool bIsAdd);

	AItemBase* SpawnActorx(EItemType ItemType,FName ID,FName SN);

	void Attach(AItemBase* Item, FName SocketName);

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Items)
		AItemBase* HelmetObj = nullptr;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Items)
		AItemBase* VestObj = nullptr;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Items)
		AItemBase* BackpackObj = nullptr;

	void ClearEquipments();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Meshes)
		USkeletalMeshComponent* SKM_Hair;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Meshes)
		USkeletalMeshComponent* SKM_UnderwearTop;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Meshes)
		USkeletalMeshComponent* SKM_UnderwearBottom;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Meshes)
		USkeletalMeshComponent* SKM_ClothTop;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Meshes)
		USkeletalMeshComponent* SKM_ClothBottom;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Meshes)
		USkeletalMeshComponent* SKM_Whole;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Meshes)
		USkeletalMeshComponent* SKM_Shoes;

	UMaterialInstanceDynamic* SkinMatRef;

	UFUNCTION(BlueprintCallable, Category = SkeletalMeshes)
		void InitSkeletalMesh();

	USkeletalMesh* GetFashionDatas(FName ID);

	UTexture* GetFashionDatasTexture(FName ID);

	FString ItemFashionTablePath;

	UDataTable* ItemFashionTableObject;

	void ReplaceSkeletalMesh(EFashionType FashionType,FName ID);


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Meshes)
		UTexture* SkinMatTest;

	UFUNCTION()
		void UpdateFashionx(AItemBase* Fashion, bool bIsAdd);

	UFUNCTION()
		void UpdateWeaponx(AItemWeapon* Weapon, EWeaponPosition Position, bool bIsOnHand);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Meshes)
		UAnimSequence* HoldWeaponStance;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Meshes)
		UAnimSequence* NoWeaponStance;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Meshes)
		APUBGA_Character* PlayerCharacterRef;

	

	

	void UpdateWeapon();


	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Meshes)
		AItemBase* HoldWeapon;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Meshes)
		AItemBase* LeftWeapon;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Meshes)
		AItemBase* RightWeapon;

	void ClearWeapons();

	void UpdateAccessories(AItemBase* CharacterWeapon,AItemBase* d3DWeapon);

	UFUNCTION()
		void UpdateWeaponAcc(AItemWeapon* Weapon, bool bIsRemove, AItemWeaponAcc* AccObj, EWeaponAccType AccType);



};
