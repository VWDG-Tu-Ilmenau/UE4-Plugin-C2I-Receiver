#pragma once
#include "Engine.h"
#include "C2IReceiverBPLibrary.generated.h"

UCLASS()
class UC2IReceiverBPLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintPure, Category = "Output|SbS Plugin", meta = (DisplayName = "Test", Keywords = "Tests"))
		static bool Test();



};