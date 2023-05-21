#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CA_InventoryItem.h"
#include "CA_InventorySlot.h"
#include "CA_CharacterInventoryComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class CUBEALPHA_API UCA_CharacterInventoryComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UCA_CharacterInventoryComponent();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TArray<UCA_InventorySlot*> InventorySlots;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Inventory")
		int32 MaxInventorySlots;

	// Add an item to the inventory
	UFUNCTION(BlueprintCallable)
		bool AddItemToInventory(TSubclassOf<UCA_InventoryItem> ItemClass, int32 Quantity);

	// Remove an item from the inventory
	UFUNCTION(BlueprintCallable)
		bool RemoveItemFromInventory(int32 SlotIndex, int32 Quantity);

	// Get the quantity of a specific item in the inventory
	UFUNCTION(BlueprintCallable)
		int32 GetItemQuantity(TSubclassOf<UCA_InventoryItem> ItemClass);

	// Get the index of a specific item in the inventory
	UFUNCTION(BlueprintCallable)
		int32 GetItemIndex(TSubclassOf<UCA_InventoryItem> ItemClass);

	UFUNCTION(BlueprintCallable)
		void IncreaseInventorySize(int32 SizeAdded);
};
