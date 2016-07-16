// Fill out your copyright notice in the Description page of Project Settings.

#include "BuildingRoom.h"
#include "Grabber.h"


// Sets default values for this component's properties
UGrabber::UGrabber()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	bWantsBeginPlay = true;
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UGrabber::BeginPlay()
{
	Super::BeginPlay();

	// ...
    
    UE_LOG(LogTemp, Warning, TEXT("Grabber reporting for dutty !"));
	
}


// Called every frame
void UGrabber::TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction )
{
	Super::TickComponent( DeltaTime, TickType, ThisTickFunction );

	// GET PLAYER VIEW POINT THIS TICK
   
    auto World = GetWorld();
    if(World){
        FVector PlayerViewPointLocation;
        FRotator PlayerViewPointRotation;
        World->GetFirstPlayerController()->GetPlayerViewPoint(PlayerViewPointLocation, PlayerViewPointRotation );
    
        UE_LOG(LogTemp, Warning, TEXT("location %s , position %s "), *PlayerViewPointLocation.ToString(),*PlayerViewPointRotation.ToString());
    
        FVector LineTraceEnd = PlayerViewPointLocation + ( PlayerViewPointRotation.Vector() * Reach );
        
        DrawDebugLine(
                      World,
                      PlayerViewPointLocation,
                      LineTraceEnd,
                      FColor::Red,
                      false,
                      0.0f,
                      0.0f,
                      10.0f
                      
        );
    
    }
    
    
    // ray-cast out to reach distance
    
    //see what we it

}

