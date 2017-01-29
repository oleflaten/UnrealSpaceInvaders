// Fill out your copyright notice in the Description page of Project Settings.

#include "Uke3_UE.h"
#include "Bullet.h"
#include "Enemy.h"


// Sets default values
ABullet::ABullet()
{
    // Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
    PrimaryActorTick.bCanEverTick = true;
    
    //Collision object and RootObject
    RootSphere = CreateDefaultSubobject<USphereComponent>(TEXT("MySphere"));
    RootComponent = RootSphere;
    RootSphere->bGenerateOverlapEvents = true;
    RootSphere->OnComponentBeginOverlap.AddDynamic(this, &ABullet::OnOverlap);
}

// Called when the game starts or when spawned
void ABullet::BeginPlay()
{
    Super::BeginPlay();
    
}

// Called every frame
void ABullet::Tick( float DeltaTime )
{
    Super::Tick( DeltaTime );
    
    FVector NewLocation = GetActorLocation();
    NewLocation += GetActorForwardVector() * Speed * DeltaTime;
    SetActorLocation(NewLocation);
    
    TimeLived += DeltaTime;
    if (TimeLived > TimeBeforeDestroy)
    {
        this->Destroy();
    }
}

void ABullet::OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor *OtherActor,
                        UPrimitiveComponent *OtherComponent, int32 OtherBodyIndex,
                        bool bFromSweep, const FHitResult &SweepResult)
{
    //UE_LOG(LogTemp, Warning, TEXT("Bullet Overlap %s"), *OtherActor->GetName())
    if(OtherActor->IsA(AEnemy::StaticClass()))
    {
        //Score += 10;
        Cast<AEnemy>(OtherActor)->ImHit(); //OtherActor->Destroy();
        //PartikkelFX:
        UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), ExplotionFX, GetTransform(), true);
        
        //SoundFX
        //UGameplayStatics::PlaySound2D(GetWorld(), ExplotionSound, 1.f, 1.f, 0.f);
        UGameplayStatics::PlaySoundAtLocation(GetWorld(), ExplotionSound, GetActorLocation());

        //Destroy Bullet:
        Destroy();
    }
}

//Setter verdi og initierer statisk Score-variabel:
//int ABullet::Score = 0;

