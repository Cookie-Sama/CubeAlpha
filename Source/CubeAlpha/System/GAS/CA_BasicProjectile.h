#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CubeAlpha.h"
#include "CA_BasicProjectile.generated.h"

UCLASS()
class CUBEALPHA_API ACA_BasicProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACA_BasicProjectile();

	UFUNCTION()
	virtual void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32
			OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere)
		UStaticMeshComponent* ProjectileMesh;

	UPROPERTY(BlueprintReadOnly, Category = "DataAsset")
		float ProjectileDamage;

	UPROPERTY(BlueprintReadOnly, Category = "DataAsset")
		CA_DamageType ProjectileDamageType = CA_DamageType::Physical;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "DataAsset")
		float Range;

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere)
		class UProjectileMovementComponent* ProjectileMovement;

	void CalculateLifeSpan();

protected:
	virtual void BeginPlay() override;
};
