#pragma once

#include "CoreMinimal.h"
#include "Character/Player/CA_PlayerCharacter.h"
#include "CA_ManaAttributeSet.h"
#include "CA_ManaPlayerCharacter.generated.h"

/**
 * 
 */
UCLASS()
class CUBEALPHA_API ACA_ManaPlayerCharacter : public ACA_PlayerCharacter
{
	GENERATED_BODY()
public:
	ACA_ManaPlayerCharacter(const class FObjectInitializer& ObjectInitializer);

	UPROPERTY(BluePrintAssignable, Category = "Events")
		FOnVariableAttributeChangedDelegate OnManaChanged;

	UPROPERTY(BluePrintAssignable, Category = "Events")
		FOnVariableAttributeChangedDelegate OnMaxManaChanged;

	UPROPERTY(BluePrintAssignable, Category = "Events")
		FOnSimpleAttributeChangedDelegate OnManaRegenChanged;

	FTimerHandle ManaRegenTimerHandle;
	void RegenMana() const;

protected:
	virtual void BeginPlay() override;

#pragma region Mana

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "CubeAlpha|Player|Mana")
		UCA_ManaAttributeSet* ManaAttributeSet;

	FDelegateHandle ManaChangedDelegateHandle;
	FDelegateHandle MaxManaChangedDelegateHandle;
	FDelegateHandle ManaRegenChangedDelegateHandle;

	bool bIsManaDelayActive;
	FTimerHandle ManaDelayTimerHandle;
	void DisableManaDelay();
public:
	UFUNCTION(BlueprintCallable, Category = "CubeAlpha|Character|Attributes")
		float GetMana() const;
	UFUNCTION(BlueprintCallable, Category = "CubeAlpha|Character|Attributes")
		void SetMana(float NewMana) const;
	UFUNCTION(BlueprintCallable, Category = "CubeAlpha|Character|Attributes")
		float GetMaxMana() const;
	UFUNCTION(BlueprintCallable, Category = "CubeAlpha|Character|Attributes")
		void SetMaxMana(float NewMaxMana) const;
	UFUNCTION(BlueprintCallable, Category = "CubeAlpha|Character|Attributes")
		float GetManaRegen() const;
	UFUNCTION(BlueprintCallable, Category = "CubeAlpha|Character|Attributes")
		void SetManaRegen(float NewManaRegen) const;

	virtual void ManaChanged(const FOnAttributeChangeData& Data);
	virtual void MaxManaChanged(const FOnAttributeChangeData& Data);
	virtual void ManaRegenChanged(const FOnAttributeChangeData& Data);

#pragma endregion

protected:
	virtual void LevelUpStats() const override;
};
