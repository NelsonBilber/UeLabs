// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "TankTrack.h"
#include "TankMovementComponent.h"

UTankMovementComponent::UTankMovementComponent()
{
    bWantsBeginPlay = true;
    PrimaryComponentTick.bCanEverTick = false;

}

void UTankMovementComponent::Initialise(UTankTrack* LeftTrackToSet, UTankTrack* RightTrackToSet)
{
    if(!RightTrack || !LeftTrack){
        UE_LOG(LogTemp, Warning, TEXT("FAIL SETUP, TRACKs .................... !!"));
        return;
    }
    else
    {
        RightTrack = RightTrackToSet;
        LeftTrack = LeftTrackToSet;
        
        UE_LOG(LogTemp, Warning, TEXT("Good to roll .................... !!"));
    }
}





void UTankMovementComponent::IntendMoveForward(float Throw)
{
    UE_LOG(LogTemp, Warning, TEXT("Intend move forward throw %f "), Throw);
    
    if(!RightTrack || !LeftTrack){
        UE_LOG(LogTemp, Warning, TEXT("No tracks setup"));
        return;
    }

	
    RightTrack->SetThrottle(Throw);
    LeftTrack->SetThrottle(Throw);
}
