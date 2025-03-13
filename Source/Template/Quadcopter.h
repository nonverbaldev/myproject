// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Quadcopter.generated.h"

class UCameraComponent;

UCLASS()
class TEMPLATE_API AQuadcopter : public APawn
{
	GENERATED_BODY()

	private:
    /** The mesh associated with this Quadcopter. */
    UPROPERTY(Category = Pawn, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
    UStaticMeshComponent* MeshComponent;

	/** The camera associated with this Quadcopter. */
	UPROPERTY(Category = Pawn, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	UCameraComponent* CameraComponent;



public:
	// Sets default values for this Quadcopter's properties
	AQuadcopter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;


	UFUNCTION(BlueprintCallable, Category = "Quadcopter")
	virtual void Quadcopter_Throttle(float Val);
	UFUNCTION(BlueprintCallable, Category = "Quadcopter")
	virtual void Quadcopter_Yaw(float Val);
	UFUNCTION(BlueprintCallable, Category = "Quadcopter")
	virtual void Mouse_Roll(float Val);
	UFUNCTION(BlueprintCallable, Category = "Quadcopter")
	virtual void Mouse_Pitch(float Val);


public:
    UPROPERTY(Category = Quadcopter, EditAnywhere, BlueprintReadOnly)
    float ThrottleInput;
    UPROPERTY(Category = Quadcopter, EditAnywhere, BlueprintReadOnly)
    float ThrottleForce;
	UPROPERTY(Category = Quadcopter, EditAnywhere, BlueprintReadOnly)
	FRotator RelativeRotation;
	UPROPERTY(Category = Quadcopter, EditAnywhere, BlueprintReadOnly)
	float MouseSensitivity;
	UPROPERTY(Category = Quadcopter, EditAnywhere, BlueprintReadOnly)
	bool bHasRelativeRotation;
};

void InitializeQuadcopterInputBindings();
