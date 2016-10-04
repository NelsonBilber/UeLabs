
#include "BattleTank.h"
#include "Tank.h"
#include "TankAIController.h"


void ATankAIController::BeginPlay()
{
    Super::BeginPlay();
  
}

void ATankAIController::Tick( float DeltaTime )
{
    Super::Tick( DeltaTime );

	//Get current player controller
	auto PlayerTank = Cast<ATank>(GetWorld()->GetFirstPlayerController()->GetPawn());
	//Get Current Pawn -> AIController
	auto ControlledTank = Cast<ATank>(GetPawn());
    
	if (PlayerTank) {
		ControlledTank->AimAt(PlayerTank->GetActorLocation());
		ControlledTank->Fire();
    }
}
