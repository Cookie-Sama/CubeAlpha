#include "Character/CA_CharacterBase.h"
#include "Components/CapsuleComponent.h"
#include "CA_AbilitySystemComponent.h"
#include "CA_CombatAttributeSet.h"
#include "CA_HealthAttributeSet.h"
#include "CA_MovementAttributeSet.h"
#include "CA_RPGStatsAttributeSet.h"
#include "CubeAlphaStatsRow.h"
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

	//TODO FIXME figure how to move it to PlayerState
	/*AbilitySystemComponent->RegisterGameplayTagEvent(FGameplayTag::RequestGameplayTag(FName("State.Debuff.Stun")), EGameplayTagEventType::NewOrRemoved).AddUObject(this, &ACA_CharacterBase::StunTagChanged);
	AbilitySystemComponent->RegisterGameplayTagEvent(FGameplayTag::RequestGameplayTag(FName("State.Debuff.SpeedDowned")), EGameplayTagEventType::NewOrRemoved).AddUObject(this, &ACA_CharacterBase::SpeedDownTagChanged);
	AbilitySystemComponent->RegisterGameplayTagEvent(FGameplayTag::RequestGameplayTag(FName("State.Buff.SpeedBoosted")), EGameplayTagEventType::NewOrRemoved).AddUObject(this, &ACA_CharacterBase::SpeedBoostTagChanged);*/
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
	if (GetLocalRole() != ROLE_Authority || !AbilitySystemComponent.IsValid() || !AbilitySystemComponent->CharacterAbilitiesGiven) {
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

	if(AbilitySystemComponent.IsValid())
	{
		AbilitySystemComponent->CancelAbilities();

		FGameplayTagContainer EffectTagsToRemove;
		EffectTagsToRemove.AddTag(EffectRemoveOnDeathTag);
		AbilitySystemComponent->RemoveActiveEffectsWithTags(EffectTagsToRemove);
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
	return AbilitySystemComponent.Get();
}

void ACA_CharacterBase::AddCharacterAbilities()
{
	if (GetLocalRole() != ROLE_Authority || !AbilitySystemComponent.IsValid() || AbilitySystemComponent->CharacterAbilitiesGiven) {
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
	if (AbilitySystemComponent.IsValid() && DefaultAttributes)
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
	if (GetLocalRole() != ROLE_Authority || !AbilitySystemComponent.IsValid() || AbilitySystemComponent->StartupEffectsApplied) {
		return;
	}

	FGameplayEffectContextHandle EffectContext = AbilitySystemComponent->MakeEffectContext();
	EffectContext.AddSourceObject(this);

	for (TSubclassOf<UGameplayEffect> GameplayEffect : StartupEffects)
	{
		FGameplayEffectSpecHandle NewHandle = AbilitySystemComponent->MakeOutgoingSpec(GameplayEffect, RPGStatsAttributeSet->GetLevel(), EffectContext);
		if (NewHandle.IsValid())
		{
			FActiveGameplayEffectHandle ActiveGEHandle = AbilitySystemComponent->ApplyGameplayEffectSpecToTarget(*NewHandle.Data.Get(), AbilitySystemComponent.Get());
		}
	}

	AbilitySystemComponent->StartupEffectsApplied = true;
}

void ACA_CharacterBase::SpeedDownTagChanged(const FGameplayTag CallbackTag, const int32 NewCount)
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

void ACA_CharacterBase::SpeedBoostTagChanged(const FGameplayTag CallbackTag, const int32 NewCount)
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

void ACA_CharacterBase::StunTagChanged(const FGameplayTag CallbackTag, const int32 NewCount)
{
	if (NewCount > 0)
	{
		GetCharacterMovement()->MovementMode = EMovementMode::MOVE_None;
		FGameplayTagContainer AbilityTagsToCancel;
		AbilityTagsToCancel.AddTag(FGameplayTag::RequestGameplayTag(FName("Ability")));

		FGameplayTagContainer AbilityTagsToIgnore;
		AbilityTagsToIgnore.AddTag(FGameplayTag::RequestGameplayTag(FName("Ability.NotCanceledByStun")));

		AbilitySystemComponent->CancelAbilities(&AbilityTagsToCancel, &AbilityTagsToIgnore);
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

void ACA_CharacterBase::ApplyDamage(const float Damage, const CA_DamageType Type)
{
	const float mitigatedDamage = CalculateMitigatedDamage(Damage, Type);

	SetHealth(GetHealth() - mitigatedDamage);
	if(GetHealth()<=0)
	{
		Die();
	}
}

float ACA_CharacterBase::CalculateMitigatedDamage(const float Damage, const CA_DamageType Type) const
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
void ACA_CharacterBase::Tick(const float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ACA_CharacterBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

#pragma region AttributeSetGetterSetters
float ACA_CharacterBase::GetPhysicalDamage() const
{
	if (CombatAttributeSet.IsValid()) {
		return CombatAttributeSet->GetPhysicalDamage();
	}
	return 0.0f;
}

void ACA_CharacterBase::SetPhysicalDamage(const float &NewPhysicalDamage) const
{
	if (CombatAttributeSet.IsValid()) {
		CombatAttributeSet->SetPhysicalDamage(NewPhysicalDamage);
	}
}

float ACA_CharacterBase::GetMagicalDamage() const
{
	if (CombatAttributeSet.IsValid()) {
		return CombatAttributeSet->GetMagicalDamage();
	}
	return 0.0f;
}

void ACA_CharacterBase::SetMagicalDamage(const float& NewMagicalDamage) const
{
	if (CombatAttributeSet.IsValid()) {
		CombatAttributeSet->SetMagicalDamage(NewMagicalDamage);
	}
}

float ACA_CharacterBase::GetPhysicalResistance() const
{
	if (CombatAttributeSet.IsValid()) {
		return CombatAttributeSet->GetPhysicalResistance();
	}
	return 0.0f;
}

void ACA_CharacterBase::SetPhysicalResistance(const float& NewPhysicalResistance) const
{
	if (CombatAttributeSet.IsValid()) {
		CombatAttributeSet->SetPhysicalResistance(NewPhysicalResistance);
	}
}

float ACA_CharacterBase::GetMagicalResistance() const
{
	if (CombatAttributeSet.IsValid()) {
		return CombatAttributeSet->GetMagicalResistance();
	}
	return 0.0f;
}

void ACA_CharacterBase::SetMagicalResistance(const float& NewMagicalResistance) const
{
	if (CombatAttributeSet.IsValid()) {
		CombatAttributeSet->SetMagicalResistance(NewMagicalResistance);
	}
}

float ACA_CharacterBase::GetDefense() const
{
	if (CombatAttributeSet.IsValid()) {
		return CombatAttributeSet->GetDefense();
	}
	return 0.0f;
}

void ACA_CharacterBase::SetDefense(const float& NewDefense) const
{
	if (CombatAttributeSet.IsValid()) {
		CombatAttributeSet->SetDefense(NewDefense);
	}
}

float ACA_CharacterBase::GetHealth() const
{
	if (HealthAttributeSet.IsValid()) {
		return HealthAttributeSet->GetHealth();
	}
	return 0.0f;
}

void ACA_CharacterBase::SetHealth(const float& NewHealth) const
{
	if (HealthAttributeSet.IsValid()) {
		HealthAttributeSet->SetHealth(NewHealth);
	}
}

float ACA_CharacterBase::GetMaxHealth() const
{
	if (HealthAttributeSet.IsValid()) {
		return HealthAttributeSet->GetMaxHealth();
	}
	return 0.0f;
}

void ACA_CharacterBase::SetMaxHealth(const float& NewMaxHealth) const
{
	if (HealthAttributeSet.IsValid()) {
		HealthAttributeSet->SetMaxHealth(NewMaxHealth);
	}
}

float ACA_CharacterBase::GetHealthRegen() const
{
	if (HealthAttributeSet.IsValid()) {
		return HealthAttributeSet->GetHealthRegen();
	}
	return 0.0f;
}

void ACA_CharacterBase::SetHealthRegen(const float& NewHealthRegen) const
{
	if (HealthAttributeSet.IsValid()) {
		HealthAttributeSet->SetHealthRegen(NewHealthRegen);
	}
}

float ACA_CharacterBase::GetMoveSpeed() const
{
	if (MovementAttributeSet.IsValid()) {
		return MovementAttributeSet->GetMoveSpeed();
	}
	return 0.0f;
}

void ACA_CharacterBase::SetMoveSpeed(const float& NewMoveSpeed) const
{
	if (MovementAttributeSet.IsValid()) {
		MovementAttributeSet->SetMoveSpeed(NewMoveSpeed);
	}
}

float ACA_CharacterBase::GetJumpHeight() const
{
	if (MovementAttributeSet.IsValid()) {
		return MovementAttributeSet->GetJumpHeight();
	}
	return 0.0f;
}

void ACA_CharacterBase::SetJumpHeight(const float& NewJumpHeight) const
{
	if (MovementAttributeSet.IsValid()) {
		MovementAttributeSet->SetJumpHeight(NewJumpHeight);
	}
}

float ACA_CharacterBase::GetStamina() const
{
	if (MovementAttributeSet.IsValid()) {
		return MovementAttributeSet->GetStamina();
	}
	return 0.0f;
}

void ACA_CharacterBase::SetStamina(const float& NewStamina) const
{
	if (MovementAttributeSet.IsValid()) {
		MovementAttributeSet->SetStamina(NewStamina);
	}
}

float ACA_CharacterBase::GetMaxStamina() const
{
	if (MovementAttributeSet.IsValid()) {
		return MovementAttributeSet->GetMaxStamina();
	}
	return 0.0f;
}

void ACA_CharacterBase::SetMaxStamina(const float& NewMaxStamina) const
{
	if (MovementAttributeSet.IsValid()) {
		MovementAttributeSet->SetMaxStamina(NewMaxStamina);
	}
}

float ACA_CharacterBase::GetBaseVitality() const
{
	if (RPGStatsAttributeSet.IsValid()) {
		return RPGStatsAttributeSet->GetBaseVitality();
	}
	return 0.0f;
}

void ACA_CharacterBase::SetBaseVitality(const float& NewBaseVitality) const
{
	if (RPGStatsAttributeSet.IsValid()) {
		RPGStatsAttributeSet->SetBaseVitality(NewBaseVitality);
	}
}

float ACA_CharacterBase::GetVitality() const
{
	if (RPGStatsAttributeSet.IsValid()) {
		return RPGStatsAttributeSet->GetVitality();
	}
	return 0.0f;
}

void ACA_CharacterBase::SetVitality(const float& NewVitality) const
{
	if (RPGStatsAttributeSet.IsValid()) {
		RPGStatsAttributeSet->SetVitality(NewVitality);
	}
}

float ACA_CharacterBase::GetBaseStrength() const
{
	if (RPGStatsAttributeSet.IsValid()) {
		return RPGStatsAttributeSet->GetBaseStrength();
	}
	return 0.0f;
}

void ACA_CharacterBase::SetBaseStrength(const float& NewBaseStrength) const
{
	if (RPGStatsAttributeSet.IsValid()) {
		RPGStatsAttributeSet->SetBaseStrength(NewBaseStrength);
	}
}

float ACA_CharacterBase::GetStrength() const
{
	if (RPGStatsAttributeSet.IsValid()) {
		return RPGStatsAttributeSet->GetStrength();
	}
	return 0.0f;
}

void ACA_CharacterBase::SetStrength(const float& NewStrength) const
{
	if (RPGStatsAttributeSet.IsValid()) {
		RPGStatsAttributeSet->SetStrength(NewStrength);
	}
}

float ACA_CharacterBase::GetBaseIntelligence() const
{
	if (RPGStatsAttributeSet.IsValid()) {
		return RPGStatsAttributeSet->GetBaseIntelligence();
	}
	return 0.0f;
}

void ACA_CharacterBase::SetBaseIntelligence(const float& NewBaseIntelligence) const
{
	if (RPGStatsAttributeSet.IsValid()) {
		RPGStatsAttributeSet->SetBaseIntelligence(NewBaseIntelligence);
	}
}

float ACA_CharacterBase::GetIntelligence() const
{
	if (RPGStatsAttributeSet.IsValid()) {
		return RPGStatsAttributeSet->GetIntelligence();
	}
	return 0.0f;
}

void ACA_CharacterBase::SetIntelligence(const float& NewIntelligence) const
{
	if (RPGStatsAttributeSet.IsValid()) {
		RPGStatsAttributeSet->SetIntelligence(NewIntelligence);
	}
}

float ACA_CharacterBase::GetBaseAgility() const
{
	if (RPGStatsAttributeSet.IsValid()) {
		return RPGStatsAttributeSet->GetBaseAgility();
	}
	return 0.0f;
}

void ACA_CharacterBase::SetBaseAgility(const float& NewBaseAgility) const
{
	if (RPGStatsAttributeSet.IsValid()) {
		RPGStatsAttributeSet->SetBaseAgility(NewBaseAgility);
	}
}

float ACA_CharacterBase::GetAgility() const
{
	if (RPGStatsAttributeSet.IsValid()) {
		return RPGStatsAttributeSet->GetAgility();
	}
	return 0.0f;
}

void ACA_CharacterBase::SetAgility(const float& NewAgility) const
{
	if (RPGStatsAttributeSet.IsValid()) {
		RPGStatsAttributeSet->SetAgility(NewAgility);
	}
}

float ACA_CharacterBase::GetBaseEndurance() const
{
	if (RPGStatsAttributeSet.IsValid()) {
		return RPGStatsAttributeSet->GetBaseEndurance();
	}
	return 0.0f;
}

void ACA_CharacterBase::SetBaseEndurance(const float& NewBaseEndurance) const
{
	if (RPGStatsAttributeSet.IsValid()) {
		RPGStatsAttributeSet->SetBaseEndurance(NewBaseEndurance);
	}
}

float ACA_CharacterBase::GetEndurance() const
{
	if (RPGStatsAttributeSet.IsValid()) {
		return RPGStatsAttributeSet->GetEndurance();
	}
	return 0.0f;
}

void ACA_CharacterBase::SetEndurance(const float& NewEndurance) const
{
	if (RPGStatsAttributeSet.IsValid()) {
		RPGStatsAttributeSet->SetEndurance(NewEndurance);
	}
}

float ACA_CharacterBase::GetCharacterLevel() const
{
	if (RPGStatsAttributeSet.IsValid()) {
		return RPGStatsAttributeSet->GetLevel();
	}
	return 0.0f;
}

void ACA_CharacterBase::SetCharacterLevel(const float& NewLevel) const
{
	if (RPGStatsAttributeSet.IsValid()) {
		RPGStatsAttributeSet->SetLevel(NewLevel);
	}
}
#pragma endregion

void ACA_CharacterBase::LevelUp() const
{
	if (GetCharacterLevel() < 10) {
		const float NewLevel = GetCharacterLevel() + 1;
		SetCharacterLevel(NewLevel);
		FString ContextString;
		FCA_StatsRow* StatsRow = StatsDataTable->FindRow<FCA_StatsRow>(FName(*FString::Printf(TEXT("%f"), NewLevel)), ContextString);
		if(StatsRow)
		{
			SetBaseVitality(StatsRow->Vitality);
			SetBaseStrength(StatsRow->Strength);
			SetBaseIntelligence(StatsRow->Intelligence);
			SetBaseAgility(StatsRow->Agility);
			SetBaseEndurance(StatsRow->Endurance);
			//TODO Update real stats
		}
		SetHealth(GetMaxHealth());
		SetStamina(GetMaxStamina());
	}
}
