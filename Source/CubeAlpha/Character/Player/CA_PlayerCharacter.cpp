#include "Character/Player/CA_PlayerCharacter.h"
#include "CA_AbilitySystemComponent.h"
ACA_PlayerCharacter::ACA_PlayerCharacter(const class FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer.SetDefaultSubobjectClass<UCharacterMovementComponent>(ACharacter::CharacterMovementComponentName))
{
}

#pragma region Cooldowns
bool ACA_PlayerCharacter::GetCooldownRemainingForAbility(const FGameplayTag AbilityTag, float& OutTimeRemaining)
{
	FString CooldownTag = AbilityTag.ToString().Append(".OnCooldown");

	FGameplayTagContainer tags;
	tags.AddTag(FGameplayTag::RequestGameplayTag(FName(CooldownTag)));

	return GetCooldownRemainingForTag(tags, OutTimeRemaining);
}

bool ACA_PlayerCharacter::GetCooldownDurationForAbility(const FGameplayTag AbilityTag, float& OutDuration)
{
	FString CooldownTag = AbilityTag.ToString().Append(".OnCooldown");

	FGameplayTagContainer tags;
	tags.AddTag(FGameplayTag::RequestGameplayTag(FName(CooldownTag)));

	return GetCooldownDurationForTag(tags, OutDuration);
}

bool ACA_PlayerCharacter::GetCooldownRemainingForTag(const FGameplayTagContainer CooldownTags, float& OutTimeRemaining)
{
	if (AbilitySystemComponent.IsValid() && CooldownTags.Num() > 0)
	{
		OutTimeRemaining = 0.f;

		FGameplayEffectQuery const Query = FGameplayEffectQuery::MakeQuery_MatchAnyOwningTags(CooldownTags);
		TArray<float>  TimeRemaining = AbilitySystemComponent->GetActiveEffectsTimeRemaining(Query);

		if (TimeRemaining.Num() > 0)
		{
			OutTimeRemaining = TimeRemaining[0];
			return true;
		}
	}

	return false;
}

bool ACA_PlayerCharacter::GetCooldownDurationForTag(const FGameplayTagContainer CooldownTags, float& OutDuration)
{
	if (AbilitySystemComponent.IsValid() && CooldownTags.Num() > 0)
	{
		OutDuration = 0.f;

		FGameplayEffectQuery const Query = FGameplayEffectQuery::MakeQuery_MatchAnyOwningTags(CooldownTags);
		TArray<float>  Duration = AbilitySystemComponent->GetActiveEffectsDuration(Query);

		if (Duration.Num() > 0)
		{
			OutDuration = Duration[0];
			return true;
		}
	}

	return false;
}

#pragma endregion

#pragma region Experience
float ACA_PlayerCharacter::GetExperience() const
{
	return ExperienceAttributeSet->GetExperience();
}

void ACA_PlayerCharacter::SetExperience(const float& NewExperience) const
{
	ExperienceAttributeSet->SetExperience(NewExperience);
}

float ACA_PlayerCharacter::GetMaxExperience() const
{
	return ExperienceAttributeSet->GetMaxExperience();
}

void ACA_PlayerCharacter::SetMaxExperience(const float& NewMaxExperience) const
{
	ExperienceAttributeSet->SetMaxExperience(NewMaxExperience);
}
#pragma endregion