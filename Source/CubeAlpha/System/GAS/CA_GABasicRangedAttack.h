// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "System/GAS/CA_GameplayAbility.h"
#include "CA_GABasicRangedAttack.generated.h"

/**
 * 
 */
UCLASS()
class CUBEALPHA_API UCA_GABasicRangedAttack : public UCA_GameplayAbility
{
	GENERATED_BODY()

public:
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;
};
