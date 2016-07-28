// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/ActorComponent.h"
#include "OpenDoor.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE(FDoorEvent);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BUILDINGROOM_API UOpenDoor : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UOpenDoor();

	// Called when the game starts
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction ) override;
    
    void OpenTheDoor();
    
    void CloseDoor();
    
    float GetTotalMassOfActorsOnPlate();
    
    UPROPERTY(BlueprintAssignable)
    FDoorEvent OnOpen;
    
    UPROPERTY(BlueprintAssignable)
    FDoorEvent OnClose;

private:
    UPROPERTY(VisibleAnywhere)
    float OpenAngle = 90.0f;
	
    UPROPERTY(EditAnywhere)
    ATriggerVolume* PressurePlate = nullptr;
    
    UPROPERTY(EditAnywhere)
    float DoorCloseDelay = 1.f;
    
    float LastDoorOpenTime;
    
    UPROPERTY()
    AActor* ActorThatOpensDoor = nullptr;
    
    AActor* Owner; // the owning door
};
