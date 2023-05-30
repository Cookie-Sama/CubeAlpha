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
	if (GetEquippedItem(NewGear->GetEquipmentSlot()))
	{
		UE_LOG(LogTemp, Warning, TEXT("GearItem already equipped in the same slot."));
		return false;
	}

	// Check if the gear item is compatible with the character's class
	const ACA_CharacterWithEquipment* Owner = Cast<ACA_CharacterWithEquipment>(GetOwner());
	if (NewGear->GetEquipmentClassType() != EClassType::All && NewGear->GetEquipmentClassType() != Owner->GetCharacterClass())
	{
		UE_LOG(LogTemp, Warning, TEXT("GearItem is not compatible with the character's class."));
		return false;
	}

	// Unequip any existing gear in the same equipment slot
	UnequipItem(NewGear->GetEquipmentSlot());

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

int32 UCA_CharacterEquipmentComponent::GetTotalAttributeValue(const EEquipmentAttribute Attribute) const
{
	int32 TotalValue = 0;

	for (const TPair<EEquipmentSlot, UCA_GearItem*>& EquippedItemPair : EquippedItems)
	{
		if (const UCA_GearItem* EquippedItem = EquippedItemPair.Value)
		{
			switch (Attribute)
			{
			case EEquipmentAttribute::Vitality:
				TotalValue += EquippedItem->GetVitality();
				break;
			case EEquipmentAttribute::Strength:
				TotalValue += EquippedItem->GetStrength();
				break;
			case EEquipmentAttribute::Intelligence:
				TotalValue += EquippedItem->GetIntelligence();
				break;
			case EEquipmentAttribute::Agility:
				TotalValue += EquippedItem->GetAgility();
				break;
			case EEquipmentAttribute::Endurance:
				TotalValue += EquippedItem->GetEndurance();
				break;
			case EEquipmentAttribute::Defense:
				TotalValue += EquippedItem->GetDefense();
				break;
			case EEquipmentAttribute::PhysicalDamage:
				TotalValue += EquippedItem->GetPhysicalDamage();
				break;
			case EEquipmentAttribute::MagicalDamage:
				TotalValue += EquippedItem->GetMagicalDamage();
				break;
			case EEquipmentAttribute::PhysicalResistance:
				TotalValue += EquippedItem->GetPhysicalResistance();
				break;
			case EEquipmentAttribute::MagicalResistance:
				TotalValue += EquippedItem->GetMagicalResistance();
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
	return GetTotalAttributeValue(EEquipmentAttribute::Defense);
}

int32 UCA_CharacterEquipmentComponent::GetTotalVitality() const
{
	return GetTotalAttributeValue(EEquipmentAttribute::Vitality);
}

int32 UCA_CharacterEquipmentComponent::GetTotalStrength() const
{
	return GetTotalAttributeValue(EEquipmentAttribute::Strength);
}

int32 UCA_CharacterEquipmentComponent::GetTotalIntelligence() const
{
	return GetTotalAttributeValue(EEquipmentAttribute::Intelligence);
}

int32 UCA_CharacterEquipmentComponent::GetTotalAgility() const
{
	return GetTotalAttributeValue(EEquipmentAttribute::Agility);
}

int32 UCA_CharacterEquipmentComponent::GetTotalEndurance() const
{
	return GetTotalAttributeValue(EEquipmentAttribute::Endurance);
}

int32 UCA_CharacterEquipmentComponent::GetTotalPhysicalDamage() const
{
	return GetTotalAttributeValue(EEquipmentAttribute::PhysicalDamage);
}

int32 UCA_CharacterEquipmentComponent::GetTotalMagicalDamage() const
{
	return GetTotalAttributeValue(EEquipmentAttribute::MagicalDamage);
}

int32 UCA_CharacterEquipmentComponent::GetTotalPhysicalResistance() const
{
	return GetTotalAttributeValue(EEquipmentAttribute::PhysicalResistance);
}

int32 UCA_CharacterEquipmentComponent::GetTotalMagicalResistance() const
{
	return GetTotalAttributeValue(EEquipmentAttribute::MagicalResistance);
}
