#include "CA_ManaAttributeSet.h"
#include "Net/UnrealNetwork.h"

void UCA_ManaAttributeSet::OnRep_Mana(const FGameplayAttributeData& OldMana)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UCA_ManaAttributeSet, Mana, OldMana);
}

void UCA_ManaAttributeSet::OnRep_MaxMana(const FGameplayAttributeData& OldMaxMana)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UCA_ManaAttributeSet, MaxMana, OldMaxMana);
}

void UCA_ManaAttributeSet::OnRep_ManaRegen(const FGameplayAttributeData& OldManaRegen)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UCA_ManaAttributeSet, ManaRegen, OldManaRegen);
}

void UCA_ManaAttributeSet::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME_CONDITION_NOTIFY(UCA_ManaAttributeSet, Mana, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UCA_ManaAttributeSet, MaxMana, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UCA_ManaAttributeSet, ManaRegen, COND_None, REPNOTIFY_Always);
}
