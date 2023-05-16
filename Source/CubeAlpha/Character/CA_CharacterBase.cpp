// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/CA_CharacterBase.h"

// Sets default values
ACA_CharacterBase::ACA_CharacterBase()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ACA_CharacterBase::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACA_CharacterBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ACA_CharacterBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

