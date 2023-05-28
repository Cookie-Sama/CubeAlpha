// Fill out your copyright notice in the Description page of Project Settings.


#include "System/GAS/CA_TimeAOE.h"

#include "CA_CharacterBase.h"

// Sets default values
ACA_TimeAOE::ACA_TimeAOE()
{
	AoeMesh = CreateDefaultSubobject<UStaticMeshComponent>(FName("AOE Mesh"));
	AoeMesh->SetCollisionProfileName(FName("OverlapAll"));
	AoeMesh->SetGenerateOverlapEvents(true);
	AoeMesh->OnComponentBeginOverlap.AddDynamic(this, &ACA_TimeAOE::OnOverlapBegin);
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	bReplicates = true;
	InitialLifeSpan = AoeDuration;

}

void ACA_TimeAOE::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	GetWorldTimerManager().ClearTimer(TimerHandle);
	GetWorldTimerManager().SetTimer(TimerHandle, this, &ACA_TimeAOE::CallFunctionOnOverlappingActors, 1.0f, true);
}

// Called when the game starts or when spawned
void ACA_TimeAOE::BeginPlay()
{
	Super::BeginPlay();
	
}

void ACA_TimeAOE::CallFunctionOnOverlappingActors() const
{
	const ACA_CharacterBase* AoeOwner = Cast<ACA_CharacterBase>(GetInstigator());
	TArray<AActor*> OverlappingActors;
	AoeMesh->GetOverlappingActors(OverlappingActors);

	if (IsValid(AoeOwner))
	{
		for (AActor* OverlappingActor : OverlappingActors)
		{
			if (OverlappingActor != GetInstigator()) {
				ACA_CharacterBase* Target = Cast<ACA_CharacterBase>(OverlappingActor);
				if (IsValid(Target) && !Target->IsPawnControlled()) {
					Target->ApplyDamage(AoeDamage, AoeDamageType);
				}
			}
		}
	}
}

// Called every frame
void ACA_TimeAOE::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

