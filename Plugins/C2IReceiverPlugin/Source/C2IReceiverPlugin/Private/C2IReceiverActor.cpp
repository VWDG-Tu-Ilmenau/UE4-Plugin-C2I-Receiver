// Fill out your copyright notice in the Description page of Project Settings.

#include "C2IReceiverPlugin.h"
#include "C2IReceiverActor.h"


// Sets default values
AC2IReceiverActor::AC2IReceiverActor()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AC2IReceiverActor::BeginPlay()
{
	Super::BeginPlay();

}


void AC2IReceiverActor::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
	UWorld* World = GetWorld();

	GetWorld()->GetTimerManager().ClearTimer(TimerHandleTest);

	if (TCPClientSocket != NULL) {
		TCPClientSocket->Close();
		ISocketSubsystem::Get(PLATFORM_SOCKETSUBSYSTEM)->DestroySocket(TCPClientSocket);
	}

}

// Called every frame
void AC2IReceiverActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

bool AC2IReceiverActor::TryToConnectToServer(FString _ip /*= "127.0.0.1"*/, int32 _port /*= 12345*/)
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

		GetWorldTimerManager().SetTimer(TimerHandleTest, this, &AC2IReceiverActor::CheckForReceivedData, 0.01f, true);


	}
	else
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("Shit.")));

	return connected;
}

void AC2IReceiverActor::CheckForReceivedData()
{
	TArray<uint8> ReceivedData;
	uint32 Size;
	bool hasData = TCPClientSocket->HasPendingData(Size);
	if (hasData)
	{
		ReceivedData.Init(FMath::Min(Size, 65507u), Size);
		
		int32 Read = 0;
		TCPClientSocket->Recv(ReceivedData.GetData(), ReceivedData.Num(), Read);
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("Data Read! %d"), ReceivedData.Num()));
	}

	if (ReceivedData.Num() <= 0)
	{
		//No Data Received
		return;
	}

	char* Data = (char*)ReceivedData.GetData();
	Data[Size] = '\0';
	FString Msg = UTF8_TO_TCHAR(Data);


	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT(Msg));
	OnTCPCallback.Broadcast(Msg);
}
