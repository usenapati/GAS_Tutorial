// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GAS_Types.h"
#include "Components/ActorComponent.h"
#include "FootstepsComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class GASTUTORIAL_API UFootstepsComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UFootstepsComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly)
	FName LeftFootSocket = TEXT("foot_l");

	UPROPERTY(EditDefaultsOnly)
	FName RightFootSocket = TEXT("foot_r");

public:	
	void HandleFootstep(EFoot Foot);	
};
