#include "System/Player/CA_CharacterInventoryComponent.h"

// Sets default values for this component's properties
UCA_CharacterInventoryComponent::UCA_CharacterInventoryComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	MaxInventorySlots = 20;
}

bool UCA_CharacterInventoryComponent::AddItemToInventory(const TSubclassOf<UCA_InventoryItem> ItemClass, const int32 Quantity)
{
    if (ItemClass == nullptr || Quantity <= 0)
    {
        return false;
    }

    // Check if we can move an item into an existing slot
    for (UCA_InventorySlot* Slot : InventorySlots)
    {
        if (Slot->CanStackItem(ItemClass, Quantity))
        {
            Slot->Quantity += Quantity;
            return true;
        }
    }

    // Check Inventory Size
    if (InventorySlots.Num() < MaxInventorySlots)
    {
        // Add a slot
        UCA_InventorySlot* NewSlot = NewObject<UCA_InventorySlot>(this);
        NewSlot->ItemClass = ItemClass;
        NewSlot->Quantity = Quantity;

        InventorySlots.Add(NewSlot);
        return true;
    }

    return false; // Inventory Full
}

bool UCA_CharacterInventoryComponent::RemoveItemFromInventory(const int32 SlotIndex, const int32 Quantity)
{
    if (SlotIndex < 0 || SlotIndex >= InventorySlots.Num() || Quantity <= 0)
    {
        return false;
    }

    UCA_InventorySlot* Slot = InventorySlots[SlotIndex];
    if (Slot->ItemClass == nullptr || Slot->Quantity < Quantity)
    {
        return false;
    }

    Slot->Quantity -= Quantity;
    if (Slot->Quantity <= 0)
    {
        Slot->ItemClass = nullptr;
        Slot->Quantity = 0;
    }

    return true;
}

int32 UCA_CharacterInventoryComponent::GetItemQuantity(const TSubclassOf<UCA_InventoryItem> ItemClass)
{
    if (ItemClass == nullptr)
    {
        return 0;
    }

    int32 Quantity = 0;
    for (const UCA_InventorySlot* Slot : InventorySlots)
    {
        if (Slot->ItemClass == ItemClass)
        {
            Quantity += Slot->Quantity;
        }
    }

    return Quantity;
}

int32 UCA_CharacterInventoryComponent::GetItemIndex(const TSubclassOf<UCA_InventoryItem> ItemClass)
{
    if (ItemClass == nullptr)
    {
        return -1;
    }

    for (int32 Index = 0; Index < InventorySlots.Num(); Index++)
    {
	    if (const UCA_InventorySlot* Slot = InventorySlots[Index]; Slot->ItemClass == ItemClass)
        {
            return Index;
        }
    }

    return -1;
}

void UCA_CharacterInventoryComponent::IncreaseInventorySize(const int32 SizeAdded)
{
    if (SizeAdded <= 0)
    {
        return;
    }

    MaxInventorySlots += SizeAdded;
}
