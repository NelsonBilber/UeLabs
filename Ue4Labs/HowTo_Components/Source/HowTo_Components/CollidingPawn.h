// Copyright 1998-2015 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "GameFramework/Pawn.h"
#include "CollidingPawn.generated.h"

UCLASS()
class HOWTO_COMPONENTS_API ACollidingPawn : public APawn
{
    GENERATED_BODY()
    
public:
    // Sets default values for this pawn's properties
    ACollidingPawn();
    
    // Called when the game starts or when spawned
    virtual void BeginPlay() override;
    
    // Called every frame
    virtual void Tick( float DeltaSeconds ) override;
    
    // Called to bind functionality to input
    virtual void SetupPlayerInputComponent(class UInputComponent* InputComponent) override;
    
    UParticleSystemComponent* OurParticleSystem;
    class UCollidingPawnMovementComponent* OurMovementComponent;
    
    virtual UPawnMovementComponent* GetMovementComponent() const override;
    
    void MoveForward(float AxisValue);
    void MoveRight(float AxisValue);
    void Turn(float AxisValue);
    void ParticleToggle();
};

