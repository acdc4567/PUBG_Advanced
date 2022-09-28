// PUBG Advanced Tutorial. Blueprint To C++!!


#include "Bullets/BulletProjectile.h"
#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Bullets/BulletDecal.h"

// Sets default values
ABulletProjectile::ABulletProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CollisionSphere = CreateDefaultSubobject<USphereComponent>("CollisionSphere");
	CollisionSphere->InitSphereRadius(.5f);
	CollisionSphere->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	SetRootComponent(CollisionSphere);

	MovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>("ProjectileMovementComponent");
	MovementComponent->InitialSpeed = 100000.f;
	MovementComponent->MaxSpeed = 100000.f;



}

// Called when the game starts or when spawned
void ABulletProjectile::BeginPlay()
{
	Super::BeginPlay();
	
	

	MovementComponent->OnComponentActivated.AddDynamic(this,&ABulletProjectile::OnComponentActivation_Handle);
	CollisionSphere->OnComponentHit.AddDynamic(this,&ABulletProjectile::OnComponentHit_Handle);
	SetLifeSpan(15.f);
}

void ABulletProjectile::OnComponentActivation_Handle(UActorComponent* Component, bool bReset) {
	InitLocation = GetActorLocation();

}

void ABulletProjectile::OnComponentHit_Handle(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit) {
	FTransform SpawnTransform;
	SpawnTransform.SetLocation(Hit.Location);
	FQuat TQuat = Hit.ImpactNormal.ToOrientationQuat();
	SpawnTransform.SetRotation(TQuat);
	ABulletDecal* Decal = GetWorld()->SpawnActorDeferred<ABulletDecal>(BulletDecalClass, SpawnTransform);
	if (Decal) {
		//Decal->SetOwner(this);
		Decal->FinishSpawning(SpawnTransform);
	}
	SetLifeSpan(3.f);
}

// Called every frame
void ABulletProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FVector TempVector = GetActorLocation() - InitLocation;

	CurrentDistance = TempVector.Size();
	if (CurrentDistance<10000.f) {
		MovementComponent->MaxSpeed = f100MVelocity;
	}
	else if (CurrentDistance < 30000.f) {
		MovementComponent->MaxSpeed = f300MVelocity;
	}
	else if (CurrentDistance < 50000.f) {
		MovementComponent->MaxSpeed = f500MVelocity;
	}
	else {
		MovementComponent->MaxSpeed = f500MVelocity;
	}

}

