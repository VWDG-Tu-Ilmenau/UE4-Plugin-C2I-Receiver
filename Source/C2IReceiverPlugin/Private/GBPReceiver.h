// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "../Public/C2IReceiverActor.h"

#include "GBPReceiver.generated.h"

UCLASS()
class AGBPReceiver : public AC2IReceiverActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AGBPReceiver();

	// Called every frame
	virtual void Tick(float DeltaTime) override;
	virtual void CheckForReceivedData();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason);

};
