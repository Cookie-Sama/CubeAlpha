#include "Character/CA_CharacterWithEquipment.h"

ACA_CharacterWithEquipment::ACA_CharacterWithEquipment(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer.SetDefaultSubobjectClass<UCharacterMovementComponent>(ACharacter::CharacterMovementComponentName))
{
	CharacterEquipment = CreateDefaultSubobject<UCA_CharacterEquipmentComponent>("Equipment");
}

void ACA_CharacterWithEquipment::BeginPlay()
{
	Super::BeginPlay();
	UpdateAttributes();

}

EClassType ACA_CharacterWithEquipment::GetCharacterClass() const
{
	return CharacterClass;
}

void ACA_CharacterWithEquipment::SetCharacterClass(const EClassType NewCharacterClass)
{
	CharacterClass = NewCharacterClass;
}

void ACA_CharacterWithEquipment::UpdateAttributes() const
{
	SetVitality(GetBaseVitality() + CharacterEquipment->GetTotalVitality());
	SetStrength(GetBaseStrength() + CharacterEquipment->GetTotalStrength());
	SetIntelligence(GetBaseIntelligence() + CharacterEquipment->GetTotalIntelligence());
	SetAgility(GetBaseAgility() * CharacterEquipment->GetTotalAgility());
	SetEndurance(GetBaseEndurance() + CharacterEquipment->GetTotalEndurance());
	SetDefense(CharacterEquipment->GetTotalDefense());

	//This part override the changes covered by the CharacterBase
	SetPhysicalDamage((GetStrength() * 0.2) + CharacterEquipment->GetTotalPhysicalDamage());
	SetMagicalDamage((GetIntelligence() * 0.2) + CharacterEquipment->GetTotalMagicalDamage());
	SetPhysicalResistance((GetStrength() / 100) + CharacterEquipment->GetTotalPhysicalResistance());
	SetMagicalResistance((GetIntelligence() / 100) + CharacterEquipment->GetTotalMagicalResistance());
}
