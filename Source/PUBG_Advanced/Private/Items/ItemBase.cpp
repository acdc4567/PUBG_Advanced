// PUBG Advanced Tutorial. Blueprint To C++!!


#include "Items/ItemBase.h"
#include "Player/PUBGA_Character.h"
#include "PlayerController/PUBGA_PlayerController.h"
#include "Kismet/GameplayStatics.h"



// Sets default values
AItemBase::AItemBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Scene = CreateDefaultSubobject<USceneComponent>("Scene");
	SetRootComponent(Scene);







}

// Called when the game starts or when spawned
void AItemBase::BeginPlay()
{
	Super::BeginPlay();
	
	CharacterRef = Cast<APUBGA_Character>(UGameplayStatics::GetPlayerCharacter(this, 0));
	ControllerRef = Cast<APUBGA_PlayerController>(UGameplayStatics::GetPlayerController(this, 0));



}

void AItemBase::Init(EItemType ItemTypex, FName Namex) {

	ItemType = ItemTypex;
	Name = Namex;


}

int32 AItemBase::GetWeight() {
	return int32();
}

void AItemBase::UpdateAmount(const bool& bAdd, const bool& bReduce, const int32& Amountx) {

	if (bAdd) {
		Amount += Amountx;
	}
	else if(bReduce) {
		Amount -= Amountx;
	}
	else {
		Amount = Amountx;
	}


}

// Called every frame
void AItemBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

