#pragma once

#include "CoreMinimal.h"
#include "Character/CA_CharacterBase.h"
#include "CA_ExperienceAttributeSet.h"
#include "CA_PlayerCharacter.generated.h"

/**
 * 
 */
UCLASS()
class CUBEALPHA_API ACA_PlayerCharacter : public ACA_CharacterBase
{
	GENERATED_BODY()
public:
	ACA_PlayerCharacter(const class FObjectInitializer& ObjectInitializer);

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
		class USpringArmComponent* CameraBoom;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
		class UCameraComponent* FollowCamera;

	/** Returns CameraBoom subObject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	/** Returns FollowCamera subObject **/
	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }

#pragma region Cooldowns

	UFUNCTION(BlueprintCallable, meta = (DynamicOutputParam = "OutTimeRemaining"))
		bool GetCooldownRemainingForAbility(FGameplayTag AbilityTag, float& OutTimeRemaining);

	UFUNCTION(BlueprintCallable, meta = (DynamicOutputParam = "OutDuration"))
		bool GetCooldownDurationForAbility(FGameplayTag AbilityTag, float& OutDuration);

	UFUNCTION(BlueprintCallable, meta = (DynamicOutputParam = "OutTimeRemaining"))
		bool GetCooldownRemainingForTag(FGameplayTagContainer CooldownTags, float& OutTimeRemaining);

	UFUNCTION(BlueprintCallable, meta = (DynamicOutputParam = "OutDuration"))
		bool GetCooldownDurationForTag(FGameplayTagContainer CooldownTags, float& OutDuration);

#pragma endregion

#pragma region Experience
protected:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "CubeAlpha|Player|Experience")
		UCA_ExperienceAttributeSet* ExperienceAttributeSet;

public:
	UFUNCTION(BlueprintCallable, Category = "CubeAlpha|Character|Attributes")
	float GetExperience() const;
	UFUNCTION(BlueprintCallable, Category = "CubeAlpha|Character|Attributes")
	void SetExperience(const float& NewExperience) const;
	UFUNCTION(BlueprintCallable, Category = "CubeAlpha|Character|Attributes")
	float GetMaxExperience() const;
	UFUNCTION(BlueprintCallable, Category = "CubeAlpha|Character|Attributes")
	void SetMaxExperience(const float& NewMaxExperience) const;
#pragma endregion

};
