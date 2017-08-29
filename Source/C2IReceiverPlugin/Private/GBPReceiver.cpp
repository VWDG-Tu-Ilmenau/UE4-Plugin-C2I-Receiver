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

void AGBPReceiver::ConvertInputToGPB(std::string _incomingmsg)
{
	bool parseSuccessful = InputGPB.ParseFromString(_incomingmsg);
	if (!parseSuccessful)
	{
		//LOG(DEBUG) << "Can not convert GPB input stream to GPB object.\n" << InputGPB.DebugString();
	}

	std::string miao = "";
	InputGPB.SerializeToString(&miao);

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
			//////////////////////////////////////////////////////////////////////////
			//read header
			ReceivedData.Init(FMath::Min(Size, 65507u), headersize);

			int32 Read = 0;

			TCPClientSocket->Recv(ReceivedData.GetData(), ReceivedData.Num(), Read);
			//GEngine->AddOnScreenDebugMessage(1, 10, FColor::Green, "1. Number of Elements in Array: " + FString::FromInt(ReceivedData.Num()) + " : " + FString::FromInt(Read)); //should be 8

			FString Msg = StringFromBinaryArray(ReceivedData);
			//GEngine->AddOnScreenDebugMessage(2, 10, FColor::Red, "2. Size to read for message: " + Msg); //should be 

			//////////////////////////////////////////////////////////////////////////
			//read payload
			int64 payloadSize = FCString::Atoi(*Msg);
			ReceivedData.Init(FMath::Min(Size, 65507u), payloadSize); //reinitializes the array with size provided by header

			Read = 0;

			TCPClientSocket->Recv(ReceivedData.GetData(), ReceivedData.Num(), Read);
			//GEngine->AddOnScreenDebugMessage(3, 10, FColor::Blue, "3. Number of Elements in Array: " + FString::FromInt(ReceivedData.Num()) + " : " + FString::FromInt(Read)); //should be the same than Msg

		
			//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("Data Read! %d"), ReceivedData.Num()));

			if (ReceivedData.Num() <= 0)
			{
				//No Data Received
				return;
			}

			//////////////////////////////////////////////////////////////////////////
			//Convert binary array
			// 
			Msg = StringFromBinaryArray(ReceivedData);
			//Create a string from a byte array!


			//TODO convert to GPB!

			std::string MyStdString(TCHAR_TO_UTF8(*Msg));
			ConvertInputToGPB(MyStdString);
			
			
			//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, Msg);

			OnTCPCallback.Broadcast(Msg);
		}

	}


}

bool AGBPReceiver::TryToConnectToServer(FString _ip /*= "127.0.0.1"*/, int32 _port /*= 12345*/)
{
	TCPClientSocket = ISocketSubsystem::Get(PLATFORM_SOCKETSUBSYSTEM)->CreateSocket(NAME_Stream, TEXT("default"), false);

	FString address = _ip;
	int32 port = _port;
	FIPv4Address ip;
	FIPv4Address::Parse(address, ip);


	TSharedRef<FInternetAddr> addr = ISocketSubsystem::Get(PLATFORM_SOCKETSUBSYSTEM)->CreateInternetAddr();
	addr->SetIp(ip.Value);
	addr->SetPort(port);

	bool connected = TCPClientSocket->Connect(*addr);

	TArray<uint8> ReceivedData;
	int32 Read = 0;

	if (connected)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("Connected!")));

		GetWorldTimerManager().SetTimer(TimerHandleTest, this, &AGBPReceiver::CheckForReceivedData, 0.01f, true);


	}
	else
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("Could not connect to server. Please try again.")));

	return connected;
}

