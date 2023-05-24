#include "System/GAS/CA_GABasicRangedAttack.h"

#include "CA_PlayerCharacter.h"
#include "GDAT_PlayMontageAndWaitForEvent.h"

UCA_GABasicRangedAttack::UCA_GABasicRangedAttack()
{
	AbilityTags.AddTag(FGameplayTag::RequestGameplayTag("Player.Ability.Primary"));
}

void UCA_GABasicRangedAttack::ActivateAbility(const FGameplayAbilitySpecHandle Handle,
                                              const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
                                              const FGameplayEventData* TriggerEventData)
{
	const ACA_PlayerCharacter* Owner = Cast<ACA_PlayerCharacter>(ActorInfo->AvatarActor.Get());
	FGameplayTagContainer Tags;
	Tags.AddTag(FGameplayTag::RequestGameplayTag("Ability.Primary"));
	UGDAT_PlayMontageAndWaitForEvent* Task = UGDAT_PlayMontageAndWaitForEvent::PlayMontageAndWaitForEvent(this,NAME_None,Owner->PrimaryMontage,Tags, Owner->PrimaryPlayRate, NAME_None, false, 1.0f);
	Task->OnInterrupted.AddDynamic(this, &UCA_GABasicRangedAttack::OnCancelled);
	Task->OnCancelled.AddDynamic(this, &UCA_GABasicRangedAttack::OnCancelled);
	Task->EventReceived.AddDynamic(this, &UCA_GABasicRangedAttack::OnGameplayEventReceived);
	Task->ReadyForActivation();
}

void UCA_GABasicRangedAttack::OnGameplayEventReceived(FGameplayTag EventTag, FGameplayEventData EventData)
{
	if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Oui"));
	EndAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, true, false);
}
