// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/CA_CharacterBase.h"

// Sets default values
ACA_CharacterBase::ACA_CharacterBase()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ACA_CharacterBase::BeginPlay()
{
	Super::BeginPlay();
	
}

void ACA_CharacterBase::ApplyDamage(float Damage, DamageType Type)
{

}

float ACA_CharacterBase::CalculateMitigatedDamage(float Damage, DamageType Type)
{
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