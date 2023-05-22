#include "Character/NPC/CA_NPCWithEquipment.h"

ACA_NPCWithEquipment::ACA_NPCWithEquipment(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer.SetDefaultSubobjectClass<UCharacterMovementComponent>(ACharacter::CharacterMovementComponentName))
{
}
