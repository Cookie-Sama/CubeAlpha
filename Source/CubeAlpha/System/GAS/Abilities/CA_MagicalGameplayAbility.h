#pragma once

#include "CoreMinimal.h"
#include "System/GAS/Abilities/CA_GameplayAbility.h"
#include "CA_MagicalGameplayAbility.generated.h"

/**
 * 
 */
UCLASS()
class CUBEALPHA_API UCA_MagicalGameplayAbility : public UCA_GameplayAbility
{
	GENERATED_BODY()

public:

	UCA_MagicalGameplayAbility();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DataAsset")
		EMagicElementType Element;
};
