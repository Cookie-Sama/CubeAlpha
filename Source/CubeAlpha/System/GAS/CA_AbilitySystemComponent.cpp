#include "System/GAS/CA_AbilitySystemComponent.h"

void UCA_AbilitySystemComponent::ReceiveDamage(UCA_AbilitySystemComponent* SourceASC, float UnmitigatedDamage,
	float MitigatedDamage)
{
	ReceivedDamage.Broadcast(SourceASC, UnmitigatedDamage, MitigatedDamage);
}
