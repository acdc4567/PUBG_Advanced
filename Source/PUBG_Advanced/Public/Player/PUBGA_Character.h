// PUBG Advanced Tutorial. Blueprint To C++!!

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "PUBGA_Character.generated.h"

UCLASS()
class PUBG_ADVANCED_API APUBGA_Character : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	APUBGA_Character();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
