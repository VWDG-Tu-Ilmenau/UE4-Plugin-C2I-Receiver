#include "C2ITestActor.h"
#include "C2IReceiverPlugin.h"

#include "Engine.h"


AC2ITestActor::AC2ITestActor(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	OnTestDelegate.AddDynamic(this, &AC2ITestActor::TestFunction);
	OnTestDelegateParam.AddDynamic(this, &AC2ITestActor::TestFunctionParam);
}

void AC2ITestActor::Test_Implementation() const
{
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, FString(TEXT("Test_Implementation")));
	}

	OnTestDelegate.Broadcast();
}

void AC2ITestActor::TestParam_Implementation(float _tmpVal) const
{
	FString t = FString::SanitizeFloat(_tmpVal*2);
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, t);
	}

	OnTestDelegateParam.Broadcast(_tmpVal);
}

void AC2ITestActor::TestFunction()
{
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, FString(TEXT("TestFunction")));
	}
}


void AC2ITestActor::TestFunctionParam(float _val)
{
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, FString(TEXT("TestFunctionParam")));
	}
}

FString AC2ITestActor::TestFunctionRetVal(FString _testval)
{
//	TestVal = _testval;
	return _testval + _testval;
}



