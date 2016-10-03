#include "BattleTank.h"
#include "TankAimingComponent.h"
#include "Projectile.h"
#include "TankBarrel.h"
#include "Tank.h"


// Sets default values
ATank::ATank()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
    
    TankAimingComponent = CreateDefaultSubobject<UTankAimingComponent>(FName("Aiming Component"));

}

// Called when the game starts or when spawned
void ATank::BeginPlay()
{
	Super::BeginPlay();
	
}

void ATank::SetBarrelReference(UTankBarrel* BarrelToSet)
{
    TankAimingComponent->SetBarrelReference(BarrelToSet);
	Barrel = BarrelToSet;
}

void ATank::SetTurretReference(UTankTurret* TurretToSet)
{
	TankAimingComponent->SetTurretReference(TurretToSet);
}


// Called to bind functionality to input
void ATank::SetupPlayerInputComponent(class UInputComponent* InputComponent)
{
	Super::SetupPlayerInputComponent(InputComponent);

}


void ATank::AimAt(FVector HitLocation)
{
    TankAimingComponent->AimAt(HitLocation, LaunchSpeed);
}


void ATank::Fire()
{
	if (!Barrel) 
		return;

	auto Location = Barrel->GetSocketLocation(FName("Projectile"));
	Location.X += Location.X + 10;
	auto Rotation = Barrel->GetSocketRotation(FName("Projectile"));
	auto Time = GetWorld()->GetTimeSeconds();

	UE_LOG(LogTemp, Warning, TEXT("%f: Tank fire at location %s and Rotation %s"), Time, *Location.ToString(), *Rotation.ToString());

	//Spawn a projectile at the socket location on the barrel
	GetWorld()->SpawnActor<AProjectile>(
										ProjectileBlueprint,
										Location,
										Rotation 
		);
}
 
