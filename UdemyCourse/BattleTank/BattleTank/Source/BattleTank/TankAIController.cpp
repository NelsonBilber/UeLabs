// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "TankAIController.h"




void TankAIController::BeginPlay()
{
    Super::BeginPlay();
    
    auto ControlledTank = GetGameControlledTank();
    
    if(ControlledTank) {
        UE_LOG(LogTemp, Warning, TEXT("AI => Player Controller BeginPlay() possessing %s "), *(ControlledTank->GetName()));
    } else  {
        UE_LOG(LogTemp, Warning, TEXT("AI => Player Controller BeginPlay() NOT possessing a Tank "));
    }
}

ATank* TankAIController::GetGameControlledTank() const
{
    return Cast<ATank>(GetPawn());
}
