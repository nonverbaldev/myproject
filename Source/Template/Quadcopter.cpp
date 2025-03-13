// Fill out your copyright notice in the Description page of Project Settings.


#include "Quadcopter.h"
#include "GameFramework/PlayerInput.h"
#include "Engine/StaticMesh.h"
#include "Camera/CameraComponent.h"

// Sets default values
AQuadcopter::AQuadcopter()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

    MeshComponent = CreateOptionalDefaultSubobject<UStaticMeshComponent>("MeshComponent");
    if (MeshComponent) 
	{
        MeshComponent->SetupAttachment(RootComponent);
		MeshComponent->SetSimulatePhysics(true);
        MeshComponent->SetMassOverrideInKg(NAME_None, 1.f, true);	
    }

	CameraComponent = CreateOptionalDefaultSubobject<UCameraComponent>("CameraComponent");
	if (CameraComponent)
	{
		CameraComponent->SetupAttachment(MeshComponent);
		CameraComponent->SetRelativeRotation(FRotator(55.f, 0.f, 0.f));
		CameraComponent->SetFieldOfView(130.f);
	}
    ThrottleInput = 0.f;
    ThrottleForce = 100000.f;
	RelativeRotation = FRotator::ZeroRotator;
	MouseSensitivity = 1.f;
	bHasRelativeRotation = false;
}

// Called when the game starts or when spawned
void AQuadcopter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AQuadcopter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (ThrottleInput != 0.f) 
	{
		MeshComponent->AddForce(GetActorUpVector() * ThrottleInput * DeltaTime);
		ThrottleInput = 0.f;
	}
	if (bHasRelativeRotation) 
	{
		SetActorRelativeRotation(RelativeRotation);
	}

}

// Called to bind functionality to input
void AQuadcopter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	check(PlayerInputComponent);

	PlayerInputComponent->BindAxis("Quadcopter_Throttle", this, &AQuadcopter::Quadcopter_Throttle);
	PlayerInputComponent->BindAxis("Quadcopter_Yaw", this, &AQuadcopter::Quadcopter_Yaw);
	PlayerInputComponent->BindAxis("Quadcopter_Throttle", this, &AQuadcopter::Mouse_Roll);
	PlayerInputComponent->BindAxis("Quadcopter_Yaw", this, &AQuadcopter::Mouse_Pitch);
}

void AQuadcopter::Quadcopter_Throttle(float Val)
{
	if (Val != 0.f) 
	{
		ThrottleInput = Val * ThrottleForce;
	}
}

void AQuadcopter::Quadcopter_Yaw(float Val)
{
}

void AQuadcopter::Mouse_Roll(float Val)
{
	if (Val != 0.f)
	{
		RelativeRotation.Roll += Val * MouseSensitivity;
		bHasRelativeRotation = true;

	}
}

void AQuadcopter::Mouse_Pitch(float Val)
{
	if (Val != 0.f)
	{
		RelativeRotation.Pitch += Val * MouseSensitivity;
		bHasRelativeRotation = true;

	}
}

void InitializeQuadcopterInputBindings()
{
	static bool bBindingsAdded = false;
	if (!bBindingsAdded)
	{
		bBindingsAdded = true;

		UPlayerInput::AddEngineDefinedAxisMapping(FInputAxisKeyMapping("Quadcopter_Throttle", EKeys::W, 1.f));
		UPlayerInput::AddEngineDefinedAxisMapping(FInputAxisKeyMapping("Quadcopter_Yaw", EKeys::A, -1.f));
		UPlayerInput::AddEngineDefinedAxisMapping(FInputAxisKeyMapping("Quadcopter_Yaw", EKeys::D, -1.f));

		UPlayerInput::AddEngineDefinedAxisMapping(FInputAxisKeyMapping("Mouse_Roll", EKeys::MouseX, 1.f));
		UPlayerInput::AddEngineDefinedAxisMapping(FInputAxisKeyMapping("Mouse_Pitch", EKeys::MouseY, 1.f));
		UPlayerInput::AddEngineDefinedAxisMapping(FInputAxisKeyMapping("Mouse_Roll", EKeys::MouseX, -1.f));
		UPlayerInput::AddEngineDefinedAxisMapping(FInputAxisKeyMapping("Mouse_Pitch", EKeys::MouseY, -1.f));

	}
}
