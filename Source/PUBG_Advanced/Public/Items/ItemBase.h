// PUBG Advanced Tutorial. Blueprint To C++!!

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PUBGA_Enums.h"
#include "ItemBase.generated.h"

class APUBGA_Character;
class APUBGA_PlayerController;







UCLASS()
class PUBG_ADVANCED_API AItemBase : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AItemBase();

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Publics, meta = (ExposeOnSpawn = "true"))
		FName ID;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Publics, meta = (ExposeOnSpawn = "true"))
		FName SN;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Publics, meta = (ExposeOnSpawn = "true"))
		int32 Amount;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Publics)
		USceneComponent* Scene;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Publics)
		EItemType ItemType;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Publics)
		FName Name;





protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	
	

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Protecteds)
		APUBGA_Character* CharacterRef;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Protecteds)
		APUBGA_PlayerController* ControllerRef;

	void Init(EItemType ItemTypex,FName Namex);

	virtual int32 GetWeight();

	void UpdateAmount(const bool& bAdd, const bool& bReduce, const int32& Amountx);





public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
