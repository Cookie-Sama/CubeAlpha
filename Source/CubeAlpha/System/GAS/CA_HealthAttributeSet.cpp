#include "System/GAS/CA_HealthAttributeSet.h"
#include "Net/UnrealNetwork.h"

void UCA_HealthAttributeSet::OnRep_Health(const FGameplayAttributeData& OldHealth)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UCA_HealthAttributeSet, Health, OldHealth);
}

void UCA_HealthAttributeSet::OnRep_MaxHealth(const FGameplayAttributeData& OldMaxHealth)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UCA_HealthAttributeSet, MaxHealth, OldMaxHealth);
}

void UCA_HealthAttributeSet::OnRep_HealthRegen(const FGameplayAttributeData& OldHealthRegen)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UCA_HealthAttributeSet, HealthRegen, OldHealthRegen);
}

void UCA_HealthAttributeSet::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME_CONDITION_NOTIFY(UCA_HealthAttributeSet, Health, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UCA_HealthAttributeSet, MaxHealth, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UCA_HealthAttributeSet, HealthRegen, COND_None, REPNOTIFY_Always);
}
