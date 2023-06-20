#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "CA_InventoryItemDataAsset.h"
#include "CubeAlpha.h"
#include "CA_InventoryItem.generated.h"

UCLASS(Blueprintable)
class CUBEALPHA_API UCA_InventoryItem : public UObject
{
	GENERATED_BODY()
public:
    UCA_InventoryItem();

protected:

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory Item")
        UCA_InventoryItemDataAsset* ItemDataAsset;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory Item")
        UTexture2D* ItemImage;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory Item")
        UStaticMesh* ItemMesh;

public:

#pragma region GettersSetters
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
        uint8 GetCopperValue() const;

    UFUNCTION(BlueprintCallable, Category = "Inventory Item")
        void SetCopperValue(uint8 NewValue);

    UFUNCTION(BlueprintCallable, Category = "Inventory Item")
        uint8 GetSilverValue() const;

    UFUNCTION(BlueprintCallable, Category = "Inventory Item")
        void SetSilverValue(uint8 NewValue);

    UFUNCTION(BlueprintCallable, Category = "Inventory Item")
        uint8 GetGoldValue() const;

    UFUNCTION(BlueprintCallable, Category = "Inventory Item")
        void SetGoldValue(uint8 NewValue);

    UFUNCTION(BlueprintCallable, Category = "Inventory Item")
        uint8 GetPlatinumValue() const;

    UFUNCTION(BlueprintCallable, Category = "Inventory Item")
        void SetPlatinumValue(uint8 NewValue);

    UFUNCTION(BlueprintCallable, Category = "Inventory Item")
        int32 GetItemValue() const;

    UFUNCTION(BlueprintCallable, Category = "Inventory Item")
        UTexture2D* GetItemImage() const;

    UFUNCTION(BlueprintCallable, Category = "Inventory Item")
        void SetItemImage(UTexture2D* NewImage);

    UFUNCTION(BlueprintCallable, Category = "Inventory Item")
        UStaticMesh* GetItemMesh() const;

    UFUNCTION(BlueprintCallable, Category = "Inventory Item")
        void SetItemMesh(UStaticMesh* NewMesh);
#pragma endregion

};
