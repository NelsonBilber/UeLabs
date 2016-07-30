// Fill out your copyright notice in the Description page of Project Settings.

#include "Spawn_CPP_to_BP.h"
#include "MySceneComponent.h"


// Sets default values for this component's properties
UMySceneComponent::UMySceneComponent():
    CubeComponent(nullptr),
    CubeComponentMesh(nullptr),
    CubeComponentMaterial(nullptr)
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	bWantsBeginPlay = true;
	PrimaryComponentTick.bCanEverTick = true;
    bWantsInitializeComponent = true;
	// ...
}


// Called when the game starts
void UMySceneComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
    CubeComponent->SetVisibility(true);
    CubeComponent->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
    CubeComponent->SetMobility(EComponentMobility::Movable);
    CubeComponent->SetRelativeScale3D(FVector(1, 1, 1));
    CubeComponent->AttachTo(this);

    CubeComponent->RegisterComponent(); //without this don't work

}


// Called every frame
void UMySceneComponent::TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction )
{
	Super::TickComponent( DeltaTime, TickType, ThisTickFunction );

	// ...
}

void  UMySceneComponent::InitializeComponent(){

    Super::InitializeComponent();
    
    /* ------------------------------------
        create a component
        set a metarial
        Set a mesh
     ------------------------------------- */
    
    CubeComponent = NewObject<UStaticMeshComponent>(this, TEXT("CubeComponent"));
    CubeComponent->SetMaterial(0, CubeComponentMaterial);
    CubeComponent->SetStaticMesh(CubeComponentMesh);
}

