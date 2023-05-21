#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "CA_InventoryItem.h"
#include "CA_InventorySlot.generated.h"

UCLASS()
class CUBEALPHA_API UCA_InventorySlot : public UObject
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int32 SlotIndex;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TSubclassOf<UCA_InventoryItem> ItemClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int32 Quantity;

	UCA_InventorySlot();

	bool CanStackItem(const TSubclassOf<UCA_InventoryItem> InItemClass, int32 InQuantity) const;
};
