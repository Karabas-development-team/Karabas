// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyCharacter.h"

#include "HeroCharacter.h"
#include "UObject/ConstructorHelpers.h"
#include "GameFramework/Character.h"
#include "Components/CapsuleComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Runtime/Core/Public/Misc/OutputDevice.h"
#include "Runtime/Core/Public/Misc/OutputDeviceNull.h"

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

	mesh_component->PhysicsTransformUpdateMode = EPhysicsTransformUpdateMode::Type::SimulationUpatesComponentTransform;
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;
	enemy_is_seen = false;
}

void AEnemyCharacter::BeginPlay() {
	Super::BeginPlay();
	if (anim_instance_class) {
		mesh_component->SetAnimInstanceClass(anim_instance_class);
	}
}

void AEnemyCharacter::on_see_pawn(APawn *other_pawn) {
	AHeroCharacter* hero_character = Cast<AHeroCharacter>(other_pawn);
	if (hero_character) {
		enemy_is_seen = true;
	}
}


void AEnemyCharacter::death() {
	//Destroy();
	UE_LOG(LogTemp, Warning, TEXT("death"));
	FOutputDeviceNull ar;
	const FString command = FString::Printf(TEXT("ShowAchievement %i"), score);
	UGameplayStatics::GetPlayerController(GetWorld(), 0)->CallFunctionByNameWithArguments(*command, ar, NULL, true);
}

void AEnemyCharacter::affect_health_Implementation(float delta) {
	calculate_health(delta);
	if (is_dead && !dying) {
		dying = true;
		death();
	}
}