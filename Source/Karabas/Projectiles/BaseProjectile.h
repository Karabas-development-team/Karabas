// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BaseProjectile.generated.h"

UCLASS()
class KARABAS_API ABaseProjectile : public AActor
{
	GENERATED_BODY()
public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Collision")
		USphereComponent *collision_comp;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Config")
		UStaticMeshComponent *mesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Config")
		UProjectileMovementComponent *proj_movement;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Visual")
		UParticleSystem* particles;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Sound")
		USoundBase *hit_sound;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Visual")
		class UMaterialInterface *decal_material;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		float damage = 1;

	FTimerHandle DelayBeforeDeath;

	bool destroy_on_hit = true;

private:
	FTimerHandle timer_delay_before_death;
	
public:	
	// Sets default values for this actor's properties
	ABaseProjectile();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
		void on_overlap_begin(UPrimitiveComponent* OverlappedComp,
			AActor* OtherActor,
			UPrimitiveComponent* OtherComp,
			int32 OtherBodyIndex,
			bool bFromSweep,
			const FHitResult& SweepResult);

	void destroy();

	void spawn_particles(const FHitResult &sweep_result);
	void spawn_mark(const FHitResult &sweep_result);
};
