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

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "DataAsset")
		float AbilityDamage = 0;

	virtual void OnAvatarSet(const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilitySpec& Spec) override;

protected:

	UFUNCTION()
	void OnCancelled(FGameplayTag EventTag, FGameplayEventData EventData)
	{
		EndAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, true, true);
	}

	UFUNCTION()
	void OnCompleted(FGameplayTag EventTag, FGameplayEventData EventData)
	{
		EndAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, true, false);
	}

	UFUNCTION()
	virtual void OnGameplayEventReceived(FGameplayTag EventTag, FGameplayEventData EventData);
};
