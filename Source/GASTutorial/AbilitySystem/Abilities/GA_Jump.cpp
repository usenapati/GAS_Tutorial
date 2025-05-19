// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/Abilities/GA_Jump.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystemComponent.h"
#include "GameFramework/Character.h"

UGA_Jump::UGA_Jump()
{
	NetExecutionPolicy = EGameplayAbilityNetExecutionPolicy::LocalPredicted;
	InstancingPolicy = EGameplayAbilityInstancingPolicy::NonInstanced;
}

bool UGA_Jump::CanActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
	const FGameplayTagContainer* SourceTags, const FGameplayTagContainer* TargetTags,
	FGameplayTagContainer* OptionalRelevantTags) const
{
	if (!Super::CanActivateAbility(Handle, ActorInfo, SourceTags, TargetTags, OptionalRelevantTags))
	{
		return false;
	}
	const ACharacter* Character = CastChecked<ACharacter>(ActorInfo->AvatarActor.Get(), ECastCheckedType::NullAllowed);
	return Character->CanJump();
}

void UGA_Jump::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
	const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	if (HasAuthorityOrPredictionKey(ActorInfo, &ActivationInfo))
	{
		if (!CommitAbility(Handle, ActorInfo, ActivationInfo))
		{
			return;
		}
		Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);
		const auto Actor = ActorInfo->AvatarActor.Get();
		ACharacter* Character = CastChecked<ACharacter>(Actor, ECastCheckedType::NullAllowed);
		Character->Jump();
		//UAbilitySystemComponent* AbilityComponent = ActorInfo->AbilitySystemComponent.Get()
		if(UAbilitySystemComponent* AbilityComponent =  UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(Character))
		{
			FGameplayEffectContextHandle EffectContext = AbilityComponent->MakeEffectContext();

			FGameplayEffectSpecHandle SpecHandle = AbilityComponent->MakeOutgoingSpec(JumpEffect, 1, EffectContext);
			if(SpecHandle.IsValid())
			{
				FActiveGameplayEffectHandle ActiveGEHandle = AbilityComponent->ApplyGameplayEffectSpecToSelf(*SpecHandle.Data.Get(), AbilityComponent->GetPredictionKeyForNewAction());

				if (!ActiveGEHandle.WasSuccessfullyApplied())
				{
					UE_LOG(LogTemp, Error, TEXT("Failed to apply jump effect! %s"), *GetNameSafe(Character));
				}
			}
		}
	}
}


