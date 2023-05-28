#include "Character/CA_CharacterBase.h"
#include "Components/CapsuleComponent.h"
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

	AbilitySystemComponent = CreateDefaultSubobject<UCA_AbilitySystemComponent>("AbilitySystemComp");
	AbilitySystemComponent->SetIsReplicated(true);
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Mixed);

	CombatAttributeSet = CreateDefaultSubobject<UCA_CombatAttributeSet>("Combat Attribute Set");
	HealthAttributeSet = CreateDefaultSubobject<UCA_HealthAttributeSet>("Health Attribute Set");
	MovementAttributeSet = CreateDefaultSubobject<UCA_MovementAttributeSet>("Movement Attribute Set");
	RPGStatsAttributeSet = CreateDefaultSubobject<UCA_RPGStatsAttributeSet>("RPG Stats Attribute Set");

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
	if (GetLocalRole() != ROLE_Authority || !AbilitySystemComponent || !AbilitySystemComponent->CharacterAbilitiesGiven) {
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

	if(AbilitySystemComponent)
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
	return AbilitySystemComponent;
}

void ACA_CharacterBase::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	if (AbilitySystemComponent)
	{
		AbilitySystemComponent->InitAbilityActorInfo(this, this);
	}
	InitializeAttributes();
	GiveDefaultAbilities();
}

void ACA_CharacterBase::OnRep_PlayerState()
{
	Super::OnRep_PlayerState();
	if (AbilitySystemComponent)
	{
		AbilitySystemComponent->InitAbilityActorInfo(this, this);
	}
	UE_LOG(LogTemp, Error, TEXT("LA"));
	InitializeAttributes();
}

void ACA_CharacterBase::GiveDefaultAbilities()
{
	if (HasAuthority() && AbilitySystemComponent)
	{
		for (TSubclassOf<UCA_GameplayAbility>& StartupAbility : CharacterAbilities)
		{
			AbilitySystemComponent->GiveAbility(FGameplayAbilitySpec(StartupAbility.GetDefaultObject(), 1, 0));
		}
	}
}

void ACA_CharacterBase::AddCharacterAbilities()
{
	if (GetLocalRole() != ROLE_Authority || !AbilitySystemComponent || AbilitySystemComponent->CharacterAbilitiesGiven) {
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
	if (GetLocalRole() != ROLE_Authority || !AbilitySystemComponent || AbilitySystemComponent->StartupEffectsApplied) {
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

	if (AbilitySystemComponent)
	{
		PhysicalDamageChangedDelegateHandle = AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(CombatAttributeSet->GetPhysicalDamageAttribute()).AddUObject(this, &ACA_CharacterBase::PhysicalDamageChanged);
		MagicalDamageChangedDelegateHandle = AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(CombatAttributeSet->GetMagicalDamageAttribute()).AddUObject(this, &ACA_CharacterBase::MagicalDamageChanged);
		PhysicalResistanceChangedDelegateHandle = AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(CombatAttributeSet->GetPhysicalResistanceAttribute()).AddUObject(this, &ACA_CharacterBase::PhysicalResistanceChanged);
		PhysicalResistanceChangedDelegateHandle = AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(CombatAttributeSet->GetMagicalResistanceAttribute()).AddUObject(this, &ACA_CharacterBase::MagicalResistanceChanged);
		DefenseChangedDelegateHandle = AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(CombatAttributeSet->GetDefenseAttribute()).AddUObject(this, &ACA_CharacterBase::DefenseChanged);

		HealthChangedDelegateHandle = AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(HealthAttributeSet->GetHealthAttribute()).AddUObject(this, &ACA_CharacterBase::HealthChanged);
		MaxHealthChangedDelegateHandle = AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(HealthAttributeSet->GetMaxHealthAttribute()).AddUObject(this, &ACA_CharacterBase::MaxHealthChanged);
		HealthRegenChangedDelegateHandle = AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(HealthAttributeSet->GetHealthRegenAttribute()).AddUObject(this, &ACA_CharacterBase::HealthRegenChanged);

		MoveSpeedChangedDelegateHandle = AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(MovementAttributeSet->GetMoveSpeedAttribute()).AddUObject(this, &ACA_CharacterBase::MoveSpeedChanged);
		JumpHeightChangedDelegateHandle = AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(MovementAttributeSet->GetJumpHeightAttribute()).AddUObject(this, &ACA_CharacterBase::JumpHeightChanged);
		StaminaChangedDelegateHandle = AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(MovementAttributeSet->GetStaminaAttribute()).AddUObject(this, &ACA_CharacterBase::StaminaChanged);
		MaxStaminaChangedDelegateHandle = AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(MovementAttributeSet->GetMaxStaminaAttribute()).AddUObject(this, &ACA_CharacterBase::MaxStaminaChanged);

		BaseVitalityChangedDelegateHandle = AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(RPGStatsAttributeSet->GetBaseVitalityAttribute()).AddUObject(this, &ACA_CharacterBase::BaseVitalityChanged);
		VitalityChangedDelegateHandle = AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(RPGStatsAttributeSet->GetVitalityAttribute()).AddUObject(this, &ACA_CharacterBase::VitalityChanged);
		BaseStrengthChangedDelegateHandle = AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(RPGStatsAttributeSet->GetBaseStrengthAttribute()).AddUObject(this, &ACA_CharacterBase::BaseStrengthChanged);
		StrengthChangedDelegateHandle = AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(RPGStatsAttributeSet->GetStrengthAttribute()).AddUObject(this, &ACA_CharacterBase::StrengthChanged);
		BaseIntelligenceChangedDelegateHandle = AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(RPGStatsAttributeSet->GetBaseIntelligenceAttribute()).AddUObject(this, &ACA_CharacterBase::BaseIntelligenceChanged);
		IntelligenceChangedDelegateHandle = AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(RPGStatsAttributeSet->GetIntelligenceAttribute()).AddUObject(this, &ACA_CharacterBase::IntelligenceChanged);
		BaseAgilityChangedDelegateHandle = AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(RPGStatsAttributeSet->GetBaseAgilityAttribute()).AddUObject(this, &ACA_CharacterBase::BaseAgilityChanged);
		AgilityChangedDelegateHandle = AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(RPGStatsAttributeSet->GetAgilityAttribute()).AddUObject(this, &ACA_CharacterBase::AgilityChanged);
		BaseEnduranceChangedDelegateHandle = AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(RPGStatsAttributeSet->GetBaseEnduranceAttribute()).AddUObject(this, &ACA_CharacterBase::BaseEnduranceChanged);
		EnduranceChangedDelegateHandle = AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(RPGStatsAttributeSet->GetEnduranceAttribute()).AddUObject(this, &ACA_CharacterBase::EnduranceChanged);
		CharacterLevelChangedDelegateHandle = AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(RPGStatsAttributeSet->GetLevelAttribute()).AddUObject(this, &ACA_CharacterBase::CharacterLevelChanged);
	}

	GetCharacterMovement()->JumpZVelocity = 700 * GetJumpHeight();//700 cm/s is the base jump height in Unreal
	GetCharacterMovement()->MaxWalkSpeed = 500 * GetMoveSpeed();
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
	if (CombatAttributeSet) {
		return CombatAttributeSet->GetPhysicalDamage();
	}
	return 0.0f;
}

void ACA_CharacterBase::SetPhysicalDamage(const float &NewPhysicalDamage) const
{
	if (CombatAttributeSet) {
		CombatAttributeSet->SetPhysicalDamage(NewPhysicalDamage);
	}
}

float ACA_CharacterBase::GetMagicalDamage() const
{
	if (CombatAttributeSet) {
		return CombatAttributeSet->GetMagicalDamage();
	}
	return 0.0f;
}

void ACA_CharacterBase::SetMagicalDamage(const float& NewMagicalDamage) const
{
	if (CombatAttributeSet) {
		CombatAttributeSet->SetMagicalDamage(NewMagicalDamage);
	}
}

float ACA_CharacterBase::GetPhysicalResistance() const
{
	if (CombatAttributeSet) {
		return CombatAttributeSet->GetPhysicalResistance();
	}
	return 0.0f;
}

void ACA_CharacterBase::SetPhysicalResistance(const float& NewPhysicalResistance) const
{
	if (CombatAttributeSet) {
		CombatAttributeSet->SetPhysicalResistance(NewPhysicalResistance);
	}
}

float ACA_CharacterBase::GetMagicalResistance() const
{
	if (CombatAttributeSet) {
		return CombatAttributeSet->GetMagicalResistance();
	}
	return 0.0f;
}

void ACA_CharacterBase::SetMagicalResistance(const float& NewMagicalResistance) const
{
	if (CombatAttributeSet) {
		CombatAttributeSet->SetMagicalResistance(NewMagicalResistance);
	}
}

float ACA_CharacterBase::GetDefense() const
{
	if (CombatAttributeSet) {
		return CombatAttributeSet->GetDefense();
	}
	return 0.0f;
}

void ACA_CharacterBase::SetDefense(const float& NewDefense) const
{
	if (CombatAttributeSet) {
		CombatAttributeSet->SetDefense(NewDefense);
	}
}

float ACA_CharacterBase::GetHealth() const
{
	if (HealthAttributeSet) {
		return HealthAttributeSet->GetHealth();
	}
	return 0.0f;
}

void ACA_CharacterBase::SetHealth(const float& NewHealth) const
{
	if (HealthAttributeSet) {
		HealthAttributeSet->SetHealth(NewHealth);
	}
}

float ACA_CharacterBase::GetMaxHealth() const
{
	if (HealthAttributeSet) {
		return HealthAttributeSet->GetMaxHealth();
	}
	return 0.0f;
}

void ACA_CharacterBase::SetMaxHealth(const float& NewMaxHealth) const
{
	if (HealthAttributeSet) {
		HealthAttributeSet->SetMaxHealth(NewMaxHealth);
	}
}

float ACA_CharacterBase::GetHealthRegen() const
{
	if (HealthAttributeSet) {
		return HealthAttributeSet->GetHealthRegen();
	}
	return 0.0f;
}

void ACA_CharacterBase::SetHealthRegen(const float& NewHealthRegen) const
{
	if (HealthAttributeSet) {
		HealthAttributeSet->SetHealthRegen(NewHealthRegen);
	}
}

float ACA_CharacterBase::GetMoveSpeed() const
{
	if (MovementAttributeSet) {
		return MovementAttributeSet->GetMoveSpeed();
	}
	return 0.0f;
}

void ACA_CharacterBase::SetMoveSpeed(const float& NewMoveSpeed) const
{
	if (MovementAttributeSet) {
		MovementAttributeSet->SetMoveSpeed(NewMoveSpeed);
	}
}

float ACA_CharacterBase::GetJumpHeight() const
{
	if (MovementAttributeSet) {
		return MovementAttributeSet->GetJumpHeight();
	}
	return 0.0f;
}

void ACA_CharacterBase::SetJumpHeight(const float& NewJumpHeight) const
{
	if (MovementAttributeSet) {
		MovementAttributeSet->SetJumpHeight(NewJumpHeight);
	}
}

float ACA_CharacterBase::GetStamina() const
{
	if (MovementAttributeSet) {
		return MovementAttributeSet->GetStamina();
	}
	return 0.0f;
}

void ACA_CharacterBase::SetStamina(const float& NewStamina) const
{
	if (MovementAttributeSet) {
		MovementAttributeSet->SetStamina(NewStamina);
	}
}

float ACA_CharacterBase::GetMaxStamina() const
{
	if (MovementAttributeSet) {
		return MovementAttributeSet->GetMaxStamina();
	}
	return 0.0f;
}

void ACA_CharacterBase::SetMaxStamina(const float& NewMaxStamina) const
{
	if (MovementAttributeSet) {
		MovementAttributeSet->SetMaxStamina(NewMaxStamina);
	}
}

float ACA_CharacterBase::GetBaseVitality() const
{
	if (RPGStatsAttributeSet) {
		return RPGStatsAttributeSet->GetBaseVitality();
	}
	return 0.0f;
}

void ACA_CharacterBase::SetBaseVitality(const float& NewBaseVitality) const
{
	if (RPGStatsAttributeSet) {
		RPGStatsAttributeSet->SetBaseVitality(NewBaseVitality);
	}
}

float ACA_CharacterBase::GetVitality() const
{
	if (RPGStatsAttributeSet) {
		return RPGStatsAttributeSet->GetVitality();
	}
	return 0.0f;
}

void ACA_CharacterBase::SetVitality(const float& NewVitality) const
{
	if (RPGStatsAttributeSet) {
		RPGStatsAttributeSet->SetVitality(NewVitality);
	}
}

float ACA_CharacterBase::GetBaseStrength() const
{
	if (RPGStatsAttributeSet) {
		return RPGStatsAttributeSet->GetBaseStrength();
	}
	return 0.0f;
}

void ACA_CharacterBase::SetBaseStrength(const float& NewBaseStrength) const
{
	if (RPGStatsAttributeSet) {
		RPGStatsAttributeSet->SetBaseStrength(NewBaseStrength);
	}
}

float ACA_CharacterBase::GetStrength() const
{
	if (RPGStatsAttributeSet) {
		return RPGStatsAttributeSet->GetStrength();
	}
	return 0.0f;
}

void ACA_CharacterBase::SetStrength(const float& NewStrength) const
{
	if (RPGStatsAttributeSet) {
		RPGStatsAttributeSet->SetStrength(NewStrength);
	}
}

float ACA_CharacterBase::GetBaseIntelligence() const
{
	if (RPGStatsAttributeSet) {
		return RPGStatsAttributeSet->GetBaseIntelligence();
	}
	return 0.0f;
}

void ACA_CharacterBase::SetBaseIntelligence(const float& NewBaseIntelligence) const
{
	if (RPGStatsAttributeSet) {
		RPGStatsAttributeSet->SetBaseIntelligence(NewBaseIntelligence);
	}
}

float ACA_CharacterBase::GetIntelligence() const
{
	if (RPGStatsAttributeSet) {
		return RPGStatsAttributeSet->GetIntelligence();
	}
	return 0.0f;
}

void ACA_CharacterBase::SetIntelligence(const float& NewIntelligence) const
{
	if (RPGStatsAttributeSet) {
		RPGStatsAttributeSet->SetIntelligence(NewIntelligence);
	}
}

float ACA_CharacterBase::GetBaseAgility() const
{
	if (RPGStatsAttributeSet) {
		return RPGStatsAttributeSet->GetBaseAgility();
	}
	return 0.0f;
}

void ACA_CharacterBase::SetBaseAgility(const float& NewBaseAgility) const
{
	if (RPGStatsAttributeSet) {
		RPGStatsAttributeSet->SetBaseAgility(NewBaseAgility);
	}
}

float ACA_CharacterBase::GetAgility() const
{
	if (RPGStatsAttributeSet) {
		return RPGStatsAttributeSet->GetAgility();
	}
	return 0.0f;
}

void ACA_CharacterBase::SetAgility(const float& NewAgility) const
{
	if (RPGStatsAttributeSet) {
		RPGStatsAttributeSet->SetAgility(NewAgility);
	}
}

float ACA_CharacterBase::GetBaseEndurance() const
{
	if (RPGStatsAttributeSet) {
		return RPGStatsAttributeSet->GetBaseEndurance();
	}
	return 0.0f;
}

void ACA_CharacterBase::SetBaseEndurance(const float& NewBaseEndurance) const
{
	if (RPGStatsAttributeSet) {
		RPGStatsAttributeSet->SetBaseEndurance(NewBaseEndurance);
	}
}

float ACA_CharacterBase::GetEndurance() const
{
	if (RPGStatsAttributeSet) {
		return RPGStatsAttributeSet->GetEndurance();
	}
	return 0.0f;
}

void ACA_CharacterBase::SetEndurance(const float& NewEndurance) const
{
	if (RPGStatsAttributeSet) {
		RPGStatsAttributeSet->SetEndurance(NewEndurance);
	}
}

float ACA_CharacterBase::GetCharacterLevel() const
{
	if (RPGStatsAttributeSet) {
		return RPGStatsAttributeSet->GetLevel();
	}
	return 0.0f;
}

void ACA_CharacterBase::SetCharacterLevel(const float& NewLevel) const
{
	if (RPGStatsAttributeSet) {
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

#pragma region AttributeSetChanges
void ACA_CharacterBase::PhysicalDamageChanged(const FOnAttributeChangeData& Data)
{
}

void ACA_CharacterBase::MagicalDamageChanged(const FOnAttributeChangeData& Data)
{
}

void ACA_CharacterBase::PhysicalResistanceChanged(const FOnAttributeChangeData& Data)
{
}

void ACA_CharacterBase::MagicalResistanceChanged(const FOnAttributeChangeData& Data)
{
}

void ACA_CharacterBase::DefenseChanged(const FOnAttributeChangeData& Data)
{
}

void ACA_CharacterBase::HealthChanged(const FOnAttributeChangeData& Data)
{
}

void ACA_CharacterBase::MaxHealthChanged(const FOnAttributeChangeData& Data)
{
}

void ACA_CharacterBase::HealthRegenChanged(const FOnAttributeChangeData& Data)
{
}

void ACA_CharacterBase::MoveSpeedChanged(const FOnAttributeChangeData& Data)
{
}

void ACA_CharacterBase::JumpHeightChanged(const FOnAttributeChangeData& Data)
{
}

void ACA_CharacterBase::StaminaChanged(const FOnAttributeChangeData& Data)
{
}

void ACA_CharacterBase::MaxStaminaChanged(const FOnAttributeChangeData& Data)
{
}

void ACA_CharacterBase::BaseVitalityChanged(const FOnAttributeChangeData& Data)
{
}

void ACA_CharacterBase::VitalityChanged(const FOnAttributeChangeData& Data)
{
}

void ACA_CharacterBase::BaseStrengthChanged(const FOnAttributeChangeData& Data)
{
}

void ACA_CharacterBase::StrengthChanged(const FOnAttributeChangeData& Data)
{
}

void ACA_CharacterBase::BaseIntelligenceChanged(const FOnAttributeChangeData& Data)
{
}

void ACA_CharacterBase::IntelligenceChanged(const FOnAttributeChangeData& Data)
{
}

void ACA_CharacterBase::BaseAgilityChanged(const FOnAttributeChangeData& Data)
{
}

void ACA_CharacterBase::AgilityChanged(const FOnAttributeChangeData& Data)
{
}

void ACA_CharacterBase::BaseEnduranceChanged(const FOnAttributeChangeData& Data)
{
}

void ACA_CharacterBase::EnduranceChanged(const FOnAttributeChangeData& Data)
{
}

void ACA_CharacterBase::CharacterLevelChanged(const FOnAttributeChangeData& Data)
{
}
#pragma endregion
