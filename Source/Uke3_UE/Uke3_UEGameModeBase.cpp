// Fill out your copyright notice in the Description page of Project Settings.

#include "Uke3_UE.h"
#include "Uke3_UEGameModeBase.h"
#include "Enemy.h"

AUke3_UEGameModeBase::AUke3_UEGameModeBase()
{
    PrimaryActorTick.bCanEverTick = true;
    //UE_LOG(LogTemp, Error, TEXT("Game Mode Base contructor kaller!"));
}

// Called when the game starts or when spawned
void AUke3_UEGameModeBase::BeginPlay()
{
    Super::BeginPlay();
    
    UWorld* World = GetWorld();
    if(World)
    {
        for (int j{1}; j < 5; j++)
        {
            for(int i{1}; i < 11; i++)
            {
                FVector Location = FVector((800.f - j * 200), (-1000.f + i * 200), 70.f);
                EnemyArray.Add(World->SpawnActor<AEnemy>(EnemyBlueprint, Location, FRotator::ZeroRotator));
            }
        }
    }
}

// Called every frame
void AUke3_UEGameModeBase::Tick( float DeltaTime )
{
    Super::Tick( DeltaTime );
    
    EnemyTimer += DeltaTime;
    
    if (EnemyTimer >= SpawnDelay)
    {
        //UE_LOG(LogTemp, Warning, TEXT("Spawn Enemy"))
        
        UWorld* World = GetWorld();
        
        if(World)
        {
            FVector Location = FVector(1000.f, FMath::RandRange(-800.f, 800.f), 70.f);
            World->SpawnActor<AEnemy>(EnemyBlueprint, Location, FRotator::ZeroRotator);
        }
        EnemyTimer = 0.f;
    }
    
    EnemyTurnTime += DeltaTime;
    
    if (EnemyTurnTime > 4.0f)
    {
        for (int i = 0; i < EnemyArray.Num(); i++) // auto Enemy: EnemyArray)
        {
            if (EnemyArray[i])
            {
                switch (EnemyMoveDirection) {
                    case 1:
                        EnemyArray[i]->MoveDirection = FVector(1.0f, 0.f, 0.f);
                        break;
                    case 2:
                        EnemyArray[i]->MoveDirection = FVector(0.0f, 1.f, 0.f);
                        break;
                    case 3:
                        EnemyArray[i]->MoveDirection = FVector(1.0f, 0.f, 0.f);
                        break;
                    case 4:
                        EnemyArray[i]->MoveDirection = FVector(0.0f, -1.f, 0.f);
                        break;
                    default:
                        UE_LOG(LogTemp, Error, TEXT("Enemy Move Logic not working!"));
                        break;
                }
            }
//            else{
//                EnemyArray.RemoveAt(i);
//            }
        }
//        UE_LOG(LogTemp, Error, TEXT("Enemys left %d!"), EnemyArray.Num());
        EnemyMoveDirection = ((EnemyMoveDirection) % 4) + 1;
        EnemyTurnTime = 0.f;
    }
}

void AUke3_UEGameModeBase::DeleteEnemy(class AEnemy *EnemyToDelete)
{
    //Skulle ha kalt opp denne og slettet fienden fra arrayet.
}
