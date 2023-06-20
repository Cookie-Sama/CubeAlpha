#include "System/Player/CA_InventoryItemDataAsset.h"

#pragma region GettersSetters
FString UCA_InventoryItemDataAsset::GetItemName() const
{
	return ItemName;
}

void UCA_InventoryItemDataAsset::SetItemName(FString NewName)
{
	ItemName = NewName;
}

ERarity UCA_InventoryItemDataAsset::GetRarity() const
{
	return Rarity;
}

void UCA_InventoryItemDataAsset::SetRarity(ERarity NewRarity)
{
	Rarity = NewRarity;
}

EItemType UCA_InventoryItemDataAsset::GetItemType() const
{
	return ItemType;
}

void UCA_InventoryItemDataAsset::SetItemType(EItemType NewType)
{
	ItemType = NewType;
}

uint8 UCA_InventoryItemDataAsset::GetMaxStackSize() const
{
	return MaxStackSize;
}

void UCA_InventoryItemDataAsset::SetMaxStackSize(uint8 NewSize)
{
	MaxStackSize = NewSize;
}

uint8 UCA_InventoryItemDataAsset::GetCopperValue() const
{
	return CopperValue;
}

void UCA_InventoryItemDataAsset::SetCopperValue(uint8 NewValue)
{
	CopperValue = NewValue;
}

uint8 UCA_InventoryItemDataAsset::GetSilverValue() const
{
	return SilverValue;
}

void UCA_InventoryItemDataAsset::SetSilverValue(uint8 NewValue)
{
	SilverValue = NewValue;
}

uint8 UCA_InventoryItemDataAsset::GetGoldValue() const
{
	return GoldValue;
}

void UCA_InventoryItemDataAsset::SetGoldValue(uint8 NewValue)
{
	GoldValue = NewValue;
}

uint8 UCA_InventoryItemDataAsset::GetPlatinumValue() const
{
	return PlatinumValue;
}

void UCA_InventoryItemDataAsset::SetPlatinumValue(uint8 NewValue)
{
	PlatinumValue = NewValue;
}

int32 UCA_InventoryItemDataAsset::GetItemValue() const
{
	return (PlatinumValue * 1000000) + (GoldValue * 10000) + (SilverValue * 100) + CopperValue;
}
#pragma endregion
