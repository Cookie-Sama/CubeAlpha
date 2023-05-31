#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "CA_HUD.generated.h"

UCLASS()
class CUBEALPHA_API ACA_HUD : public AHUD
{
	GENERATED_BODY()

public:
	virtual void DrawHUD() override;
};
