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
