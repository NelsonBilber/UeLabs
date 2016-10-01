// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Tank.h"
#include "GameFramework/PlayerController.h"
#include "TankPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class BATTLETANK_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
    
    virtual void BeginPlay() override;
    
    ATank* GetGameControlledTank() const;
    
    void Tick(float DeltaTime) override;
    
private:
    
    //start tank move the barrel so that a shot would it
    //where the crossjar intersetcs the world
    void AimTowardsCrosshair();
    
    bool GetSightRayHitLocation(FVector& HitLocation) const;
    
    bool GetLookDirection(FVector2D ScreenLocation, FVector& LookDirection) const;
    
    UPROPERTY(EditAnywhere)
    float CrosshairXLocation = 0.5;
    
    UPROPERTY(EditAnywhere)
    float CrosshairYLocation = 0.33;
	
};
