#include "System/Player/CA_InventoryItem.h"

UCA_InventoryItem::UCA_InventoryItem()
{
	ItemType = EItemType::Unknown;
}

FString UCA_InventoryItem::GetItemName() const
{
	return ItemName;
}

void UCA_InventoryItem::SetItemName(FString NewName)
{
	ItemName = NewName;
}

ERarity UCA_InventoryItem::GetRarity() const
{
	return Rarity;
}

void UCA_InventoryItem::SetRarity(const ERarity NewRarity)
{
	Rarity = NewRarity;
}

EItemType UCA_InventoryItem::GetItemType() const
{
	return ItemType;
}

void UCA_InventoryItem::SetItemType(const EItemType NewType)
{
	ItemType = NewType;
}

uint8 UCA_InventoryItem::GetMaxStackSize() const
{
	return MaxStackSize;
}

void UCA_InventoryItem::SetMaxStackSize(const uint8 NewSize)
{
	MaxStackSize = NewSize;
}

bool UCA_InventoryItem::IsValid() const
{
	return !ItemName.IsEmpty();
}

//Return the value as Total Copper Value
int32 UCA_InventoryItem::GetItemValue() const
{
	return (PlatinumValue * 1000000) + (GoldValue*10000) + (SilverValue*100) + CopperValue;
}
