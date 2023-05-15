#pragma once

#include "CoreMinimal.h"
#include "Engine/AssetManager.h"
#include "CA_AssetManager.generated.h"

/**
 * 
 */
UCLASS()
class CUBEALPHA_API UCA_AssetManager : public UAssetManager
{
	GENERATED_BODY()
public:
	virtual void StartInitialLoading() override;
};
