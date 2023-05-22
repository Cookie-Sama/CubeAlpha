#include "Character/CA_CharacterEquipmentComponent.h"
#include "CA_CharacterWithEquipment.h"

// Sets default values for this component's properties
UCA_CharacterEquipmentComponent::UCA_CharacterEquipmentComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

bool UCA_CharacterEquipmentComponent::EquipItem(const TSubclassOf<UCA_GearItem> GearItem)
{
	if (GearItem == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("Invalid GearItem to equip."));
		return false;
	}

	UCA_GearItem* NewGear = Cast<UCA_GearItem>(GearItem.Get());
	if (!NewGear)
	{
		UE_LOG(LogTemp, Warning, TEXT("Invalid GearItem to equip."));
		return false;
	}

	// Check if the gear item is already equipped in the same equipment slot
	if (GetEquippedItem(NewGear->EquipmentSlot))
	{
		UE_LOG(LogTemp, Warning, TEXT("GearItem already equipped in the same slot."));
		return false;
	}

	// Check if the gear item is compatible with the character's class
	const ACA_CharacterWithEquipment* Owner = Cast<ACA_CharacterWithEquipment>(GetOwner());
	if (NewGear->EquipmentClassType != EClassType::All && NewGear->EquipmentClassType != Owner->GetCharacterClass())
	{
		UE_LOG(LogTemp, Warning, TEXT("GearItem is not compatible with the character's class."));
		return false;
	}

	// Unequip any existing gear in the same equipment slot
	UnequipItem(NewGear->EquipmentSlot);

	// Add the new gear item to the equipped gear map
	EquippedItems.Add(NewGear->GetEquipmentSlot(), NewGear);
	Owner->UpdateAttributes();
	return true;
}

bool UCA_CharacterEquipmentComponent::UnequipItem(const EEquipmentSlot Slot)
{
	if (const UCA_GearItem* ExistingGear = GetEquippedItem(Slot); !ExistingGear)
	{
		UE_LOG(LogTemp, Warning, TEXT("No GearItem equipped in the specified slot."));
		return false;
	}

	// Remove the gear item from the equipped gear map
	EquippedItems.Remove(Slot);
	const ACA_CharacterWithEquipment* Owner = Cast<ACA_CharacterWithEquipment>(GetOwner());
	Owner->UpdateAttributes();
	return true;
}

UCA_GearItem* UCA_CharacterEquipmentComponent::GetEquippedItem(const EEquipmentSlot Slot)
{
	if (UCA_GearItem** GearItem = EquippedItems.Find(Slot))
	{
		return *GearItem;
	}

	return nullptr;
}

int32 UCA_CharacterEquipmentComponent::GetTotalAttributeValue(const EAttribute Attribute) const
{
	int32 TotalValue = 0;

	for (const TPair<EEquipmentSlot, UCA_GearItem*>& EquippedItemPair : EquippedItems)
	{
		if (const UCA_GearItem* EquippedItem = EquippedItemPair.Value)
		{
			switch (Attribute)
			{
			case EAttribute::Vitality:
				TotalValue += EquippedItem->Vitality;
				break;
			case EAttribute::Strength:
				TotalValue += EquippedItem->Strength;
				break;
			case EAttribute::Intelligence:
				TotalValue += EquippedItem->Intelligence;
				break;
			case EAttribute::Agility:
				TotalValue += EquippedItem->Agility;
				break;
			case EAttribute::Endurance:
				TotalValue += EquippedItem->Endurance;
				break;
			case EAttribute::Defense:
				TotalValue += EquippedItem->Defense;
				break;
			default:
				break;
			}
		}
	}

	return TotalValue;
}

int32 UCA_CharacterEquipmentComponent::GetTotalDefense() const
{
	return GetTotalAttributeValue(EAttribute::Defense);
}

int32 UCA_CharacterEquipmentComponent::GetTotalVitality() const
{
	return GetTotalAttributeValue(EAttribute::Vitality);
}

int32 UCA_CharacterEquipmentComponent::GetTotalStrength() const
{
	return GetTotalAttributeValue(EAttribute::Strength);
}

int32 UCA_CharacterEquipmentComponent::GetTotalIntelligence() const
{
	return GetTotalAttributeValue(EAttribute::Intelligence);
}

int32 UCA_CharacterEquipmentComponent::GetTotalAgility() const
{
	return GetTotalAttributeValue(EAttribute::Agility);
}

int32 UCA_CharacterEquipmentComponent::GetTotalEndurance() const
{
	return GetTotalAttributeValue(EAttribute::Endurance);
}
