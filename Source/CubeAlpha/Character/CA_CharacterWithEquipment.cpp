#include "Character/CA_CharacterWithEquipment.h"

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
	SetDefense(CharacterEquipment->GetTotalStrength());
}
