// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AbilitySystemInterface.h"
#include "CubeAlpha.h"
#include "CA_CombatAttributeSet.h"
#include "CA_HealthAttributeSet.h"
#include "CA_MovementAttributeSet.h"
#include "CA_RPGStatsAttributeSet.h"
#include "CA_CharacterBase.generated.h"

UCLASS()
class CUBEALPHA_API ACA_CharacterBase : public ACharacter, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ACA_CharacterBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void ApplyDamage(float Damage, DamageType Type);
	float CalculateMitigatedDamage(float Damage, DamageType Type);

#pragma region AttributeSet
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "CubeAlpha|Character|AttributeSet")
	UCA_CombatAttributeSet* CombatAttributeSet;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "CubeAlpha|Character|AttributeSet")
	UCA_HealthAttributeSet* HealthAttributeSet;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "CubeAlpha|Character|AttributeSet")
	UCA_MovementAttributeSet* MovementAttributeSet;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "CubeAlpha|Character|AttributeSet")
	UCA_RPGStatsAttributeSet* RPGStatsAttributeSet;
#pragma endregion

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
#pragma region AttributeSetGetterSetters
	float GetPhysicalDamage() const;
	void SetPhysicalDamage(const float &NewPhysicalDamage) const;

	float GetMagicalDamage() const;
	void SetMagicalDamage(const float &NewMagicalDamage) const;

	float GetPhysicalResistance() const;
	void SetPhysicalResistance(const float& NewPhysicalResistance) const;

	float GetMagicalResistance() const;
	void SetMagicalResistance(const float& NewMagicalResistance) const;

	float GetDefense() const;
	void SetDefense(const float& NewDefense) const;

	float GetHealth() const;
	void SetHealth(const float& NewHealth) const;

	float GetMaxHealth() const;
	void SetMaxHealth(const float& NewMaxHealth) const;

	float GetHealthRegen() const;
	void SetHealthRegen(const float& NewHealthRegen) const;
#pragma endregion
};
