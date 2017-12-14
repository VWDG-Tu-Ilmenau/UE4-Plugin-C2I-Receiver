// Fill out your copyright notice in the Description page of Project Settings.

#pragma once


#include "CoreMinimal.h"
#include "C2IReceiverActor.h"

#include "ProtobufHandler.h"
#include "GPBDataDispatcher.h"

#include "GPBReceiver.generated.h"

UCLASS()
class AGPBPReceiver : public AC2IReceiverActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AGPBPReceiver();

	// Called every frame
	virtual void Tick(float DeltaTime) override;
	virtual void CheckForReceivedData() override;

	UFUNCTION(BlueprintCallable, Category = "Car2IXS|GPBReceiver")
		virtual bool TryToConnectToServer(FString _ip = "127.0.0.1", int32 _port = 12345) override;

	UFUNCTION(BlueprintCallable, Category = "Car2IXS|GPBReceiver")
		UGPBDataDispatcher* GetGPBDataDispatcherRef();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason);

private:
	bool ConvertInputToGPB(TArray<uint8> _receivedData);
	c2ipb::Call InputGPB;

	UGPBDataDispatcher* GPBDataDispatcher_;

	int32 GetPayloadSize(FString header, TArray<uint8> ReceivedData, uint32 Size);
	int32 GetIntFromTArray(TArray<uint8> ReceivedData);
};
