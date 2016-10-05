// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "TankTrack.h"



void UTankTrack::SetThrottle(float Throttle)
{
    if (GetOwner())
	{
		auto ForceApplied = GetForwardVector() * Throttle * TrackMaxDrivingForce;
		auto ForceLocation = GetComponentLocation();
		auto TankRoot = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());

		TankRoot->AddForceAtLocation(ForceApplied, ForceLocation);
        
        auto Name = GetName();
        UE_LOG(LogTemp, Warning, TEXT("%s Throttle %f"), *Name, Throttle);
	}
}
