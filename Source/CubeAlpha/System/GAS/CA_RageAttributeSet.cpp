#include "System/GAS/CA_RageAttributeSet.h"
#include "Net/UnrealNetwork.h"

void UCA_RageAttributeSet::OnRep_Rage(const FGameplayAttributeData& OldRage)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UCA_RageAttributeSet, Rage, OldRage);
}

void UCA_RageAttributeSet::OnRep_MaxRage(const FGameplayAttributeData& OldMaxRage)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UCA_RageAttributeSet, MaxRage, OldMaxRage);
}

void UCA_RageAttributeSet::OnRep_RageRegen(const FGameplayAttributeData& OldRageRegen)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UCA_RageAttributeSet, RageRegen, OldRageRegen);
}

void UCA_RageAttributeSet::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME_CONDITION_NOTIFY(UCA_RageAttributeSet, Rage, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UCA_RageAttributeSet, MaxRage, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UCA_RageAttributeSet, RageRegen, COND_None, REPNOTIFY_Always);
}
