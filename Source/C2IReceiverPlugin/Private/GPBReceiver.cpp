// Fill out your copyright notice in the Description page of Project Settings.

#include "GPBReceiver.h"
#include "C2IReceiverPlugin.h"


// Sets default values
AGPBPReceiver::AGPBPReceiver()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	
	GPBDataDispatcher_ = CreateDefaultSubobject<UGPBDataDispatcher>(TEXT("GPBDataDispatcher"));
}

// Called when the game starts or when spawned
void AGPBPReceiver::BeginPlay()
{
	Super::BeginPlay();

}

void AGPBPReceiver::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
}

bool AGPBPReceiver::ConvertInputToGPB(TArray<uint8> _receivedData)
{
	bool parseSuccessful = InputGPB.ParseFromArray(_receivedData.GetData(), _receivedData.Num());
	
	if (!parseSuccessful)
	{
		UE_LOG(LogTemp, Warning, TEXT("Can not convert GPB input stream to GPB object.\n %s"), *FString(InputGPB.DebugString().c_str()));
		return false;
	}
	bool isInitialized = InputGPB.IsInitialized();
	if (!isInitialized)
	{
		UE_LOG(LogTemp, Warning, TEXT("Can not initialize GPB input stream to GPB object.\n %s"), *FString(InputGPB.DebugString().c_str()));
		return false;
	}
	//UE_LOG(LogTemp, Warning, TEXT("Received: \n %s"), *FString(InputGPB.DebugString().c_str()));

	return true;
}

// Called every frame
void AGPBPReceiver::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AGPBPReceiver::CheckForReceivedData()
{
	uint32 Size;
	TArray<uint8> ReceivedData;

	uint32 headersize = sizeof(int32) ;

	bool hasData = TCPClientSocket->HasPendingData(Size);

	//TODO: read bytes size; read(size) bytes content
	if (hasData)
	{
		if (Size > headersize)
		{
			//////////////////////////////////////////////////////////////////////////
			//read header
			ReceivedData.Init(0, headersize); //init array for header size
			int32 Read = 0;

			TCPClientSocket->Recv(ReceivedData.GetData(), ReceivedData.Num(), Read);
			
			if (Read != headersize)
			{
				UE_LOG(LogTemp, Warning, TEXT("%s"), "Header: Read different amount of bytes than int32: %f vs %f", Read, headersize);
			}

			FString header = StringFromBinaryArray(ReceivedData); //this is the one used by WoCarZ
			//UE_LOG(LogTemp, Warning, TEXT("Header: Read. Payload size: %s"), *header);
			
			//////////////////////////////////////////////////////////////////////////
			//How much payload is there?
			int32 payloadSize = 0;
			if (!header.IsNumeric())
			{
				UE_LOG(LogTemp, Warning, TEXT("Header: Header is not numeric: %s. Using fallback method."), *header);
				payloadSize = int32(	//this is the one used by C2I_Socket Plugin
					(unsigned char)(ReceivedData[3]) << 24 | 
					(unsigned char)(ReceivedData[2]) << 16 |
					(unsigned char)(ReceivedData[1]) << 8 |
					(unsigned char)(ReceivedData[0]));
			}
			else
			{
				payloadSize = FCString::Atoi(*header);
			}

			ReceivedData.Init(0, payloadSize); //Reinitializes the array with size provided by header
			Read = 0;

			//////////////////////////////////////////////////////////////////////////
			//Read payload
			TCPClientSocket->Recv(ReceivedData.GetData(), ReceivedData.Num(), Read);

			if (ReceivedData.Num() <= 0)
			{
				return;
			}
	
			if (Read != payloadSize)
			{
				UE_LOG(LogTemp, Warning, TEXT("Payload: Read a different amount of bytes than payloadSize: %d  vs. %d"), Read, payloadSize);
			}

			bool isOK = ConvertInputToGPB(ReceivedData);
			


			//UE_LOG(LogTemp, Warning, TEXT("Payload: Content: %s \n"), *FString(InputGPB.DebugString().c_str())); 
			
			if (isOK)
			{
				
				//this value is only for debugging purposes. Blueprints access values via the dispatcher.
				float val = InputGPB.event().val_float(); 
				OnTCPCallback.Broadcast(FString::SanitizeFloat(val));
				
				//insert GPB into DataStructure
				GPBDataDispatcher_->InsertValueIntoRegistry(InputGPB);
				
			}
			else
			{
				UE_LOG(LogTemp, Warning, TEXT("Protobuffer not right!"));
				UE_LOG(LogTemp, Warning, TEXT("Payload: Content: %s \n"), *FString(InputGPB.DebugString().c_str()));
			}
				
			
		}
	}
}

bool AGPBPReceiver::TryToConnectToServer(FString _ip /*= "127.0.0.1"*/, int32 _port /*= 12345*/)
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

		GetWorldTimerManager().SetTimer(TimerHandleTest, this, &AGPBPReceiver::CheckForReceivedData, 0.01f, true);


	}
	else
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("Could not connect to server. Please try again.")));

	return connected;
}

UGPBDataDispatcher* AGPBPReceiver::GetGPBDataDispatcherRef()
{
	return GPBDataDispatcher_;
}

