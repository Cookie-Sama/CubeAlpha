#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "CA_AbilitySystemComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FReceivedDamageDelegate, UCA_AbilitySystemComponent*, SourceASC, float, UnmitigatedDamage, float, MitigatedDamage);

UCLASS()
class CUBEALPHA_API UCA_AbilitySystemComponent : public UAbilitySystemComponent
{
	GENERATED_BODY()
public:

	bool CharacterAbilitiesGiven = false;
	bool StartupEffectsApplied = false;

	FReceivedDamageDelegate ReceivedDamage;

	virtual void ReceiveDamage(UCA_AbilitySystemComponent* SourceASC, float UnmitigatedDamage, float MitigatedDamage);
};
