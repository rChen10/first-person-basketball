// Fill out your copyright notice in the Description page of Project Settings.


#include "FPSProjectile.h"

// Sets default values
AFPSProjectile::AFPSProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	bIsBlue = false;

	if(!RootComponent)
	{
		RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("ProjectileSceneComponent"));
	}
	if(!CollisionComponent)
	{
		// Use a sphere as a simple collision representation.
		CollisionComponent = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComponent"));
		// Set the sphere's collision profile name to "Projectile".
		CollisionComponent->BodyInstance.SetCollisionProfileName(TEXT("Projectile"));
		// Event called when component hits something.
		CollisionComponent->OnComponentHit.AddDynamic(this, &AFPSProjectile::OnHit);
		// Set the sphere's collision radius.
		CollisionComponent->InitSphereRadius(15.0f);
		// Set the root component to be the collision component.
		RootComponent = CollisionComponent;
	}
	if(!ProjectileMovementComponent)
	{
	    // Use this component to drive this projectile's movement.
	    ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovementComponent"));
	    ProjectileMovementComponent->SetUpdatedComponent(CollisionComponent);
	    ProjectileMovementComponent->InitialSpeed = 800.0f;
	    ProjectileMovementComponent->MaxSpeed = 1100.0f;
	    ProjectileMovementComponent->bRotationFollowsVelocity = false;
	    ProjectileMovementComponent->bShouldBounce = true;
	    ProjectileMovementComponent->Bounciness = 0.4f;
	    ProjectileMovementComponent->Friction = 0.3f;
	    ProjectileMovementComponent->ProjectileGravityScale = 0.2f;
	}

	if(!ProjectileMeshComponent)
	{
	    ProjectileMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ProjectileMeshComponent"));
		static ConstructorHelpers::FObjectFinder<UStaticMesh>Mesh(TEXT("'/Game/BasketballOrange.BasketballOrange'"));
	    //static ConstructorHelpers::FObjectFinder<UStaticMesh>Mesh(TEXT("StaticMesh'/Game/Sphere.Sphere'"));
	    if(Mesh.Succeeded())
	    {
	        ProjectileMeshComponent->SetStaticMesh(Mesh.Object);
	    }
	}

	static ConstructorHelpers::FObjectFinder<UMaterial>OrangeMaterial(TEXT("'/Game/Orange_Team_Color.Orange_Team_Color'"));
	if (OrangeMaterial.Succeeded())
	{
		OrangeProjectileMaterialInstance = UMaterialInstanceDynamic::Create(OrangeMaterial.Object, ProjectileMeshComponent);
	}
	static ConstructorHelpers::FObjectFinder<UMaterial>BlueMaterial(TEXT("'/Game/Blue_Team_Color.Blue_Team_Color'"));
	if (BlueMaterial.Succeeded())
	{
		BlueProjectileMaterialInstance = UMaterialInstanceDynamic::Create(BlueMaterial.Object, ProjectileMeshComponent);
	}
	ProjectileMeshComponent->SetMaterial(0, OrangeProjectileMaterialInstance);
	ProjectileMeshComponent->SetRelativeScale3D(FVector(0.3f, 0.3f, 0.3f));
	ProjectileMeshComponent->SetupAttachment(RootComponent);
	ProjectileMeshComponent->SetSimulatePhysics(true);

	// Delete the projectile after 3 seconds.
	//InitialLifeSpan = 3.0f;
}

// Called when the game starts or when spawned
void AFPSProjectile::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AFPSProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Function that initializes the projectile's velocity in the shoot direction.
void AFPSProjectile::FireInDirection(const FVector& ShootDirection)
{
    ProjectileMovementComponent->Velocity = ShootDirection * ProjectileMovementComponent->InitialSpeed;
}

// Function that is called when the projectile hits something.
void AFPSProjectile::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit)
{
    /*if (OtherActor != this && OtherComponent->IsSimulatingPhysics())
    {
		HitComponent->AddImpulseAtLocation(ProjectileMovementComponent->Velocity * 100.0f, Hit.ImpactPoint);
    }*/
	//HitComponent->AddImpulseAtLocation(ProjectileMovementComponent->Velocity * 100.0f, Hit.ImpactPoint);

    //Destroy();
}

bool AFPSProjectile::IsBlue()
{
	return bIsBlue;
}

void AFPSProjectile::SetIsBlue(bool newBool)
{
	bIsBlue = newBool;
	if (newBool) {
		ProjectileMeshComponent->SetMaterial(0, BlueProjectileMaterialInstance);
	}
	else {
		ProjectileMeshComponent->SetMaterial(0, OrangeProjectileMaterialInstance);
	}
}


