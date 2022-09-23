// PUBG Advanced Tutorial. Blueprint To C++!!

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "PUBGA_GameModeBase.generated.h"

class APickUpBase;
/**
 * 
 */
UCLASS()
class PUBG_ADVANCED_API APUBGA_GameModeBase : public AGameModeBase
{
	GENERATED_BODY()
public:
	APUBGA_GameModeBase();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = GenerateItems)
		TArray<APickUpBase* > GeneratedItems;

	UFUNCTION(BlueprintCallable)
		void GetGeneratedItems(TArray<APickUpBase*> Items);



};
