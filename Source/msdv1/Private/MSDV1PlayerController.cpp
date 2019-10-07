
#include "MSDV1PlayerController.h"
#include "EngineUtils.h"
#include "Kismet/GameplayStatics.h"



AMSDV1PlayerController::AMSDV1PlayerController() : m_rotationSpeed(100.0f),
m_rotationTag("Rotable"),
m_shouldRotate(true),
m_mainCameraTag("MainCamera"),
m_floorTag("Floor")
{

	PrimaryActorTick.bCanEverTick = true;

	m_actors.Reserve(10); // Reservamos 10 punteros  en el TArray.
	m_cameras.Reserve(5);
	m_floor.Reserve(1);

}

void AMSDV1PlayerController::BeginPlay() {

	Super::BeginPlay();

	int32 numActors = 0;

	UGameplayStatics::GetAllActorsWithTag(GetWorld(), m_rotationTag, m_actors);
	/*
	UWorld* world = GetWorld();

	for (TActorIterator<AStaticMeshActor> itr(world); itr; ++itr) {
		m_staticActors.Add(*itr);
		++numActors;
	}

	*/

	UE_LOG(LogTemp, Warning, TEXT("We found %d Static Mesh Actors"), m_actors.Num());
	// Cambiamos a cámara fija
	UGameplayStatics::GetAllActorsWithTag(GetWorld(), m_mainCameraTag, m_cameras);
	if (m_cameras.Num() > 0) {
		this->SetViewTarget(m_cameras[0]);
	}

	UGameplayStatics::GetAllActorsWithTag(GetWorld(), m_floorTag, m_floor);
	if (m_floor.Num() > 0) {
		FVector origin;
		FVector size;
		m_floor[0]->GetActorBounds(true, origin, size);
		FVector location = m_floor[0]->GetActorLocation();
		UE_LOG(LogTemp, Warning, TEXT("We found the Floor. Origin: %g %g %g Size %g %g %g"), location[0], location[1], location[2], size[0], size[1], size[2]);
		m_xLimits[0] = origin[0] -  size[0];
		m_xLimits[1] = origin[0] - size[0] + 4 * size[0];
		m_yLimits[0] = origin[1] - size[1];
		m_yLimits[1] = origin[1] - size[1] + 4 * size[1];
		UE_LOG(LogTemp,Warning,TEXT("Limits %g %g %g %g"), m_xLimits[0], m_xLimits[1], m_yLimits[0], m_yLimits[1])
	}
	else
		UE_LOG(LogTemp, Warning, TEXT("We didn't find the Floor"));
}

void AMSDV1PlayerController::Tick(float deltaTime) {

	Super::Tick(deltaTime);

	if (!m_shouldRotate) {
		return;
	}

	const FRotator rotation(0.0f, m_rotationSpeed*deltaTime, 0.0f);

	const int32 numActors = m_actors.Num();

	for (int32 i = 0; i < numActors; ++i)
	{
		m_actors[i]->AddActorWorldRotation(rotation,true);
	}
	

}

void AMSDV1PlayerController::SetupInputComponent() {
	Super::SetupInputComponent();
	InputComponent->BindAction(TEXT("ToggleRotation"), IE_Pressed, this, &AMSDV1PlayerController::OnToggleRotation);
}

void AMSDV1PlayerController::OnToggleRotation() {
	m_shouldRotate = !m_shouldRotate;
}