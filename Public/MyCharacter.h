// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "UObject/ScriptInterface.h"
#include "MyAttributeSet.h"
#include "GameplayEffectTypes.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Character.h"
#include "MyCharacter.generated.h"

class UGameplayAbility;
class UGameplayEffect;

UENUM(BlueprintType)
enum class AbilityInput : uint8
{
	Sprint UMETA(DisplayName = "Sprint"),
	InputAbility1 UMETA(DisplayName = "InputAbility 1"), //This maps the first ability(input ID should be 0 in int) to the action mapping(which you define in the project settings) by the name of "InputAbility1". "Input Spell 1" is the blueprint name of the element.
	InputAbility2 UMETA(DisplayName = "Input Ability 2"),//Maps ability 2(input ID 1) to action mapping InputAbility2. "Input Spell 2" is mostly Inputd for when the enum is a blueprint variable.
	InputAbility3 UMETA(DisplayName = "Input Ability 3"),
	InputAbility4 UMETA(DisplayName = "Input Ability 4"),
	InputAbility5 UMETA(DisplayName = "Input Ability 5"),
	InputAbility6 UMETA(DisplayName = "Input Ability 6"),
	InputAbility7 UMETA(DisplayName = "Input Ability 7"),
	InputAbility8 UMETA(DisplayName = "Input Ability 8"),
	InputAbility9 UMETA(DisplayName = "Input Ability 9"),
	InputAbility10 UMETA(DisplayName = "Input Ability 10"),
	InputAbility11 UMETA(DisplayName = "Input Ability 11"),
	InputAbility12 UMETA(DisplayName = "Input Ability 12"),
	InputAbility13 UMETA(DisplayName = "Input Ability 13"),
	InputAbility14 UMETA(DisplayName = "Input Ability 14"),
	InputAbility15 UMETA(DisplayName = "Input Ability 15"),
	InputAbility16 UMETA(DisplayName = "Input Ability 16"),
};

UCLASS()
class INTOTHEARENA_API AMyCharacter : public ACharacter, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AMyCharacter(const class FObjectInitializer& ObjectInitializer);
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Abilities, meta = (AllowPrivateAccess = "true"))
		class UAbilitySystemComponent* AbilitySystem;

	UAbilitySystemComponent* GetAbilitySystemComponent() const override
	{
		return AbilitySystem;
	};


	UPROPERTY()
		UMyAttributeSet* AttributeSet;

	UFUNCTION(BlueprintImplementableEvent)
		void OnDamaged(float DamageAmount, const FHitResult& HitInfo, const struct FGameplayTagContainer& DamageTags, AMyCharacter* InstigatorCharacter, AActor* DamageCauser);

	UFUNCTION(BlueprintImplementableEvent)
		void OnHealthChanged(float DeltaValue, const struct FGameplayTagContainer& EventTags);

	UFUNCTION(BlueprintImplementableEvent)
		void OnArmorChanged(float DeltaValue, const struct FGameplayTagContainer& EventTags);

	UFUNCTION(BlueprintImplementableEvent)
		void OnMovementSpeedChanged(float DeltaValue, const struct FGameplayTagContainer& EventTags);

	UFUNCTION(BlueprintImplementableEvent)
		void OnEnduranceChanged(float DeltaValue, const struct FGameplayTagContainer& EventTags);

	//Realm Ranks or character levels
	UPROPERTY(EditAnywhere, Replicated, Category = Abilities)
		int32 RealmRank;

	// Default abilities for this Character. These will be removed on Character death and regiven if Character respawns.

	UPROPERTY()
		TArray<FGameplayAbilitySpecHandle> SpellAbilityHandles;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Abilities")
		TArray<TSubclassOf<class UGameplayAbility>> DefaultAbilities;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Abilities")
		TArray<TSubclassOf<class UGameplayAbility>> ClassAbilities;

	// Default attributes for a character for initializing on spawn/respawn.
	// This is an instant GE that overrides the values for attributes that get reset on spawn/respawn.
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Abilities")
		TSubclassOf<class UGameplayEffect> DefaultAttributes;

	// These effects are only applied on startup
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Abilities")
		TArray<TSubclassOf<class UGameplayEffect>> DefaultEffects;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	//Damage Functions
	virtual void HandleDamage(float DamageAmount, const FHitResult& HitInfo, const struct FGameplayTagContainer& DamageTags, AMyCharacter* InstigatorCharacter, AActor* DamageCauser);
	virtual void HandleHealthChanged(float DeltaValue, const struct FGameplayTagContainer& EventTags);
	virtual void HandleArmorChanged(float DeltaValue, const struct FGameplayTagContainer& EventTags);
	virtual void HandleMovementSpeedChanged(float MovementSpeedModifier, const struct FGameplayTagContainer& EventTags, FString Opperator);
	virtual void HandleEnduranceChanged(float DeltaValue, const struct FGameplayTagContainer& EventTags);

	//Attribute functions
	virtual void InitializeDefaultAbilities();
	virtual void InitializeClassAbilities();
	virtual void InitializeAttributes();
	virtual void PossessedBy(AController* NewController);
	virtual void OnRep_PlayerState() override;
	virtual void InitializeDefaultEffects();
	UFUNCTION(BlueprintCallable)
	virtual void AddAbilities();

	/*
	*Attribute Get function
	*/
	UFUNCTION(BlueprintCallable)
		virtual float GetHealth() const;

	UFUNCTION(BlueprintCallable)
		virtual float GetMaxHealth() const;

	UFUNCTION(BlueprintCallable)
		virtual float GetHealthPercent() const;

	UFUNCTION(BlueprintCallable)
		virtual float GetArmor() const;

	UFUNCTION(BlueprintCallable)
		virtual float GetMaxArmor() const;

	UFUNCTION(BlueprintCallable)
		virtual float GetArmorPercent() const;

	UFUNCTION(BlueprintCallable)
		virtual float GetMovementSpeedModifier() const;

	UFUNCTION(BlueprintCallable)
		virtual float GetAttackSpeed() const;

	UFUNCTION(BlueprintCallable)
		virtual float GetDamage() const;

	UFUNCTION(BlueprintCallable)
		virtual float GetBaseDamage() const;

	UFUNCTION(BlueprintCallable)
		virtual float GetPhysicalEffectiveness() const;

	UFUNCTION(BlueprintCallable)
		virtual float GetMagicalEffectiveness() const;

	UFUNCTION(BlueprintCallable)
		virtual float GetEndurance() const;

	UFUNCTION(BlueprintCallable)
		virtual float GetEndurancePercent() const;

	UFUNCTION(BlueprintCallable)
		virtual int32 GetRealmRank() const;

	UFUNCTION(BlueprintCallable)
		virtual bool IsAlive() const;

	/*
	*Attribute Set Functions
	*/

	UFUNCTION(BlueprintCallable)
		virtual void SetHealth(float Health);

	UFUNCTION(BlueprintCallable)
		virtual void SetEndurance(float Endurance);

	UFUNCTION(BlueprintCallable)
		virtual void SetArmor(float Armor);



	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	// Friended to allow access to handle functions above
	friend UMyAttributeSet;
};
