// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "AIController.h"
#include "TankAIController.generated.h"

UCLASS()
class BATTLETANK_API ATankAIController : public AAIController
{
	GENERATED_BODY()

public:
    
    virtual void BeginPlay() override;
	
protected:
    
    UPROPERTY(EditDefaultsOnly, Category = "Setup")
    float AcceptanceRadius = 80000;
    
    
private:
	
    
    virtual void SetPawn(APawn* InPawn) override;

	virtual void Tick(float DeltaSeconds) override;
    
    UFUNCTION()
    void OnPossedTankDeath();
    
};
