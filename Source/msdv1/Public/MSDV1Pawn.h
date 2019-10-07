// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/DefaultPawn.h"
#include "MSDV1Pawn.generated.h"

UCLASS()
class MSDV1_API AMSDV1Pawn : public ADefaultPawn
{
	GENERATED_BODY()

protected:

	virtual void BeginPlay() override;

public:
	// Sets default values for this pawn's properties
	AMSDV1Pawn();


	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:
	void OnMoveForward(float value);
	void OnMoveRight(float value);
	void OnLookUp(float value);
	void OnLookRight(float value);

	UStaticMeshComponent* MeshComponent;

	float m_horizontalCamSpeed;
	float m_verticalCamSpeed;
	float m_speed;

};
