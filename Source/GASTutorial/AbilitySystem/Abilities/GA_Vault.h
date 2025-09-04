// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/Tasks/AbilityTask_PlayMontageAndWait.h"
#include "AbilitySystem/Abilities/GAS_GameplayAbility.h"
#include "GA_Vault.generated.h"

/**
 * 
 */
UCLASS()
class GASTUTORIAL_API UGA_Vault : public UGAS_GameplayAbility
{
	GENERATED_BODY()

	UGA_Vault();

	virtual bool CommitCheck(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, FGameplayTagContainer* OptionalRelevantTags = nullptr) override;

	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;

	virtual void EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled) override;

	protected:
	UPROPERTY(EditDefaultsOnly, Category = "HorizontalTrace")
	float HorizontalTraceRadius = 30.f;

	UPROPERTY(EditDefaultsOnly, Category = "HorizontalTrace")
	float HorizontalTraceLength = 500.f;

	UPROPERTY(EditDefaultsOnly, Category = "HorizontalTrace")
	float HorizontalTraceCount = 5.f;

	UPROPERTY(EditDefaultsOnly, Category = "HorizontalTrace")
	float HorizontalTraceStep = 30.f;

	UPROPERTY(EditDefaultsOnly, Category = "VerticalTrace")
	float VerticalTraceRadius = 30.f;

	UPROPERTY(EditDefaultsOnly, Category = "VerticalTrace")
	float VerticalTraceStep = 30.f;

	UPROPERTY(EditDefaultsOnly)
	TArray<TEnumAsByte<EObjectTypeQuery>> TraceObjectTypes;

	UPROPERTY(EditDefaultsOnly)
	UAnimMontage* VaultMontage = nullptr;

	UAbilityTask_PlayMontageAndWait* Montage = nullptr;
	
	FVector JumpToLocation;
	FVector JumpOverLocation;

	UPROPERTY(EditDefaultsOnly)
	TArray<TEnumAsByte<ECollisionChannel>> CollisionChannelsToIgnore;
};
