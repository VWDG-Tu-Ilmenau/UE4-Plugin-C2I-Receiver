// Fill out your copyright notice in the Description page of Project Settings.

#pragma once


#include "CoreMinimal.h"
#include "../Public/C2IReceiverActor.h"

#include "AllowWindowsPlatformTypes.h"
//#include "MessageTmp.pb.h"
#include "MessageC2I_to_Dispatcher.pb.h"
#include "HideWindowsPlatformTypes.h"

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
	virtual void CheckForReceivedData() override;

	UFUNCTION(BlueprintCallable, Category = "Car2IXS|Receiver")
		virtual bool TryToConnectToServer(FString _ip = "127.0.0.1", int32 _port = 12345) override;


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason);

private:
	bool ConvertInputToGPB(TArray<uint8> _receivedData);
	c2ipb::Call InputGPB;

};
