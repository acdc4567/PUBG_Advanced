// PUBG Advanced Tutorial. Blueprint To C++!!


#include "Animation/Notifies/ReloadEndAnimNotify.h"

void UReloadEndAnimNotify::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference) {
	OnNotified.Broadcast(MeshComp);
	Super::Notify(MeshComp, Animation, EventReference);


}