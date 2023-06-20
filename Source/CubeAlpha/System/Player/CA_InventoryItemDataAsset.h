#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "CubeAlpha.h"
#include "CA_InventoryItemDataAsset.generated.h"

/**
 * 
 */
UCLASS()
class CUBEALPHA_API UCA_InventoryItemDataAsset : public UDataAsset
{
	GENERATED_BODY()

protected:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Inventory Item Data Asset")
        FString ItemName;

    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Inventory Item Data Asset")
        ERarity Rarity;

    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Inventory Item Data Asset")
        EItemType ItemType;

    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Inventory Item Data Asset")
        uint8 MaxStackSize;

    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Inventory Item Data Asset")
        uint8 CopperValue;

    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Inventory Item Data Asset")
        uint8 SilverValue;

    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Inventory Item Data Asset")
        uint8 GoldValue;

    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Inventory Item Data Asset")
        uint8 PlatinumValue;

public:

#pragma region GettersSetters
    UFUNCTION(BlueprintCallable, Category = "Inventory Item Data Asset")
        FString GetItemName() const;

    UFUNCTION(BlueprintCallable, Category = "Inventory Item Data Asset")
        void SetItemName(FString NewName);

    UFUNCTION(BlueprintCallable, Category = "Inventory Item Data Asset")
        ERarity GetRarity() const;

    UFUNCTION(BlueprintCallable, Category = "Inventory Item Data Asset")
        void SetRarity(ERarity NewRarity);

    UFUNCTION(BlueprintCallable, Category = "Inventory Item Data Asset")
        EItemType GetItemType() const;

    UFUNCTION(BlueprintCallable, Category = "Inventory Item Data Asset")
        void SetItemType(EItemType NewType);

    UFUNCTION(BlueprintCallable, Category = "Inventory Item Data Asset")
        uint8 GetMaxStackSize() const;

    UFUNCTION(BlueprintCallable, Category = "Inventory Item Data Asset")
        void SetMaxStackSize(uint8 NewSize);

    UFUNCTION(BlueprintCallable, Category = "Inventory Item Data Asset")
        uint8 GetCopperValue() const;

    UFUNCTION(BlueprintCallable, Category = "Inventory Item Data Asset")
        void SetCopperValue(uint8 NewValue);

    UFUNCTION(BlueprintCallable, Category = "Inventory Item Data Asset")
        uint8 GetSilverValue() const;

    UFUNCTION(BlueprintCallable, Category = "Inventory Item Data Asset")
        void SetSilverValue(uint8 NewValue);

    UFUNCTION(BlueprintCallable, Category = "Inventory Item Data Asset")
        uint8 GetGoldValue() const;

    UFUNCTION(BlueprintCallable, Category = "Inventory Item Data Asset")
        void SetGoldValue(uint8 NewValue);

    UFUNCTION(BlueprintCallable, Category = "Inventory Item Data Asset")
        uint8 GetPlatinumValue() const;

    UFUNCTION(BlueprintCallable, Category = "Inventory Item Data Asset")
        void SetPlatinumValue(uint8 NewValue);

    UFUNCTION(BlueprintCallable, Category = "Inventory Item Data Asset")
        int32 GetItemValue() const;
#pragma endregion

};
