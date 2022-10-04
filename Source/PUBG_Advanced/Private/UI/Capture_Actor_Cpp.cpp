// PUBG Advanced Tutorial. Blueprint To C++!!


#include "UI/Capture_Actor_Cpp.h"
#include "Components/SkeletalMeshComponent.h"



ACapture_Actor_Cpp::ACapture_Actor_Cpp() {
	SkeletalMesh = CreateDefaultSubobject<USkeletalMeshComponent>("SkeletalMesh");
	SkeletalMesh->SetupAttachment(GetRootComponent());

}
