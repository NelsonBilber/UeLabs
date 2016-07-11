// Fill out your copyright notice in the Description page of Project Settings.

#include "Spawn_CPP_to_BP.h"
#include "MyPlayerController.h"




AMyPlayerController::AMyPlayerController()
{
}


void AMyPlayerController::BeginPlay(){
	Super::BeginPlay();
	/*
	if (!ActorClass) {
		ActorClass = AMyActor::StaticClass();
	}

	/* spawn an actor into word */
/*
	static ConstructorHelpers::FClassFinder<UBlueprint> BPActor(TEXT("Blueprint'/Game/BP_MyActor.BP_MyActor_C'"));

        if(BPActor.Class)
        {
        	ActorFromBP = Cast<AMyActor>(GetWorld()->SpawnActor(BPActor.Class));
	}
*/


	if (!ActorFromBP){
		ActorFromBP = GetWorld()->SpawnActor<AMyActor>(ActorClass);
	}
	*/

}
