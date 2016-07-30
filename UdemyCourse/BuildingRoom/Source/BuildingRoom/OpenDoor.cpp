// Fill out your copyright notice in the Description page of Project Settings.

#include "BuildingRoom.h"
#include "OpenDoor.h"


// Sets default values for this component's properties
UOpenDoor::UOpenDoor()
{
    bWantsBeginPlay = true;
	PrimaryComponentTick.bCanEverTick = true;
}


// Called when the game starts
void UOpenDoor::BeginPlay()
{
	Super::BeginPlay();
    
    if(GetWorld()) {
        ActorThatOpensDoor = GetWorld()->GetFirstPlayerController()->GetPawn();
        Owner = GetOwner();
    }
}

void UOpenDoor::OpenTheDoor()
{
    
    //FRotator NewRotation = FRotator(0.0f, 90.0f, 0.0f);
    //if(Owner)
    //    Owner->SetActorRotation(NewRotation);
    
    if(Owner)
       OnOpen.Broadcast();
    
}

void UOpenDoor::CloseDoor()
{
    
    //FRotator NewRotation = FRotator(0.0f, 0.0f, 0.0f);
   
    //if(Owner)
    //    Owner->SetActorRotation(NewRotation);
    
    OnClose.Broadcast();
    
}


// Called every frame
void UOpenDoor::TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction )
{
	Super::TickComponent( DeltaTime, TickType, ThisTickFunction );

    if(GetTotalMassOfActorsOnPlate() >= 0.f)
    {
        OpenTheDoor();
        LastDoorOpenTime = GetWorld()->GetTimeSeconds();
    }
	
    if( GetWorld()->GetTimeSeconds() - LastDoorOpenTime > DoorCloseDelay )
    {
        CloseDoor();
    }
    
}

float UOpenDoor::GetTotalMassOfActorsOnPlate()
{
    float TotalMass = 0.1f;
    
    TArray< AActor* > OverlappingActors;
    PressurePlate->GetOverlappingActors(OverlappingActors);
    
    for(const auto& Actor: OverlappingActors)
    {
        TotalMass += Actor->FindComponentByClass< UPrimitiveComponent >()->GetMass();
    }
    
    return TotalMass;

}

