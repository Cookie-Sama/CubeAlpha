#include "System/Player/CA_InventoryItem.h"

UCA_InventoryItem::UCA_InventoryItem()
{
	ItemDataAsset = CreateDefaultSubobject<UCA_InventoryItemDataAsset>("Item Data Asset");
	ItemDataAsset->SetItemType(EItemType::Unknown);
}

#pragma region GettersSetters
FString UCA_InventoryItem::GetItemName() const
{
	return ItemDataAsset->GetItemName();
}

void UCA_InventoryItem::SetItemName(FString NewName)
{
	ItemDataAsset->SetItemName(NewName);
}

ERarity UCA_InventoryItem::GetRarity() const
{
	return ItemDataAsset->GetRarity();
}

void UCA_InventoryItem::SetRarity(const ERarity NewRarity)
{
	ItemDataAsset->SetRarity(NewRarity);
}

EItemType UCA_InventoryItem::GetItemType() const
{
	return ItemDataAsset->GetItemType();
}

void UCA_InventoryItem::SetItemType(const EItemType NewType)
{
	ItemDataAsset->SetItemType(NewType);
}

uint8 UCA_InventoryItem::GetMaxStackSize() const
{
	return ItemDataAsset->GetMaxStackSize();
}

void UCA_InventoryItem::SetMaxStackSize(const uint8 NewSize)
{
	ItemDataAsset->SetMaxStackSize(NewSize);
}

bool UCA_InventoryItem::IsValid() const
{
	return ItemDataAsset!=nullptr;
}

uint8 UCA_InventoryItem::GetCopperValue() const
{
	return ItemDataAsset->GetCopperValue();
}

void UCA_InventoryItem::SetCopperValue(uint8 NewValue)
{
	ItemDataAsset->SetCopperValue(NewValue);
}

uint8 UCA_InventoryItem::GetSilverValue() const
{
	return ItemDataAsset->GetSilverValue();
}

void UCA_InventoryItem::SetSilverValue(uint8 NewValue)
{
	ItemDataAsset->SetSilverValue(NewValue);
}

uint8 UCA_InventoryItem::GetGoldValue() const
{
	return ItemDataAsset->GetGoldValue();
}

void UCA_InventoryItem::SetGoldValue(uint8 NewValue)
{
	ItemDataAsset->SetGoldValue(NewValue);
}

uint8 UCA_InventoryItem::GetPlatinumValue() const
{
	return ItemDataAsset->GetPlatinumValue();
}

void UCA_InventoryItem::SetPlatinumValue(uint8 NewValue)
{
	ItemDataAsset->SetPlatinumValue(NewValue);
}

//Return the value as Total Copper Value
int32 UCA_InventoryItem::GetItemValue() const
{
	return ItemDataAsset->GetItemValue();
}

UTexture2D* UCA_InventoryItem::GetItemImage() const
{
	return ItemImage;
}

void UCA_InventoryItem::SetItemImage(UTexture2D* NewImage)
{
	ItemImage = NewImage;
}

UStaticMesh* UCA_InventoryItem::GetItemMesh() const
{
	return ItemMesh;
}

void UCA_InventoryItem::SetItemMesh(UStaticMesh* NewMesh)
{
	ItemMesh = NewMesh;
}
#pragma endregion
