#include "Character/CA_CharacterBase.h"

// Sets default values
ACA_CharacterBase::ACA_CharacterBase()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

UAbilitySystemComponent* ACA_CharacterBase::GetAbilitySystemComponent() const
{
	return nullptr;
}

// Called when the game starts or when spawned
void ACA_CharacterBase::BeginPlay()
{
	Super::BeginPlay();
	
}

void ACA_CharacterBase::ApplyDamage(float Damage, CA_DamageType Type)
{
	const float mitigatedDamage = CalculateMitigatedDamage(Damage, Type);

	SetHealth(GetHealth() - mitigatedDamage);//TODO Death routine
}

float ACA_CharacterBase::CalculateMitigatedDamage(float Damage, CA_DamageType Type) const
{
	float mitigatedDamage = Damage - GetDefense();
	if(Type == CA_DamageType::Physical)
	{
		mitigatedDamage -= mitigatedDamage * GetPhysicalResistance();
	}
	else
	{
		mitigatedDamage -= mitigatedDamage * GetMagicalResistance();
	}

	mitigatedDamage = FMath::Max(mitigatedDamage, 0.0f); //To Avoid negative damage

	return mitigatedDamage;
}

// Called every frame
void ACA_CharacterBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ACA_CharacterBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

float ACA_CharacterBase::GetPhysicalDamage() const
{
	return CombatAttributeSet->GetPhysicalDamage();
}

void ACA_CharacterBase::SetPhysicalDamage(const float &NewPhysicalDamage) const
{
	CombatAttributeSet->SetPhysicalDamage(NewPhysicalDamage);
}

float ACA_CharacterBase::GetMagicalDamage() const
{
	return CombatAttributeSet->GetMagicalDamage();
}

void ACA_CharacterBase::SetMagicalDamage(const float& NewMagicalDamage) const
{
	CombatAttributeSet->SetMagicalDamage(NewMagicalDamage);
}

float ACA_CharacterBase::GetPhysicalResistance() const
{
	return CombatAttributeSet->GetPhysicalResistance();
}

void ACA_CharacterBase::SetPhysicalResistance(const float& NewPhysicalResistance) const
{
	CombatAttributeSet->SetPhysicalResistance(NewPhysicalResistance);
}

float ACA_CharacterBase::GetMagicalResistance() const
{
	return CombatAttributeSet->GetMagicalResistance();
}

void ACA_CharacterBase::SetMagicalResistance(const float& NewMagicalResistance) const
{
	CombatAttributeSet->SetMagicalResistance(NewMagicalResistance);
}

float ACA_CharacterBase::GetDefense() const
{
	return CombatAttributeSet->GetDefense();
}

void ACA_CharacterBase::SetDefense(const float& NewDefense) const
{
	CombatAttributeSet->SetDefense(NewDefense);
}

float ACA_CharacterBase::GetHealth() const
{
	return HealthAttributeSet->GetHealth();
}

void ACA_CharacterBase::SetHealth(const float& NewHealth) const
{
	HealthAttributeSet->SetHealth(NewHealth);
}

float ACA_CharacterBase::GetMaxHealth() const
{
	return HealthAttributeSet->GetMaxHealth();
}

void ACA_CharacterBase::SetMaxHealth(const float& NewMaxHealth) const
{
	HealthAttributeSet->SetMaxHealth(NewMaxHealth);
}

float ACA_CharacterBase::GetHealthRegen() const
{
	return HealthAttributeSet->GetHealthRegen();
}

void ACA_CharacterBase::SetHealthRegen(const float& NewHealthRegen) const
{
	HealthAttributeSet->SetHealthRegen(NewHealthRegen);
}

float ACA_CharacterBase::GetMoveSpeed() const
{
	return MovementAttributeSet->GetMoveSpeed();
}

void ACA_CharacterBase::SetMoveSpeed(const float& NewMoveSpeed) const
{
	MovementAttributeSet->SetMoveSpeed(NewMoveSpeed);
}

float ACA_CharacterBase::GetJumpHeight() const
{
	return MovementAttributeSet->GetJumpHeight();
}

void ACA_CharacterBase::SetJumpHeight(const float& NewJumpHeight) const
{
	MovementAttributeSet->SetJumpHeight(NewJumpHeight);
}

float ACA_CharacterBase::GetBaseVitality() const
{
	return RPGStatsAttributeSet->GetBaseVitality();
}

void ACA_CharacterBase::SetBaseVitality(const float& NewBaseVitality) const
{
	RPGStatsAttributeSet->SetBaseVitality(NewBaseVitality);
}

float ACA_CharacterBase::GetVitality() const
{
	return RPGStatsAttributeSet->GetVitality();
}

void ACA_CharacterBase::SetVitality(const float& NewVitality) const
{
	RPGStatsAttributeSet->SetVitality(NewVitality);
}

float ACA_CharacterBase::GetBaseStrength() const
{
	return RPGStatsAttributeSet->GetBaseStrength();
}

void ACA_CharacterBase::SetBaseStrength(const float& NewBaseStrength) const
{
	RPGStatsAttributeSet->SetBaseStrength(NewBaseStrength);
}

float ACA_CharacterBase::GetStrength() const
{
	return RPGStatsAttributeSet->GetStrength();
}

void ACA_CharacterBase::SetStrength(const float& NewStrength) const
{
	RPGStatsAttributeSet->SetStrength(NewStrength);
}

float ACA_CharacterBase::GetBaseIntelligence() const
{
	return RPGStatsAttributeSet->GetBaseIntelligence();
}

void ACA_CharacterBase::SetBaseIntelligence(const float& NewBaseIntelligence) const
{
	RPGStatsAttributeSet->SetBaseIntelligence(NewBaseIntelligence);
}

float ACA_CharacterBase::GetIntelligence() const
{
	return RPGStatsAttributeSet->GetIntelligence();
}

void ACA_CharacterBase::SetIntelligence(const float& NewIntelligence) const
{
	RPGStatsAttributeSet->SetIntelligence(NewIntelligence);
}

float ACA_CharacterBase::GetBaseAgility() const
{
	return RPGStatsAttributeSet->GetBaseAgility();
}

void ACA_CharacterBase::SetBaseAgility(const float& NewBaseAgility) const
{
	RPGStatsAttributeSet->SetBaseAgility(NewBaseAgility);
}

float ACA_CharacterBase::GetAgility() const
{
	return RPGStatsAttributeSet->GetAgility();
}

void ACA_CharacterBase::SetAgility(const float& NewAgility) const
{
	RPGStatsAttributeSet->SetAgility(NewAgility);
}

float ACA_CharacterBase::GetBaseEndurance() const
{
	return RPGStatsAttributeSet->GetBaseEndurance();
}

void ACA_CharacterBase::SetBaseEndurance(const float& NewBaseEndurance) const
{
	RPGStatsAttributeSet->SetBaseEndurance(NewBaseEndurance);
}

float ACA_CharacterBase::GetEndurance() const
{
	return RPGStatsAttributeSet->GetEndurance();
}

void ACA_CharacterBase::SetEndurance(const float& NewEndurance) const
{
	RPGStatsAttributeSet->SetEndurance(NewEndurance);
}

float ACA_CharacterBase::GetCharacterLevel() const
{
	return RPGStatsAttributeSet->GetLevel();
}

void ACA_CharacterBase::SetCharacterLevel(const float& NewLevel) const
{
	RPGStatsAttributeSet->SetLevel(NewLevel);
}

void ACA_CharacterBase::LevelUp() const
{
	float Level = GetCharacterLevel()+1;
	SetCharacterLevel(Level);
	//TODO Update Stats
}
