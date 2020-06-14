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


UCLASS()
class INTOTHEARENA_API AMyCharacter : public ACharacter, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AMyCharacter();
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
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Abilities")
		TArray<TSubclassOf<class UGameplayAbility>> CharacterAbilities;

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
	virtual void HandleMovementSpeedChanged(float MovementSpeed, const struct FGameplayTagContainer& EventTags);
	virtual void HandleEnduranceChanged(float DeltaValue, const struct FGameplayTagContainer& EventTags);

	//Attribute functions
	virtual void InitializeDefaultAbilities();
	virtual void InitializeAttributes();
	virtual void InitializeDefaultEffects();

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
		virtual float GetMovementSpeedMultiplier() const;

	UFUNCTION(BlueprintCallable)
		virtual float GetAttackSpeed() const;

	UFUNCTION(BlueprintCallable)
		virtual float GetDamage() const;

	UFUNCTION(BlueprintCallable)
		virtual float GetPhysicalEffectiveness() const;

	UFUNCTION(BlueprintCallable)
		virtual float GetMagicalEffectiveness() const;

	UFUNCTION(BlueprintCallable)
		virtual float GetEndurance() const;

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
