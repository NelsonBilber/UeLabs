// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "TankPlayerController.h"


void ATankPlayerController::BeginPlay()
{
    Super::BeginPlay();
    
    auto ControlledTank = GetGameControlledTank();
    
    if(ControlledTank)
    {
        UE_LOG(LogTemp, Warning, TEXT("Player Controller BeginPlay() possessing %s "), *(ControlledTank->GetName()));
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("Player Controller BeginPlay() NOT possessing a Tank "));
    }
}


ATank* ATankPlayerController::GetGameControlledTank() const
{
    return Cast<ATank>(GetPawn());
}

void ATankPlayerController::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
    AimTowardsCrosshair();
}


void ATankPlayerController::AimTowardsCrosshair()
{
    if(!GetGameControlledTank())
    {
        return;
    }
    

    FVector HitLocation; //parameter
    
    if(GetSightRayHitLocation(HitLocation))
    {
        //UE_LOG(LogTemp, Warning, TEXT("Hit location: %s "), *(HitLocation.ToString()));
        //if hits the landscape tell controlled tank to aim ait this point
    }
}

//Checks it hits landscape
bool ATankPlayerController::GetSightRayHitLocation(FVector& HitLocation) const
{
  
    //Find the cross air
    int32 ViewPortSizeX, ViewPortSizeY;
    GetViewportSize(ViewPortSizeX, ViewPortSizeY);
    auto ScreenLocation = FVector2D(ViewPortSizeX * CrosshairXLocation, ViewPortSizeY * CrosshairYLocation);
    //UE_LOG(LogTemp, Warning, TEXT("ScreenLocation: %s"), *ScreenLocation.ToString());
    
    FVector LookDirection;
    if(GetLookDirection(ScreenLocation, LookDirection))
    {
        UE_LOG(LogTemp, Warning, TEXT("Look Direction: %s "), *(LookDirection.ToString()));
    }
    
    //line-trace along that look direction
    
    return true;
}

bool ATankPlayerController::GetLookDirection(FVector2D ScreenLocation, FVector& LookDirection) const
{
    FVector CameraWorldLocation;
    return DeprojectScreenPositionToWorld(ScreenLocation.X, ScreenLocation.Y, CameraWorldLocation, LookDirection);
}
