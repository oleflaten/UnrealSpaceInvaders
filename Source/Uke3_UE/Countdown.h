// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "Countdown.generated.h"

UCLASS()
class UKE3_UE_API ACountdown : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACountdown();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;
    
    int32 CountdownTime;
    
    UTextRenderComponent* CountdownText;
    
    void UpdateTimerDisplay();
    
    void AdvanceTimer();
    
    void CountdownHasFinished();
    
    FTimerHandle CountdownTimerHandle;
};
