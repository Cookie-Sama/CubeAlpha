#pragma once

#include "CoreMinimal.h"
#include "Character/CA_CharacterWithEquipment.h"
#include "CA_NPCWithEquipment.generated.h"

/**
 * 
 */
UCLASS()
class CUBEALPHA_API ACA_NPCWithEquipment : public ACA_CharacterWithEquipment
{
	GENERATED_BODY()
public:
	ACA_NPCWithEquipment(const class FObjectInitializer& ObjectInitializer);
};
