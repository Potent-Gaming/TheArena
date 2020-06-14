// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "AbilitySystemComponent.h"
#include "MyAttributeSet.generated.h"

#define ATTRIBUTE_ACCESSORS(ClassName, PropertyName) \
    GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \
    GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName) \
    GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName) \
    GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)

/**
 * 
 */
UCLASS()
class INTOTHEARENA_API UMyAttributeSet : public UAttributeSet
{
	GENERATED_BODY()

public:
	// Constructor and overrides
	UMyAttributeSet();
	virtual void PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue) override;
	virtual void PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data) override;
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, ReplicatedUsing = OnRep_Health, Category = "Attributes")
	FGameplayAttributeData Health;
	ATTRIBUTE_ACCESSORS(UMyAttributeSet, Health)

	UPROPERTY(EditAnywhere, BlueprintReadWrite, ReplicatedUsing = OnRep_MaxHealth, Category = "Attributes")
	FGameplayAttributeData MaxHealth;
	ATTRIBUTE_ACCESSORS(UMyAttributeSet, MaxHealth)

	UPROPERTY(EditAnywhere, BlueprintReadWrite, ReplicatedUsing = OnRep_Damage, Category = "Attributes")
	FGameplayAttributeData Damage;
	ATTRIBUTE_ACCESSORS(UMyAttributeSet, Damage)

	UPROPERTY(EditAnywhere, BlueprintReadWrite, ReplicatedUsing = OnRep_Armor, Category = "Attributes")
	FGameplayAttributeData Armor;
	ATTRIBUTE_ACCESSORS(UMyAttributeSet, Armor)

	UPROPERTY(EditAnywhere, BlueprintReadWrite, ReplicatedUsing = OnRep_MaxArmor, Category = "Attributes")
	FGameplayAttributeData MaxArmor;
	ATTRIBUTE_ACCESSORS(UMyAttributeSet, MaxArmor)

	UPROPERTY(EditAnywhere, BlueprintReadWrite, ReplicatedUsing = OnRep_MovementSpeedMultiplier, Category = "Attributes")
	FGameplayAttributeData MovementSpeedMultiplier;
	ATTRIBUTE_ACCESSORS(UMyAttributeSet, MovementSpeedMultiplier)

	UPROPERTY(EditAnywhere, BlueprintReadWrite, ReplicatedUsing = OnRep_AttackSpeed, Category = "Attributes")
	FGameplayAttributeData AttackSpeed;
	ATTRIBUTE_ACCESSORS(UMyAttributeSet, AttackSpeed)

	UPROPERTY(EditAnywhere, BlueprintReadWrite, ReplicatedUsing = OnRep_PhysicalEffectiveness, Category = "Attributes")
	FGameplayAttributeData PhysicalEffectiveness;
	ATTRIBUTE_ACCESSORS(UMyAttributeSet, PhysicalEffectiveness)

	UPROPERTY(EditAnywhere, BlueprintReadWrite, ReplicatedUsing = OnRep_MagicalEffectiveness, Category = "Attributes")
	FGameplayAttributeData MagicalEffectiveness;
	ATTRIBUTE_ACCESSORS(UMyAttributeSet, MagicalEffectiveness)

	UPROPERTY(EditAnywhere, BlueprintReadWrite, ReplicatedUsing = OnRep_Endurance, Category = "Attributes")
	FGameplayAttributeData Endurance;
	ATTRIBUTE_ACCESSORS(UMyAttributeSet, Endurance)

	UPROPERTY(EditAnywhere, BlueprintReadWrite, ReplicatedUsing = OnRep_MaxEndurance, Category = "Attributes")
	FGameplayAttributeData MaxEndurance;
	ATTRIBUTE_ACCESSORS(UMyAttributeSet, MaxEndurance)

	UPROPERTY(BlueprintReadOnly, Category = "Attributes")
	FGameplayAttributeData OldValue;
	ATTRIBUTE_ACCESSORS(UMyAttributeSet, OldValue)


protected:
	/** Helper function to proportionally adjust the value of an attribute when it's associated max attribute changes. (i.e. When MaxHealth increases, Health increases by an amount that maintains the same percentage as before) */
	void AdjustAttributeForMaxChange(FGameplayAttributeData& AffectedAttribute, const FGameplayAttributeData& MaxAttribute, float NewMaxValue, const FGameplayAttribute& AffectedAttributeProperty);

	//Replicated attribute functions
	UFUNCTION()
		virtual void OnRep_Health();

	UFUNCTION()
		virtual void OnRep_MaxHealth();

	UFUNCTION()
		virtual void OnRep_Damage();

	UFUNCTION()
		virtual void OnRep_MovementSpeedMultiplier();

	UFUNCTION()
		virtual void OnRep_AttackSpeed();

	UFUNCTION()
		virtual void OnRep_Armor();

	UFUNCTION()
		virtual void OnRep_MaxArmor();

	UFUNCTION()
		virtual void OnRep_PhysicalEffectiveness();

	UFUNCTION()
		virtual void OnRep_MagicalEffectiveness();

	UFUNCTION()
		virtual void OnRep_Endurance();

	UFUNCTION()
		virtual void OnRep_MaxEndurance();
};
