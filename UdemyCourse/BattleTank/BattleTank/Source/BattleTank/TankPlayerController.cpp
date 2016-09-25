// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "TankPlayerController.h"


void ATankPlayerController::BeginPlay()
{
    Super::BeginPlay();
    
    auto ControlledTank = GetGameControlledTank();
    
    if(ControlledTank) {
        UE_LOG(LogTemp, Warning, TEXT("Player Controller BeginPlay() possessing %s "), *(ControlledTank->GetName()));
    } else  {
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
    
    //Get world location if line trace throught crosshair
    
    FVector HitLocation; //parameter
    
    if(GetSightRayHitLocation(HitLocation))
    {
        UE_LOG(LogTemp, Warning, TEXT("Hit location: %s "), *(HitLocation.ToString()));
    
        //if hits the landscape tell controlled tank to aim ait this point
    }
}

//Checks it hits landscape
bool ATankPlayerController::GetSightRayHitLocation(FVector& HitLocation) const
{
    
    HitLocation = FVector(1.0);
    
    return true;
}
