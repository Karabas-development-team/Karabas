// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseCharacter.h"

#include "Components/CapsuleComponent.h"

// Sets default values
ABaseCharacter::ABaseCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	GetCapsuleComponent()->SetCollisionProfileName(TEXT("Pawn"));

	GetCapsuleComponent()->BodyInstance.SetResponseToChannel(ECC_WorldDynamic, ECR_Overlap);
	this->SetActorTickInterval(0.008);
}

// Called when the game starts or when spawned
void ABaseCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABaseCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ABaseCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

//Implement CalculateHealth
void ABaseCharacter::calculate_health(float Delta)
{
	if (!is_dead) {
		health += Delta;
		if (health > max_health) {
			health = max_health;
		} 
		else {
			calculate_dead();
		}
	}
}

//Implement CalculateDead
void ABaseCharacter::calculate_dead()
{
	if (health <= 0) {
		is_dead = true;
	}
	else {
		is_dead = false;
	}
}

void ABaseCharacter::death() {
	Destroy();
}

void ABaseCharacter::affect_health_Implementation(float Delta) {
	check(0 && "You must override this");
}
