#include "System/GAS/Abilities/CA_BaseAbilityWithDuration.h"

void UCA_BaseAbilityWithDuration::ActivateAbility(const FGameplayAbilitySpecHandle Handle,
	const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
	const FGameplayEventData* TriggerEventData)
{
	if (!CommitAbility(Handle, ActorInfo, ActivationInfo))
	{
		Super::EndAbility(Handle, ActorInfo, ActivationInfo, true, true);
	}

	OnAbilityDurationStartedImplementation();
	GetWorld()->GetTimerManager().SetTimer(AbilityTimerHandle, this, &UCA_BaseAbilityWithDuration::OnDurationTimerEnded, AbilityDuration, false);
}

void UCA_BaseAbilityWithDuration::EndAbility(const FGameplayAbilitySpecHandle Handle,
	const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
	bool bReplicateEndAbility, bool bWasCancelled)
{
	GetWorld()->GetTimerManager().ClearTimer(AbilityTimerHandle);
	OnAbilityDurationEndedImplementation();
	EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);
}

void UCA_BaseAbilityWithDuration::OnDurationTimerEnded()
{
	EndAbility(CurrentSpecHandle, GetCurrentActorInfo(), GetCurrentActivationInfo(), true, false);
}
