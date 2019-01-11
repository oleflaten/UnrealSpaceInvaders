// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Pawn.h"
#include "MyPawn.generated.h"

class ACameraActor;
class UInputComponent;
class ABullet;

UCLASS()
class UKE3_UE_API AMyPawn : public APawn
{
    GENERATED_BODY()
    
    
public:
    // Sets default values for this pawn's properties
    AMyPawn();
    
    // Called when the game starts or when spawned
    virtual void BeginPlay() override;
    
    // Called every frame
    virtual void Tick( float DeltaSeconds ) override;
    
    // Called to bind functionality to input
    virtual void SetupPlayerInputComponent(UInputComponent* mInputComponent) override;
    
    UPROPERTY(EditAnywhere)
    UStaticMeshComponent* OurVisibleComponent;
    
    UPROPERTY(EditAnywhere, Category = "Spawning")
    TSubclassOf<ABullet> BulletBlueprint;
    
    UShapeComponent* CollisionBox{nullptr};
    
    //Input functions
    void Move_XAxis(float AxisValue);
    void Move_YAxis(float AxisValue);
    void RotateZ(float AxisValue);
    void StartGrowing();
    void StopGrowing();
    void Shoot();
    void ShootMore();
    void Restart();
    
    //Input variables
    FVector CurrentVelocity;
    float CurrentRotation{0.f};
    bool bGrowing{false};
    
    bool bDied{false};
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "HUD Variables")
    int Ammo{30};
    
    UPROPERTY(EditAnywhere)
    float SpeedScale{1.f};
    float TimeBeforeAccelerate{1.f};
    float TimeAccellerating{0.f};
    
    UFUNCTION()
    void OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor *OtherActor, UPrimitiveComponent *OtherComponent, int32 OtherBodyIndex, bool bFromSweep, const FHitResult &SweepResult);
    
    UPROPERTY(EditAnywhere)
    ACameraActor* TopDownCamera{nullptr};
    
    UPROPERTY(EditAnywhere)
    USoundBase* ShootSound{nullptr};
    
private:
    void GrowShrink(float DeltaTime);
    void Movement(float DeltaTime);
};
