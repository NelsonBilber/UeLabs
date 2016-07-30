// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "Countdown.generated.h"

UCLASS()
class HOWTO_VTE_API ACountdown : public AActor
{
	GENERATED_BODY()
	
public:	
    ACountdown();
    
    // Called when the game starts or when spawned
    virtual void BeginPlay() override;
    
    // Called every frame
    virtual void Tick( float DeltaSeconds ) override;
    
    //How long, in seconds, the countdown will run
    UPROPERTY(EditAnywhere)
    int32 CountdownTime;
    
    UTextRenderComponent* CountdownText;
    
    void UpdateTimerDisplay();
    
    void AdvanceTimer();
    
    UFUNCTION(BlueprintNativeEvent)
    void CountdownHasFinished();
    virtual void CountdownHasFinished_Implementation();
    
    FTimerHandle CountdownTimerHandle;
};
