// Copyright 1998-2015 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "GameFramework/PawnMovementComponent.h"
#include "CollidingPawnMovementComponent.generated.h"

/**
 *
 */
UCLASS()
class HOWTO_COMPONENTS_API UCollidingPawnMovementComponent : public UPawnMovementComponent
{
    GENERATED_BODY()
    
public:
    virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction) override;
};