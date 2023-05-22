#pragma once

#include "CoreMinimal.h"
#include "System/Player/CA_InventoryItem.h"
#include "CubeAlpha.h"
#include "CA_GearItem.generated.h"

UENUM(BlueprintType)
enum class EEquipmentSlot : uint8
{
    Helmet,
    Shoulders,
    Torso,
    Gloves,
    Pants,
    Boots,
    Weapon,
    Necklace,
    Ring,
    Unknown
};

UCLASS()
class CUBEALPHA_API UCA_GearItem : public UCA_InventoryItem
{
	GENERATED_BODY()

public:
    UCA_GearItem();

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gear Item")
        EEquipmentSlot EquipmentSlot;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gear Item")
        EClassType EquipmentClassType;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gear Item")
        int32 EquipmentLevel;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gear Item")
        int32 Defense;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gear Item")
        int32 Vitality;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gear Item")
        int32 Strength;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gear Item")
        int32 Intelligence;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gear Item")
        int32 Agility;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gear Item")
        int32 Endurance;


public:
    UFUNCTION(BlueprintCallable, Category = "Gear Item")
        EEquipmentSlot GetEquipmentSlot() const;

    UFUNCTION(BlueprintCallable, Category = "Gear Item")
        void SetEquipmentSlot(const EEquipmentSlot NewSlot);

    UFUNCTION(BlueprintCallable, Category = "Gear Item")
        EClassType GetEquipmentClassType() const;

    UFUNCTION(BlueprintCallable, Category = "Gear Item")
        void SetEquipmentClassType(EClassType NewClassType);

	UFUNCTION(BlueprintCallable, Category = "Gear Item")
        int32 GetEquipmentLevel() const;

    UFUNCTION(BlueprintCallable, Category = "Gear Item")
        void SetEquipmentLevel(int32 NewLevel);

    UFUNCTION(BlueprintCallable, Category = "Gear Item")
        int32 GetDefense() const;

    UFUNCTION(BlueprintCallable, Category = "Gear Item")
        void SetDefense(int32 NewDefense);

    UFUNCTION(BlueprintCallable, Category = "Gear Item")
        int32 GetVitality() const;

    UFUNCTION(BlueprintCallable, Category = "Gear Item")
        void SetVitality(int32 NewVitality);

    UFUNCTION(BlueprintCallable, Category = "Gear Item")
        int32 GetStrength() const;

    UFUNCTION(BlueprintCallable, Category = "Gear Item")
        void SetStrength(int32 NewStrength);

    UFUNCTION(BlueprintCallable, Category = "Gear Item")
        int32 GetIntelligence() const;

    UFUNCTION(BlueprintCallable, Category = "Gear Item")
        void SetIntelligence(int32 NewIntelligence);

    UFUNCTION(BlueprintCallable, Category = "Gear Item")
        int32 GetAgility() const;

    UFUNCTION(BlueprintCallable, Category = "Gear Item")
        void SetAgility(int32 NewAgility);

    UFUNCTION(BlueprintCallable, Category = "Gear Item")
        int32 GetEndurance() const;

    UFUNCTION(BlueprintCallable, Category = "Gear Item")
        void SetEndurance(int32 NewEndurance);
};
