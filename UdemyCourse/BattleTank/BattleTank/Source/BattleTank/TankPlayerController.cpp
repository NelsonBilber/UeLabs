
#include "BattleTank.h"
#include "Tank.h"
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
        //if hits the landscape tell controlled tank to aim ait this point
        GetGameControlledTank()->AimAt(HitLocation);
    }
}

//Checks it hits landscape
bool ATankPlayerController::GetSightRayHitLocation(FVector& HitLocation) const
{
    int32 ViewPortSizeX, ViewPortSizeY;
    GetViewportSize(ViewPortSizeX, ViewPortSizeY);
    auto ScreenLocation = FVector2D(ViewPortSizeX * CrosshairXLocation, ViewPortSizeY * CrosshairYLocation);
    //UE_LOG(LogTemp, Warning, TEXT("ScreenLocation: %s"), *ScreenLocation.ToString());
    
    FVector LookDirection;
    if(GetLookDirection(ScreenLocation, LookDirection))
    {
        //line-trace along that look direction
        //UE_LOG(LogTemp, Warning, TEXT("Look Direction: %s "), *(LookDirection.ToString()));
        GetLookVectorHitLocation(LookDirection, HitLocation);
    }
    
    return true;
}

bool ATankPlayerController::GetLookVectorHitLocation(FVector LookDirection, FVector& HitLocation) const
{
    FHitResult HitResult;
    auto Startlocation = PlayerCameraManager->GetCameraLocation(); //Get Current Camera Location
    auto Endlocation = Startlocation + (LookDirection * LineTraceRange);
    
    if(GetWorld()->LineTraceSingleByChannel(
                                            HitResult,
                                            Startlocation,
                                            Endlocation,
                                            ECollisionChannel::ECC_Visibility )) {
        HitLocation = HitResult.Location;
        return true;
    }
    HitLocation = FVector(0);
    return false;
}

bool ATankPlayerController::GetLookDirection(FVector2D ScreenLocation, FVector& LookDirection) const
{
    FVector CameraWorldLocation;
    return DeprojectScreenPositionToWorld(ScreenLocation.X, ScreenLocation.Y, CameraWorldLocation, LookDirection);
}
