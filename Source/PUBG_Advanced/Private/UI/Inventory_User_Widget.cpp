// PUBG Advanced Tutorial. Blueprint To C++!!


#include "UI/Inventory_User_Widget.h"
#include "PlayerState/PUBGA_PlayerState.h"
#include "PlayerController/PUBGA_PlayerController.h"
#include "Kismet/GameplayStatics.h"
#include "Components/ProgressBar.h"



bool UInventory_User_Widget::InitializePlayerController(APUBGA_PlayerController* APC) {
	if (PlayerControllerRef)return 1;
	if (APC) {
		PlayerControllerRef = APC;
		return 1;
	}
	else {
		return 1;
	}

	return 1;
}

bool UInventory_User_Widget::InitializePlayerState(APUBGA_PlayerState* APS) {
	if (!PlayerControllerRef)return 1;
	if (PlayerStateRef)return 1;
	if (PlayerControllerRef->GetPlayerStateRef()) {
		//PlayerStateRef = PlayerControllerRef->GetPlayerStateRef();
		
		if (PlayerStateRef) {

			return 1;
		}

	}
	else {
		return 1;
	}

	return 1;
}

void UInventory_User_Widget::NativeConstruct() {
	Super::NativeConstruct();
	
	PlayerControllerRef = Cast<APUBGA_PlayerController>(UGameplayStatics::GetPlayerController(this, 0));
	if (PlayerControllerRef) {
		PlayerStateRef = PlayerControllerRef->GetPlayerStateRef();
		if (PlayerStateRef) {
			PlayerStateRef->OnItemsChanged.AddDynamic(this, &UInventory_User_Widget::UpdateList);
			UpdateList(nullptr, 0);

		}

	}


}

void UInventory_User_Widget::NativeDestruct() {
	Super::NativeDestruct();

	PlayerControllerRef = Cast<APUBGA_PlayerController>(UGameplayStatics::GetPlayerController(this, 0));
	if (PlayerControllerRef) {
		PlayerStateRef = PlayerControllerRef->GetPlayerStateRef();
		if (PlayerStateRef) {
			PlayerStateRef->OnItemsChanged.RemoveDynamic(this, &UInventory_User_Widget::UpdateList);
		}


	}


}

void UInventory_User_Widget::UpdateList(AItemBase* Item, bool bIsAdd) {
	if (!PlayerStateRef)return;
	PlayerStateRef->CheckBackpackCapacity(0);
	float ItemsTotalWeightf = float(PlayerStateRef->GetItemsWeightTot());
	float BPCapacityf = float(PlayerStateRef->GetTotalCapacityOfBP());
	
	BackpackCapacityBar->SetPercent(ItemsTotalWeightf/ BPCapacityf);


}
