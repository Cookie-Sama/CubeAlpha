#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CA_InventoryItem.h"
#include "CA_CharacterInventory.generated.h"

USTRUCT(BlueprintType)
struct FInventorySlot
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int32 SlotIndex;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TSubclassOf<UCA_InventoryItem> ItemClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int32 Quantity;

	FInventorySlot()
		: SlotIndex(0)
		, ItemClass(nullptr)
		, Quantity(0)
	{}

	bool CanStackItem(const TSubclassOf<UCA_InventoryItem> InItemClass, int32 InQuantity) const
	{
		if (InItemClass == nullptr)
			return false;

		if (InItemClass != this->ItemClass)
			return false;

		if (InQuantity <= 0 || InQuantity > ItemClass.GetDefaultObject()->GetStackSize())
			return false;

		return (this->Quantity + InQuantity) <= ItemClass.GetDefaultObject()->GetStackSize();
	}
};

UCLASS()
class CUBEALPHA_API ACA_CharacterInventory : public AActor
{
	GENERATED_BODY()
public:

	ACA_CharacterInventory();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FInventorySlot> InventorySlots;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Inventory")
		int32 MaxInventorySlots;

	// Add an item to the inventory
	UFUNCTION(BlueprintCallable)
	bool AddItemToInventory(TSubclassOf<UCA_InventoryItem> ItemClass, int32 Quantity);

	// Remove an item from the inventory
	UFUNCTION(BlueprintCallable)
	bool RemoveItemFromInventory(int32 SlotIndex, int32 Quantity);

	// Get the quantity of a specific item in the inventory
	UFUNCTION(BlueprintCallable)
	int32 GetItemQuantity(TSubclassOf<UCA_InventoryItem> ItemClass);

	// Get the index of a specific item in the inventory
	UFUNCTION(BlueprintCallable)
	int32 GetItemIndex(TSubclassOf<UCA_InventoryItem> ItemClass);

};
