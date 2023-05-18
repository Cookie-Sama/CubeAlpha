#include "Character/NPC/CA_NPCCharacter.h"

ACA_NPCCharacter::ACA_NPCCharacter(const class FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer.SetDefaultSubobjectClass<UCharacterMovementComponent>(ACharacter::CharacterMovementComponentName))
{
}
