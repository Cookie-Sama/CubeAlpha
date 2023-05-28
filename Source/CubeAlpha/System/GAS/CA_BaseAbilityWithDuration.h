#pragma once

#include "CoreMinimal.h"
#include "System/GAS/CA_GameplayAbility.h"
#include "CA_BaseAbilityWithDuration.generated.h"

/**
 * 
 */
UCLASS()
class CUBEALPHA_API UCA_BaseAbilityWithDuration : public UCA_GameplayAbility
{
	GENERATED_BODY()
public:

	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;

	virtual void EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled) override;

protected:
	// These functions need to be implemented in the child classes
	virtual void OnAbilityDurationStartedImplementation() {};
	virtual void OnAbilityDurationEndedImplementation() {};

	FTimerHandle AbilityTimerHandle;

	UPROPERTY(EditAnywhere, Category = "DataAsset")
		float AbilityDuration;

	void OnDurationTimerEnded();
};
