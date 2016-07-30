// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/SceneComponent.h"
#include "MySceneComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SPAWN_CPP_TO_BP_API UMySceneComponent : public USceneComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UMySceneComponent();

	// Called when the game starts
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction ) override;

    virtual void InitializeComponent() override;
    
    UPROPERTY()
    UStaticMeshComponent * CubeComponent;
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Nelson | CubeComponent")
    UStaticMesh* CubeComponentMesh;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Nelson | CubeComponent")
    UMaterial* CubeComponentMaterial;
	
};
