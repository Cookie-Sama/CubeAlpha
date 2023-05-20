#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AbilitySystemInterface.h"
#include "CubeAlpha.h"
#include "CA_GameplayAbility.h"
#include "GameplayTagContainer.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "CA_CharacterBase.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FCharacterDiedDelegate, ACA_CharacterBase*, Character);

UCLASS()
class CUBEALPHA_API ACA_CharacterBase : public ACharacter, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ACA_CharacterBase(const class FObjectInitializer& ObjectInitializer);

#pragma region DeathMechanic
	UPROPERTY(BlueprintAssignable, Category = "CubeAlpha|Character")
	FCharacterDiedDelegate OnCharacterDied;

	UFUNCTION(BluePrintCallable, Category = "CubeAlpha|Character")
		virtual bool IsAlive() const;

	UFUNCTION(BluePrintCallable, Category = "CubeAlpha|Character")
		virtual int32 GetAbilityLevel(CA_AbilityID AbilityID) const;

	virtual void RemoveCharacterAbilities();

	UFUNCTION(BlueprintCallable)
	virtual void Die();

	UFUNCTION(BlueprintCallable, Category="CubeAlpha|Character")
	virtual void FinishDying();

	FGameplayTag DeadTag;
	FGameplayTag EffectRemoveOnDeathTag;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "CubeAlpha|Character")
		FText CharacterName;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "CubeAlpha|Animation")
		UAnimMontage* DeathMontage;

private:
	UFUNCTION(NetMulticast, Reliable)
	void MulticastRPCPlayDeathAnimation();
	void MulticastRPCPlayDeathAnimation_Implementation() { PlayAnimMontage(DeathMontage); }

#pragma endregion

public:
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "DivineAscension|Abilities")
		TArray<TSubclassOf<class UCA_GameplayAbility>> CharacterAbilities;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "CubeAlpha|Abilities")
		TSubclassOf<class UGameplayEffect> DefaultAttributes;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "CubeAlpha|Abilities")
		TArray<TSubclassOf<class UGameplayEffect>> StartupEffects;

	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;

	virtual void AddCharacterAbilities();
	virtual void InitializeAttributes();
	virtual void AddStartupEffects();

	virtual void SpeedDownTagChanged(const FGameplayTag CallbackTag, int32 NewCount);

	virtual void SpeedBoostTagChanged(const FGameplayTag CallbackTag, int32 NewCount);

	virtual void StunTagChanged(const FGameplayTag CallbackTag, int32 NewCount);

	UFUNCTION(BlueprintNativeEvent)
		void OnActiveGameplayEffectAddedCallback(UAbilitySystemComponent* Target, const FGameplayEffectSpec& SpecApplied, FActiveGameplayEffectHandle ActiveHandle);
	virtual void OnActiveGameplayEffectAddedCallback_Implementation(UAbilitySystemComponent* Target, const FGameplayEffectSpec& SpecApplied, FActiveGameplayEffectHandle ActiveHandle) {};
	UFUNCTION(BlueprintNativeEvent)
		void OnRemoveGameplayEffectCallback(const FActiveGameplayEffect& EffectRemoved);
	virtual void OnRemoveGameplayEffectCallback_Implementation(const FActiveGameplayEffect& EffectRemoved) {};

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Abilities", meta = (AllowPrivateAccess = "true"))
	TWeakObjectPtr<class UCA_AbilitySystemComponent> AbilitySystemComponent;

	virtual void ApplyDamage(float Damage, CA_DamageType Type);
	float CalculateMitigatedDamage(float Damage, CA_DamageType Type) const;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
		UDataTable* StatsDataTable;

#pragma region AttributeSet
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "CubeAlpha|Character|AttributeSet")
	TWeakObjectPtr<class UCA_CombatAttributeSet> CombatAttributeSet;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "CubeAlpha|Character|AttributeSet")
	TWeakObjectPtr<class UCA_HealthAttributeSet> HealthAttributeSet;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "CubeAlpha|Character|AttributeSet")
	TWeakObjectPtr<class UCA_MovementAttributeSet> MovementAttributeSet;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "CubeAlpha|Character|AttributeSet")
	TWeakObjectPtr<class UCA_RPGStatsAttributeSet> RPGStatsAttributeSet;
#pragma endregion

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

#pragma region AttributeSetGetterSetters
	UFUNCTION(BlueprintCallable, Category = "CubeAlpha|Character|Attributes")
	float GetPhysicalDamage() const;
	UFUNCTION(BlueprintCallable, Category = "CubeAlpha|Character|Attributes")
	void SetPhysicalDamage(const float &NewPhysicalDamage) const;
	UFUNCTION(BlueprintCallable, Category = "CubeAlpha|Character|Attributes")
	float GetMagicalDamage() const;
	UFUNCTION(BlueprintCallable, Category = "CubeAlpha|Character|Attributes")
	void SetMagicalDamage(const float &NewMagicalDamage) const;
	UFUNCTION(BlueprintCallable, Category = "CubeAlpha|Character|Attributes")
	float GetPhysicalResistance() const;
	UFUNCTION(BlueprintCallable, Category = "CubeAlpha|Character|Attributes")
	void SetPhysicalResistance(const float &NewPhysicalResistance) const;
	UFUNCTION(BlueprintCallable, Category = "CubeAlpha|Character|Attributes")
	float GetMagicalResistance() const;
	UFUNCTION(BlueprintCallable, Category = "CubeAlpha|Character|Attributes")
	void SetMagicalResistance(const float &NewMagicalResistance) const;
	UFUNCTION(BlueprintCallable, Category = "CubeAlpha|Character|Attributes")
	float GetDefense() const;
	UFUNCTION(BlueprintCallable, Category = "CubeAlpha|Character|Attributes")
	void SetDefense(const float &NewDefense) const;
	UFUNCTION(BlueprintCallable, Category = "CubeAlpha|Character|Attributes")
	float GetHealth() const;
	UFUNCTION(BlueprintCallable, Category = "CubeAlpha|Character|Attributes")
	void SetHealth(const float &NewHealth) const;
	UFUNCTION(BlueprintCallable, Category = "CubeAlpha|Character|Attributes")
	float GetMaxHealth() const;
	UFUNCTION(BlueprintCallable, Category = "CubeAlpha|Character|Attributes")
	void SetMaxHealth(const float &NewMaxHealth) const;
	UFUNCTION(BlueprintCallable, Category = "CubeAlpha|Character|Attributes")
	float GetHealthRegen() const;
	UFUNCTION(BlueprintCallable, Category = "CubeAlpha|Character|Attributes")
	void SetHealthRegen(const float &NewHealthRegen) const;
	UFUNCTION(BlueprintCallable, Category = "CubeAlpha|Character|Attributes")
	float GetMoveSpeed() const;
	UFUNCTION(BlueprintCallable, Category = "CubeAlpha|Character|Attributes")
	void SetMoveSpeed(const float& NewMoveSpeed) const;
	UFUNCTION(BlueprintCallable, Category = "CubeAlpha|Character|Attributes")
	float GetJumpHeight() const;
	UFUNCTION(BlueprintCallable, Category = "CubeAlpha|Character|Attributes")
	void SetJumpHeight(const float& NewJumpHeight) const;
	UFUNCTION(BlueprintCallable, Category = "CubeAlpha|Character|Attributes")
	float GetStamina()const;
	UFUNCTION(BlueprintCallable, Category = "CubeAlpha|Character|Attributes")
	void SetStamina(const float& NewStamina) const;
	UFUNCTION(BlueprintCallable, Category = "CubeAlpha|Character|Attributes")
	float GetMaxStamina()const;
	UFUNCTION(BlueprintCallable, Category = "CubeAlpha|Character|Attributes")
	void SetMaxStamina(const float& NewMaxStamina) const;
	UFUNCTION(BlueprintCallable, Category = "CubeAlpha|Character|Attributes")
	float GetBaseVitality() const;
	UFUNCTION(BlueprintCallable, Category = "CubeAlpha|Character|Attributes")
	void SetBaseVitality(const float& NewBaseVitality) const;
	UFUNCTION(BlueprintCallable, Category = "CubeAlpha|Character|Attributes")
	float GetVitality() const;
	UFUNCTION(BlueprintCallable, Category = "CubeAlpha|Character|Attributes")
	void SetVitality(const float& NewVitality) const;
	UFUNCTION(BlueprintCallable, Category = "CubeAlpha|Character|Attributes")
	float GetBaseStrength() const;
	UFUNCTION(BlueprintCallable, Category = "CubeAlpha|Character|Attributes")
	void SetBaseStrength(const float& NewBaseStrength) const;
	UFUNCTION(BlueprintCallable, Category = "CubeAlpha|Character|Attributes")
	float GetStrength() const;
	UFUNCTION(BlueprintCallable, Category = "CubeAlpha|Character|Attributes")
	void SetStrength(const float& NewStrength) const;
	UFUNCTION(BlueprintCallable, Category = "CubeAlpha|Character|Attributes")
	float GetBaseIntelligence() const;
	UFUNCTION(BlueprintCallable, Category = "CubeAlpha|Character|Attributes")
	void SetBaseIntelligence(const float& NewBaseIntelligence) const;
	UFUNCTION(BlueprintCallable, Category = "CubeAlpha|Character|Attributes")
	float GetIntelligence() const;
	UFUNCTION(BlueprintCallable, Category = "CubeAlpha|Character|Attributes")
	void SetIntelligence(const float& NewIntelligence) const;
	UFUNCTION(BlueprintCallable, Category = "CubeAlpha|Character|Attributes")
	float GetBaseAgility() const;
	UFUNCTION(BlueprintCallable, Category = "CubeAlpha|Character|Attributes")
	void SetBaseAgility(const float& NewBaseAgility) const;
	UFUNCTION(BlueprintCallable, Category = "CubeAlpha|Character|Attributes")
	float GetAgility() const;
	UFUNCTION(BlueprintCallable, Category = "CubeAlpha|Character|Attributes")
	void SetAgility(const float& NewAgility) const;
	UFUNCTION(BlueprintCallable, Category = "CubeAlpha|Character|Attributes")
	float GetBaseEndurance() const;
	UFUNCTION(BlueprintCallable, Category = "CubeAlpha|Character|Attributes")
	void SetBaseEndurance(const float& NewBaseEndurance) const;
	UFUNCTION(BlueprintCallable, Category = "CubeAlpha|Character|Attributes")
	float GetEndurance() const;
	UFUNCTION(BlueprintCallable, Category = "CubeAlpha|Character|Attributes")
	void SetEndurance(const float& NewEndurance) const;
	UFUNCTION(BlueprintCallable, Category = "CubeAlpha|Character|Attributes")
	float GetCharacterLevel() const;
	UFUNCTION(BlueprintCallable, Category = "CubeAlpha|Character|Attributes")
	void SetCharacterLevel(const float& NewLevel) const;

#pragma endregion

	UFUNCTION(BlueprintCallable, Category = "CubeAlpha|Character|Attributes")
		void LevelUp() const;
};
