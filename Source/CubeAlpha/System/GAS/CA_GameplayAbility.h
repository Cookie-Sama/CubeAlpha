#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "CubeAlpha.h"
#include "CA_GameplayAbility.generated.h"

/**
 * 
 */
UCLASS()
class CUBEALPHA_API UCA_GameplayAbility : public UGameplayAbility
{
	GENERATED_BODY()
public:
	UCA_GameplayAbility();
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Ability")
		CA_AbilityID AbilityID = CA_AbilityID::None;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Ability")
		bool ActivateAbilityOnGranted = false;

	virtual void OnAvatarSet(const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilitySpec& Spec) override;
};
