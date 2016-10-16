// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "Tank.h"
#include "TankAimingComponent.h"
#include "Tank.h"
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
        if(!AimingComponent)
            return;
        
		// Aim towards the player
		AimingComponent->AimAt(PlayerTank->GetActorLocation());

        if(AimingComponent->GetFiringState() == EFiringState::Locked )
        {
            AimingComponent->Fire();
        }
	}
}


void ATankAIController::SetPawn(APawn* InPawn)
{
    Super::SetPawn(InPawn);
   
    if(InPawn)
    {
        auto PosseedTank = Cast<ATank>(InPawn);
        if(!PosseedTank) return;
        
        //subscribe local method deade event
        PosseedTank->OnDeath.AddUniqueDynamic(this, &ATankAIController::OnPossedTankDeath);
    }
}

void ATankAIController::OnPossedTankDeath()
{
    if(!GetPawn()) return;
    
    GetPawn()->DetachFromControllerPendingDestroy();
}
