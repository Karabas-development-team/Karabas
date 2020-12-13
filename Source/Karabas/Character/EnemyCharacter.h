// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Runtime/AIModule/Classes/Perception/PawnSensingComponent.h"
#include "Runtime/Core/Public/Math/TransformNonVectorized.h"
#include "Runtime/Engine/Classes/Materials/MaterialInstanceDynamic.h"
#include "Runtime/Engine/Public/TimerManager.h"

#include "CoreMinimal.h"
#include "BaseCharacter.h"
#include "EnemyCharacter.generated.h"

/**
 * 
 */
UCLASS()
class KARABAS_API AEnemyCharacter : public ABaseCharacter
{
	GENERATED_BODY()
public:

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AI")
		UPawnSensingComponent* pawn_sensor;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Animation")
		UClass* anim_instance_class;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Material")
		UMaterialInstanceDynamic* dynamic_material;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Material")
		FLinearColor enemy_color;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AI")
		bool enemy_is_seen;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Config")
		int32 score = 5;

	AEnemyCharacter();
private:
	FTimerHandle delay_before_death;

	bool dying = false;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
public:
	UFUNCTION()
		void on_see_pawn(APawn *other_pawn);

	void death() override;

	//IDamageable
	void affect_health_Implementation(float delta) override;
};
