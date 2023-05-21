#include "CA_InventorySlot.h"

UCA_InventorySlot::UCA_InventorySlot():
SlotIndex(0),
ItemClass(nullptr),
Quantity(0)
{}

bool UCA_InventorySlot::CanStackItem(const TSubclassOf<UCA_InventoryItem> InItemClass, int32 InQuantity) const
{
	if (InItemClass == nullptr)
		return false;

	if (InItemClass != this->ItemClass)
		return false;

	const UCA_InventoryItem* Item = Cast<UCA_InventoryItem>(InItemClass.Get());
	if (!Item)
		return false;

	if (InQuantity <= 0 || InQuantity > Item->GetMaxStackSize())
		return false;

	return (this->Quantity + InQuantity) <= Item->GetMaxStackSize();
}
