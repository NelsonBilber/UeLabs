// Fill out your copyright notice in the Description page of Project Settings.

#include "HowTo_PlayerCamera.h"
#include "PawnWithCamera.h"


// Sets default values
APawnWithCamera::APawnWithCamera()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
    
    
    // Root
    
    RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
    
    //Braço da camera
    
    OurCameraSpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraSpringArm"));
    OurCameraSpringArm->AttachTo(RootComponent);
    OurCameraSpringArm->SetRelativeLocationAndRotation(FVector(0.0f, 0.0f, 50.0f), FRotator(-60.0f, 0.0f, 0.0f));
    OurCameraSpringArm->TargetArmLength = 400.f;
    OurCameraSpringArm->bEnableCameraLag = true;
    OurCameraSpringArm->CameraLagSpeed = 3.0f;
    
    //camera em si
    
    OurCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("GameCamera"));
    OurCamera->AttachTo(OurCameraSpringArm, USpringArmComponent::SocketName);
    
    // take control of default player
    AutoPossessPlayer = EAutoReceiveInput::Player0;

}

// Called when the game starts or when spawned
void APawnWithCamera::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APawnWithCamera::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );
    
    if(bZoomingIn)
    {
        ZoomFactor += DeltaTime / 0.5f;
    }
    else
    {
        ZoomFactor -= DeltaTime / 0.25f;
    }
    
    ZoomFactor = FMath::Clamp<float>(ZoomFactor, 0.0f, 1.0f);
    
    //Blend our camera's FOV and our SpringArm's length based on ZoomFactor
    OurCamera->FieldOfView = FMath::Lerp<float>(90.0f, 60.0f, ZoomFactor);
    OurCameraSpringArm->TargetArmLength = FMath::Lerp<float>(400.0f, 300.0f, ZoomFactor);
    
    //Rotate our actor's yaw, which will turn our camera because we're attached to it
    {
        FRotator NewRotation = GetActorRotation();
        NewRotation.Yaw += CameraInput.X;
        SetActorRotation(NewRotation);
    }
    
    //Rotate our camera's pitch, but limit it so we're always looking downward
    {
        FRotator NewRotation = OurCameraSpringArm->GetComponentRotation();
        NewRotation.Pitch = FMath::Clamp(NewRotation.Pitch + CameraInput.Y, -80.0f, -15.0f);
        OurCameraSpringArm->SetWorldRotation(NewRotation);
    }
    
    //Handle movement based on our "MoveX" and "MoveY" axes
    {
        if (!MovementInput.IsZero())
        {
            //Scale our movement input axis values by 100 units per second
            MovementInput = MovementInput.SafeNormal() * 100.0f;
            FVector NewLocation = GetActorLocation();
            NewLocation += GetActorForwardVector() * MovementInput.X * DeltaTime;
            NewLocation += GetActorRightVector() * MovementInput.Y * DeltaTime;
            SetActorLocation(NewLocation);
        }
    }

}
    


// Called to bind functionality to input
void APawnWithCamera::SetupPlayerInputComponent(class UInputComponent* InputComponent)
{
	Super::SetupPlayerInputComponent(InputComponent);
    
    //interact with UnrealEngine
    
    //Hook up events for "ZoomIn"
    InputComponent->BindAction("ZoomIn", IE_Pressed, this, &APawnWithCamera::ZoomIn);
    InputComponent->BindAction("ZoomIn", IE_Released, this, &APawnWithCamera::ZoomOut);
    
    //Hook up every-frame handling for our four axes
    InputComponent->BindAxis("MoveForward", this, &APawnWithCamera::MoveForward);
    InputComponent->BindAxis("MoveRight", this, &APawnWithCamera::MoveRight);
    InputComponent->BindAxis("CameraPitch", this, &APawnWithCamera::PitchCamera);
    InputComponent->BindAxis("CameraYaw", this, &APawnWithCamera::YawCamera);
    
}

void APawnWithCamera::MoveForward(float AxisValue)
{
    MovementInput.X = FMath::Clamp<float>(AxisValue, -1.0f, 1.0f);
}

void APawnWithCamera::MoveRight(float AxisValue)
{
    MovementInput.Y = FMath::Clamp<float>(AxisValue, -1.0f, 1.0f);
}

void APawnWithCamera::PitchCamera(float AxisValue)
{
    CameraInput.Y = AxisValue;
}

void APawnWithCamera::YawCamera(float AxisValue)
{
    CameraInput.X = AxisValue;
}

void APawnWithCamera::ZoomIn()
{
    bZoomingIn = true;
}

void APawnWithCamera::ZoomOut()
{
    bZoomingIn = false;
}

