#pragma once
#include "Engine.h"
#include "C2IReceiverBPLibrary.generated.h"

UCLASS()
class UC2IReceiverBPLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintPure, Category = "C2I", meta = (DisplayName = "Test", Keywords = "Tests"))
		static bool Test();


	UFUNCTION(BlueprintCallable, Category = "C2I", meta = (DisplayName = "TestDelegateBPLib", Keywords = "TestDelegateBPLib"))
		static void TestDelegateBPLib();
};