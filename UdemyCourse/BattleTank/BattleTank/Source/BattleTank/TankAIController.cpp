
#include "BattleTank.h"
#include "Tank.h"
#include "TankAIController.h"


void ATankAIController::BeginPlay()
{
    Super::BeginPlay();
    
    auto PlayerTank = GetPlayerTank();
    
    if(PlayerTank)
    {
        UE_LOG(LogTemp, Warning, TEXT("AI => Player Controller found player %s "), *(PlayerTank->GetName()));
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("AI => Player Controller can't find player tank "));
    }
}

void ATankAIController::Tick( float DeltaTime )
{
    Super::Tick( DeltaTime );
    
    if(GetPlayerTank())
    {
        GetGameControlledTank()->AimAt(GetPlayerTank()->GetActorLocation());
    }
}

//Get Current Pawn -> AIController
ATank* ATankAIController::GetGameControlledTank() const
{
    return Cast<ATank>(GetPawn());
}


//Get current player controller
ATank* ATankAIController::GetPlayerTank() const
{
    auto PlayerPawn = GetWorld()->GetFirstPlayerController()->GetPawn();
    if(PlayerPawn)
    {
        return Cast<ATank>(PlayerPawn);
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("AIController => Can't find player tank "));
        return nullptr;
    }

}
