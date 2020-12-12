// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseProjectile.h"

#include "Components/StaticMeshComponent.h"
#include "UObject/ConstructorHelpers.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/DecalActor.h"
#include "Components/DecalComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "../Interfaces/Damageable.h"

// Sets default values
ABaseProjectile::ABaseProjectile()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ProjectileMesh"));
	mesh->OnComponentBeginOverlap.AddDynamic(this, &ABaseProjectile::on_overlap_begin);
	//mesh->SetWorldScale3D(FVector(0.5, 0.03, 0.03));
	mesh->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Overlap);
	RootComponent = mesh;

	proj_movement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovement"));
	proj_movement->ProjectileGravityScale = 0;
	proj_movement->InitialSpeed = 6000;

	InitialLifeSpan = 1.5;

	/*static ConstructorHelpers::FObjectFinder<UStaticMesh>mesh_file(TEXT("StaticMesh'/Game/Shapes/Sphere.Sphere'"));
	if (mesh_file.Succeeded())
	{
		mesh->SetStaticMesh(mesh_file.Object);
	}

	static ConstructorHelpers::FObjectFinder<UMaterialInterface>mat_file(TEXT("Material'/Game/Projectiles/LazerHoleDecal.LazerHoleDecal'"));
	if (mat_file.Succeeded())
	{
		decal_material = mat_file.Object;
	}*/


	//collision_comp->OnComponentBeginOverlap.AddDynamic(this, &ABaseProjectile::on_overlap_begin);

	/*static ConstructorHelpers::FObjectFinder<UParticleSystem>particles_file(TEXT("ParticleSystem'/Game/Materials/LaserSparks.LaserSparks'"));
	if (particles_file.Succeeded())
	{
		particles = particles_file.Object;
	}*/
}

// Called when the game starts or when spawned
void ABaseProjectile::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void ABaseProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ABaseProjectile::on_overlap_begin(UPrimitiveComponent *OverlappedComp,
	AActor *OtherActor,
	UPrimitiveComponent *OtherComp,
	int32 OtherBodyIndex,
	bool bFromSweep,
	const FHitResult &SweepResult)
{

	spawn_mark(SweepResult);
	spawn_particles(SweepResult);

	if (hit_sound) {
		UGameplayStatics::SpawnSoundAttached(hit_sound, mesh);
	}

	IDamageable* damageable = Cast<IDamageable>(OtherActor);
	if (damageable) {
		damageable->Execute_affect_health(OtherActor, -damage);
	}

	destroy();
}

void ABaseProjectile::destroy()
{
	Destroy();
}

void ABaseProjectile::spawn_particles(const FHitResult &sweep_result)
{
	if (particles) {
		FTransform transform = FTransform(UKismetMathLibrary::MakeRotFromX(sweep_result.Normal), sweep_result.Location, FVector(1, 1, 1));
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), particles, transform);
	}
}

void ABaseProjectile::spawn_mark(const FHitResult &sweep_result)
{
	if (decal_material && !sweep_result.GetActor()->ActorHasTag(FName("Enemy"))) {
		ADecalActor *decal = GetWorld()->SpawnActor<ADecalActor>(sweep_result.Location - sweep_result.GetComponent()->GetComponentLocation(), FRotator());
		if (decal)
		{
			decal->SetActorRotation(UKismetMathLibrary::MakeRotFromX(sweep_result.Normal));
			decal->SetDecalMaterial(decal_material);
			decal->SetLifeSpan(2.0f);
			decal->GetDecal()->DecalSize = FVector(10, 10, 10);
			decal->AttachToComponent(sweep_result.GetComponent(), FAttachmentTransformRules::KeepRelativeTransform);
		}
	}
}

