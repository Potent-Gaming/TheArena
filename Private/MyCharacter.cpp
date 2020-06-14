// Fill out your copyright notice in the Description page of Project Settings.


#include "MyCharacter.h"
#include "AbilitySystemGlobals.h"
#include "Net/UnrealNetwork.h"
#include "GameplayTagContainer.h"
#include "GameplayTagsModule.h"
#include "MyDamageExecutionCalculation.h"

// Sets default values
AMyCharacter::AMyCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	// Create ability system component, and set it to be explicitly replicated
	AbilitySystem = CreateDefaultSubobject<UAbilitySystemComponent>(TEXT("AbilitySystem"));
	AbilitySystem->SetReplicationMode(EGameplayEffectReplicationMode::Mixed);
	AbilitySystem->SetIsReplicated(true);

	// Create the attribute set, this replicates by default
	AttributeSet = CreateDefaultSubobject<UMyAttributeSet>(TEXT("AttributeSet"));
	RealmRank = 1;

}

// Called when the game starts or when spawned
void AMyCharacter::BeginPlay()
{
	Super::BeginPlay();

	InitializeAttributes();
	InitializeDefaultAbilities();
	InitializeDefaultEffects();
}

void AMyCharacter::HandleDamage(float DamageAmount, const FHitResult& HitInfo, const struct FGameplayTagContainer& DamageTags, AMyCharacter* InstigatorPawn, AActor* DamageCauser)
{
	OnDamaged(DamageAmount, HitInfo, DamageTags, InstigatorPawn, DamageCauser);
}

void AMyCharacter::HandleHealthChanged(float DeltaValue, const struct FGameplayTagContainer& EventTags)
{
	OnHealthChanged(DeltaValue, EventTags);
}

void AMyCharacter::HandleArmorChanged(float DeltaValue, const struct FGameplayTagContainer& EventTags)
{
	OnArmorChanged(DeltaValue, EventTags);
}

void AMyCharacter::HandleMovementSpeedChanged(float MovementSpeedMultiplier, const struct FGameplayTagContainer& EventTags)
{

	OnMovementSpeedChanged(MovementSpeedMultiplier, EventTags);
	GetCharacterMovement()->MaxWalkSpeed = FMath::Clamp((GetCharacterMovement()->MaxWalkSpeed * MovementSpeedMultiplier),0.f, GetCharacterMovement()->MaxWalkSpeed * 2);
}
void AMyCharacter::HandleEnduranceChanged(float DeltaValue, const struct FGameplayTagContainer& EventTags)
{
	OnEnduranceChanged(DeltaValue, EventTags);
}


//Atrribute Functions
void AMyCharacter::InitializeAttributes()
{
	if (HasAuthority())
	{
		if (!AttributeSet)
		{
			UE_LOG(LogTemp, Warning, TEXT("Failed Initialized"));
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("Initialized"));
			// Can run on Server and Client
			FGameplayEffectContextHandle EffectContext = AbilitySystem->MakeEffectContext();
			EffectContext.AddSourceObject(this);

			FGameplayEffectSpecHandle NewHandle = AbilitySystem->MakeOutgoingSpec(DefaultAttributes, GetRealmRank(), EffectContext);
			if (NewHandle.IsValid())
			{
				FActiveGameplayEffectHandle ActiveGEHandle = AbilitySystem->ApplyGameplayEffectSpecToTarget(*NewHandle.Data.Get(), AbilitySystem);
			}
		}
	}
}


void AMyCharacter::InitializeDefaultAbilities()
{
	if (HasAuthority())
	{
		UE_LOG(LogTemp, Warning, TEXT("Granted Abilities"));
		for (TSubclassOf<UGameplayAbility>& StartupAbility : CharacterAbilities)
		{
			AbilitySystem->GiveAbility(FGameplayAbilitySpec(StartupAbility, 1, INDEX_NONE, this));
		}
	}
}

void AMyCharacter::InitializeDefaultEffects()
{
	if (HasAuthority())
	{ 
		FGameplayEffectContextHandle EffectContext = AbilitySystem->MakeEffectContext();
		EffectContext.AddSourceObject(this);

		for (TSubclassOf<UGameplayEffect> GameplayEffect : DefaultEffects)
		{
			FGameplayEffectSpecHandle NewHandle = AbilitySystem->MakeOutgoingSpec(GameplayEffect, 1, EffectContext);
			if (NewHandle.IsValid())
			{
				FActiveGameplayEffectHandle ActiveGEHandle = AbilitySystem->ApplyGameplayEffectSpecToTarget(*NewHandle.Data.Get(), AbilitySystem);
			}
		}
	}
}

void AMyCharacter::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AMyCharacter, RealmRank);
}


// Called to bind functionality to input
void AMyCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}


/*
*
* Attribute Get functions
*
*/
float AMyCharacter::GetHealth() const
{
	if (!AttributeSet)
		return 1.f;

	return AttributeSet->GetHealth();
}

int32 AMyCharacter::GetRealmRank() const
{
	return RealmRank;
}

float AMyCharacter::GetMaxHealth() const
{
	return AttributeSet->GetMaxHealth();
}

float AMyCharacter::GetHealthPercent() const
{
	return ((AttributeSet->GetHealth()) / (AttributeSet->GetMaxHealth()));
}

float AMyCharacter::GetArmor() const
{
	return AttributeSet->GetArmor();
}

float AMyCharacter::GetMaxArmor() const
{
	return AttributeSet->GetMaxArmor();
}

float AMyCharacter::GetArmorPercent() const
{
	return ((AttributeSet->GetArmor()) / (AttributeSet->GetMaxArmor()));
}

float AMyCharacter::GetMovementSpeedMultiplier() const
{
	return AttributeSet->GetMovementSpeedMultiplier();
}

float AMyCharacter::GetAttackSpeed() const
{
	return AttributeSet->GetAttackSpeed();
}

float AMyCharacter::GetDamage() const
{
	return AttributeSet->GetDamage();
}

float AMyCharacter::GetPhysicalEffectiveness() const
{
	return AttributeSet->GetPhysicalEffectiveness();
}

float AMyCharacter::GetMagicalEffectiveness() const
{
	return AttributeSet->GetMagicalEffectiveness();
}

float AMyCharacter::GetEndurance() const
{
	return AttributeSet->GetEndurance();
}

bool AMyCharacter::IsAlive() const
{
	return GetHealth() > 0.0f;
}

/*
*Set Functions
*/

void AMyCharacter::SetHealth(float Health)
{
	return AttributeSet->SetHealth(Health);
}


void AMyCharacter::SetArmor(float Armor)
{
	return AttributeSet->SetArmor(Armor);
}

void AMyCharacter::SetEndurance(float Endurance)
{
	return AttributeSet->SetEndurance(Endurance);
}


