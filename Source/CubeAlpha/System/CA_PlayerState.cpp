#include "System/CA_PlayerState.h"

ACA_PlayerState::ACA_PlayerState()
{

	NetUpdateFrequency = 100.0f;

	DeadTag = FGameplayTag::RequestGameplayTag("State.Dead");
}

void ACA_PlayerState::ShowAbilityConfirmCancelText(bool ShowText)
{
	//TODO Later when HUD
}

void ACA_PlayerState::BeginPlay()
{
	Super::BeginPlay();

}

