// PUBG Advanced Tutorial. Blueprint To C++!!

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "PUBGA_PlayerControllerx.generated.h"

class APUBGA_Characterx;


/**
 * 
 */
UCLASS()
class PUBG_ADVANCED_API APUBGA_PlayerControllerx : public APlayerController
{
	GENERATED_BODY()


public:

	APUBGA_PlayerControllerx();

	void OnPossessx(APUBGA_Characterx* inCharacter);

	virtual void SetupInputComponent() override;

protected:

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Players)
		APUBGA_Characterx* PlayerCharacterRef;

	void MouseTurn(float Value);
	void MouseLookUp(float Value);









};
