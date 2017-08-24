// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "Networking.h" //Networking
#include "GameFramework/Actor.h"
#include "Engine.h"
#include "AnyCustomData.h"

#include "C2IReceiverActor.generated.h"

/************************************************************************/
/* I'm a client and connect to TCP servers :)                           */
/************************************************************************/

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FDelegateTCPCallback, FString, tmpVal);


UCLASS()
class C2IRECEIVERPLUGIN_API AC2IReceiverActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AC2IReceiverActor();

protected:
	// Called when the game starts or when spawned
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

public:		
	FSocket* TCPClientSocket;
	FIPv4Endpoint RemoteAddressForConnection;
	
	UPROPERTY(BlueprintAssignable, Category = "Car2IXS|Receiver")
		FDelegateTCPCallback OnTCPCallback;

	UFUNCTION(BlueprintCallable, Category = "Car2IXS|Receiver")
		bool TryToConnectToServer(FString _ip = "127.0.0.1", int32 _port = 12345);

	virtual void CheckForReceivedData();

	FString StringFromBinaryArray(TArray<uint8> BinaryArray);
protected:
	FTimerHandle TimerHandleTest;
	FCriticalSection MyMutex;



};