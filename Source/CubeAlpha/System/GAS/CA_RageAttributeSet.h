#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "AbilitySystemComponent.h"
#include "CA_RageAttributeSet.generated.h"

// Uses macros from AttributeSet.h
#define ATTRIBUTE_ACCESSORS(ClassName, PropertyName) \
	GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)

UCLASS()
class CUBEALPHA_API UCA_RageAttributeSet : public UAttributeSet
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadOnly, Category = "Rage", ReplicatedUsing = OnRep_Rage)
		FGameplayAttributeData Rage;
	ATTRIBUTE_ACCESSORS(UCA_RageAttributeSet, Rage)

	UFUNCTION()
	virtual void OnRep_Rage(const FGameplayAttributeData& OldRage);

	UPROPERTY(BlueprintReadOnly, Category = "Rage", ReplicatedUsing = OnRep_MaxRage)
		FGameplayAttributeData MaxRage;
	ATTRIBUTE_ACCESSORS(UCA_RageAttributeSet, MaxRage)

	UFUNCTION()
	virtual void OnRep_MaxRage(const FGameplayAttributeData& OldMaxRage);

	UPROPERTY(BlueprintReadOnly, Category = "Rage", ReplicatedUsing = OnRep_RageRegen)
		FGameplayAttributeData RageRegen;
	ATTRIBUTE_ACCESSORS(UCA_RageAttributeSet, RageRegen)

	UFUNCTION()
	virtual void OnRep_RageRegen(const FGameplayAttributeData& OldRageRegen);

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
};
