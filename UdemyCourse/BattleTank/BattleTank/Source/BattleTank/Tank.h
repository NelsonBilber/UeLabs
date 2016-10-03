// Fill out your copyright notice in the Description page of Project Settings.

#pragma once


#include "GameFramework/Pawn.h"
#include "Tank.generated.h"


class UTankBarrel;
class UTankTurret;
class UTankAimingComponent;


UCLASS()
class BATTLETANK_API ATank : public APawn
{
	GENERATED_BODY()

public:
    void AimAt(FVector HitLocation);
    
protected:
    
    UTankAimingComponent* TankAimingComponent = nullptr;
    
    UFUNCTION(BlueprintCallable, Category = "Setup")
    void SetBarrelReference(UTankBarrel* BarrelToSet);

	UFUNCTION(BlueprintCallable, Category = "Setup")
	void SetTurretReference(UTankTurret* TurretToSet);
    
private:
	// Sets default values for this pawn's properties
	ATank();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* InputComponent) override;
    
    UPROPERTY(EditAnywhere, Category = "Firing")
    float LaunchSpeed = 100000; //Sensible starting value of 1000 m/s
    
};
