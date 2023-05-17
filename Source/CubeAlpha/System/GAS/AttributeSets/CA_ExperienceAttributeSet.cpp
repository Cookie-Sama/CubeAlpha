#include "CA_ExperienceAttributeSet.h"
#include "Net/UnrealNetwork.h"

void UCA_ExperienceAttributeSet::OnRep_Experience(const FGameplayAttributeData& OldExperience)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UCA_ExperienceAttributeSet, Experience, OldExperience);
}

void UCA_ExperienceAttributeSet::OnRep_MaxExperience(const FGameplayAttributeData& OldMaxExperience)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UCA_ExperienceAttributeSet, MaxExperience, OldMaxExperience);
}

void UCA_ExperienceAttributeSet::OnRep_ExperienceMultiplier(const FGameplayAttributeData& OldExperienceMultiplier)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UCA_ExperienceAttributeSet, ExperienceMultiplier, OldExperienceMultiplier);
}

void UCA_ExperienceAttributeSet::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME_CONDITION_NOTIFY(UCA_ExperienceAttributeSet, Experience, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UCA_ExperienceAttributeSet, MaxExperience, COND_None, REPNOTIFY_Always);
}
