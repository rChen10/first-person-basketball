// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "FPSProjectile.generated.h"

UCLASS()
class FPSPROJECT_API AFPSProjectile : public AActor
{
    GENERATED_BODY()

public: 
    // Sets default values for this actor's properties
    AFPSProjectile();

protected:
    // Called when the game starts or when spawned
    virtual void BeginPlay() override;
    bool bIsBlue;

public:
    // Called every frame
    virtual void Tick( float DeltaTime ) override;

    // Sphere collision component.
    UPROPERTY(VisibleDefaultsOnly, Category = Projectile)
    USphereComponent* CollisionComponent;

    // Projectile movement component.
    UPROPERTY(VisibleAnywhere, Category = Movement)
    UProjectileMovementComponent* ProjectileMovementComponent;

    // Function that initializes the projectile's velocity in the shoot direction.
    void FireInDirection(const FVector& ShootDirection);

    // Projectile mesh
    UPROPERTY(VisibleDefaultsOnly, Category = Projectile)
    UStaticMeshComponent* ProjectileMeshComponent;

    // Orange Projectile material
    UPROPERTY(VisibleDefaultsOnly, Category = Movement)
    UMaterialInstanceDynamic* OrangeProjectileMaterialInstance;

    // Blue Projectile material
    UPROPERTY(VisibleDefaultsOnly, Category = Movement)
    UMaterialInstanceDynamic* BlueProjectileMaterialInstance;

    // Function that is called when the projectile hits something.
    UFUNCTION()
    void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit);

    // Function that determines whether the projectile is Blue.
    UFUNCTION(BlueprintCallable, Category="Color")
    bool IsBlue();

    // Function that set whether the projectile is Blue.
    UFUNCTION(BlueprintCallable, Category="Color")
    void SetIsBlue(bool newBool);

};