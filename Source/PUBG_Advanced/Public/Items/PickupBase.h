// PUBG Advanced Tutorial. Blueprint To C++!!

#pragma once

#include "CoreMinimal.h"
#include "Items/ItemBase.h"
#include "PUBGA_Enums.h"
#include "PickUpBase.generated.h"

DECLARE_MULTICAST_DELEGATE_OneParam(FOnBoxBeginOverlapSign,APickUpBase*);
DECLARE_MULTICAST_DELEGATE_OneParam(FOnBoxEndOverlapSign, APickUpBase*);

class UBoxComponent;
class UWidgetComponent;
/**
 * 
 */
UCLASS()
class PUBG_ADVANCED_API APickUpBase : public AItemBase
{
	GENERATED_BODY()


public:
	APickUpBase();

	FOnBoxBeginOverlapSign OnBoxBeginOverlapSign;
	FOnBoxEndOverlapSign OnBoxEndOverlapSign;

	void EnableOutline(bool bEnable);

	FORCEINLINE UBoxComponent* GetBox() const { return Box; }

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Protecteds)
		FName UI_Prefix;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Protecteds)
		UStaticMeshComponent* StaticMeshx1;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Protecteds)
		UWidgetComponent* UI;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Protecteds)
		UStaticMeshComponent* Outline;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Protecteds)
		UBoxComponent* Box;

	

	void InitPickup(EItemType ItemTypex, FName Namex, FName UI_Prefix1, UStaticMesh* StaticMeshx);

	void LineTraceToLands();

	UFUNCTION()
		void BoxOverlapHandle(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
		void BoxOverlapEndHandle(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);




	
	


};
