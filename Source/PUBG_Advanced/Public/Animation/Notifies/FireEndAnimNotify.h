// PUBG Advanced Tutorial. Blueprint To C++!!

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "FireEndAnimNotify.generated.h"

DECLARE_MULTICAST_DELEGATE_OneParam(FFireEndNotifiedSignature, USkeletalMeshComponent*);

/**
 * 
 */
UCLASS()
class PUBG_ADVANCED_API UFireEndAnimNotify : public UAnimNotify
{
	GENERATED_BODY()
public:

	virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference) override;

	FFireEndNotifiedSignature OnNotified;

};
