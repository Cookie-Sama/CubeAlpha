#include "System/CA_PlayerState.h"
#include "CA_AbilitySystemComponent.h"
#include "CA_CombatAttributeSet.h"
#include "CA_HealthAttributeSet.h"
#include "CA_MovementAttributeSet.h"
#include "CA_RPGStatsAttributeSet.h"

ACA_PlayerState::ACA_PlayerState()
{
	AbilitySystemComponent = CreateDefaultSubobject<UCA_AbilitySystemComponent>("AbilitySystemComp");
	AbilitySystemComponent->SetIsReplicated(true);
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Mixed);

	CombatAttributeSet = CreateDefaultSubobject<UCA_CombatAttributeSet>("Combat Attribute Set");
	HealthAttributeSet = CreateDefaultSubobject<UCA_HealthAttributeSet>("Health Attribute Set");
	MovementAttributeSet = CreateDefaultSubobject<UCA_MovementAttributeSet>("Movement Attribute Set");
	RPGStatsAttributeSet = CreateDefaultSubobject<UCA_RPGStatsAttributeSet>("RPG Stats Attribute Set");

	NetUpdateFrequency = 100.0f;

	DeadTag = FGameplayTag::RequestGameplayTag("State.Dead");
}

UAbilitySystemComponent* ACA_PlayerState::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

UCA_CombatAttributeSet* ACA_PlayerState::GetCombatAttributeSet()
{
	return CombatAttributeSet;
}

UCA_HealthAttributeSet* ACA_PlayerState::GetHealthAttributeSet()
{
	return HealthAttributeSet;
}

UCA_MovementAttributeSet* ACA_PlayerState::GetMovementAttributeSet()
{
	return MovementAttributeSet;
}

UCA_RPGStatsAttributeSet* ACA_PlayerState::GetRPGStatsAttributeSet()
{
	return RPGStatsAttributeSet;
}

bool ACA_PlayerState::IsAlive() const
{
	return GetHealth() > 0.0f;
}

void ACA_PlayerState::ShowAbilityConfirmCancelText(bool ShowText)
{
	//TODO Later when HUD
}

#pragma region AttributeSetGetters
float ACA_PlayerState::GetPhysicalDamage() const
{
	return CombatAttributeSet->GetPhysicalDamage();
}

float ACA_PlayerState::GetMagicalDamage() const
{
	return CombatAttributeSet->GetMagicalDamage();
}

float ACA_PlayerState::GetPhysicalResistance() const
{
	return CombatAttributeSet->GetPhysicalResistance();
}

float ACA_PlayerState::GetMagicalResistance() const
{
	return CombatAttributeSet->GetMagicalResistance();
}

float ACA_PlayerState::GetDefense() const
{
	return CombatAttributeSet->GetDefense();
}

float ACA_PlayerState::GetHealth() const
{
	return HealthAttributeSet->GetHealth();
}

float ACA_PlayerState::GetMaxHealth() const
{
	return HealthAttributeSet->GetMaxHealth();
}

float ACA_PlayerState::GetHealthRegen() const
{
	return HealthAttributeSet->GetHealthRegen();
}

float ACA_PlayerState::GetMoveSpeed() const
{
	return MovementAttributeSet->GetMoveSpeed();
}

float ACA_PlayerState::GetJumpHeight() const
{
	return MovementAttributeSet->GetJumpHeight();
}

float ACA_PlayerState::GetStamina() const
{
	return MovementAttributeSet->GetStamina();
}

float ACA_PlayerState::GetMaxStamina() const
{
	return MovementAttributeSet->GetMaxStamina();
}

float ACA_PlayerState::GetBaseVitality() const
{
	return RPGStatsAttributeSet->GetBaseVitality();
}

float ACA_PlayerState::GetVitality() const
{
	return RPGStatsAttributeSet->GetVitality();
}

float ACA_PlayerState::GetBaseStrength() const
{
	return RPGStatsAttributeSet->GetBaseStrength();
}

float ACA_PlayerState::GetStrength() const
{
	return RPGStatsAttributeSet->GetStrength();
}

float ACA_PlayerState::GetBaseIntelligence() const
{
	return RPGStatsAttributeSet->GetBaseIntelligence();
}

float ACA_PlayerState::GetIntelligence() const
{
	return RPGStatsAttributeSet->GetIntelligence();
}

float ACA_PlayerState::GetBaseAgility() const
{
	return RPGStatsAttributeSet->GetBaseAgility();
}

float ACA_PlayerState::GetAgility() const
{
	return RPGStatsAttributeSet->GetAgility();
}

float ACA_PlayerState::GetBaseEndurance() const
{
	return RPGStatsAttributeSet->GetBaseEndurance();
}

float ACA_PlayerState::GetEndurance() const
{
	return RPGStatsAttributeSet->GetEndurance();
}

float ACA_PlayerState::GetCharacterLevel() const
{
	return RPGStatsAttributeSet->GetLevel();
}
#pragma endregion

void ACA_PlayerState::BeginPlay()
{
	Super::BeginPlay();

	if(AbilitySystemComponent)
	{
		PhysicalDamageChangedDelegateHandle = AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(CombatAttributeSet->GetPhysicalDamageAttribute()).AddUObject(this, &ACA_PlayerState::PhysicalDamageChanged);
		MagicalDamageChangedDelegateHandle = AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(CombatAttributeSet->GetMagicalDamageAttribute()).AddUObject(this, &ACA_PlayerState::MagicalDamageChanged);
		PhysicalResistanceChangedDelegateHandle = AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(CombatAttributeSet->GetPhysicalResistanceAttribute()).AddUObject(this, &ACA_PlayerState::PhysicalResistanceChanged);
		PhysicalResistanceChangedDelegateHandle = AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(CombatAttributeSet->GetMagicalResistanceAttribute()).AddUObject(this, &ACA_PlayerState::MagicalResistanceChanged);
		DefenseChangedDelegateHandle = AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(CombatAttributeSet->GetDefenseAttribute()).AddUObject(this, &ACA_PlayerState::DefenseChanged);

		HealthChangedDelegateHandle = AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(HealthAttributeSet->GetHealthAttribute()).AddUObject(this, &ACA_PlayerState::HealthChanged);
		MaxHealthChangedDelegateHandle = AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(HealthAttributeSet->GetMaxHealthAttribute()).AddUObject(this, &ACA_PlayerState::MaxHealthChanged);
		HealthRegenChangedDelegateHandle = AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(HealthAttributeSet->GetHealthRegenAttribute()).AddUObject(this, &ACA_PlayerState::HealthRegenChanged);

		MoveSpeedChangedDelegateHandle = AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(MovementAttributeSet->GetMoveSpeedAttribute()).AddUObject(this, &ACA_PlayerState::MoveSpeedChanged);
		JumpHeightChangedDelegateHandle = AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(MovementAttributeSet->GetJumpHeightAttribute()).AddUObject(this, &ACA_PlayerState::JumpHeightChanged);
		StaminaChangedDelegateHandle = AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(MovementAttributeSet->GetStaminaAttribute()).AddUObject(this, &ACA_PlayerState::StaminaChanged);
		MaxStaminaChangedDelegateHandle = AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(MovementAttributeSet->GetMaxStaminaAttribute()).AddUObject(this, &ACA_PlayerState::MaxStaminaChanged);

		BaseVitalityChangedDelegateHandle = AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(RPGStatsAttributeSet->GetBaseVitalityAttribute()).AddUObject(this, &ACA_PlayerState::BaseVitalityChanged);
		VitalityChangedDelegateHandle = AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(RPGStatsAttributeSet->GetVitalityAttribute()).AddUObject(this, &ACA_PlayerState::VitalityChanged);
		BaseStrengthChangedDelegateHandle = AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(RPGStatsAttributeSet->GetBaseStrengthAttribute()).AddUObject(this, &ACA_PlayerState::BaseStrengthChanged);
		StrengthChangedDelegateHandle = AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(RPGStatsAttributeSet->GetStrengthAttribute()).AddUObject(this, &ACA_PlayerState::StrengthChanged);
		BaseIntelligenceChangedDelegateHandle = AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(RPGStatsAttributeSet->GetBaseIntelligenceAttribute()).AddUObject(this, &ACA_PlayerState::BaseIntelligenceChanged);
		IntelligenceChangedDelegateHandle = AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(RPGStatsAttributeSet->GetIntelligenceAttribute()).AddUObject(this, &ACA_PlayerState::IntelligenceChanged);
		BaseAgilityChangedDelegateHandle = AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(RPGStatsAttributeSet->GetBaseAgilityAttribute()).AddUObject(this, &ACA_PlayerState::BaseAgilityChanged);
		AgilityChangedDelegateHandle = AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(RPGStatsAttributeSet->GetAgilityAttribute()).AddUObject(this, &ACA_PlayerState::AgilityChanged);
		BaseEnduranceChangedDelegateHandle = AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(RPGStatsAttributeSet->GetBaseEnduranceAttribute()).AddUObject(this, &ACA_PlayerState::BaseEnduranceChanged);
		EnduranceChangedDelegateHandle = AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(RPGStatsAttributeSet->GetEnduranceAttribute()).AddUObject(this, &ACA_PlayerState::EnduranceChanged);
		CharacterLevelChangedDelegateHandle = AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(RPGStatsAttributeSet->GetLevelAttribute()).AddUObject(this, &ACA_PlayerState::CharacterLevelChanged);
	}
}

void ACA_PlayerState::PhysicalDamageChanged(const FOnAttributeChangeData& Data)
{
}

void ACA_PlayerState::MagicalDamageChanged(const FOnAttributeChangeData& Data)
{
}

void ACA_PlayerState::PhysicalResistanceChanged(const FOnAttributeChangeData& Data)
{
}

void ACA_PlayerState::MagicalResistanceChanged(const FOnAttributeChangeData& Data)
{
}

void ACA_PlayerState::DefenseChanged(const FOnAttributeChangeData& Data)
{
}

void ACA_PlayerState::HealthChanged(const FOnAttributeChangeData& Data)
{
}

void ACA_PlayerState::MaxHealthChanged(const FOnAttributeChangeData& Data)
{
}

void ACA_PlayerState::HealthRegenChanged(const FOnAttributeChangeData& Data)
{
}

void ACA_PlayerState::MoveSpeedChanged(const FOnAttributeChangeData& Data)
{
}

void ACA_PlayerState::JumpHeightChanged(const FOnAttributeChangeData& Data)
{
}

void ACA_PlayerState::StaminaChanged(const FOnAttributeChangeData& Data)
{
}

void ACA_PlayerState::MaxStaminaChanged(const FOnAttributeChangeData& Data)
{
}

void ACA_PlayerState::BaseVitalityChanged(const FOnAttributeChangeData& Data)
{
}

void ACA_PlayerState::VitalityChanged(const FOnAttributeChangeData& Data)
{
}

void ACA_PlayerState::BaseStrengthChanged(const FOnAttributeChangeData& Data)
{
}

void ACA_PlayerState::StrengthChanged(const FOnAttributeChangeData& Data)
{
}

void ACA_PlayerState::BaseIntelligenceChanged(const FOnAttributeChangeData& Data)
{
}

void ACA_PlayerState::IntelligenceChanged(const FOnAttributeChangeData& Data)
{
}

void ACA_PlayerState::BaseAgilityChanged(const FOnAttributeChangeData& Data)
{
}

void ACA_PlayerState::AgilityChanged(const FOnAttributeChangeData& Data)
{
}

void ACA_PlayerState::BaseEnduranceChanged(const FOnAttributeChangeData& Data)
{
}

void ACA_PlayerState::EnduranceChanged(const FOnAttributeChangeData& Data)
{
}

void ACA_PlayerState::CharacterLevelChanged(const FOnAttributeChangeData& Data)
{
}
