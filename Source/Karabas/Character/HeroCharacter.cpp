// Fill out your copyright notice in the Description page of Project Settings.


#include "HeroCharacter.h"

#include "GameFramework/Character.h"
#include "Components/InputComponent.h"
#include "UObject/ConstructorHelpers.h"

AHeroCharacter::AHeroCharacter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//Camera setting
	selfie_stick = CreateDefaultSubobject<USpringArmComponent>(TEXT("SelfieStick"));
	selfie_stick->SetupAttachment(RootComponent);
	selfie_stick->TargetArmLength = 100;
	selfie_stick->SetRelativeRotation(FRotator(-90, 0, 0));
	selfie_stick->bDoCollisionTest = false;
	selfie_stick->bInheritPitch = false;
	selfie_stick->bInheritRoll = false;
	selfie_stick->bInheritYaw = false;

	hero_camera = CreateDefaultSubobject<UCameraComponent>(TEXT("HeroCamera"));
	hero_camera->SetupAttachment(selfie_stick);
	hero_camera->SetRelativeRotation(FRotator(90, 0, 0));

	/*static ConstructorHelpers::FObjectFinder<UClass>FoundWeapon(TEXT("BlueprintGeneratedClass'/Game/Blueprints/Weapons/ShotgunWeapon.ShotgunWeapon_C'"));
	if (FoundWeapon.Succeeded())
	{
		weapon_class = FoundWeapon.Object;
	}

	static ConstructorHelpers::FObjectFinder<UClass>AnimClass(TEXT("AnimBlueprintGeneratedClass'/Game/MyAnim/HeroAnimBP.HeroAnimBP_C'"));
	if (AnimClass.Succeeded())
	{
		anim_instance_class = AnimClass.Object;
	}*/

	this->Tags.Add(FName("Player"));


}

void AHeroCharacter::BeginPlay()
{
	Super::BeginPlay();

	if (anim_instance_class) {
		GetMesh()->SetAnimInstanceClass(anim_instance_class);
	}
}

void AHeroCharacter::move_up(float val)
{
	if (!is_dead) AddMovementInput(FVector(1, 0, 0), val);
}

void AHeroCharacter::move_right(float val)
{
	if (!is_dead) AddMovementInput(FVector(0, 1, 0), val);
}

void AHeroCharacter::attack()
{
	UE_LOG(LogTemp, Warning, TEXT("attack"));
}

void AHeroCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AHeroCharacter::SetupPlayerInputComponent(UInputComponent *PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveUp", this, &AHeroCharacter::move_up);
	PlayerInputComponent->BindAxis("MoveRight", this, &AHeroCharacter::move_right);

	PlayerInputComponent->BindAction("Fire", IE_Pressed, this, &AHeroCharacter::attack);
}

void AHeroCharacter::affect_health_Implementation(float Delta)
{
	calculate_health(Delta);
	//todo
}
