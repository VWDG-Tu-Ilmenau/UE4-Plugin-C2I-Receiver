#pragma once
#include "Engine.h"
#include "C2ITestBPLibrary.generated.h"

UCLASS()
class UC2ITestBPLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintPure, Category = "C2I", meta = (DisplayName = "Test", Keywords = "Tests"))
		static bool Test();


	UFUNCTION(BlueprintCallable, Category = "C2I", meta = (DisplayName = "TestDelegateBPLib", Keywords = "TestDelegateBPLib"))
		static void TestDelegateBPLib();
};