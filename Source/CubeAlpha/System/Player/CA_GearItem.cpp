#include "System/Player/CA_GearItem.h"

UCA_GearItem::UCA_GearItem()
{
	ItemDataAsset->SetItemType(EItemType::Gear);
	ItemDataAsset->SetMaxStackSize(1);
}

#pragma region GettersSetters
EEquipmentSlot UCA_GearItem::GetEquipmentSlot() const
{
	return EquipmentSlot;
}

void UCA_GearItem::SetEquipmentSlot(const EEquipmentSlot NewSlot)
{
	EquipmentSlot = NewSlot;
}

EClassType UCA_GearItem::GetEquipmentClassType() const
{
	return EquipmentClassType;
}

void UCA_GearItem::SetEquipmentClassType(const EClassType NewClassType)
{
	EquipmentClassType = NewClassType;
}

int32 UCA_GearItem::GetEquipmentLevel() const
{
	return EquipmentLevel;
}

void UCA_GearItem::SetEquipmentLevel(const int32 NewLevel)
{
	EquipmentLevel = NewLevel;
}

int32 UCA_GearItem::GetDefense() const
{
	return Defense;
}

void UCA_GearItem::SetDefense(const int32 NewDefense)
{
	Defense = NewDefense;
}

int32 UCA_GearItem::GetVitality() const
{
	return Vitality;
}

void UCA_GearItem::SetVitality(const int32 NewVitality)
{
	Vitality = NewVitality;
}

int32 UCA_GearItem::GetStrength() const
{
	return Strength;
}

void UCA_GearItem::SetStrength(const int32 NewStrength)
{
	Strength = NewStrength;
}

int32 UCA_GearItem::GetIntelligence() const
{
	return Intelligence;
}

void UCA_GearItem::SetIntelligence(const int32 NewIntelligence)
{
	Intelligence = NewIntelligence;
}

int32 UCA_GearItem::GetAgility() const
{
	return Agility;
}

void UCA_GearItem::SetAgility(const int32 NewAgility)
{
	Agility = NewAgility;
}

int32 UCA_GearItem::GetEndurance() const
{
	return Endurance;
}

void UCA_GearItem::SetEndurance(const int32 NewEndurance)
{
	Endurance = NewEndurance;
}

int32 UCA_GearItem::GetPhysicalDamage() const
{
	return PhysicalDamage;
}

void UCA_GearItem::SetPhysicalDamage(const int32 NewPhysicalDamage)
{
	PhysicalDamage = NewPhysicalDamage;
}

int32 UCA_GearItem::GetMagicalDamage() const
{
	return MagicalDamage;
}

void UCA_GearItem::SetMagicalDamage(const int32 NewMagicalDamage)
{
	MagicalDamage = NewMagicalDamage;
}

int32 UCA_GearItem::GetPhysicalResistance() const
{
	return PhysicalResistance;
}

void UCA_GearItem::SetPhysicalResistance(const int32 NewPhysicalResistance)
{
	PhysicalResistance = NewPhysicalResistance;
}

int32 UCA_GearItem::GetMagicalResistance() const
{
	return MagicalResistance;
}

void UCA_GearItem::SetMagicalResistance(const int32 NewMagicalResistance)
{
	MagicalResistance = NewMagicalResistance;
}
#pragma endregion
