// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Pawn.h"
#include "PawnWithCamera.generated.h"

UCLASS()
class HOWTO_PLAYERCAMERA_API APawnWithCamera : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	APawnWithCamera();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* InputComponent) override;
 
    
protected:
    
    void MoveForward(float AxisValue);
    void MoveRight(float AxisValue);
    void PitchCamera(float AxisValue);
    void YawCamera(float Axisvalue);
    void ZoomIn();
    void ZoomOut();
    
    UPROPERTY(EditAnywhere)
    USpringArmComponent* OurCameraSpringArm;
    UCameraComponent* OurCamera;
	
    
    //input variables
    FVector2D MovementInput;
    FVector2D CameraInput;
    float ZoomFactor;
    bool bZoomingIn;
};
