// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "MSDV1GameInstance.generated.h"

/**
 * 
 */
UCLASS(Blueprintable)
class MSDV1_API UMSDV1GameInstance : public UGameInstance
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadWrite)
		AActor* Floor;
	
};
