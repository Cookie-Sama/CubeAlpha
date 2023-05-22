#include "Character/NPC/CA_NPCWithoutEquipment.h"

ACA_NPCWithoutEquipment::ACA_NPCWithoutEquipment(const class FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer.SetDefaultSubobjectClass<UCharacterMovementComponent>(ACharacter::CharacterMovementComponentName))
{
}
