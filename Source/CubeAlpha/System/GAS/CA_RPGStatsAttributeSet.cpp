#include "System/GAS/CA_RPGStatsAttributeSet.h"
#include "Net/UnrealNetwork.h"

void UCA_RPGStatsAttributeSet::OnRep_BaseVitality(const FGameplayAttributeData& OldBaseVitality)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UCA_RPGStatsAttributeSet, BaseVitality, OldBaseVitality);
}

void UCA_RPGStatsAttributeSet::OnRep_Vitality(const FGameplayAttributeData& OldVitality)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UCA_RPGStatsAttributeSet, Vitality, OldVitality);
}

void UCA_RPGStatsAttributeSet::OnRep_BaseStrength(const FGameplayAttributeData& OldBaseStrength)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UCA_RPGStatsAttributeSet, BaseStrength, OldBaseStrength);
}

void UCA_RPGStatsAttributeSet::OnRep_Strength(const FGameplayAttributeData& OldStrength)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UCA_RPGStatsAttributeSet, Strength, OldStrength);
}

void UCA_RPGStatsAttributeSet::OnRep_BaseIntelligence(const FGameplayAttributeData& OldBaseIntelligence)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UCA_RPGStatsAttributeSet, BaseIntelligence, OldBaseIntelligence);
}

void UCA_RPGStatsAttributeSet::OnRep_Intelligence(const FGameplayAttributeData& OldIntelligence)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UCA_RPGStatsAttributeSet, Intelligence, OldIntelligence);
}

void UCA_RPGStatsAttributeSet::OnRep_BaseAgility(const FGameplayAttributeData& OldBaseAgility)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UCA_RPGStatsAttributeSet, BaseAgility, OldBaseAgility);
}

void UCA_RPGStatsAttributeSet::OnRep_Agility(const FGameplayAttributeData& OldAgility)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UCA_RPGStatsAttributeSet, Agility, OldAgility);
}

void UCA_RPGStatsAttributeSet::OnRep_BaseEndurance(const FGameplayAttributeData& OldBaseEndurance)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UCA_RPGStatsAttributeSet, BaseEndurance, OldBaseEndurance);
}

void UCA_RPGStatsAttributeSet::OnRep_Endurance(const FGameplayAttributeData& OldEndurance)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UCA_RPGStatsAttributeSet, Endurance, OldEndurance);
}

void UCA_RPGStatsAttributeSet::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME_CONDITION_NOTIFY(UCA_RPGStatsAttributeSet, BaseVitality, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UCA_RPGStatsAttributeSet, Vitality, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UCA_RPGStatsAttributeSet, BaseStrength, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UCA_RPGStatsAttributeSet, Strength, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UCA_RPGStatsAttributeSet, BaseIntelligence, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UCA_RPGStatsAttributeSet, Intelligence, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UCA_RPGStatsAttributeSet, BaseAgility, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UCA_RPGStatsAttributeSet, Agility, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UCA_RPGStatsAttributeSet, BaseEndurance, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UCA_RPGStatsAttributeSet, Endurance, COND_None, REPNOTIFY_Always);
}
