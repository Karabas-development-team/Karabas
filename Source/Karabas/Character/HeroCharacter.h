// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "../Weapons/BaseWeapon.h"

#include "CoreMinimal.h"
#include "BaseCharacter.h"
#include "HeroCharacter.generated.h"

/**
 * 
 */
UCLASS()
class KARABAS_API AHeroCharacter : public ABaseCharacter
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Camera")
		USpringArmComponent *selfie_stick;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Camera")
		UCameraComponent *hero_camera;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Weapon")
		TSubclassOf<class ABaseWeapon> weapon_class;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Animation")
		UClass *anim_instance_class;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Weapon")
		ABaseWeapon* weapon;
public:
	AHeroCharacter();
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION()
		void move_up(float val);

	UFUNCTION()
		void move_right(float val);

	UFUNCTION()
		void look_up(float val);

	UFUNCTION()
		void turn(float val);

	UFUNCTION()
		void attack();
public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	//IDamageable
	void affect_health_Implementation(float Delta) override;
};
