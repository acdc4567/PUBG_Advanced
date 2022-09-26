// PUBG Advanced Tutorial. Blueprint To C++!!

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "PUBGA_Enums.h"
#include "Engine/DataTable.h"
#include "PUBGA_PlayerState.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FOnWeaponChangedSignature, AItemWeapon*, Weapon, EWeaponPosition, Position, bool, bIsOnHand);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnAmmoChangedSignature, bool, bIsTrue);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnHealthChangedSignature, float, Value);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnEnergyChangedSignature, float, Value);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnEquipmentChangedSignature, AItemBase*, Equipment, bool, bIsAdd);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnFashionChangedSignature, AItemBase*, Fashion, bool, bIsAdd);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnItemsChangedSignature, AItemBase*, Item, bool, bIsAdd);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_FourParams(FOnWeaponAccChangedSignature, AItemWeapon*, Weapon, bool, bIsRemove, AItemWeaponAcc*, AccObj, EWeaponAccType, AccType);


class APickUpBase;
class AItemWeapon;
class AItemBase;
class APUBGA_PlayerController;
class AItemWeaponAcc;


/**
 * 
 */
UCLASS()
class PUBG_ADVANCED_API APUBGA_PlayerState : public APlayerState
{
	GENERATED_BODY()


public:
	APUBGA_PlayerState();



protected:

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;


	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Items)
		AItemWeapon* Weapon1;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Items)
		AItemWeapon* Weapon2;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Items)
		AItemWeapon* HoldGun;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Items)
		int32 Ammo556;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Items)
		int32 Ammo762;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Items)
		TArray<AItemBase*> Equipments;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Items)
		TArray<AItemBase*> Fashions;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Items)
		TArray<AItemBase*> ItemsInBackpack;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Character)
		float HealthPoint=100.f;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Items)
		float EnergyPoint=100.f;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Items)
		int32 KillAmount;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Items)
		APUBGA_PlayerController* PlayerControllerRef;

	FString ItemEquipmentTablePath;

	UDataTable* ItemEquipmentTableObject;




public:

	UPROPERTY(BlueprintAssignable, Category = "Events")
		FOnWeaponChangedSignature OnWeaponChanged;

	FOnAmmoChangedSignature OnAmmoChanged;

	FOnHealthChangedSignature OnHealthChanged;

	FOnEnergyChangedSignature OnEnergyChanged;

	FOnEquipmentChangedSignature OnEquipmentChanged;

	FOnFashionChangedSignature OnFashionChanged;

	FOnItemsChangedSignature OnItemsChanged;

	FOnWeaponAccChangedSignature OnWeaponAccChanged;


	//Getters

	AItemWeapon* GetWeapon1();

	AItemWeapon* GetWeapon2();

	UFUNCTION(BlueprintPure)
		AItemWeapon* GetHoldGun();

	int32 GetAmmo556();

	int32 GetAmmo762();

	float GetHealthPoint();

	float GetEnergyPoint();

	TArray<AItemBase*> GetEquipments();

	TArray<AItemBase*> GetFashions();

	UFUNCTION(BlueprintCallable)
		TArray<AItemBase*> GetItems();

	//Setters

	void SetWeapon1(AItemWeapon* WeaponToSet);

	void SetWeapon2(AItemWeapon* WeaponToSet);

	UFUNCTION(BlueprintCallable)
		void SetHoldGun(AItemWeapon* WeaponToSet);

	void SetAmmo556(int32 Value);

	void SetAmmo762(int32 Value);

	void SetHealthPoint(float Value);

	void SetEnergyPoint(float Value);

	void AddEquipment(AItemBase* Equipment);

	void AddFashion(AItemBase* Fashion);

	void AddItem(AItemBase* Item);

	bool RemoveEquipment(AItemBase* Equipment);

	bool RemoveFashion(AItemBase* Fashion);

	bool RemoveItem(AItemBase* Item);

	bool CheckBackpackCapacity(int32 AddWeight);

	void UpdateAmmoObject();

	void UpdateAmmoAmount(FName IDx,bool bAdd,int32 Amountx);

	bool CheckReplaceBackpack(AItemBase* Item);

	void UpdateWeaponAcc(EWeaponPosition Position, EWeaponAccType AccType, AItemWeaponAcc* ItemWeaponAcc);





};
