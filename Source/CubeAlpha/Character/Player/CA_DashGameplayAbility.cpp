#include "Character/Player/CA_DashGameplayAbility.h"

#include "CA_PlayerCharacter.h"

UCA_DashGameplayAbility::UCA_DashGameplayAbility()
{
	InstancingPolicy = EGameplayAbilityInstancingPolicy::InstancedPerActor;
	ReplicationPolicy = EGameplayAbilityReplicationPolicy::ReplicateYes;
	AbilityTags.AddTag(FGameplayTag::RequestGameplayTag("Player.Ability.Movement"));
	AbilityID = CA_AbilityID::Movement;
}

void UCA_DashGameplayAbility::ActivateAbility(const FGameplayAbilitySpecHandle Handle,
	const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
	const FGameplayEventData* TriggerEventData)
{
	if (!CommitAbility(Handle, ActorInfo, ActivationInfo))
	{
		EndAbility(Handle, ActorInfo, ActivationInfo, true, true);
	}

	ACA_PlayerCharacter* Character = CastChecked<ACA_PlayerCharacter>(ActorInfo->AvatarActor.Get());
	FVector Velo = ActorInfo->AvatarActor->GetVelocity();
	Velo.Normalize();
	Velo.Z = 100;
	Velo.X *= DashSpeed;
	Velo.Y *= DashSpeed;
	Character->LaunchCharacter(Velo, false, false);
	EndAbility(Handle, ActorInfo, ActivationInfo, true, false);
}
