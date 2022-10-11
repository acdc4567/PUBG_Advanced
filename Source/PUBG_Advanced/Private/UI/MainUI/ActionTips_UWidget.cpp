// PUBG Advanced Tutorial. Blueprint To C++!!


#include "UI/MainUI/ActionTips_UWidget.h"
#include "Components/TextBlock.h"

void UActionTips_UWidget::SetInfo(FName Infox) {
	FText TempText = FText::FromName(Infox);
	Info->SetText(TempText);


}


