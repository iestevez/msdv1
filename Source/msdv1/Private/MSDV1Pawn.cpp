// Fill out your copyright notice in the Description page of Project Settings.


#include "MSDV1Pawn.h"
#include "MSDV1PlayerController.h"
#include "Components/InputComponent.h"
#include "GameFramework/Actor.h"
#include "UObject/ConstructorHelpers.h"
#include "Components/StaticMeshComponent.h"

// Sets default values
AMSDV1Pawn::AMSDV1Pawn()
	: m_horizontalCamSpeed(30.0f)
	, m_verticalCamSpeed(30.0f)
	, m_speed(10.0f)

{
	// Structure to hold one-time initialization
	struct FConstructorStatics
	{
		ConstructorHelpers::FObjectFinder<UStaticMesh> SphereMesh;
		FConstructorStatics()
			: SphereMesh(TEXT("/Engine/EngineMeshes/Cylinder")) {}
	};
	static FConstructorStatics ConstructorStatics;
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	MeshComponent = GetMeshComponent();
	MeshComponent->SetStaticMesh(ConstructorStatics.SphereMesh.Object);

}

void AMSDV1Pawn::BeginPlay() {

	Super::BeginPlay();
}


// Called to bind functionality to input
// It is called when the PlayerController owns the pawn
void AMSDV1Pawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	checkf(PlayerInputComponent != nullptr, TEXT("The input component for the default pawn was not created"));
	//Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAxis(TEXT("Forward"), this, &AMSDV1Pawn::OnMoveForward);
	PlayerInputComponent->BindAxis(TEXT("Right"), this, &AMSDV1Pawn::OnMoveRight);
	PlayerInputComponent->BindAxis(TEXT("LookUp"), this, &AMSDV1Pawn::OnLookUp);
	PlayerInputComponent->BindAxis(TEXT("LookRight"), this, &AMSDV1Pawn::OnLookRight);

	

}

void AMSDV1Pawn::OnMoveForward(float value) {

	if (value != 0.0f) {
		AMSDV1PlayerController* PCon = (class AMSDV1PlayerController*) GetController();
		//const FRotator rot = GetControlRotation();
		//const FVector dir = FRotationMatrix(rot).GetScaledAxis(EAxis::X);
		const FVector dir = MeshComponent->GetForwardVector();
		const FVector position = GetActorLocation();
		FVector newposition = position + m_speed*value * FVector(dir[0],dir[1],0.0f);
		bool outOfLimits = false;
		if (PCon->m_xLimits[0] > newposition[0]) {
			newposition[0] = PCon->m_xLimits[0];
			newposition[1] = position[1];
			newposition = position;
			UE_LOG(LogTemp, Warning, TEXT("1. x0 %g x1 %g np0 %g "), PCon->m_xLimits[0], PCon->m_xLimits[1], newposition[0]);
			//value = 0.0f;
		}
		if (PCon->m_xLimits[1] < newposition[0]) {
			newposition[0] = PCon->m_xLimits[1];
			newposition[1] = position[1];
			newposition = position;
			UE_LOG(LogTemp, Warning, TEXT("2. x0 %g x1 %g np0 %g "), PCon->m_xLimits[0], PCon->m_xLimits[1], newposition[0]);
			//value = 0.0f;
		}
		if (PCon->m_yLimits[0] > newposition[1]) {
			newposition[1] = PCon->m_yLimits[0];
			newposition[0] = position[0];
			newposition = position;
			UE_LOG(LogTemp, Warning, TEXT("3. y0 %g y1 %g np1 %g "), PCon->m_yLimits[0], PCon->m_yLimits[1], newposition[1]);
			//value = 0.0f;
		}
		if (PCon->m_yLimits[1] < newposition[1]) {
			newposition[1] = PCon->m_yLimits[1];
			newposition[0] = position[0];
			newposition = position;
			UE_LOG(LogTemp, Warning, TEXT("4. y0 %g y1 %g np1 %g "), PCon->m_yLimits[0], PCon->m_yLimits[1], newposition[1]);
			//value = 0.0f;
		}
		
		this->SetActorLocation(newposition,true);
		//AddMovementInput(dir, value);
	}
}


void AMSDV1Pawn::OnMoveRight(float value) {

	if (value != 0.0f) {
		float deltaTime = GetWorld()->GetDeltaSeconds();
		//AddControllerYawInput(value*m_speed*deltaTime);
		//const FRotator rot = GetControlRotation();
		//const FVector dir = FRotationMatrix(rot).GetScaledAxis(EAxis::Y);
		const FRotator deltaRot = FRotator(0.0f, value, 0.0f);
		MeshComponent->AddLocalRotation(deltaRot);
		//AddMovementInput(dir, value);
		//AddControllerYawInput(value);
	}
}

void AMSDV1Pawn::OnLookUp(float value) {

	if (value != 0.0f) {

		float deltaTime = GetWorld()->GetDeltaSeconds();
		//AddControllerPitchInput(m_verticalCamSpeed*value*deltaTime);

	}

}

void AMSDV1Pawn::OnLookRight(float value) {

	if (value != 0.0f) {

		float deltaTime = GetWorld()->GetDeltaSeconds();
		//AddControllerYawInput(m_horizontalCamSpeed*value*deltaTime);

	}

}