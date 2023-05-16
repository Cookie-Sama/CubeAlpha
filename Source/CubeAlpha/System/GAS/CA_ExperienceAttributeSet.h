// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "AbilitySystemComponent.h"
#include "CA_ExperienceAttributeSet.generated.h"

// Uses macros from AttributeSet.h
#define ATTRIBUTE_ACCESSORS(ClassName, PropertyName) \
	GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)

UCLASS()
class CUBEALPHA_API UCA_ExperienceAttributeSet : public UAttributeSet
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadOnly, Category = "Experience", ReplicatedUsing = OnRep_Experience)
		FGameplayAttributeData Experience;
	ATTRIBUTE_ACCESSORS(UCA_ExperienceAttributeSet, Experience)

	UFUNCTION()
	virtual void OnRep_Experience(const FGameplayAttributeData& OldExperience);

	UPROPERTY(BlueprintReadOnly, Category = "Experience", ReplicatedUsing = OnRep_MaxExperience)
		FGameplayAttributeData MaxExperience;
	ATTRIBUTE_ACCESSORS(UCA_ExperienceAttributeSet, MaxExperience)

	UFUNCTION()
	virtual void OnRep_MaxExperience(const FGameplayAttributeData& OldMaxExperience);

	UPROPERTY(BlueprintReadOnly, Category = "Experience", ReplicatedUsing = OnRep_ExperienceMultiplier)
		FGameplayAttributeData ExperienceMultiplier;
	ATTRIBUTE_ACCESSORS(UCA_ExperienceAttributeSet, ExperienceMultiplier)

	UFUNCTION()
	virtual void OnRep_ExperienceMultiplier(const FGameplayAttributeData& OldExperienceMultiplier);

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
};
