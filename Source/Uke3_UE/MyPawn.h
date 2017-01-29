// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Pawn.h"
#include "MyPawn.generated.h"

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
    virtual void SetupPlayerInputComponent(class UInputComponent* InputComponent) override;
    
    UPROPERTY(EditAnywhere)
    USceneComponent* OurVisibleComponent;
    
    //UPROPERTY(EditAnywhere)
    //float CameraRotation = -5.f;
    
    //UCameraComponent* OurCamera = nullptr;
    
    UPROPERTY(EditAnywhere, Category="Spawning")
    TSubclassOf<class ABullet> BulletBlueprint;
    
    UShapeComponent* CollisionBox = nullptr;
    
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
    float CurrentRotation;
    bool bGrowing;
    
    bool Died{false};
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "HUD Variables")
    int Ammo = 30;
    
    UPROPERTY(EditAnywhere)
    float SpeedScale = 1.f;
    float TimeBeforeAccelerate = 1.f;
    float TimeAccellerating{0.f};
    
    UFUNCTION()
    void OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor *OtherActor, UPrimitiveComponent *OtherComponent, int32 OtherBodyIndex, bool bFromSweep, const FHitResult &SweepResult);
    
    UPROPERTY(EditAnywhere)
    ACameraActor* TopDownCamera = nullptr;
    
    UPROPERTY(EditAnywhere)
    USoundBase* ShootSound;
    
    //UPROPERTY(EditAnywhere)
    //USceneComponent* DummySceneComponent;
    
private:
    void GrowShrink(float DeltaTime);
    void Movement(float DeltaTime);
};
