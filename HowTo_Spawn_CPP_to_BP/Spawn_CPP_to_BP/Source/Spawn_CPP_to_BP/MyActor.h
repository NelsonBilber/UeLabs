// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "MySceneComponent.h"
#include "MyActor.generated.h"


class MySceneComponent;

UCLASS()
class SPAWN_CPP_TO_BP_API AMyActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMyActor(const FObjectInitializer& ObjectInitializer);

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

    
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    UMySceneComponent* MyComponent;
	
};
