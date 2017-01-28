// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/GameModeBase.h"
#include "Uke3_UEGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class UKE3_UE_API AUke3_UEGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
public:
    AUke3_UEGameModeBase();
    
    // Called when the game starts or when spawned
    virtual void BeginPlay() override;
    
    // Called every frame
    virtual void Tick( float DeltaSeconds ) override;
    
    void DeleteEnemy(class AEnemy *EnemyToDelete);
    
private:
    UPROPERTY(EditAnywhere, Category = "Spawning")
    TSubclassOf<class AEnemy> EnemyBlueprint;
    
    UPROPERTY(EditAnywhere, Category = "Spawning")
    float SpawnDelay = 2.f;

    float EnemyTimer{0.f};
    
    float EnemyTurnTime{0.0f};
    
    int EnemyMoveDirection = 1; //Down, left, down, right
    
    TArray<class AEnemy*> EnemyArray;
    
    
};
