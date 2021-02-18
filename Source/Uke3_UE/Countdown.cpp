// Fill out your copyright notice in the Description page of Project Settings.

#include "Countdown.h"
#include "Uke3_UE.h"
#include "Components/TextRenderComponent.h"
#include "Engine/World.h"
#include "GameFramework/Actor.h"

// Sets default values
ACountdown::ACountdown()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
    PrimaryActorTick.bCanEverTick = false;
    
    CountdownText = CreateDefaultSubobject<UTextRenderComponent>(TEXT("CountdownNumber"));
    CountdownText->SetHorizontalAlignment(EHTA_Center);
    CountdownText->SetWorldSize(250.0f);
    RootComponent = CountdownText;
    
    CountdownTime = 3;
}

// Called when the game starts or when spawned
void ACountdown::BeginPlay()
{
	Super::BeginPlay();
    UpdateTimerDisplay();
	GetWorld()->GetTimerManager().SetTimer(CountdownTimerHandle, this, &ACountdown::AdvanceTimer, 1.0f, true);
	
}

// Called every frame - not used
// void ACountdown::Tick( float DeltaTime )
// {
// 	Super::Tick( DeltaTime );

// }

void ACountdown::UpdateTimerDisplay()
{
    CountdownText->SetText(FText::AsNumber(CountdownTime));
}

void ACountdown::AdvanceTimer()
{
    --CountdownTime;
    UpdateTimerDisplay();
    if (CountdownTime < 1)
    {
        CountdownHasFinished();
    }
    if (CountdownTime < 0)
    {
        //We're done counting down, so stop running the timer.
		GetWorld()->GetTimerManager().ClearTimer(CountdownTimerHandle);
        Destroy();
    }
}

void ACountdown::CountdownHasFinished()
{
    //Change to a special readout
    CountdownText->SetText(INVTEXT("GO!")); //INVTEXT == text that does not need translation / localization
}

