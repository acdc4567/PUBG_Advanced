// PUBG Advanced Tutorial. Blueprint To C++!!


#include "Animation/Notifies/OnEquipEndAnimNotify.h"

void UOnEquipEndAnimNotify::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference) {
	OnNotifiedEnd.Broadcast(MeshComp);
	Super::Notify(MeshComp, Animation, EventReference);


}