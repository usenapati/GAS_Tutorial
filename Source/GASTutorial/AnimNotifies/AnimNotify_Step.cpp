// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimNotifies/AnimNotify_Step.h"

#include "GAS_Character.h"
#include "ActorComponents/FootstepsComponent.h"

void UAnimNotify_Step::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	Super::Notify(MeshComp, Animation);
	
	check(MeshComp);

	AGAS_Character* Character = MeshComp ? Cast<AGAS_Character>(MeshComp->GetOwner()) : nullptr;
	if (Character)
	{
		if (UFootstepsComponent* FootstepsComponent = Character->GetFootstepsComponent())
		{
			FootstepsComponent->HandleFootstep(Foot);
		}
	}
}
