// Fill out your copyright notice in the Description page of Project Settings.

#include "C2IReceiverPlugin.h"
#include "GBPReceiver.h"


// Sets default values
AGBPReceiver::AGBPReceiver()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
}

// Called when the game starts or when spawned
void AGBPReceiver::BeginPlay()
{
	Super::BeginPlay();

}

void AGBPReceiver::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
}

// Called every frame
void AGBPReceiver::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AGBPReceiver::CheckForReceivedData()
{
	uint32 Size;
	TArray<uint8> ReceivedData;

	uint32 headersize = sizeof(int64) ;

	bool hasData = TCPClientSocket->HasPendingData(Size);

	//TODO: read 4bytes size; read(size) bytes content
	if (hasData)
	{
		if (Size > headersize)
		{
			//read header
			ReceivedData.Init(FMath::Min(Size, 65507u), headersize);

			int32 Read = 0;

			TCPClientSocket->Recv(ReceivedData.GetData(), ReceivedData.Num(), Read);
			GEngine->AddOnScreenDebugMessage(1, 10, FColor::Green, "1. Number of Elements in Array: " + FString::FromInt(ReceivedData.Num()) + " : " + FString::FromInt(Read)); //should be 8

			FString Msg = StringFromBinaryArray(ReceivedData);
			GEngine->AddOnScreenDebugMessage(2, 10, FColor::Red, "2. Size to read for message: " + Msg); //should be 

			//read payload
			int64 payloadSize = FCString::Atoi(*Msg);
			ReceivedData.Init(FMath::Min(Size, 65507u), payloadSize); //reinitializes the array with size provided by header

			Read = 0;

			TCPClientSocket->Recv(ReceivedData.GetData(), ReceivedData.Num(), Read);
			GEngine->AddOnScreenDebugMessage(3, 10, FColor::Blue, "3. Number of Elements in Array: " + FString::FromInt(ReceivedData.Num()) + " : " + FString::FromInt(Read)); //should be the same than Msg

			check(Read == payloadSize);

			//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("Data Read! %d"), ReceivedData.Num()));



			if (ReceivedData.Num() <= 0)
			{
				//No Data Received
				return;
			}

			//char* Data = (char*)ReceivedData.GetData();
			//Data[Size] = '\0';



			//FString Msg = UTF8_TO_TCHAR(ReceivedData);


			Msg = StringFromBinaryArray(ReceivedData);
			//Create a string from a byte array!



			//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, Msg);

			OnTCPCallback.Broadcast(Msg);
		}

	}


}

