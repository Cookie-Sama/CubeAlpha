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
