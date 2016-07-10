// Fill out your copyright notice in the Description page of Project Settings.

#include "Spawn_CPP_to_BP.h"
#include "MySceneComponent.h"
#include "MyActor.h"


// Sets default values
AMyActor::AMyActor(const FObjectInitializer& ObjectInitializer):
        Super(ObjectInitializer)
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

    
    /* Associate componente to Actor by code  */
    MyComponent = ObjectInitializer.CreateDefaultSubobject<UMySceneComponent>(this, "MyComponent");
    MyComponent->AttachTo(RootComponent);
}

// Called when the game starts or when spawned
void AMyActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMyActor::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}

