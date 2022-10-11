// PUBG Advanced Tutorial. Blueprint To C++!!

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PUBGA_Enums.h"

#include "ActionTips_UWidget.generated.h"


class UTextBlock;


/**
 * 
 */
UCLASS()
class PUBG_ADVANCED_API UActionTips_UWidget : public UUserWidget
{
	GENERATED_BODY()
public:

	void SetInfo(FName Infox);
protected:

	

	UPROPERTY(meta = (BindWidget))
		UTextBlock* Info;

	


};
