#include "System/CA_AssetManager.h"
#include "AbilitySystemGlobals.h"
void UCA_AssetManager::StartInitialLoading()
{
	Super::StartInitialLoading();
	UAbilitySystemGlobals::Get().InitGlobalData();

	//Message de log au lancement pour verif le bon fonctionnement
	UE_LOG(LogTemp, Warning, TEXT("DA ASSET Manager OK"));
}
