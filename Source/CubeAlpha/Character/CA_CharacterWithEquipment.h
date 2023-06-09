#pragma once

#include "CoreMinimal.h"
#include "Character/CA_CharacterBase.h"
#include "CA_CharacterEquipmentComponent.h"
#include "CA_CharacterWithEquipment.generated.h"

UCLASS()
class CUBEALPHA_API ACA_CharacterWithEquipment : public ACA_CharacterBase
{
	GENERATED_BODY()
public:
	ACA_CharacterWithEquipment(const class FObjectInitializer& ObjectInitializer);

protected:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character")
		EClassType CharacterClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character")
		UCA_CharacterEquipmentComponent* CharacterEquipment;

public:

	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable, Category = "Character")
		EClassType GetCharacterClass() const;

	UFUNCTION(BlueprintCallable, Category = "Character")
		void SetCharacterClass(const EClassType NewCharacterClass);

	UFUNCTION(BlueprintCallable, Category = "Character")
		void UpdateAttributes() const;
};
