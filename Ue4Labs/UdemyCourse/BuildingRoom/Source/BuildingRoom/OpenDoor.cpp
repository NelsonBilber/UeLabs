// Fill out your copyright notice in the Description page of Project Settings.

#include "BuildingRoom.h"
#include "OpenDoor.h"


// Sets default values for this component's properties
UOpenDoor::UOpenDoor()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	bWantsBeginPlay = true;
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UOpenDoor::BeginPlay()
{
	Super::BeginPlay();

	// ...
    if(GetWorld()) {
        ActorThatOpensDoor = GetWorld()->GetFirstPlayerController()->GetPawn();
        Owner = GetOwner();
    }
}

void UOpenDoor::OpenTheDoor(){
    
    FRotator NewRotation = FRotator(0.0f, 90.0f, 0.0f);
   
    if(Owner)
        Owner->SetActorRotation(NewRotation);
    
}

void UOpenDoor::CloseDoor(){
    
    FRotator NewRotation = FRotator(0.0f, 0.0f, 0.0f);
   
    if(Owner)
        Owner->SetActorRotation(NewRotation);
    
}


// Called every frame
void UOpenDoor::TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction )
{
	Super::TickComponent( DeltaTime, TickType, ThisTickFunction );

	// ...
    if(PressurePlate){
        if(PressurePlate->IsOverlappingActor(ActorThatOpensDoor)){
            OpenTheDoor();
            LastDoorOpenTime = GetWorld()->GetTimeSeconds();
        }
        if( GetWorld()->GetTimeSeconds() - LastDoorOpenTime > DoorCloseDelay ){
            CloseDoor();
        }
    }
}
