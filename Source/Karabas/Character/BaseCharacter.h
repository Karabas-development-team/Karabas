// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../Interfaces/Damageable.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/ArrowComponent.h"
#include "Components/SceneComponent.h"

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "BaseCharacter.generated.h"

UCLASS()
class KARABAS_API ABaseCharacter : public APawn, public IDamageable
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Character")
		USceneComponent *scene_root;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Character")
		UArrowComponent *arrow_component;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Character")
		USkeletalMeshComponent *mesh_component;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "BaseCharacter")
		float health = 100;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "BaseCharacter")
		float max_health = 100;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "BaseCharacter")
		bool is_dead = false;

public:
	// Sets default values for this character's properties
	ABaseCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	//Calculate death function(helper)
	virtual void calculate_dead();

	virtual void death();

	//Calculate health function
	UFUNCTION(BlueprintCallable, Category = "BaseCharacter")
		virtual void calculate_health(float delta);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Health")
		void affect_health(float Delta);
	virtual void affect_health_Implementation(float Delta);
};
