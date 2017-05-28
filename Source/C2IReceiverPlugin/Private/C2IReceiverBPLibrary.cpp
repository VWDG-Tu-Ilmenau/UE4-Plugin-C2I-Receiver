#include "C2IReceiverPlugin.h"

#include "C2IReceiverBPLibrary.h"



bool UC2IReceiverBPLibrary::Test()
{
	return true;
}

void UC2IReceiverBPLibrary::TestDelegateBPLib()
{
	FString t = FString("EVENTHYPE");


	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, t);
	}
}
