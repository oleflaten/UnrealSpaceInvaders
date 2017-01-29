// Fill out your copyright notice in the Description page of Project Settings.

#include "Uke3_UE.h"
#include "Uke3_UEGameModeBase.h"
#include "Enemy.h"


// Sets default values
AEnemy::AEnemy()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
    //Collision object and RootObject
    RootBox = CreateDefaultSubobject<UBoxComponent>(TEXT("MyEnemy"));
    RootComponent = RootBox;
    RootBox->bGenerateOverlapEvents = true;
}

// Called when the game starts or when spawned
void AEnemy::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AEnemy::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );
    
    FVector NewLocation = GetActorLocation();
    NewLocation += (MoveDirection * Speed * DeltaTime);
    SetActorLocation(NewLocation);
    
    if (NewLocation.X < DestroyPlacement)
    {
        this->Destroy();
    }
}

void AEnemy::ImHit()
{
    UE_LOG(LogTemp, Warning, TEXT("Enemy hit! Im going down!"))
    Cast<AUke3_UEGameModeBase>(GameModePointer)->DeleteEnemy(PlaceInArray);
    Destroy();
}

