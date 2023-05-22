#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "GameplayEffectTypes.h"
#include "CA_PlayerState.generated.h"

UCLASS()
class CUBEALPHA_API ACA_PlayerState : public APlayerState
{
	GENERATED_BODY()
public:
	ACA_PlayerState();

	UFUNCTION(BlueprintCallable, Category = "CubeAlpha|PlayerState")
	void ShowAbilityConfirmCancelText(bool ShowText);

protected:
	FGameplayTag DeadTag;

	virtual void BeginPlay() override;
};
