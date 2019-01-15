// Fill out your copyright notice in the Description page of Project Settings.

#include "MyPawn.h"
#include "Uke3_UE.h"
#include "Enemy.h"
#include "Bullet.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/World.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Camera/CameraActor.h"
#include "Components/InputComponent.h"


// Sets default values
AMyPawn::AMyPawn()
{
    // Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
    PrimaryActorTick.bCanEverTick = true;
    
    // Set this pawn to be controlled by the lowest-numbered player
    AutoPossessPlayer = EAutoReceiveInput::Player0;
    
    // Create a dummy root component we can attach things to.
    RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
    // Create a visible object
    OurVisibleComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("OurVisibleComponent"));
 
    OurVisibleComponent->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void AMyPawn::BeginPlay()
{
    Super::BeginPlay();
    
    // Respond when our "Grow" key is pressed or released.
    InputComponent->BindAction("Grow", IE_Pressed, this, &AMyPawn::StartGrowing);
    InputComponent->BindAction("Grow", IE_Released, this, &AMyPawn::StopGrowing);
    InputComponent->BindAction("Shoot", IE_Pressed, this, &AMyPawn::Shoot);
    InputComponent->BindAction("Shoot", IE_Repeat, this, &AMyPawn::ShootMore);
    InputComponent->BindAction("Restart", IE_Pressed, this, &AMyPawn::Restart).bExecuteWhenPaused = true;
    
    // Respond every frame to the values of our two movement axes, "MoveX" and "MoveY".
    InputComponent->BindAxis("MoveX", this, &AMyPawn::Move_XAxis);
    InputComponent->BindAxis("MoveY", this, &AMyPawn::Move_YAxis);
    InputComponent->BindAxis("RotateZ", this, &AMyPawn::RotateZ);
        
    CollisionBox = this->FindComponentByClass<UBoxComponent>();
    
    if (CollisionBox)
    {
        CollisionBox->OnComponentBeginOverlap.AddDynamic(this, &AMyPawn::OnOverlap);
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("CollisionBox not found!"));
    }
    
    APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
    PlayerController->SetViewTarget(TopDownCamera);
    
    //Mouse setup
    PlayerController->bShowMouseCursor = true;
    PlayerController->bEnableClickEvents = true;
    PlayerController->bEnableMouseOverEvents = true;   
}

// Called every frame
void AMyPawn::Tick( float DeltaTime )
{
    Super::Tick( DeltaTime );
    // Handle growing and shrinking based on our "Grow" action
    GrowShrink(DeltaTime);
    
    // Handle movement based on our "MoveX" and "MoveY" axes
    Movement(DeltaTime);
}

// Called to bind functionality to input
// void AMyPawn::SetupPlayerInputComponent(UInputComponent* mInputComponent)
// {
//     Super::SetupPlayerInputComponent(mInputComponent);
// }

void AMyPawn::GrowShrink(float DeltaTime)
{
    float CurrentScale = OurVisibleComponent->GetComponentScale().X;
    //UE_LOG(LogTemp, Warning, TEXT("Current Scale %d!"), CurrentScale);
    if (bGrowing)
    {
        // Grow to double size over the course of one second
        CurrentScale += DeltaTime;
    }
    else
    {
        // Shrink half as fast as we grow
        CurrentScale -= (DeltaTime * 0.5f);
    }
    // Make sure we never drop below our starting size, or increase past double size.
    CurrentScale = FMath::Clamp(CurrentScale, 1.0f, 2.0f);
    OurVisibleComponent->SetWorldScale3D(FVector(CurrentScale));
}

void AMyPawn::Movement(float DeltaTime)
{
    if (!CurrentVelocity.IsZero())
    {
        TimeAccellerating += DeltaTime;
        if (TimeAccellerating >= TimeBeforeAccelerate)
        {
            SpeedScale += 0.05;
            SpeedScale > 5.0f ? SpeedScale = 4.0f : SpeedScale;   //SpeedScale aldri over 5.0
        }
        FVector NewLocation = GetActorLocation() + (CurrentVelocity * SpeedScale * DeltaTime);
        SetActorLocation(NewLocation);
    }
    else
    {
        SpeedScale = 2.5f;
        TimeAccellerating = 0.f;
    }
    FRotator TempRotation = GetActorRotation();
    TempRotation.Yaw += CurrentRotation;
    SetActorRotation(TempRotation);
    
}
void AMyPawn::Move_XAxis(float AxisValue)
{
    // Move at 100 units per second forward or backward
    CurrentVelocity.X = FMath::Clamp(AxisValue, -1.0f, 1.0f) * 100.0f;
}

void AMyPawn::Move_YAxis(float AxisValue)
{
    // Move at 100 units per second right or left
    CurrentVelocity.Y = FMath::Clamp(AxisValue, -1.0f, 1.0f) * 100.0f;
}

void AMyPawn::RotateZ(float AxisValue)
{
    CurrentRotation = FMath::Clamp(AxisValue, -1.0f, 1.0f);
}


void AMyPawn::StartGrowing()
{
    UE_LOG(LogTemp, Warning, TEXT("Grow!"));
    bGrowing = true;
}

void AMyPawn::StopGrowing()
{
    UE_LOG(LogTemp, Warning, TEXT("Not Grow!"));
    bGrowing = false;
}

void AMyPawn::Shoot()
{
    if (Ammo > 0)
    {
        Ammo--;
        UWorld* World = GetWorld();	//Henter peker til spillverdenen
        if (World)			//tester at verdenen finnes
        {
            FVector Location = GetActorLocation();   //Henter plasseringen til PlayerPawn
            //Kan settes til annen plassering for det du vil spawne
            World->SpawnActor<ABullet>(BulletBlueprint, Location + FVector(0.4f, 0.f, 0.f), GetActorRotation());
            
            //Play Sound
            UGameplayStatics::PlaySound2D(World, ShootSound, 1.f, 1.f, 0.f);
        }
    }
}

void AMyPawn::ShootMore()
{
    UE_LOG(LogTemp, Warning, TEXT("Button IE_Repeat"));
}

void AMyPawn::OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor *OtherActor, UPrimitiveComponent *OtherComponent,
                        int32 OtherBodyIndex, bool bFromSweep, const FHitResult &SweepResult)
{
    //UE_LOG(LogTemp, Warning, TEXT("Player Overlap"))
    if(OtherActor->IsA(AEnemy::StaticClass()))
    {
        bDied = true;
        this->SetActorHiddenInGame(true);
        UGameplayStatics::SetGamePaused(GetWorld(), true);
    }
}

void AMyPawn::Restart()
{
    if (bDied)
    {
        UGameplayStatics::OpenLevel(this, FName(*GetWorld()->GetName()), false);
    }
}

