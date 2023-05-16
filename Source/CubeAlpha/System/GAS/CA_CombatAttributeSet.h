#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "AbilitySystemComponent.h"
#include "CA_CombatAttributeSet.generated.h"

// Uses macros from AttributeSet.h
#define ATTRIBUTE_ACCESSORS(ClassName, PropertyName) \
	GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)

UCLASS()
class CUBEALPHA_API UCA_CombatAttributeSet : public UAttributeSet
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadOnly, Category = "Physical", ReplicatedUsing = OnRep_PhysicalDamage)
		FGameplayAttributeData PhysicalDamage;
	ATTRIBUTE_ACCESSORS(UCA_CombatAttributeSet, PhysicalDamage)

	UFUNCTION()
	virtual void OnRep_PhysicalDamage(const FGameplayAttributeData& OldPhysicalDamage);

	UPROPERTY(BlueprintReadOnly, Category = "Magical", ReplicatedUsing = OnRep_MagicalDamage)
		FGameplayAttributeData MagicalDamage;
	ATTRIBUTE_ACCESSORS(UCA_CombatAttributeSet, MagicalDamage)

	UFUNCTION()
	virtual void OnRep_MagicalDamage(const FGameplayAttributeData& OldMagicalDamage);

	UPROPERTY(BlueprintReadOnly, Category = "Physical", ReplicatedUsing = OnRep_PhysicalResistance)
		FGameplayAttributeData PhysicalResistance;
	ATTRIBUTE_ACCESSORS(UCA_CombatAttributeSet, PhysicalResistance)

	UFUNCTION()
	virtual void OnRep_PhysicalResistance(const FGameplayAttributeData& OldPhysicalResistance);

	UPROPERTY(BlueprintReadOnly, Category = "Magical", ReplicatedUsing = OnRep_MagicalResistance)
		FGameplayAttributeData MagicalResistance;
	ATTRIBUTE_ACCESSORS(UCA_CombatAttributeSet, MagicalResistance)

	UFUNCTION()
	virtual void OnRep_MagicalResistance(const FGameplayAttributeData& OldMagicalResistance);

	UPROPERTY(BlueprintReadOnly, Category = "Defense", ReplicatedUsing = OnRep_Defense)
		FGameplayAttributeData Defense;
	ATTRIBUTE_ACCESSORS(UCA_CombatAttributeSet, Defense)

	UFUNCTION()
	virtual void OnRep_Defense(const FGameplayAttributeData& OldDefense);

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
};
