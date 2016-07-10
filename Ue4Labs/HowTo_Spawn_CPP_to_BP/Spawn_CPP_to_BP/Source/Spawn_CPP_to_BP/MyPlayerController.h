// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/PlayerController.h"
#include "MyActor.h"
#include "MyPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class SPAWN_CPP_TO_BP_API AMyPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
    AMyPlayerController();
	
    AMyActor* ActorFromBP;
	
};
