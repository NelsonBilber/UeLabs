#include "BattleTank.h"
#include "Tank.h"


ATank::ATank()
{
    PrimaryActorTick.bCanEverTick = true;
}

void ATank::BeginPlay()
{
    Super::BeginPlay();
    
    CurrentHealth = StartingHealth;
}


float ATank::TakeDamage(float DamageAmount, struct FDamageEvent const & DamageEvent, class AController * EventInstigator, AActor * DamageCauser)
{
    int32 DamagePoints = FPlatformMath::RoundToInt(DamageAmount);
    int32 DamageToApply = FMath::Clamp(DamagePoints, 0, CurrentHealth);
    
    CurrentHealth -= DamageToApply;
    if (CurrentHealth <= 0)
    {
        //UE_LOG(LogTemp, Warning, TEXT("Tank died"))
        OnDeath.Broadcast();
    }
    return DamageToApply;
}

float ATank::GetHealthPercent() const
{
    return (float)CurrentHealth/(float)StartingHealth;
}
