#include "Widgets/BaseWidget.h"

#include "Framework/Game/PCGame.h"


void UBaseWidget::NativeConstruct()
{
	Super::NativeConstruct();
	//get player controller here and set it
	PlayerControllerRef = Cast<APCGame>(GetOwningPlayer());
}
