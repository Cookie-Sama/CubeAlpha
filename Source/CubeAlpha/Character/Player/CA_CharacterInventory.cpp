#include "Character/Player/CA_CharacterInventory.h"

// Sets default values
ACA_CharacterInventory::ACA_CharacterInventory()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	MaxInventorySlots = 20;
}

bool ACA_CharacterInventory::AddItemToInventory(TSubclassOf<UCA_InventoryItem> ItemClass, int32 Quantity)
{
	if (ItemClass == nullptr || Quantity <= 0) {
		return false;
	}

	// Check if the inventory is full
	if (InventorySlots.Num() >= MaxInventorySlots) {
		return false;
	}

	// Check if the item can be stacked on an existing slot
	for (FInventorySlot& Slot : InventorySlots)
	{
		if (Slot.CanStackItem(ItemClass, Quantity))
		{
			Slot.Quantity += Quantity;
			return true;
		}
	}

	// Create a new slot for the item
	FInventorySlot NewSlot;
	NewSlot.ItemClass = ItemClass;
	NewSlot.Quantity = Quantity;
	NewSlot.SlotIndex = InventorySlots.Num();
	InventorySlots.Add(NewSlot);

	return true;
}

bool ACA_CharacterInventory::RemoveItemFromInventory(int32 SlotIndex, int32 Quantity)
{
	return true;
}

int32 ACA_CharacterInventory::GetItemQuantity(TSubclassOf<UCA_InventoryItem> ItemClass)
{
	return 0;
}

int32 ACA_CharacterInventory::GetItemIndex(TSubclassOf<UCA_InventoryItem> ItemClass)
{
	return 0;
}
