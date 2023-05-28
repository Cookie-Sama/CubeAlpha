#include "System/GAS/CA_BasicProjectile.h"

#include "CA_CharacterBase.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"

// Sets default values
ACA_BasicProjectile::ACA_BasicProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	InitialLifeSpan = 5.0f;
	bReplicates = true;

	ProjectileMesh = CreateDefaultSubobject<UStaticMeshComponent>(FName("ProjectileMesh"));
	ProjectileMesh->SetCollisionProfileName(FName("OverlapAll"));

	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(FName("ProjectileMovement"));
	ProjectileMovement->ProjectileGravityScale = 0.0f;
}

void ACA_BasicProjectile::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor->IsA(ACA_CharacterBase::StaticClass()) && (OtherActor != GetInstigator()))
	{
		const ACA_CharacterBase* ProjectileOwner = Cast<ACA_CharacterBase>(GetInstigator());
		ACA_CharacterBase* Target = Cast<ACA_CharacterBase>(OtherActor);
		if (IsValid(Target) && IsValid(ProjectileOwner) && !Target->IsPawnControlled()) //No damage to other players
		{
			Target->ApplyDamage(ProjectileDamage, ProjectileDamageType);
		}
	}
}

void ACA_BasicProjectile::CalculateLifeSpan()
{
	if (const float Max = ProjectileMovement->InitialSpeed * GetLifeSpan(); Max < Range)
	{
		SetLifeSpan(Max / ProjectileMovement->InitialSpeed);
	}
	else
	{
		SetLifeSpan(Range / ProjectileMovement->InitialSpeed);
	}
}

// Called when the game starts or when spawned
void ACA_BasicProjectile::BeginPlay()
{
	Super::BeginPlay();

	CalculateLifeSpan();
}
