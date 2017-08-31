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
		UE_LOG(LogTemp, Warning, TEXT("Can not convert GPB input stream to GPB object.\n %s"), *FString(InputGPB.DebugString().c_str()));
		return;
	}
	bool isInitialized = InputGPB.IsInitialized();
	if (!isInitialized)
	{
		UE_LOG(LogTemp, Warning, TEXT("Can not initialize GPB input stream to GPB object.\n %s"), *FString(InputGPB.DebugString().c_str()));
		return;
	}

	

	std::string t = InputGPB.DebugString();
	UE_LOG(LogTemp, Warning, TEXT("4 Payload: %s"), *FString(t.c_str()));

	std::string miao = "";

	std::string targetcommand= InputGPB.targetcommand();
	std::string targetcomponent = InputGPB.targetcomponent();
	std::string eventname = InputGPB.event().eventname();


	float val = InputGPB.event().val_float();
	
	std::string valstring = std::to_string(val);
	
	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::SanitizeFloat((val)));
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString(valstring.c_str()));

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

	//TODO: read bytes size; read(size) bytes content
	if (hasData)
	{
		if (Size > headersize)
		{
			//UE_LOG(LogTemp, Warning, TEXT("##########################################"));



			//////////////////////////////////////////////////////////////////////////
			//read header
			ReceivedData.Init(0, headersize); //init array for header size
			int32 Read = 0;

			TCPClientSocket->Recv(ReceivedData.GetData(), ReceivedData.Num(), Read);
			
			if (Read != headersize)
			{
				UE_LOG(LogTemp, Warning, TEXT("%s"), "Header: Read different amount of bytes than int64: %f vs %f", Read, headersize);
			}

			FString header = StringFromBinaryArray(ReceivedData);
			//UE_LOG(LogTemp, Warning, TEXT("Header: Read. Payload size: %s"), *header);

		
			
			//////////////////////////////////////////////////////////////////////////
			//How much payload is there?
			if (!header.IsNumeric())
			{
				UE_LOG(LogTemp, Warning, TEXT("3 Header: Header is not numeric: %s"), *header);
			}
			int64 payloadSize = FCString::Strtoi64(*header, NULL, 10);;
			
			ReceivedData.Init(0, payloadSize); //reinitializes the array with size provided by header
			Read = 0;
			U//E_LOG(LogTemp, Warning, TEXT("Header: Converted Payload: %lld"), payloadSize);



			//////////////////////////////////////////////////////////////////////////
			//Read payload
			TCPClientSocket->Recv(ReceivedData.GetData(), ReceivedData.Num(), Read);

			if (ReceivedData.Num() <= 0)
			{
				return;
			}
	
			if (Read != payloadSize)
			{
				UE_LOG(LogTemp, Warning, TEXT("Payload: Read a different amount of bytes than payloadSize: %f  vs. %f"), Read, payloadSize);
			}
			InputGPB.ParseFromArray(ReceivedData.GetData(), ReceivedData.Num());
			//UE_LOG(LogTemp, Warning, TEXT("Payload: Content: %s \n"), *FString(InputGPB.DebugString().c_str())); //Leads to Chinese characters
			
			
			
			//////////////////////////////////////////////////////////////////////////
			//Convert binary array
			//FString payload = StringFromBinaryArray(ReceivedData);//Create a string from a byte array!
			//UE_LOG(LogTemp, Warning, TEXT("Payload: 2 Content: %s \n"), *payload);

			//std::string MyStdString(TCHAR_TO_UTF8(*payload));
			//UE_LOG(LogTemp, Warning, TEXT("Payload: 3 Content: %s \n"), MyStdString.c_str());

			//ConvertInputToGPB(MyStdString);
			//ConvertInputToGPB(MyStdString);
			
			//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, Msg);
			float val = InputGPB.event().val_float();
			
			OnTCPCallback.Broadcast(FString::SanitizeFloat(val));
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

