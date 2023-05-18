#include "Character/Player/CA_PlayerCharacter.h"

ACA_PlayerCharacter::ACA_PlayerCharacter(const class FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer.SetDefaultSubobjectClass<UCharacterMovementComponent>(ACharacter::CharacterMovementComponentName))
{
}

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
