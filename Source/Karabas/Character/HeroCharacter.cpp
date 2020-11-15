// Fill out your copyright notice in the Description page of Project Settings.


#include "HeroCharacter.h"

#include "GameFramework/Character.h"
#include "Components/InputComponent.h"
#include "Components/SceneComponent.h"
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
	hero_camera->bUsePawnControlRotation = true;

	static ConstructorHelpers::FObjectFinder<UClass>FoundWeapon(TEXT("BlueprintGeneratedClass'/Game/Weapons/MyBaseWeapon.MyBaseWeapon_C'"));
	if (FoundWeapon.Succeeded())
	{
		weapon_class = FoundWeapon.Object;
	}

	/*static ConstructorHelpers::FObjectFinder<UClass>AnimClass(TEXT("AnimBlueprintGeneratedClass'/Game/MyAnim/HeroAnimBP.HeroAnimBP_C'"));
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
	if (weapon_class) {
		FActorSpawnParameters SpawnInfo;
		SpawnInfo.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
		weapon = GetWorld()->SpawnActor<ABaseWeapon>(weapon_class, GetArrowComponent()->GetComponentTransform(), SpawnInfo);
		weapon->AttachToComponent(GetArrowComponent(), FAttachmentTransformRules::SnapToTargetIncludingScale);
	}
}

void AHeroCharacter::move_up(float val)
{
	if (!is_dead) AddMovementInput(GetActorForwardVector(), val);
}

void AHeroCharacter::move_right(float val)
{
	if (!is_dead) AddMovementInput(GetActorRightVector(), val);
}

void AHeroCharacter::look_up(float val)
{
	if (!is_dead) AddControllerPitchInput(val);
}

void AHeroCharacter::turn(float val)
{
	if (!is_dead) AddControllerYawInput(val);
}

void AHeroCharacter::attack()
{
	if (weapon) {
		weapon->fire();
	}
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

	PlayerInputComponent->BindAxis("LookUp", this, &AHeroCharacter::look_up);
	PlayerInputComponent->BindAxis("Turn", this, &AHeroCharacter::turn);

	PlayerInputComponent->BindAction("Fire", IE_Pressed, this, &AHeroCharacter::attack);
}

void AHeroCharacter::affect_health_Implementation(float Delta)
{
	calculate_health(Delta);
	//todo
}
