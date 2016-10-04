
#include "BattleTank.h"
#include "Tank.h"
#include "TankAIController.h"


void ATankAIController::BeginPlay()
{
    Super::BeginPlay();
  
}

void ATankAIController::Tick( float DeltaTime )
{
	Super::Tick(DeltaTime);

	auto PlayerTank = Cast<ATank>(GetWorld()->GetFirstPlayerController()->GetPawn());
	auto ControlledTank = Cast<ATank>(GetPawn());

	if (PlayerTank)
	{
		// TODO Move towards the player

		// Aim towards the player
		ControlledTank->AimAt(PlayerTank->GetActorLocation());
		//UE_LOG(LogTemp, Warning, TEXT(" AIController aim to %f"), *PlayerTank->GetActorLocation().ToString());
		ControlledTank->Fire(); // TODO limit firing rate
	}
}
