// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CubeAlpha.h"
#include "CA_InstantAOE.generated.h"

//Class for instant Damage AOE
UCLASS()
class CUBEALPHA_API ACA_InstantAOE : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACA_InstantAOE();

	UFUNCTION()
		void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32
			OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere)
		class UStaticMeshComponent* AoeMesh;

	UPROPERTY(BlueprintReadWrite, Category = "DataAsset")
		float Range = 1;//TODO maybe use this

	UPROPERTY(BlueprintReadWrite, Category = "DataAsset")
		float AoeDamage;

	UPROPERTY(BlueprintReadOnly, Category = "DataAsset")
		CA_DamageType AoeDamageType = CA_DamageType::Physical;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
