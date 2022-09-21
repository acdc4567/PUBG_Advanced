// PUBG Advanced Tutorial. Blueprint To C++!!


#include "Items/PickUpBase.h"
#include "Components/WidgetComponent.h"
#include "Components/BoxComponent.h"
#include "Player/PUBGA_Character.h"



APickUpBase::APickUpBase() {

	StaticMeshx1 = CreateDefaultSubobject<UStaticMeshComponent>("StaticMesh");
	StaticMeshx1->SetCollisionProfileName("NoCollision");
	StaticMeshx1->SetupAttachment(Scene);
	
	UI = CreateDefaultSubobject<UWidgetComponent>("UI");
	UI->SetupAttachment(StaticMeshx1);

	Outline = CreateDefaultSubobject<UStaticMeshComponent>("Outline");
	Outline->SetCollisionProfileName("NoCollision");
	Outline->SetupAttachment(StaticMeshx1);
	
	Box = CreateDefaultSubobject<UBoxComponent>("Box");
	Box->SetBoxExtent(FVector(220.f,220.f,100.f));
	Box->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
	Box->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Overlap);
	Box->SetupAttachment(Scene);


}

void APickUpBase::BeginPlay() {

	Super::BeginPlay();

	LineTraceToLands();

	Box->OnComponentBeginOverlap.AddDynamic(this, &APickUpBase::BoxOverlapHandle);
	Box->OnComponentEndOverlap.AddDynamic(this, &APickUpBase::BoxOverlapEndHandle);



}


void APickUpBase::InitPickup(EItemType ItemTypex, FName Namex, FName UI_Prefix1, UStaticMesh* StaticMeshx) {
	Init(ItemTypex,Namex);

	UI_Prefix = UI_Prefix1;
	StaticMeshx1->SetStaticMesh(StaticMeshx);






}

void APickUpBase::LineTraceToLands() {

	FCollisionQueryParams CollisionParams;
	CollisionParams.AddIgnoredActor(this);
	const auto TraceStart = GetActorLocation();
	const FVector ShootDirection = GetActorUpVector();
	FVector TraceEnd = TraceStart + ShootDirection * 1000.f * -1.f;
	FHitResult HitResult;
	GetWorld()->LineTraceSingleByChannel(HitResult, TraceStart, TraceEnd, ECollisionChannel::ECC_Visibility, CollisionParams);
	if (HitResult.bBlockingHit) {
		SetActorLocation(HitResult.Location+FVector(0.f,0.f,10.f));
	}
	




}

void APickUpBase::BoxOverlapHandle(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) {

	

	if (OtherActor ) {
		APUBGA_Character* Char = Cast<APUBGA_Character>(OtherActor);
		if (Char==CharacterRef) {
			OnBoxBeginOverlapSign.Broadcast(this);
			
		}
		
	}


}

void APickUpBase::BoxOverlapEndHandle(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex) {

	if (OtherActor) {
		APUBGA_Character* Char = Cast<APUBGA_Character>(OtherActor);
		if (Char == CharacterRef) {
			
			
			OnBoxEndOverlapSign.Broadcast(this);
			
		}

	}


}

void APickUpBase::EnableOutline(bool bEnable) {
	StaticMeshx1->SetRenderCustomDepth(bEnable);

}




