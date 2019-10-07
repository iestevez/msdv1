// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "MSDV1GameModeBase.h"

#include "msdv1.h"
#include "MSDV1PlayerController.h"
#include "MSDV1Pawn.h"
#include "GameFramework\PlayerController.h"
#include "GameFramework\DefaultPawn.h"
#include "Engine.h"
#include "EngineUtils.h"
#include "Kismet/GameplayStatics.h"

AMSDV1GameModeBase::AMSDV1GameModeBase() : m_startPlayerTag("Start") {


	PlayerControllerClass = AMSDV1PlayerController::StaticClass();
	//DefaultPawnClass = AMSDV1Pawn::StaticClass();
	struct FConstructorStatics
	{
		ConstructorHelpers::FClassFinder<APawn> BP_Pawn;
		FConstructorStatics()
			: BP_Pawn(TEXT("/Game/GameFramework/BP_MSDV1Pawn")) {}
	};
	static FConstructorStatics ConstructorStatics;
	DefaultPawnClass = ConstructorStatics.BP_Pawn.Class;
	m_startPoints.Reserve(10);
}


/*
AActor* AMSDV1GameModeBase::FindPlayerStart_Implementation(AController* PCon, const FString& IncomingName) {

	UGameplayStatics::GetAllActorsWithTag(GetWorld(), m_startPlayerTag, m_startPoints);
	if (m_startPoints.Num() > 0) {
		//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, TEXT("Player Start Actor Found"));
		//if(ShouldSpawnAtStartSpot(PCon))
			//GEngine->AddOnScreenDebugMessage(-1, 7.f, FColor::Green, TEXT("Should Spawn at start spot"));
		//else
			//GEngine->AddOnScreenDebugMessage(-1, 7.f, FColor::Red, TEXT("Should not Spawn at start spot"));
		return m_startPoints[0];
	}
	else {
		//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Player Start Actor Not Found"));
		return Super::FindPlayerStart_Implementation(PCon, IncomingName);
	}
}
*/