// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/ArrowComponent.h"

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BaseWeapon.generated.h"

USTRUCT(BlueprintType)
struct FWeaponData
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, Category = "Ammo")
		int32 max_ammo;

	UPROPERTY(EditAnywhere, Category = "Config")
		float time_between_shots;

	UPROPERTY(EditAnywhere, Category = "Config")
		TSubclassOf<class AActor> projectile_type;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sound")
		USoundBase *shot_sound;
};

UCLASS()
class KARABAS_API ABaseWeapon : public AActor
{
	GENERATED_BODY()
public:

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Config")
		FWeaponData weapon_config;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Config")
		USkeletalMeshComponent *weapon_mesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Config")
		UArrowComponent *projectile_spawn_point;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Attack")
		bool trigger_pulled;

	FTimerHandle timer_delay_bet_shots;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Attack")
		bool ability_to_fire;

	FTimerHandle timer_delay_aft_shots;

public:	
	// Sets default values for this actor's properties
	ABaseWeapon();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
		void fire();

	UFUNCTION(BlueprintCallable)
		void pull_trigger();

	UFUNCTION(BlueprintCallable)
		void release_trigger();

	UFUNCTION(BlueprintCallable)
		void recover_fire_ability();
};
