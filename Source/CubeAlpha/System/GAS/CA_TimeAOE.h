#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CubeAlpha.h"
#include "CA_TimeAOE.generated.h"

//Class for Tick Damage
UCLASS()
class CUBEALPHA_API ACA_TimeAOE : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACA_TimeAOE();

	UFUNCTION()
		void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32
			OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		UStaticMeshComponent* AoeMesh;

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, Category = "DataAsset")
		float Range;

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, Category = "DataAsset")
		float AoeDamage;

	UPROPERTY(BlueprintReadOnly, Category = "DataAsset")
		CA_DamageType AoeDamageType = CA_DamageType::Physical;

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, Category = "DataAsset")
		float AoeDuration;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void CallFunctionOnOverlappingActors() const;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	FTimerHandle TimerHandle;
};
