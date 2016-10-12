// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "Tank.h"
#include "TankAimingComponent.h"
#include "TankAIController.h"


void ATankAIController::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ATankAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	auto PlayerTank = Cast<ATank>(GetWorld()->GetFirstPlayerController()->GetPawn());
	auto ControlledTank = GetPawn();

	if (PlayerTank)
	{
		// TODO Move towards the player
        MoveToActor(PlayerTank, AcceptanceRadius);
		
        auto AimingComponent = ControlledTank->FindComponentByClass<UTankAimingComponent>();
        if(!AimingComponent) return;
        
		// Aim towards the player
		AimingComponent->AimAt(PlayerTank->GetActorLocation());

		//ControlledTank->Fire(); // TODO limit firing rate
	}
}
