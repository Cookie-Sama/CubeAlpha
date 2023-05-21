#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "CA_InventoryItem.generated.h"

UENUM(BlueprintType)
enum class EItemType : uint8
{
    Unknown,
	Gear,
    Consumable,
    Material,
    QuestItem
};

UCLASS(Blueprintable)
class CUBEALPHA_API UCA_InventoryItem : public UObject
{
	GENERATED_BODY()
protected:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Inventory Item")
        FString ItemName;

    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Inventory Item")
        ERarity Rarity;

    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Inventory Item")
        EItemType ItemType;

    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Inventory Item")
        uint8 MaxStackSize;

    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Inventory Item")
        uint8 CopperValue;

    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Inventory Item")
        uint8 SilverValue;

    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Inventory Item")
        uint8 GoldValue;

    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Inventory Item")
        uint8 PlatinumValue;

public:

    UFUNCTION(BlueprintCallable, Category = "Inventory Item")
        FString GetItemName() const;

    UFUNCTION(BlueprintCallable, Category = "Inventory Item")
        void SetItemName(FString NewName);

    UFUNCTION(BlueprintCallable, Category = "Inventory Item")
        ERarity GetRarity() const;

    UFUNCTION(BlueprintCallable, Category = "Inventory Item")
        void SetRarity(ERarity NewRarity);

    UFUNCTION(BlueprintCallable, Category = "Inventory Item")
        EItemType GetItemType() const;

    UFUNCTION(BlueprintCallable, Category = "Inventory Item")
        void SetItemType(EItemType NewType);

    UFUNCTION(BlueprintCallable, Category = "Inventory Item")
        uint8 GetMaxStackSize() const;

	UFUNCTION(BlueprintCallable, Category = "Inventory Item")
        void SetMaxStackSize(const uint8 NewSize);

	UFUNCTION(BlueprintCallable, Category = "Inventory Item")
        bool IsValid() const;

    UFUNCTION(BlueprintCallable, Category = "Inventory Item")
        int32 GetItemValue() const;
};
