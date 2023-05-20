#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "GameFramework/PlayerState.h"
#include "GameplayEffectTypes.h"
#include "CA_PlayerState.generated.h"

UCLASS()
class CUBEALPHA_API ACA_PlayerState : public APlayerState, public IAbilitySystemInterface
{
	GENERATED_BODY()
public:
	ACA_PlayerState();

	virtual class UAbilitySystemComponent* GetAbilitySystemComponent() const override;

	class UCA_CombatAttributeSet* GetCombatAttributeSet();

	class UCA_HealthAttributeSet* GetHealthAttributeSet();

	class UCA_MovementAttributeSet* GetMovementAttributeSet();

	class UCA_RPGStatsAttributeSet* GetRPGStatsAttributeSet();

	UFUNCTION(BlueprintCallable, Category = "CubeAlpha|PlayerState")
	bool IsAlive() const;

	UFUNCTION(BlueprintCallable, Category = "CubeAlpha|PlayerState")
	void ShowAbilityConfirmCancelText(bool ShowText);

#pragma region AttributeSetGetters
	UFUNCTION(BlueprintCallable, Category = "CubeAlpha|PlayerState|Attributes")
		float GetPhysicalDamage() const;
	UFUNCTION(BlueprintCallable, Category = "CubeAlpha|PlayerState|Attributes")
		float GetMagicalDamage() const;
	UFUNCTION(BlueprintCallable, Category = "CubeAlpha|PlayerState|Attributes")
		float GetPhysicalResistance() const;
	UFUNCTION(BlueprintCallable, Category = "CubeAlpha|PlayerState|Attributes")
		float GetMagicalResistance() const;
	UFUNCTION(BlueprintCallable, Category = "CubeAlpha|PlayerState|Attributes")
		float GetDefense() const;
	UFUNCTION(BlueprintCallable, Category = "CubeAlpha|PlayerState|Attributes")
		float GetHealth() const;
	UFUNCTION(BlueprintCallable, Category = "CubeAlpha|PlayerState|Attributes")
		float GetMaxHealth() const;
	UFUNCTION(BlueprintCallable, Category = "CubeAlpha|PlayerState|Attributes")
		float GetHealthRegen() const;
	UFUNCTION(BlueprintCallable, Category = "CubeAlpha|PlayerState|Attributes")
		float GetMoveSpeed() const;
	UFUNCTION(BlueprintCallable, Category = "CubeAlpha|PlayerState|Attributes")
		float GetJumpHeight() const;
	UFUNCTION(BlueprintCallable, Category = "CubeAlpha|PlayerState|Attributes")
		float GetStamina()const;
	UFUNCTION(BlueprintCallable, Category = "CubeAlpha|PlayerState|Attributes")
		float GetMaxStamina()const;
	UFUNCTION(BlueprintCallable, Category = "CubeAlpha|PlayerState|Attributes")
		float GetBaseVitality() const;
	UFUNCTION(BlueprintCallable, Category = "CubeAlpha|PlayerState|Attributes")
		float GetVitality() const;
	UFUNCTION(BlueprintCallable, Category = "CubeAlpha|PlayerState|Attributes")
		float GetBaseStrength() const;
	UFUNCTION(BlueprintCallable, Category = "CubeAlpha|PlayerState|Attributes")
		float GetStrength() const;
	UFUNCTION(BlueprintCallable, Category = "CubeAlpha|PlayerState|Attributes")
		float GetBaseIntelligence() const;
	UFUNCTION(BlueprintCallable, Category = "CubeAlpha|PlayerState|Attributes")
		float GetIntelligence() const;
	UFUNCTION(BlueprintCallable, Category = "CubeAlpha|PlayerState|Attributes")
		float GetBaseAgility() const;
	UFUNCTION(BlueprintCallable, Category = "CubeAlpha|PlayerState|Attributes")
		float GetAgility() const;
	UFUNCTION(BlueprintCallable, Category = "CubeAlpha|PlayerState|Attributes")
		float GetBaseEndurance() const;
	UFUNCTION(BlueprintCallable, Category = "CubeAlpha|PlayerState|Attributes")
		float GetEndurance() const;
	UFUNCTION(BlueprintCallable, Category = "CubeAlpha|PlayerState|Attributes")
		float GetCharacterLevel() const;
#pragma endregion

protected:
	UPROPERTY()
	class UCA_AbilitySystemComponent* AbilitySystemComponent;
	UPROPERTY()
	UCA_CombatAttributeSet* CombatAttributeSet;
	UPROPERTY()
	UCA_HealthAttributeSet* HealthAttributeSet;
	UPROPERTY()
	UCA_MovementAttributeSet* MovementAttributeSet;
	UPROPERTY()
	UCA_RPGStatsAttributeSet* RPGStatsAttributeSet;

	FGameplayTag DeadTag;

#pragma region AttributeSetDelegateHandles
	FDelegateHandle PhysicalDamageChangedDelegateHandle;
	FDelegateHandle MagicalDamageChangedDelegateHandle;
	FDelegateHandle PhysicalResistanceChangedDelegateHandle;
	FDelegateHandle MagicalResistanceChangedDelegateHandle;
	FDelegateHandle DefenseChangedDelegateHandle;

	FDelegateHandle HealthChangedDelegateHandle;
	FDelegateHandle MaxHealthChangedDelegateHandle;
	FDelegateHandle HealthRegenChangedDelegateHandle;

	FDelegateHandle MoveSpeedChangedDelegateHandle;
	FDelegateHandle	JumpHeightChangedDelegateHandle;
	FDelegateHandle StaminaChangedDelegateHandle;
	FDelegateHandle MaxStaminaChangedDelegateHandle;

	FDelegateHandle BaseVitalityChangedDelegateHandle;
	FDelegateHandle VitalityChangedDelegateHandle;
	FDelegateHandle BaseStrengthChangedDelegateHandle;
	FDelegateHandle StrengthChangedDelegateHandle;
	FDelegateHandle BaseIntelligenceChangedDelegateHandle;
	FDelegateHandle IntelligenceChangedDelegateHandle;
	FDelegateHandle BaseAgilityChangedDelegateHandle;
	FDelegateHandle AgilityChangedDelegateHandle;
	FDelegateHandle BaseEnduranceChangedDelegateHandle;
	FDelegateHandle EnduranceChangedDelegateHandle;
	FDelegateHandle CharacterLevelChangedDelegateHandle;
#pragma endregion

	virtual void BeginPlay() override;

#pragma region AttributeSetChanges
	virtual void PhysicalDamageChanged(const FOnAttributeChangeData& Data);
	virtual void MagicalDamageChanged(const FOnAttributeChangeData& Data);
	virtual void PhysicalResistanceChanged(const FOnAttributeChangeData& Data);
	virtual void MagicalResistanceChanged(const FOnAttributeChangeData& Data);
	virtual void DefenseChanged(const FOnAttributeChangeData& Data);

	virtual void HealthChanged(const FOnAttributeChangeData& Data);
	virtual void MaxHealthChanged(const FOnAttributeChangeData& Data);
	virtual void HealthRegenChanged(const FOnAttributeChangeData& Data);

	virtual void MoveSpeedChanged(const FOnAttributeChangeData& Data);
	virtual void JumpHeightChanged(const FOnAttributeChangeData& Data);
	virtual void StaminaChanged(const FOnAttributeChangeData& Data);
	virtual void MaxStaminaChanged(const FOnAttributeChangeData& Data);

	virtual void BaseVitalityChanged(const FOnAttributeChangeData& Data);
	virtual void VitalityChanged(const FOnAttributeChangeData& Data);
	virtual void BaseStrengthChanged(const FOnAttributeChangeData& Data);
	virtual void StrengthChanged(const FOnAttributeChangeData& Data);
	virtual void BaseIntelligenceChanged(const FOnAttributeChangeData& Data);
	virtual void IntelligenceChanged(const FOnAttributeChangeData& Data);
	virtual void BaseAgilityChanged(const FOnAttributeChangeData& Data);
	virtual void AgilityChanged(const FOnAttributeChangeData& Data);
	virtual void BaseEnduranceChanged(const FOnAttributeChangeData& Data);
	virtual void EnduranceChanged(const FOnAttributeChangeData& Data);
	virtual void CharacterLevelChanged(const FOnAttributeChangeData& Data);
#pragma endregion

};
