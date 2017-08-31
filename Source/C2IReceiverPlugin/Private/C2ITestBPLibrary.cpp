#include "C2IReceiverPlugin.h"

#include "C2ITestBPLibrary.h"



bool UC2ITestBPLibrary::Test()
{
	return true;
}

void UC2ITestBPLibrary::TestDelegateBPLib()
{
	FString t = FString("EVENTHYPE");


	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, t);
	}
}
