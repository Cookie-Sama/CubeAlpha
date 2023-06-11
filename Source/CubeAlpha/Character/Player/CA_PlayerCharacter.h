#pragma once

#include "CoreMinimal.h"
#include "CA_CharacterWithEquipment.h"
#include "CA_ExperienceAttributeSet.h"
#include "InputActionValue.h"
#include "InputMappingContext.h"
#include "CA_PlayerCharacter.generated.h"

/**
 * 
 */
UCLASS()
class CUBEALPHA_API ACA_PlayerCharacter : public ACA_CharacterWithEquipment
{
	GENERATED_BODY()
public:
	ACA_PlayerCharacter(const class FObjectInitializer& ObjectInitializer);

	UPROPERTY(BluePrintAssignable, Category = "Events")
		FOnVariableAttributeChangedDelegate OnExperienceChanged;

	UPROPERTY(BluePrintAssignable, Category = "Events")
		FOnVariableAttributeChangedDelegate OnMaxExperienceChanged;

	/** MappingContext */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputMappingContext* PlayerMappingContext;

	/** Jump Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* JumpAction;

	/** Move Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* MoveAction;

	/** Look Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* LookAction;

protected:

	/** Called for movement input */
	void Move(const FInputActionValue& Value);

	/** Called for looking input */
	void Look(const FInputActionValue& Value);

	// APawn interface
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual void BeginPlay() override;

public:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
		class USpringArmComponent* CameraBoom;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
		class UCameraComponent* FollowCamera;

	/** Returns CameraBoom subObject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	/** Returns FollowCamera subObject **/
	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }

	UFUNCTION(BluePrintCallable, Category = "CubeAlpha|Character|Ability")
		FTransform GetProjectileTransforms(FName Socket) const;

#pragma region Cooldowns

	UFUNCTION(BlueprintCallable, meta = (DynamicOutputParam = "OutTimeRemaining"))
		bool GetCooldownRemainingForAbility(FGameplayTag AbilityTag, float& OutTimeRemaining) const;

	UFUNCTION(BlueprintCallable, meta = (DynamicOutputParam = "OutDuration"))
		bool GetCooldownDurationForAbility(FGameplayTag AbilityTag, float& OutDuration) const;

	UFUNCTION(BlueprintCallable, meta = (DynamicOutputParam = "OutTimeRemaining"))
		bool GetCooldownRemainingForTag(FGameplayTagContainer CooldownTags, float& OutTimeRemaining) const;

	UFUNCTION(BlueprintCallable, meta = (DynamicOutputParam = "OutDuration"))
		bool GetCooldownDurationForTag(FGameplayTagContainer CooldownTags, float& OutDuration) const;

#pragma endregion

protected:
	UPROPERTY(EditAnywhere, Category = "Data Asset")
		float VitalityLevelMultiplier = 1.0f;
	UPROPERTY(EditAnywhere, Category = "Data Asset")
		float StrengthLevelMultiplier = 1.0f;
	UPROPERTY(EditAnywhere, Category = "Data Asset")
		float IntelligenceLevelMultiplier = 1.0f;
	UPROPERTY(EditAnywhere, Category = "Data Asset")
		float AgilityLevelMultiplier = 1.0f;
	UPROPERTY(EditAnywhere, Category = "Data Asset")
		float EnduranceLevelMultiplier = 1.0f;

#pragma region Experience
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "CubeAlpha|Player|Experience")
		UCA_ExperienceAttributeSet* ExperienceAttributeSet;

	FDelegateHandle ExperienceChangedDelegateHandle;
	FDelegateHandle MaxExperienceChangedDelegateHandle;

public:
	UFUNCTION(BlueprintCallable, Category = "CubeAlpha|Character|Attributes")
	float GetExperience() const;
	UFUNCTION(BlueprintCallable, Category = "CubeAlpha|Character|Attributes")
	void SetExperience(float NewExperience) const;
	UFUNCTION(BlueprintCallable, Category = "CubeAlpha|Character|Attributes")
	float GetMaxExperience() const;
	UFUNCTION(BlueprintCallable, Category = "CubeAlpha|Character|Attributes")
	void SetMaxExperience(float NewMaxExperience) const;

	virtual void ExperienceChanged(const FOnAttributeChangeData& Data);
	virtual void MaxExperienceChanged(const FOnAttributeChangeData& Data);

protected:
	UFUNCTION(BlueprintCallable, Category = "CubeAlpha|Character|Attributes")
		void LevelUp() const;

	UFUNCTION(BlueprintCallable, Category = "CubeAlpha|Character|Attributes")
		virtual void LevelUpStats() const;
#pragma endregion

};
