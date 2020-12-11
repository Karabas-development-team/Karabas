// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyCharacter.h"

#include "HeroCharacter.h"
#include "UObject/ConstructorHelpers.h"
#include "GameFramework/Character.h"
#include "Components/CapsuleComponent.h"

AEnemyCharacter::AEnemyCharacter() {
	pawn_sensor = CreateDefaultSubobject<UPawnSensingComponent>(TEXT("PawnSensor"));
	this->Tags.Add(FName("Enemy"));

	pawn_sensor->OnSeePawn.AddDynamic(this, &AEnemyCharacter::on_see_pawn);
	pawn_sensor->SetPeripheralVisionAngle(60);
	pawn_sensor->SightRadius = 1400;

	/*static ConstructorHelpers::FObjectFinder<UClass>AnimClass(TEXT("AnimBlueprintGeneratedClass'/Game/MyAnim/EnemyAnimBP.EnemyAnimBP_C'"));
	if (AnimClass.Succeeded()) {
		anim_instance_class = AnimClass.Object;
	}*/

	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;
	enemy_is_seen = false;
}

void AEnemyCharacter::BeginPlay() {
	Super::BeginPlay();
}

void AEnemyCharacter::on_see_pawn(APawn *other_pawn) {
	AHeroCharacter* hero_character = Cast<AHeroCharacter>(other_pawn);
	if (hero_character) {
		enemy_is_seen = true;
	}
}


void AEnemyCharacter::death() {
	Destroy();
}

void AEnemyCharacter::affect_health_Implementation(float delta) {
	calculate_health(delta);
	UE_LOG(LogTemp, Warning, TEXT("affect_health_Implementation"));
	if (is_dead && !dying) {
		UE_LOG(LogTemp, Warning, TEXT("dying"));
		dying = true;
		mesh_component->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
		GetWorld()->GetTimerManager().SetTimer(delay_before_death, this, &AEnemyCharacter::death, 2.4f, false);
	}
}