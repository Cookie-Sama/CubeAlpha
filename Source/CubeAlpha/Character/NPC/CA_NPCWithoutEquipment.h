#pragma once

#include "CoreMinimal.h"
#include "Character/CA_CharacterBase.h"
#include "CA_NPCWithoutEquipment.generated.h"

/**
 * 
 */
UCLASS()
class CUBEALPHA_API ACA_NPCWithoutEquipment : public ACA_CharacterBase
{
	GENERATED_BODY()
public:
	ACA_NPCWithoutEquipment(const class FObjectInitializer& ObjectInitializer);
};
