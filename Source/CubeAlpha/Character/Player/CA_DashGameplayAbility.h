#pragma once

#include "CoreMinimal.h"
#include "System/GAS/Player/CA_PlayerGameplayAbility.h"
#include "CA_DashGameplayAbility.generated.h"

/**
 * 
 */
UCLASS()
class CUBEALPHA_API UCA_DashGameplayAbility : public UCA_PlayerGameplayAbility
{
	GENERATED_BODY()
public:

	UCA_DashGameplayAbility();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DataAsset")
		float DashSpeed = 1500;

	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;
};
