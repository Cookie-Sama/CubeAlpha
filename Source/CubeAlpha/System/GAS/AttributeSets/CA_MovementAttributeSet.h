#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "AbilitySystemComponent.h"
#include "CA_MovementAttributeSet.generated.h"

// Uses macros from AttributeSet.h
#define ATTRIBUTE_ACCESSORS(ClassName, PropertyName) \
	GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)

UCLASS()
class CUBEALPHA_API UCA_MovementAttributeSet : public UAttributeSet
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintReadOnly, Category = "Movement", ReplicatedUsing = OnRep_MoveSpeed)
		FGameplayAttributeData MoveSpeed;
	ATTRIBUTE_ACCESSORS(UCA_MovementAttributeSet, MoveSpeed)

	UFUNCTION()
	virtual void OnRep_MoveSpeed(const FGameplayAttributeData& OldMoveSpeed);

	UPROPERTY(BlueprintReadOnly, Category = "Movement", ReplicatedUsing = OnRep_JumpHeight)
		FGameplayAttributeData JumpHeight;
	ATTRIBUTE_ACCESSORS(UCA_MovementAttributeSet, JumpHeight)

	UFUNCTION()
	virtual void OnRep_JumpHeight(const FGameplayAttributeData& OldJumpHeight);

	UPROPERTY(BlueprintReadOnly, Category = "Movement", ReplicatedUsing = OnRep_Stamina)
		FGameplayAttributeData Stamina;
	ATTRIBUTE_ACCESSORS(UCA_MovementAttributeSet, Stamina)

	UFUNCTION()
	virtual void OnRep_Stamina(const FGameplayAttributeData& OldStamina);


	UPROPERTY(BlueprintReadOnly, Category = "Movement", ReplicatedUsing = OnRep_MaxStamina)
		FGameplayAttributeData MaxStamina;
	ATTRIBUTE_ACCESSORS(UCA_MovementAttributeSet, MaxStamina)

		UFUNCTION()
		virtual void OnRep_MaxStamina(const FGameplayAttributeData& OldMaxStamina);

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
};
