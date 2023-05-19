#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "AbilitySystemComponent.h"
#include "CA_RPGStatsAttributeSet.generated.h"

// Uses macros from AttributeSet.h
#define ATTRIBUTE_ACCESSORS(ClassName, PropertyName) \
	GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)

UCLASS()
class CUBEALPHA_API UCA_RPGStatsAttributeSet : public UAttributeSet
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintReadOnly, Category = "Vitality", ReplicatedUsing = OnRep_BaseVitality)
		FGameplayAttributeData BaseVitality;
	ATTRIBUTE_ACCESSORS(UCA_RPGStatsAttributeSet, BaseVitality)

	UFUNCTION()
	virtual void OnRep_BaseVitality(const FGameplayAttributeData& OldBaseVitality);

	UPROPERTY(BlueprintReadOnly, Category = "Vitality", ReplicatedUsing = OnRep_Vitality)
		FGameplayAttributeData Vitality;
	ATTRIBUTE_ACCESSORS(UCA_RPGStatsAttributeSet, Vitality)

	UFUNCTION()
	virtual void OnRep_Vitality(const FGameplayAttributeData& OldVitality);

	UPROPERTY(BlueprintReadOnly, Category = "Strength", ReplicatedUsing = OnRep_BaseStrength)
		FGameplayAttributeData BaseStrength;
	ATTRIBUTE_ACCESSORS(UCA_RPGStatsAttributeSet, BaseStrength)

	UFUNCTION()
	virtual void OnRep_BaseStrength(const FGameplayAttributeData& OldBaseStrength);

	UPROPERTY(BlueprintReadOnly, Category = "Strength", ReplicatedUsing = OnRep_Strength)
		FGameplayAttributeData Strength;
	ATTRIBUTE_ACCESSORS(UCA_RPGStatsAttributeSet, Strength)

	UFUNCTION()
	virtual void OnRep_Strength(const FGameplayAttributeData& OldStrength);

	UPROPERTY(BlueprintReadOnly, Category = "Intelligence", ReplicatedUsing = OnRep_BaseIntelligence)
		FGameplayAttributeData BaseIntelligence;
	ATTRIBUTE_ACCESSORS(UCA_RPGStatsAttributeSet, BaseIntelligence)

	UFUNCTION()
	virtual void OnRep_BaseIntelligence(const FGameplayAttributeData& OldBaseIntelligence);

	UPROPERTY(BlueprintReadOnly, Category = "Intelligence", ReplicatedUsing = OnRep_Intelligence)
		FGameplayAttributeData Intelligence;
	ATTRIBUTE_ACCESSORS(UCA_RPGStatsAttributeSet, Intelligence)

	UFUNCTION()
	virtual void OnRep_Intelligence(const FGameplayAttributeData& OldIntelligence);

	UPROPERTY(BlueprintReadOnly, Category = "Agility", ReplicatedUsing = OnRep_BaseAgility)
		FGameplayAttributeData BaseAgility;
	ATTRIBUTE_ACCESSORS(UCA_RPGStatsAttributeSet, BaseAgility)

	UFUNCTION()
	virtual void OnRep_BaseAgility(const FGameplayAttributeData& OldBaseAgility);

	UPROPERTY(BlueprintReadOnly, Category = "Agility", ReplicatedUsing = OnRep_Agility)
		FGameplayAttributeData Agility;
	ATTRIBUTE_ACCESSORS(UCA_RPGStatsAttributeSet, Agility)

	UFUNCTION()
	virtual void OnRep_Agility(const FGameplayAttributeData& OldAgility);

	UPROPERTY(BlueprintReadOnly, Category = "Endurance", ReplicatedUsing = OnRep_BaseEndurance)
		FGameplayAttributeData BaseEndurance;
	ATTRIBUTE_ACCESSORS(UCA_RPGStatsAttributeSet, BaseEndurance)

	UFUNCTION()
	virtual void OnRep_BaseEndurance(const FGameplayAttributeData& OldBaseEndurance);

	UPROPERTY(BlueprintReadOnly, Category = "Endurance", ReplicatedUsing = OnRep_Endurance)
		FGameplayAttributeData Endurance;
	ATTRIBUTE_ACCESSORS(UCA_RPGStatsAttributeSet, Endurance)

	UFUNCTION()
	virtual void OnRep_Endurance(const FGameplayAttributeData& OldEndurance);

	UPROPERTY(BlueprintReadOnly, Category = "Level", ReplicatedUsing = OnRep_Level)
		FGameplayAttributeData Level;
	ATTRIBUTE_ACCESSORS(UCA_RPGStatsAttributeSet, Level)

		UFUNCTION()
		virtual void OnRep_Level(const FGameplayAttributeData& OldLevel);

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
};
