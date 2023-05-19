#include "Character/CA_CharacterBase.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

// Sets default values
ACA_CharacterBase::ACA_CharacterBase(const class FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer.SetDefaultSubobjectClass<UCharacterMovementComponent>(ACharacter::CharacterMovementComponentName))
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	GetCapsuleComponent()->SetCollisionResponseToChannel(ECollisionChannel::ECC_Visibility, ECollisionResponse::ECR_Overlap);

	bAlwaysRelevant = true;
	DeadTag = FGameplayTag::RequestGameplayTag("State.Dead");
	EffectRemoveOnDeathTag = FGameplayTag::RequestGameplayTag("State.RemoveOnDeath");

	AbilitySystemComponent->RegisterGameplayTagEvent(FGameplayTag::RequestGameplayTag(FName("State.Debuff.Stun")), EGameplayTagEventType::NewOrRemoved).AddUObject(this, &ACA_CharacterBase::StunTagChanged);
	AbilitySystemComponent->RegisterGameplayTagEvent(FGameplayTag::RequestGameplayTag(FName("State.Debuff.SpeedDowned")), EGameplayTagEventType::NewOrRemoved).AddUObject(this, &ACA_CharacterBase::SpeedDownTagChanged);
	AbilitySystemComponent->RegisterGameplayTagEvent(FGameplayTag::RequestGameplayTag(FName("State.Buff.SpeedBoosted")), EGameplayTagEventType::NewOrRemoved).AddUObject(this, &ACA_CharacterBase::SpeedBoostTagChanged);
}

bool ACA_CharacterBase::IsAlive() const
{
	return GetHealth() > 0.0f;
}

int32 ACA_CharacterBase::GetAbilityLevel(CA_AbilityID AbilityID) const
{
	return 1;//TODO Need rework
}

void ACA_CharacterBase::RemoveCharacterAbilities()
{
	if (GetLocalRole() != ROLE_Authority || !IsValid(AbilitySystemComponent) || !AbilitySystemComponent->CharacterAbilitiesGiven) {
		return;
	}
	TArray<FGameplayAbilitySpecHandle> AbilitiesToRemove;
	for (const FGameplayAbilitySpec& Spec : AbilitySystemComponent->GetActivatableAbilities())
	{
		if ((Spec.SourceObject == this) && CharacterAbilities.Contains(Spec.Ability->GetClass()))
		{
			AbilitiesToRemove.Add(Spec.Handle);
		}
	}

	for (int32 i = 0; i < AbilitiesToRemove.Num(); i++) {
		AbilitySystemComponent->ClearAbility(AbilitiesToRemove[i]);
	}

	AbilitySystemComponent->CharacterAbilitiesGiven = false;
}

void ACA_CharacterBase::Die()
{
	RemoveCharacterAbilities();
	GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	GetCharacterMovement()->GravityScale = 0;
	GetCharacterMovement()->Velocity = FVector(0);

	OnCharacterDied.Broadcast(this);

	if(IsValid(AbilitySystemComponent))
	{
		AbilitySystemComponent->CancelAbilities();

		FGameplayTagContainer EffectTagsToRemove;
		EffectTagsToRemove.AddTag(EffectRemoveOnDeathTag);
		int32 NumEffectsEremoved = AbilitySystemComponent->RemoveActiveEffectsWithTags(EffectTagsToRemove);
		AbilitySystemComponent->AddLooseGameplayTag(DeadTag);
	}
	if(DeathMontage)
	{
		MulticastRPCPlayDeathAnimation();
	}
	else
	{
		FinishDying();
	}
}

void ACA_CharacterBase::FinishDying()
{
	Destroy();
}

UAbilitySystemComponent* ACA_CharacterBase::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

void ACA_CharacterBase::AddCharacterAbilities()
{
	if (GetLocalRole() != ROLE_Authority || !IsValid(AbilitySystemComponent) || AbilitySystemComponent->CharacterAbilitiesGiven) {
		return;
	}

	for (TSubclassOf<UCA_GameplayAbility>& StartupAbility : CharacterAbilities)
	{
		AbilitySystemComponent->GiveAbility(FGameplayAbilitySpec(StartupAbility, 1, static_cast<int32>(Cast<UCA_GameplayAbility>(StartupAbility->GetDefaultObject())->AbilityID), this));
	}

	AbilitySystemComponent->CharacterAbilitiesGiven = true;
}

void ACA_CharacterBase::InitializeAttributes()
{
	if (AbilitySystemComponent && DefaultAttributes)
	{
		FGameplayEffectContextHandle EffectContext = AbilitySystemComponent->MakeEffectContext();
		EffectContext.AddSourceObject(this);
		const FGameplayEffectSpecHandle SpecHandle = AbilitySystemComponent->MakeOutgoingSpec(DefaultAttributes, RPGStatsAttributeSet->GetLevel(), EffectContext);
		if (SpecHandle.IsValid())
		{
			FActiveGameplayEffectHandle ActiveGEHandle = AbilitySystemComponent->ApplyGameplayEffectSpecToSelf(*SpecHandle.Data.Get());
		}
	}
	else if (!DefaultAttributes)
	{
		UE_LOG(LogTemp, Error, TEXT("%s() Missing DefaultAttributes for %s. Please fill in the character's Blueprint"), *FString(__FUNCTION__), *GetName());
		return;
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Problem with Ability System Component"));
		return;
	}
}

void ACA_CharacterBase::AddStartupEffects()
{
	if (GetLocalRole() != ROLE_Authority || !IsValid(AbilitySystemComponent) || AbilitySystemComponent->StartupEffectsApplied) {
		return;
	}

	FGameplayEffectContextHandle EffectContext = AbilitySystemComponent->MakeEffectContext();
	EffectContext.AddSourceObject(this);

	for (TSubclassOf<UGameplayEffect> GameplayEffect : StartupEffects)
	{
		FGameplayEffectSpecHandle NewHandle = AbilitySystemComponent->MakeOutgoingSpec(GameplayEffect, RPGStatsAttributeSet->GetLevel(), EffectContext);
		if (NewHandle.IsValid())
		{
			FActiveGameplayEffectHandle ActiveGEHandle = AbilitySystemComponent->ApplyGameplayEffectSpecToTarget(*NewHandle.Data.Get(), AbilitySystemComponent);
		}
	}

	AbilitySystemComponent->StartupEffectsApplied = true;
}

void ACA_CharacterBase::SpeedDownTagChanged(const FGameplayTag CallbackTag, int32 NewCount)
{
	if (NewCount > 0)
	{
		GetCharacterMovement()->MaxWalkSpeed = (GetMoveSpeed()/2)*600;
	}
	else if (NewCount == 0)
	{
		GetCharacterMovement()->MaxWalkSpeed = GetMoveSpeed()*600;
	}
}

void ACA_CharacterBase::SpeedBoostTagChanged(const FGameplayTag CallbackTag, int32 NewCount)
{
	if (NewCount > 0)
	{
		GetCharacterMovement()->MaxWalkSpeed = (GetMoveSpeed() *1.5) * 600;
	}
	else if (NewCount == 0)
	{
		GetCharacterMovement()->MaxWalkSpeed = GetMoveSpeed() * 600;
	}
}

void ACA_CharacterBase::StunTagChanged(const FGameplayTag CallbackTag, int32 NewCount)
{
	if (NewCount > 0)
	{
		GetCharacterMovement()->MovementMode = EMovementMode::MOVE_None;
	}
	else if (NewCount == 0)
	{
		GetCharacterMovement()->MovementMode = EMovementMode::MOVE_Walking;
	}
}

// Called when the game starts or when spawned
void ACA_CharacterBase::BeginPlay()
{
	Super::BeginPlay();
	
}

void ACA_CharacterBase::ApplyDamage(float Damage, CA_DamageType Type)
{
	const float mitigatedDamage = CalculateMitigatedDamage(Damage, Type);

	SetHealth(GetHealth() - mitigatedDamage);
	if(GetHealth()<=0)
	{
		Die();
	}
}

float ACA_CharacterBase::CalculateMitigatedDamage(float Damage, CA_DamageType Type) const
{
	float mitigatedDamage = Damage - GetDefense();
	if(Type == CA_DamageType::Physical)
	{
		mitigatedDamage -= mitigatedDamage * GetPhysicalResistance();
	}
	else
	{
		mitigatedDamage -= mitigatedDamage * GetMagicalResistance();
	}

	mitigatedDamage = FMath::Max(mitigatedDamage, 0.0f); //To Avoid negative damage

	return mitigatedDamage;
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

float ACA_CharacterBase::GetPhysicalDamage() const
{
	return CombatAttributeSet->GetPhysicalDamage();
}

void ACA_CharacterBase::SetPhysicalDamage(const float &NewPhysicalDamage) const
{
	CombatAttributeSet->SetPhysicalDamage(NewPhysicalDamage);
}

float ACA_CharacterBase::GetMagicalDamage() const
{
	return CombatAttributeSet->GetMagicalDamage();
}

void ACA_CharacterBase::SetMagicalDamage(const float& NewMagicalDamage) const
{
	CombatAttributeSet->SetMagicalDamage(NewMagicalDamage);
}

float ACA_CharacterBase::GetPhysicalResistance() const
{
	return CombatAttributeSet->GetPhysicalResistance();
}

void ACA_CharacterBase::SetPhysicalResistance(const float& NewPhysicalResistance) const
{
	CombatAttributeSet->SetPhysicalResistance(NewPhysicalResistance);
}

float ACA_CharacterBase::GetMagicalResistance() const
{
	return CombatAttributeSet->GetMagicalResistance();
}

void ACA_CharacterBase::SetMagicalResistance(const float& NewMagicalResistance) const
{
	CombatAttributeSet->SetMagicalResistance(NewMagicalResistance);
}

float ACA_CharacterBase::GetDefense() const
{
	return CombatAttributeSet->GetDefense();
}

void ACA_CharacterBase::SetDefense(const float& NewDefense) const
{
	CombatAttributeSet->SetDefense(NewDefense);
}

float ACA_CharacterBase::GetHealth() const
{
	return HealthAttributeSet->GetHealth();
}

void ACA_CharacterBase::SetHealth(const float& NewHealth) const
{
	HealthAttributeSet->SetHealth(NewHealth);
}

float ACA_CharacterBase::GetMaxHealth() const
{
	return HealthAttributeSet->GetMaxHealth();
}

void ACA_CharacterBase::SetMaxHealth(const float& NewMaxHealth) const
{
	HealthAttributeSet->SetMaxHealth(NewMaxHealth);
}

float ACA_CharacterBase::GetHealthRegen() const
{
	return HealthAttributeSet->GetHealthRegen();
}

void ACA_CharacterBase::SetHealthRegen(const float& NewHealthRegen) const
{
	HealthAttributeSet->SetHealthRegen(NewHealthRegen);
}

float ACA_CharacterBase::GetMoveSpeed() const
{
	return MovementAttributeSet->GetMoveSpeed();
}

void ACA_CharacterBase::SetMoveSpeed(const float& NewMoveSpeed) const
{
	MovementAttributeSet->SetMoveSpeed(NewMoveSpeed);
}

float ACA_CharacterBase::GetJumpHeight() const
{
	return MovementAttributeSet->GetJumpHeight();
}

void ACA_CharacterBase::SetJumpHeight(const float& NewJumpHeight) const
{
	MovementAttributeSet->SetJumpHeight(NewJumpHeight);
}

float ACA_CharacterBase::GetBaseVitality() const
{
	return RPGStatsAttributeSet->GetBaseVitality();
}

void ACA_CharacterBase::SetBaseVitality(const float& NewBaseVitality) const
{
	RPGStatsAttributeSet->SetBaseVitality(NewBaseVitality);
}

float ACA_CharacterBase::GetVitality() const
{
	return RPGStatsAttributeSet->GetVitality();
}

void ACA_CharacterBase::SetVitality(const float& NewVitality) const
{
	RPGStatsAttributeSet->SetVitality(NewVitality);
}

float ACA_CharacterBase::GetBaseStrength() const
{
	return RPGStatsAttributeSet->GetBaseStrength();
}

void ACA_CharacterBase::SetBaseStrength(const float& NewBaseStrength) const
{
	RPGStatsAttributeSet->SetBaseStrength(NewBaseStrength);
}

float ACA_CharacterBase::GetStrength() const
{
	return RPGStatsAttributeSet->GetStrength();
}

void ACA_CharacterBase::SetStrength(const float& NewStrength) const
{
	RPGStatsAttributeSet->SetStrength(NewStrength);
}

float ACA_CharacterBase::GetBaseIntelligence() const
{
	return RPGStatsAttributeSet->GetBaseIntelligence();
}

void ACA_CharacterBase::SetBaseIntelligence(const float& NewBaseIntelligence) const
{
	RPGStatsAttributeSet->SetBaseIntelligence(NewBaseIntelligence);
}

float ACA_CharacterBase::GetIntelligence() const
{
	return RPGStatsAttributeSet->GetIntelligence();
}

void ACA_CharacterBase::SetIntelligence(const float& NewIntelligence) const
{
	RPGStatsAttributeSet->SetIntelligence(NewIntelligence);
}

float ACA_CharacterBase::GetBaseAgility() const
{
	return RPGStatsAttributeSet->GetBaseAgility();
}

void ACA_CharacterBase::SetBaseAgility(const float& NewBaseAgility) const
{
	RPGStatsAttributeSet->SetBaseAgility(NewBaseAgility);
}

float ACA_CharacterBase::GetAgility() const
{
	return RPGStatsAttributeSet->GetAgility();
}

void ACA_CharacterBase::SetAgility(const float& NewAgility) const
{
	RPGStatsAttributeSet->SetAgility(NewAgility);
}

float ACA_CharacterBase::GetBaseEndurance() const
{
	return RPGStatsAttributeSet->GetBaseEndurance();
}

void ACA_CharacterBase::SetBaseEndurance(const float& NewBaseEndurance) const
{
	RPGStatsAttributeSet->SetBaseEndurance(NewBaseEndurance);
}

float ACA_CharacterBase::GetEndurance() const
{
	return RPGStatsAttributeSet->GetEndurance();
}

void ACA_CharacterBase::SetEndurance(const float& NewEndurance) const
{
	RPGStatsAttributeSet->SetEndurance(NewEndurance);
}

float ACA_CharacterBase::GetCharacterLevel() const
{
	return RPGStatsAttributeSet->GetLevel();
}

void ACA_CharacterBase::SetCharacterLevel(const float& NewLevel) const
{
	RPGStatsAttributeSet->SetLevel(NewLevel);
}

void ACA_CharacterBase::LevelUp() const
{
	if (GetCharacterLevel() < 10) {
		const float NewLevel = GetCharacterLevel() + 1;
		SetCharacterLevel(NewLevel);
		//TODO Update Stats
		FString ContextString;
		FCA_StatsRow* StatsRow = StatsDataTable->FindRow<FCA_StatsRow>(FName(*FString::Printf(TEXT("%f"), NewLevel)), ContextString);
		if(StatsRow){}
	}
}
