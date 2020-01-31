// Fill out your copyright notice in the Description page of Project Settings.


#include "FPSCharacter.h"
#include "Engine/World.h"
#include "DamageableActor.h"
// Sets default values
AFPSCharacter::AFPSCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AFPSCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}


// Called every frame
void AFPSCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AFPSCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AFPSCharacter::fireWeapon() {
	FHitResult hit = InstentShot();
	ADamageableActor* hitActor = Cast<ADamageableActor>(hit.Actor);
	if (hitActor && hitActor->isAttackable)
	{
		hitActor->takeAttack();
	}
}

FHitResult AFPSCharacter::InstentShot() {
	FVector cameraLocation; //"this calls where the bullet location is
	FRotator cameraRotation; //this calls bullet direction
	FVector endTrace = FVector::ZeroVector;//this is the Bullets Distance

	APlayerController* const playerController = GetWorld()->GetFirstPlayerController();
	if (playerController) {

		playerController->GetPlayerViewPoint(cameraLocation, cameraRotation);
		endTrace = cameraLocation + (cameraRotation.Vector() * weaponRange);
	}

	FCollisionQueryParams traceParams(SCENE_QUERY_STAT(InstentShot), true, Instigator);
	FHitResult hit(ForceInit);
	GetWorld()->LineTraceSingleByChannel(hit, cameraLocation, endTrace, ECC_Visibility, traceParams);

	return hit;
}
