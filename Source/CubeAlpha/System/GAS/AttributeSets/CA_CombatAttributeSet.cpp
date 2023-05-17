#include "CA_CombatAttributeSet.h"
#include "Net/UnrealNetwork.h"

void UCA_CombatAttributeSet::OnRep_PhysicalDamage(const FGameplayAttributeData& OldPhysicalDamage)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UCA_CombatAttributeSet, PhysicalDamage, OldPhysicalDamage);
}

void UCA_CombatAttributeSet::OnRep_MagicalDamage(const FGameplayAttributeData& OldMagicalDamage)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UCA_CombatAttributeSet, MagicalDamage, OldMagicalDamage);
}

void UCA_CombatAttributeSet::OnRep_PhysicalResistance(const FGameplayAttributeData& OldPhysicalResistance)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UCA_CombatAttributeSet, PhysicalResistance, OldPhysicalResistance);
}

void UCA_CombatAttributeSet::OnRep_MagicalResistance(const FGameplayAttributeData& OldMagicalResistance)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UCA_CombatAttributeSet, MagicalResistance, OldMagicalResistance);
}

void UCA_CombatAttributeSet::OnRep_Defense(const FGameplayAttributeData& OldDefense)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UCA_CombatAttributeSet, Defense, OldDefense);
}

void UCA_CombatAttributeSet::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME_CONDITION_NOTIFY(UCA_CombatAttributeSet, PhysicalDamage, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UCA_CombatAttributeSet, MagicalDamage, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UCA_CombatAttributeSet, PhysicalResistance, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UCA_CombatAttributeSet, MagicalResistance, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UCA_CombatAttributeSet, Defense, COND_None, REPNOTIFY_Always);
}
