#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "Containers/Array.h"
#include "Engine/StaticMeshActor.h"
#include "MSDV1PlayerController.generated.h"

UCLASS()
class MSDV1_API AMSDV1PlayerController : public APlayerController {

	GENERATED_BODY()

public:

	AMSDV1PlayerController();

	virtual void BeginPlay() override;
	virtual void Tick(float deltaTime) override;
	virtual void SetupInputComponent() override;

	FVector m_xLimits;
	FVector m_yLimits;
private:

	void OnToggleRotation();

	// Los TArray son contenedores controlados por el garbage collector
	// Si se marcan con UPROPERTY el motor entenderá que este TArray es un miembro del
	// PlayerController y no lo eliminará mientras exista el PlayerController. 
	// Es decir, será considerado en el sistema de instancias controlado por el motor
	// UPROPERTY ´también se usa para conectar C++ con el sistema de Blueprints del editor.
	/*
	UPROPERTY()
	TArray<class AStaticMeshActor*> m_staticActors;
	*/

	UPROPERTY()
	TArray<class AActor*> m_actors;

	UPROPERTY()
		TArray<class AActor*> m_cameras;

	UPROPERTY()
		TArray<class AActor*> m_floor;
	
	

	float m_rotationSpeed;
	FName m_rotationTag;
	bool m_shouldRotate;
	FName m_mainCameraTag;
	FName m_floorTag;

};