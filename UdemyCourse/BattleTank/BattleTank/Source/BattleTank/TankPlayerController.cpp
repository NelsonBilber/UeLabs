// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "TankPlayerController.h"




ATank* ATankPlayerController::GetGameControlledTank() const
{
    return Cast<ATank>(GetPawn());
}
