#include "C2ITestBPLibrary.h"

#include "C2IReceiverPlugin.h"




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
