#include "CA_MovementAttributeSet.h"
#include "Net/UnrealNetwork.h"
void UCA_MovementAttributeSet::OnRep_MoveSpeed(const FGameplayAttributeData& OldMoveSpeed)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UCA_MovementAttributeSet, MoveSpeed, OldMoveSpeed);
}

void UCA_MovementAttributeSet::OnRep_JumpHeight(const FGameplayAttributeData& OldJumpHeight)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UCA_MovementAttributeSet, JumpHeight, OldJumpHeight);
}

void UCA_MovementAttributeSet::OnRep_Stamina(const FGameplayAttributeData& OldStamina)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UCA_MovementAttributeSet, Stamina, OldStamina);
}

void UCA_MovementAttributeSet::OnRep_MaxStamina(const FGameplayAttributeData& OldMaxStamina)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UCA_MovementAttributeSet, MaxStamina, OldMaxStamina);
}

void UCA_MovementAttributeSet::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME_CONDITION_NOTIFY(UCA_MovementAttributeSet, MoveSpeed, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UCA_MovementAttributeSet, JumpHeight, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UCA_MovementAttributeSet, Stamina, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UCA_MovementAttributeSet, MaxStamina, COND_None, REPNOTIFY_Always);
}
