#include "C2IReceiverPlugin.h"


#include "C2IReceiverActor.h"

#include "Engine.h"


AC2IReceiverActor::AC2IReceiverActor(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	OnTestDelegate.AddDynamic(this, &AC2IReceiverActor::TestFunction);
	OnTestDelegateParam.AddDynamic(this, &AC2IReceiverActor::TestFunctionParam);
}

void AC2IReceiverActor::Test_Implementation() const
{
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, FString(TEXT("Test_Implementation")));
	}

	OnTestDelegate.Broadcast();
}

void AC2IReceiverActor::TestParam_Implementation(float _tmpVal) const
{
	FString t = FString::SanitizeFloat(_tmpVal*2);
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, t);
	}

	OnTestDelegateParam.Broadcast(_tmpVal);
}

void AC2IReceiverActor::TestFunction()
{
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, FString(TEXT("TestFunction")));
	}
}


void AC2IReceiverActor::TestFunctionParam(float _val)
{
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, FString(TEXT("TestFunctionParam")));
	}
}

FString AC2IReceiverActor::TestFunctionRetVal(FString _testval)
{
//	TestVal = _testval;
	return _testval + _testval;
}



