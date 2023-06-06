#include "Character/Player/CA_PlayerCharacter.h"
#include "CA_AbilitySystemComponent.h"
#include "CubeAlphaStatsRow.h"
#include "GameFramework/SpringArmComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "Components/CapsuleComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Camera/CameraComponent.h"
#include "CA_ExperienceAttributeSet.h"
#include "CA_HUD.h"

ACA_PlayerCharacter::ACA_PlayerCharacter(const class FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer.SetDefaultSubobjectClass<UCharacterMovementComponent>(ACharacter::CharacterMovementComponentName))
{
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	// Don't rotate when the controller rotates. Let that just affect the camera.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Character moves in the direction of input...	
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 500.0f, 0.0f); // ...at this rotation rate

	// Note: For faster iteration times these variables, and many more, can be tweaked in the Character Blueprint
	// instead of recompiling to adjust them
	GetCharacterMovement()->JumpZVelocity = 700.f;
	GetCharacterMovement()->AirControl = 0.35f;
	GetCharacterMovement()->MaxWalkSpeed = 500.f;
	GetCharacterMovement()->MinAnalogWalkSpeed = 20.f;
	GetCharacterMovement()->BrakingDecelerationWalking = 2000.f;

	// Create a camera boom (pulls in towards the player if there is a collision)
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 400.0f; // The camera follows at this distance behind the character	
	CameraBoom->bUsePawnControlRotation = true; // Rotate the arm based on the controller

	// Create a follow camera
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName); // Attach the camera to the end of the boom and let the boom adjust to match the controller orientation
	FollowCamera->bUsePawnControlRotation = false; // Camera does not rotate relative to arm

	ExperienceAttributeSet = CreateDefaultSubobject<UCA_ExperienceAttributeSet>("Experience Attribute Set");
}

void ACA_PlayerCharacter::Move(const FInputActionValue& Value)
{
	// input is a Vector2D
	const FVector2D MovementVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// find out which way is forward
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get forward vector
		const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);

		// get right vector 
		const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

		// add movement 
		AddMovementInput(ForwardDirection, MovementVector.Y);
		AddMovementInput(RightDirection, MovementVector.X);
	}
}

void ACA_PlayerCharacter::Look(const FInputActionValue& Value)
{
	// input is a Vector2D
	const FVector2D LookAxisVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// add yaw and pitch input to controller
		AddControllerYawInput(-LookAxisVector.X);
		AddControllerPitchInput(LookAxisVector.Y);
	}
}

void ACA_PlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	// Set up action bindings
	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent)) {

		//Jumping
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Triggered, this, &ACharacter::Jump);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ACharacter::StopJumping);

		//Moving
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ACA_PlayerCharacter::Move);

		//Looking
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &ACA_PlayerCharacter::Look);

	}
}

void ACA_PlayerCharacter::BeginPlay()
{
	Super::BeginPlay();

	//Add Input Mapping Context
	if (const APlayerController* PlayerController = Cast<APlayerController>(Controller))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(PlayerMappingContext, 0);
		}
	}

	if(AbilitySystemComponent)
	{
		ExperienceChangedDelegateHandle = AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(ExperienceAttributeSet->GetExperienceAttribute()).AddUObject(this, &ACA_PlayerCharacter::ExperienceChanged);
		MaxExperienceChangedDelegateHandle = AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(ExperienceAttributeSet->GetMaxExperienceAttribute()).AddUObject(this, &ACA_PlayerCharacter::MaxExperienceChanged);
	}

}

FTransform ACA_PlayerCharacter::GetProjectileTransforms(FName Socket) const
{
	FVector LocalCamera = FollowCamera->GetComponentLocation();
	FVector Camera_Direction = FollowCamera->GetForwardVector();
	float Range = 10000;
	FVector Destination = (Camera_Direction * Range) + LocalCamera;

	FCollisionQueryParams params;
	params.AddIgnoredActor(this);

	FVector WeaponSocketLocation = GetMesh()->GetSocketLocation(Socket);;
	FRotator Rotation;
	FTransform Projectile_Movement;

	if (FHitResult Hit; GetWorld()->LineTraceSingleByChannel(Hit, LocalCamera, Destination, ECollisionChannel::ECC_Visibility, params, FCollisionResponseParams())) {
		Rotation = UKismetMathLibrary::FindLookAtRotation(WeaponSocketLocation, Hit.ImpactPoint);

	}
	else {
		Rotation = UKismetMathLibrary::FindLookAtRotation(WeaponSocketLocation, Destination);
	}
	Projectile_Movement.SetLocation(WeaponSocketLocation);
	Projectile_Movement.SetRotation(Rotation.Quaternion());
	Projectile_Movement.SetScale3D(UE::Math::TVector(1.0, 1.0, 1.0));
	return Projectile_Movement;
}

#pragma region Cooldowns

bool ACA_PlayerCharacter::GetCooldownRemainingForAbility(const FGameplayTag AbilityTag, float& OutTimeRemaining) const
{
	FString CooldownTag = AbilityTag.ToString().Append(".OnCooldown");

	FGameplayTagContainer tags;
	tags.AddTag(FGameplayTag::RequestGameplayTag(FName(CooldownTag)));

	return GetCooldownRemainingForTag(tags, OutTimeRemaining);
}

bool ACA_PlayerCharacter::GetCooldownDurationForAbility(const FGameplayTag AbilityTag, float& OutDuration) const
{
	FString CooldownTag = AbilityTag.ToString().Append(".OnCooldown");

	FGameplayTagContainer tags;
	tags.AddTag(FGameplayTag::RequestGameplayTag(FName(CooldownTag)));

	return GetCooldownDurationForTag(tags, OutDuration);
}

bool ACA_PlayerCharacter::GetCooldownRemainingForTag(const FGameplayTagContainer CooldownTags, float& OutTimeRemaining) const
{
	if (AbilitySystemComponent && CooldownTags.Num() > 0)
	{
		OutTimeRemaining = 0.f;

		FGameplayEffectQuery const Query = FGameplayEffectQuery::MakeQuery_MatchAnyOwningTags(CooldownTags);
		TArray<float>  TimeRemaining = AbilitySystemComponent->GetActiveEffectsTimeRemaining(Query);

		if (TimeRemaining.Num() > 0)
		{
			OutTimeRemaining = TimeRemaining[0];
			return true;
		}
	}

	return false;
}

bool ACA_PlayerCharacter::GetCooldownDurationForTag(const FGameplayTagContainer CooldownTags, float& OutDuration) const
{
	if (AbilitySystemComponent && CooldownTags.Num() > 0)
	{
		OutDuration = 0.f;

		FGameplayEffectQuery const Query = FGameplayEffectQuery::MakeQuery_MatchAnyOwningTags(CooldownTags);
		TArray<float>  Duration = AbilitySystemComponent->GetActiveEffectsDuration(Query);

		if (Duration.Num() > 0)
		{
			OutDuration = Duration[0];
			return true;
		}
	}

	return false;
}

#pragma endregion

#pragma region Experience
float ACA_PlayerCharacter::GetExperience() const
{
	return ExperienceAttributeSet->GetExperience();
}

void ACA_PlayerCharacter::SetExperience(float NewExperience) const
{
	ExperienceAttributeSet->SetExperience(NewExperience);
}

float ACA_PlayerCharacter::GetMaxExperience() const
{
	return ExperienceAttributeSet->GetMaxExperience();
}

void ACA_PlayerCharacter::SetMaxExperience(float NewMaxExperience) const
{
	ExperienceAttributeSet->SetMaxExperience(NewMaxExperience);
}

void ACA_PlayerCharacter::ExperienceChanged(const FOnAttributeChangeData& Data)
{
	if(Data.NewValue >= GetMaxExperience())
	{
		const float Diff = Data.NewValue - GetMaxExperience();
		LevelUp();
		SetExperience(Diff);
	}
	OnExperienceChanged.Broadcast(GetExperience(), GetMaxExperience());
}

void ACA_PlayerCharacter::MaxExperienceChanged(const FOnAttributeChangeData& Data)
{
	OnMaxExperienceChanged.Broadcast(GetExperience(), GetMaxExperience());
}

void ACA_PlayerCharacter::LevelUp() const
{
	if (GEngine) {
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Green, TEXT("Level Up!"));
	}
	if (GetCharacterLevel() < 10) { // TODO upgrade data table, Cap at 10 for now
		const float NewLevel = GetCharacterLevel() + 1;
		SetCharacterLevel(NewLevel);
		LevelUpStats();
	}
}

void ACA_PlayerCharacter::LevelUpStats() const
{
	//TODO FIX ME
	/*const FString ContextString;
	if (const FCA_StatsRow* StatsRow = StatsDataTable->FindRow<FCA_StatsRow>(FName(*FString::Printf(TEXT("%f"), GetCharacterLevel())), ContextString))
	{
		SetBaseVitality(StatsRow->Vitality);
		SetBaseStrength(StatsRow->Strength);
		SetBaseIntelligence(StatsRow->Intelligence);
		SetBaseAgility(StatsRow->Agility);
		SetBaseEndurance(StatsRow->Endurance);
		SetMaxExperience(StatsRow->ExperienceToNextLevel);
	}*/
	SetHealth(GetMaxHealth());
	SetStamina(GetMaxStamina());
}
#pragma endregion
