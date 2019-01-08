// Fill out your copyright notice in the Description page of Project Settings.

#include "Uke3_UEGameModeBase.h"
#include "Uke3_UE.h"
#include "Enemy.h"
#include "Engine/World.h"

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
                AEnemy *tempEnemy = World->SpawnActor<AEnemy>(EnemyBlueprint, Location, FRotator::ZeroRotator);
                EnemyArray.Add(tempEnemy);
                ArraySize ++;
            }
        }
        UE_LOG(LogTemp, Error, TEXT("Enemy Array is: %d "), EnemyArray.Num());
    }
}

// Called every frame
void AUke3_UEGameModeBase::Tick( float DeltaTime )
{
    //UE_LOG(LogTemp, Error, TEXT("Game Mode Tick"));
    Super::Tick( DeltaTime );
    
    EnemyTimer += DeltaTime;
    
    // spawn extra enemy
    //    if (EnemyTimer >= SpawnDelay)
    //    {
    //        //UE_LOG(LogTemp, Warning, TEXT("Spawn Enemy"))
    
    //        UWorld* World = GetWorld();
    
    //        if(World)
    //        {
    //            FVector Location = FVector(1000.f, FMath::RandRange(-800.f, 800.f), 70.f);
    //            World->SpawnActor<AEnemy>(EnemyBlueprint, Location, FRotator::ZeroRotator);
    //        }
    //        EnemyTimer = 0.f;
    //    }
    
    EnemyTurnTime += DeltaTime;
    //UE_LOG(LogTemp, Error, TEXT("EnemyTurnTime = %f"), EnemyTurnTime);
    
    if (EnemyTurnTime > 4.0f)
    {
        UE_LOG(LogTemp, Error, TEXT("Enemy Move Logic Running"));
        //Jeg prøvde å gjøre dette i samme løkke som den under.
        //Men det fungerer dårlig å slette et element i arrayen, samtidig som
        //vi itererer gjennom den! - men jeg gjør jo igrunnen det samme nå også...
        for (int i = 0; i < EnemyArray.Num(); i++)
        {
            if (EnemyArray[i]->DeleteThisEnemy) {
                EnemyArray[i]->Destroy();
                EnemyArray.RemoveAt(i);
                UE_LOG(LogTemp, Error, TEXT("Enemy down. Enemy Array is: %d "), EnemyArray.Num());
                ArraySize--;
            }
        }
        for (auto Enemy: EnemyArray) //for (int i = 0; i < EnemyArray.Num(); i++)
        {
            switch (EnemyMoveDirection) {
                case 1:
                    Enemy->MoveDirection = FVector(1.0f, 0.f, 0.f);
                    break;
                case 2:
                    Enemy->MoveDirection = FVector(0.0f, 1.f, 0.f);
                    break;
                case 3:
                    Enemy->MoveDirection = FVector(1.0f, 0.f, 0.f);
                    break;
                case 4:
                    Enemy->MoveDirection = FVector(0.0f, -1.f, 0.f);
                    break;
                default:
                    UE_LOG(LogTemp, Error, TEXT("Enemy Move Logic not working!"));
                    break;
            }
        }
        EnemyMoveDirection = ((EnemyMoveDirection) % 4) + 1;
        EnemyTurnTime = 0.f;
    }
}

