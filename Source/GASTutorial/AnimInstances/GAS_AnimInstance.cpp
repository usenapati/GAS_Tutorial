// Fill out your copyright notice in the Description page of Project Settings.


#include "GAS_AnimInstance.h"
#include "GAS_Types.h"
#include "GAS_Character.h"
#include "DataAssets/CharacterAnimDataAsset.h"

UBlendSpace* UGAS_AnimInstance::GetLocomotionBlendSpace() const
{
	if (AGAS_Character* Character = Cast<AGAS_Character>(GetOwningActor()))
	{
		FCharacterData Data = Character->GetCharacterData();

		if (Data.CharacterAnimDataAsset)
		{
			return Data.CharacterAnimDataAsset->CharacterAnimationData.MovementBlendspace;
		}
	}
	return DefaultCharacterAnimDataAsset ? DefaultCharacterAnimDataAsset->CharacterAnimationData.MovementBlendspace : nullptr;
}

UAnimSequenceBase* UGAS_AnimInstance::GetIdleAnimation() const
{
	if (AGAS_Character* Character = Cast<AGAS_Character>(GetOwningActor()))
	{
		FCharacterData Data = Character->GetCharacterData();

		if (Data.CharacterAnimDataAsset)
		{
			return Data.CharacterAnimDataAsset->CharacterAnimationData.IdleAnimationAsset;
		}
	}
	return DefaultCharacterAnimDataAsset ? DefaultCharacterAnimDataAsset->CharacterAnimationData.IdleAnimationAsset : nullptr;
}
