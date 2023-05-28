// Fill out your copyright notice in the Description page of Project Settings.


#include "System/GAS/CA_InstantAOE.h"
#include "Components/StaticMeshComponent.h"
#include "CA_CharacterBase.h"

// Sets default values
ACA_InstantAOE::ACA_InstantAOE()
{
	InitialLifeSpan = 1.0f;
	AoeMesh = CreateDefaultSubobject<UStaticMeshComponent>(FName("AOE Mesh"));
	AoeMesh->OnComponentBeginOverlap.AddDynamic(this, &ACA_InstantAOE::OnOverlapBegin);
	AoeMesh->SetCollisionProfileName(FName("OverlapAll"));
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	bReplicates = true;

}

void ACA_InstantAOE::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor->IsA(ACA_CharacterBase::StaticClass()) && (OtherActor != GetInstigator()))
	{
		const ACA_CharacterBase* AoeOwner = Cast<ACA_CharacterBase>(GetInstigator());
		ACA_CharacterBase* Target = Cast<ACA_CharacterBase>(OtherActor);
		if (IsValid(Target) && IsValid(AoeOwner) && !Target->IsPawnControlled()) //No damage to other players
		{
			Target->ApplyDamage(AoeDamage, AoeDamageType);
		}
	}
}

// Called when the game starts or when spawned
void ACA_InstantAOE::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACA_InstantAOE::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

