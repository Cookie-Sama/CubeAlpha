#include "Character/Player/CA_ManaPlayerCharacter.h"

ACA_ManaPlayerCharacter::ACA_ManaPlayerCharacter(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer.SetDefaultSubobjectClass<UCharacterMovementComponent>(ACharacter::CharacterMovementComponentName))
{
	ManaAttributeSet = CreateDefaultSubobject<UCA_ManaAttributeSet>("Mana Attribute Set");
}

void ACA_ManaPlayerCharacter::RegenMana() const
{
	if (bIsManaDelayActive)
	{
		return;
	}
	else {
		if (GetMana() < GetMaxMana())
		{
			const float Mana = GetMana() + GetManaRegen();
			SetMana(FMath::Min(Mana, GetMaxMana()));
		}
	}
}

void ACA_ManaPlayerCharacter::BeginPlay()
{
	Super::BeginPlay();

	if (AbilitySystemComponent)
	{
		ManaChangedDelegateHandle = AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(ManaAttributeSet->GetManaAttribute()).AddUObject(this, &ACA_ManaPlayerCharacter::ManaChanged);
		MaxManaChangedDelegateHandle = AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(ManaAttributeSet->GetMaxManaAttribute()).AddUObject(this, &ACA_ManaPlayerCharacter::MaxManaChanged);
		ManaRegenChangedDelegateHandle = AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(ManaAttributeSet->GetManaRegenAttribute()).AddUObject(this, &ACA_ManaPlayerCharacter::ManaRegenChanged);
	}
	SetMaxMana(100); // Max Mana will always be 100
	SetMana(GetMaxMana());
	SetManaRegen(5.0f);
}

void ACA_ManaPlayerCharacter::DisableManaDelay()
{
	bIsManaDelayActive = false;
}

float ACA_ManaPlayerCharacter::GetMana() const
{
	return ManaAttributeSet->GetMana();
}

void ACA_ManaPlayerCharacter::SetMana(float NewMana) const
{
	ManaAttributeSet->SetMana(NewMana);
}

float ACA_ManaPlayerCharacter::GetMaxMana() const
{
	return ManaAttributeSet->GetMaxMana();
}

void ACA_ManaPlayerCharacter::SetMaxMana(float NewMaxMana) const
{
	ManaAttributeSet->SetMaxMana(NewMaxMana);
}

float ACA_ManaPlayerCharacter::GetManaRegen() const
{
	return ManaAttributeSet->GetManaRegen();
}

void ACA_ManaPlayerCharacter::SetManaRegen(float NewManaRegen) const
{
	ManaAttributeSet->SetManaRegen(NewManaRegen);
}

void ACA_ManaPlayerCharacter::ManaChanged(const FOnAttributeChangeData& Data)
{
	OnManaChanged.Broadcast(GetMana(), GetMaxMana());
	if(Data.NewValue<Data.OldValue)
	{
		bIsManaDelayActive = true;

		// Désactiver le délai après 2 secondes
		GetWorldTimerManager().SetTimer(ManaDelayTimerHandle, this, &ACA_ManaPlayerCharacter::DisableManaDelay, 2.0f, false);
	}
}

void ACA_ManaPlayerCharacter::MaxManaChanged(const FOnAttributeChangeData& Data)
{
	OnMaxManaChanged.Broadcast(GetMana(), GetMaxMana());
}

void ACA_ManaPlayerCharacter::ManaRegenChanged(const FOnAttributeChangeData& Data)
{
	if (GetManaRegen() > 0)
	{
		if (!GetWorldTimerManager().IsTimerActive(ManaRegenTimerHandle))
		{
			GetWorldTimerManager().SetTimer(ManaRegenTimerHandle, this, &ACA_ManaPlayerCharacter::RegenMana, 1, true);
		}
	}
	else
	{
		GetWorldTimerManager().ClearTimer(ManaRegenTimerHandle);
	}

	OnManaRegenChanged.Broadcast(GetManaRegen());
}

void ACA_ManaPlayerCharacter::LevelUpStats() const
{
	Super::LevelUpStats();

	SetMana(GetMaxMana());
}
