// PUBG Advanced Tutorial. Blueprint To C++!!

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BulletProjectile.generated.h"

class USphereComponent;
class UProjectileMovementComponent;
class ABulletDecal;

UCLASS()
class PUBG_ADVANCED_API ABulletProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABulletProjectile();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Publics)
		USphereComponent* CollisionSphere;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Weapon)
		UProjectileMovementComponent* MovementComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Weapon)
		TSubclassOf<ABulletDecal> BulletDecalClass;




	UFUNCTION()
		void OnComponentActivation_Handle(UActorComponent* Component, bool bReset);

	UFUNCTION()
		void OnComponentHit_Handle(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);


	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Projectilez)
		FVector InitLocation=FVector::ZeroVector;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Projectilez)
		float CurrentDistance = 0.f;


public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Projectilez)
		float InitVelocity = 0.f;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Projectilez)
		float f100MVelocity = 0.f;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Projectilez)
		float f300MVelocity = 0.f;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Projectilez)
		float f500MVelocity = 0.f;

};
