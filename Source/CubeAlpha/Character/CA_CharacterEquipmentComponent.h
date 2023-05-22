#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CubeAlpha.h"
#include "CA_GearItem.h"
#include "CA_CharacterEquipmentComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class CUBEALPHA_API UCA_CharacterEquipmentComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UCA_CharacterEquipmentComponent();

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
        TMap<EEquipmentSlot, UCA_GearItem*> EquippedItems;

    UFUNCTION(BlueprintCallable)
        bool EquipItem(TSubclassOf<UCA_GearItem> GearItem);

    UFUNCTION(BlueprintCallable)
        bool UnequipItem(EEquipmentSlot Slot);

    UFUNCTION(BlueprintCallable)
        UCA_GearItem* GetEquippedItem(EEquipmentSlot Slot);

    UFUNCTION(BlueprintCallable)
        int32 GetTotalAttributeValue(EAttribute Attribute) const;

    UFUNCTION(BlueprintCallable)
        int32 GetTotalDefense() const;

    UFUNCTION(BlueprintCallable)
        int32 GetTotalVitality() const;

    UFUNCTION(BlueprintCallable)
        int32 GetTotalStrength() const;

    UFUNCTION(BlueprintCallable)
        int32 GetTotalIntelligence() const;

    UFUNCTION(BlueprintCallable)
        int32 GetTotalAgility() const;

    UFUNCTION(BlueprintCallable)
        int32 GetTotalEndurance() const;
};
