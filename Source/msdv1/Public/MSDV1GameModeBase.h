// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"


#include "MSDV1PlayerController.h"

#include "MSDV1GameModeBase.generated.h"

/**
 * 
 La clase GameModeBase se instancia en el servidor, y no en los clientes.
 Como mínimo debería inicializar quién es el PlayerController (PlayerControllerClass) en el constructor
 y quién es el Pawn del jugador.

 */
UCLASS()
class MSDV1_API AMSDV1GameModeBase : public AGameModeBase
{
	GENERATED_BODY()
	
public:
	AMSDV1GameModeBase(); // Constructor del GameMode

	//virtual AActor* FindPlayerStart_Implementation(AController* Player, const FString& IncomingName = TEXT("")) override;

	UPROPERTY()
		FName m_startPlayerTag;

private:
	UPROPERTY()
		TArray<class AActor*> m_startPoints;
};
