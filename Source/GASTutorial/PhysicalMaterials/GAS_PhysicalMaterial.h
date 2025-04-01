// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PhysicalMaterials/PhysicalMaterial.h"
#include "GAS_PhysicalMaterial.generated.h"

/**
 * 
 */
UCLASS()
class GASTUTORIAL_API UGAS_PhysicalMaterial : public UPhysicalMaterial
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PhysicalMaterial")
	class USoundBase* FootstepSound = nullptr;
};
