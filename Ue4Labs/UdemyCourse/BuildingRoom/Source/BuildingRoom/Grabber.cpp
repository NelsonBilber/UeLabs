// Fill out your copyright notice in the Description page of Project Settings.

#include "BuildingRoom.h"
#include "Grabber.h"


// Sets default values for this component's properties
UGrabber::UGrabber()
{
	bWantsBeginPlay = true;
	PrimaryComponentTick.bCanEverTick = true;
}


// Called when the game starts
void UGrabber::BeginPlay()
{
	Super::BeginPlay();

    FindPhysicsHandleComponent();
    
    SetupInputComponent();
	
}

void UGrabber::FindPhysicsHandleComponent()
{
    
    UE_LOG(LogTemp, Warning, TEXT("Grabber reporting for dutty !"));
    
    PhysicsHandle = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();
    if(PhysicsHandle == nullptr)
    {
        UE_LOG(LogTemp, Error, TEXT("component fail  %s  to deal with physics handle"),
               *(GetOwner()->GetName()) );

    }
}

void UGrabber::SetupInputComponent()
{
   
    InputComponent = GetOwner()->FindComponentByClass<UInputComponent>();
    if(InputComponent)
    {
        UE_LOG(LogTemp, Warning, TEXT("Input component found !"));
        InputComponent->BindAction("Grab", IE_Pressed, this, &UGrabber::Grab);
        InputComponent->BindAction("Grab", IE_Released, this, &UGrabber::Release);
        
    }
    else
    {
        UE_LOG(LogTemp, Error, TEXT("!!!!!component fail  %s  to deal with input component"),
               *(GetOwner()->GetName()) );
        
    }
}

void UGrabber::Grab()
{
    
    UE_LOG(LogTemp, Warning, TEXT("Grab !"));
    
    auto HitResult = GetFirstPhysicsBodyInReach();
    auto ComponentToGrab = HitResult.GetComponent();
    auto ActorHit = HitResult.GetActor();
   
    if(ActorHit)
    {
        PhysicsHandle->GrabComponent(
                                 ComponentToGrab,
                                 NAME_None, // bone location
                                 ComponentToGrab->GetOwner()->GetActorLocation(),
                                 true //allow rotation
        );
    }
    
}

void UGrabber::Release()
{
    
    UE_LOG(LogTemp, Warning, TEXT("Release !"));
    
    PhysicsHandle->ReleaseComponent();
}



// Called every frame
void UGrabber::TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction )
{
	Super::TickComponent( DeltaTime, TickType, ThisTickFunction );
    
    if(PhysicsHandle->GrabbedComponent)
    {
        PhysicsHandle->SetTargetLocation(GetReachLineEnd());
    }
}

const FHitResult UGrabber::GetFirstPhysicsBodyInReach()
{
     // GET PLAYER VIEW POINT THIS TICK
     
     FHitResult HitResult;
     auto World = GetWorld();
     
     if(World)
     {
         FVector PlayerViewPointLocation;
         FRotator PlayerViewPointRotation;
         World->GetFirstPlayerController()->GetPlayerViewPoint(PlayerViewPointLocation, PlayerViewPointRotation );
         
         DrawDebugLine(
                       World,
                       PlayerViewPointLocation,
                       GetReachLineEnd(),
                       FColor::Red,
                       false,
                       0.0f,
                       0.0f,
                       10.0f
                       
                       );
         
         // (line trace)ray-cast out to reach distance
         
         FCollisionQueryParams TraceParameters(FName(TEXT("")), false, GetOwner());
         GetWorld()->LineTraceSingleByObjectType(
                                                 HitResult,
                                                 PlayerViewPointLocation,
                                                 GetReachLineEnd(),
                                                 FCollisionObjectQueryParams(ECollisionChannel::ECC_PhysicsBody),
                                                 TraceParameters
                                                 );
         AActor* ActorHit = HitResult.GetActor();
         if(ActorHit)
         {
             UE_LOG(LogTemp, Warning, TEXT("line trace hit+: %s "), *(ActorHit->GetName()));
         }
         
     }
     
     return HitResult;
 }


FVector UGrabber::GetReachLineEnd()
{
    FVector LineTraceEnd;
    auto World = GetWorld();
    
    if(World)
    {
        FVector PlayerViewPointLocation;
        FRotator PlayerViewPointRotation;
        World->GetFirstPlayerController()->GetPlayerViewPoint(PlayerViewPointLocation, PlayerViewPointRotation );        
        LineTraceEnd = PlayerViewPointLocation + ( PlayerViewPointRotation.Vector() * Reach );
        
    }
    
    return LineTraceEnd;

}

