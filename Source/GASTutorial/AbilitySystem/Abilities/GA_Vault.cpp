// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/Abilities/GA_Vault.h"

#include "GAS_Character.h"
#include "Kismet/KismetSystemLibrary.h"
#include "DrawDebugHelpers.h"
#include "Abilities/Tasks/AbilityTask_PlayMontageAndWait.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "ActorComponents/GAS_MotionWarpingComponent.h"

UGA_Vault::UGA_Vault()
{
	NetExecutionPolicy = EGameplayAbilityNetExecutionPolicy::LocalPredicted;
	InstancingPolicy = EGameplayAbilityInstancingPolicy::InstancedPerActor;
}

bool UGA_Vault::CommitCheck(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
	const FGameplayAbilityActivationInfo ActivationInfo, FGameplayTagContainer* OptionalRelevantTags)
{
	if (!Super::CommitCheck(Handle, ActorInfo, ActivationInfo, OptionalRelevantTags))
	{
		return false;
	}

	AGAS_Character* Character = GetGasCharacterFromActorInfo();

	if (!IsValid(Character))
	{
		return false;
	}

	const FVector StartLocation = Character->GetActorLocation();
	const FVector ForwardVector = Character->GetActorForwardVector();
	const FVector UpVector = Character->GetActorUpVector();

	TArray<AActor*> ActorsToIgnore = {Character};

	static const auto CVar = IConsoleManager::Get().FindConsoleVariable(TEXT("ShowDebugTraversal"));
	const bool bShowTraversal = CVar->GetInt() > 0;

	EDrawDebugTrace::Type DebugDrawType = bShowTraversal ? EDrawDebugTrace::ForDuration : EDrawDebugTrace::None;

	bool bJumpToLocationSet = false;

	int32 JumpToLocationIndex = INDEX_NONE;

	int i = 0;

	FHitResult TraceHit;

	float MaxJumpDistance = HorizontalTraceLength;

	for (; i < HorizontalTraceLength; ++i)
	{
		const FVector TraceStart = StartLocation + i * UpVector * HorizontalTraceStep;
		const FVector TraceEnd = TraceStart + ForwardVector * HorizontalTraceLength;

		if (UKismetSystemLibrary::SphereTraceSingleForObjects(this, TraceStart, TraceEnd, HorizontalTraceRadius, TraceObjectTypes, true, ActorsToIgnore, DebugDrawType, TraceHit, true))
		{
			if (JumpToLocationIndex == INDEX_NONE && (i < HorizontalTraceCount - 1))
			{
				JumpToLocationIndex = i;
				JumpOverLocation = TraceHit.Location;
			}
			else if (JumpToLocationIndex == (i - 1))
			{
				MaxJumpDistance = FVector::Dist2D(TraceHit.Location, TraceStart);
				break;
			}
		}
		else
		{
			if (JumpToLocationIndex != INDEX_NONE)
			{
				break;
			}
		}
	}

	if (JumpToLocationIndex == INDEX_NONE)
	{
		return false;
	}
	
	const float DistanceToJumpTo = FVector::Dist2D(StartLocation, JumpToLocation);

	const float MaxVerticalTraceDistance = MaxJumpDistance - DistanceToJumpTo;

	if (MaxVerticalTraceDistance < 0)
	{
		return false;
	}

	if (i == HorizontalTraceCount)
	{
		i = HorizontalTraceCount - 1;
	}

	const float VerticalTraceLength = FMath::Abs(JumpToLocation.Z - (StartLocation + i * UpVector * HorizontalTraceStep).Z);

	FVector VerticalStartLocation = JumpToLocation + UpVector * VerticalTraceLength;

	i = 0;

	const float VerticalTraceCount = MaxVerticalTraceDistance / VerticalTraceStep;

	bool bJumpOverLocationSet = false;

	for (; i <= VerticalTraceCount; ++i)
	{
		const FVector TraceStart = VerticalStartLocation + i * ForwardVector * VerticalTraceStep;
		const FVector TraceEnd = TraceStart + UpVector * VerticalTraceLength * -1;
	}
	return Super::CommitCheck(Handle, ActorInfo, ActivationInfo, OptionalRelevantTags);
}

void UGA_Vault::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
	const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);
}

void UGA_Vault::EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
	const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled)
{
	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);
}
