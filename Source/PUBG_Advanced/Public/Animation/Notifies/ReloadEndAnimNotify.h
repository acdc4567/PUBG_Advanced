// PUBG Advanced Tutorial. Blueprint To C++!!

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "ReloadEndAnimNotify.generated.h"

DECLARE_MULTICAST_DELEGATE_OneParam(FReloadEndNotifiedSignature, USkeletalMeshComponent*);

/**
 * 
 */
UCLASS()
class PUBG_ADVANCED_API UReloadEndAnimNotify : public UAnimNotify
{
	GENERATED_BODY()

public:

	virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference) override;

	FReloadEndNotifiedSignature OnNotified;


};
