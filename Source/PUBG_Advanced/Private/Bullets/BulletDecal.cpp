// PUBG Advanced Tutorial. Blueprint To C++!!


#include "Bullets/BulletDecal.h"

// Sets default values
ABulletDecal::ABulletDecal()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ABulletDecal::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABulletDecal::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

