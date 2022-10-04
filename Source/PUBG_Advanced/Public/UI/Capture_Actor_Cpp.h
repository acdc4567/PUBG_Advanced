// PUBG Advanced Tutorial. Blueprint To C++!!

#pragma once

#include "CoreMinimal.h"
#include "Engine/SceneCapture2D.h"
#include "Capture_Actor_Cpp.generated.h"


class USkeletalMeshComponent;


/**
 * 
 */
UCLASS()
class PUBG_ADVANCED_API ACapture_Actor_Cpp : public ASceneCapture2D
{
	GENERATED_BODY()
	
public:
	ACapture_Actor_Cpp();


protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Components)
		USkeletalMeshComponent* SkeletalMesh;



};
