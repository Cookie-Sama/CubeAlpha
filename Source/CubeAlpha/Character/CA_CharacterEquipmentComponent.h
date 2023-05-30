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

#pragma region Getters
    UFUNCTION(BlueprintCallable, Category = "Equipment Component")
        UCA_GearItem* GetEquippedItem(EEquipmentSlot Slot);

    UFUNCTION(BlueprintCallable, Category = "Equipment Component")
        int32 GetTotalAttributeValue(EEquipmentAttribute Attribute) const;

    UFUNCTION(BlueprintCallable, Category = "Equipment Component")
        int32 GetTotalDefense() const;

    UFUNCTION(BlueprintCallable, Category = "Equipment Component")
        int32 GetTotalVitality() const;

    UFUNCTION(BlueprintCallable, Category = "Equipment Component")
        int32 GetTotalStrength() const;

    UFUNCTION(BlueprintCallable, Category = "Equipment Component")
        int32 GetTotalIntelligence() const;

    UFUNCTION(BlueprintCallable, Category = "Equipment Component")
        int32 GetTotalAgility() const;

    UFUNCTION(BlueprintCallable, Category = "Equipment Component")
        int32 GetTotalEndurance() const;

    UFUNCTION(BlueprintCallable, Category = "Equipment Component")
        int32 GetTotalPhysicalDamage() const;

    UFUNCTION(BlueprintCallable, Category = "Equipment Component")
        int32 GetTotalMagicalDamage() const;

    UFUNCTION(BlueprintCallable, Category = "Equipment Component")
        int32 GetTotalPhysicalResistance() const;

    UFUNCTION(BlueprintCallable, Category = "Equipment Component")
        int32 GetTotalMagicalResistance() const;
#pragma endregion

};
