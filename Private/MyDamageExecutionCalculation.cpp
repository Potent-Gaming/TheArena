// Fill out your copyright notice in the Description page of Project Settings.


#include "MyDamageExecutionCalculation.h"
#include "MyAttributeSet.h"
#include "AbilitySystemComponent.h"

struct MyDamageStatics
{
	DECLARE_ATTRIBUTE_CAPTUREDEF(PhysicalEffectiveness);
	DECLARE_ATTRIBUTE_CAPTUREDEF(MagicalEffectiveness);
	DECLARE_ATTRIBUTE_CAPTUREDEF(Armor);

	// Meta attribute that we're passing into the ExecCalc via SetByCaller on the GESpec so we don't capture it.
	// We still need to declare and define it so that we can output to it.
	DECLARE_ATTRIBUTE_CAPTUREDEF(Damage);

	MyDamageStatics()
	{
		// We're not capturing anything from the Source in this example, but there could be like AttackPower attributes that you might want.

		// Capture the Target's Armor Effectiveness. Don't snapshot (the false).
		DEFINE_ATTRIBUTE_CAPTUREDEF(UMyAttributeSet, PhysicalEffectiveness, Target, false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UMyAttributeSet, MagicalEffectiveness, Target, false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UMyAttributeSet, Armor, Target, false);

		// The Target's received Damage. This is the value of health that will be subtracted on the Target. We're not capturing this.
		DEFINE_ATTRIBUTE_CAPTUREDEF(UMyAttributeSet, Damage, Source, true);
	}
};


static const MyDamageStatics& DamageStatics()
{
	static MyDamageStatics DStatics;
	return DStatics;
}

UMyDamageExecutionCalculation::UMyDamageExecutionCalculation()
{
	RelevantAttributesToCapture.Add(DamageStatics().PhysicalEffectivenessDef);
	RelevantAttributesToCapture.Add(DamageStatics().MagicalEffectivenessDef);
	RelevantAttributesToCapture.Add(DamageStatics().ArmorDef);
	RelevantAttributesToCapture.Add(DamageStatics().DamageDef);

}

void UMyDamageExecutionCalculation::Execute_Implementation(const FGameplayEffectCustomExecutionParameters& ExecutionParams, OUT FGameplayEffectCustomExecutionOutput& OutExecutionOutput) const
{
	UAbilitySystemComponent* TargetAbilitySystemComponent = ExecutionParams.GetTargetAbilitySystemComponent();
	UAbilitySystemComponent* SourceAbilitySystemComponent = ExecutionParams.GetSourceAbilitySystemComponent();

	AActor* SourceActor = SourceAbilitySystemComponent ? SourceAbilitySystemComponent->AvatarActor : nullptr;
	AActor* TargetActor = TargetAbilitySystemComponent ? TargetAbilitySystemComponent->AvatarActor : nullptr;

	const FGameplayEffectSpec& Spec = ExecutionParams.GetOwningSpec();
	//const FModifierSpec& ModSpec = Spec.Modifiers[0];
	//ExecutionParams.
	//	UE_LOG(LogTemp, Warning, TEXT("Test"));
	//const FGameplayEffectModifierMagnitude& Mod = 
	

	// Gather the tags from the source and target as that can affect which buffs should be used
	const FGameplayTagContainer* SourceTags = Spec.CapturedSourceTags.GetAggregatedTags();
	const FGameplayTagContainer* TargetTags = Spec.CapturedTargetTags.GetAggregatedTags();


	FAggregatorEvaluateParameters EvaluationParameters;
	EvaluationParameters.SourceTags = SourceTags;
	EvaluationParameters.TargetTags = TargetTags;

	
	
	float Damage = 0.f;
	//FMath::Max<float>(
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(DamageStatics().DamageDef, EvaluationParameters, Damage); //, 0.0f);

	//Calculations for Physical Damage
	if (Spec.CapturedSourceTags.GetAggregatedTags()->HasTag(FGameplayTag::RequestGameplayTag(FName(TEXT("Damage.Physical")))))
	{
		//UE_LOG(LogTemp, Warning, TEXT("Physical"));

		float PhysicalEffectiveness = 0.f;
		FMath::Max<float>(ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(DamageStatics().PhysicalEffectivenessDef, EvaluationParameters, PhysicalEffectiveness), 0.0f);

		float Armor = 0.f;
		FMath::Max<float>(ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(DamageStatics().ArmorDef, EvaluationParameters, Armor), 0.0f);

		if (Armor > 0.f)
		{
			float UnmitigatedDamage = Damage; // Can multiply any damage boosters here

			float MitigatedDamage = (UnmitigatedDamage * PhysicalEffectiveness);

			if (MitigatedDamage > 0.f)
			{
				// Set the Target's damage meta attribute
				OutExecutionOutput.AddOutputModifier(FGameplayModifierEvaluatedData(DamageStatics().DamageProperty, EGameplayModOp::Additive, MitigatedDamage));
			}
		}
		else
		{
			OutExecutionOutput.AddOutputModifier(FGameplayModifierEvaluatedData(DamageStatics().DamageProperty, EGameplayModOp::Additive, Damage));
		}
	}

	// Calculations for Magical Damage
	if (Spec.CapturedSourceTags.GetAggregatedTags()->HasTag(FGameplayTag::RequestGameplayTag(FName(TEXT("Damage.Magical")))))
	{
		//UE_LOG(LogTemp, Warning, TEXT("Magical"));

		float MagicalEffectiveness = 0.f;
		FMath::Max<float>(ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(DamageStatics().MagicalEffectivenessDef, EvaluationParameters, MagicalEffectiveness), 0.0f);
		float UnmitigatedDamage = Damage; // Can multiply any damage boosters here

		float MitigatedDamage = (UnmitigatedDamage * MagicalEffectiveness);

		if (MitigatedDamage > 0.f)
		{
			// Set the Target's damage meta attribute
			OutExecutionOutput.AddOutputModifier(FGameplayModifierEvaluatedData(DamageStatics().DamageProperty, EGameplayModOp::Additive, MitigatedDamage));
		}
	}
}