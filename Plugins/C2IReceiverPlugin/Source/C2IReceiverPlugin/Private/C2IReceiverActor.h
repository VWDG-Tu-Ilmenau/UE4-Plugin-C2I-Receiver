#pragma once

#include "GameFramework/Actor.h"
#include "C2IReceiverActor.generated.h"


// https://docs.unrealengine.com/latest/INT/Programming/UnrealArchitecture/Delegates/index.html
// http://www.tomlooman.com/ue4-ufunction-keywords-explained/

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FTestDelegate);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FTestDelegateParam, float, tmpVal);



UCLASS()
class  AC2IReceiverActor : public AActor
{
	GENERATED_UCLASS_BODY()


public:
	//////////////////////////////////////////////////////////////////////////
	//Use these functions to test you delegates in blueprint

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "C2I")
		void Test() const;	
	
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "C2I")
		void TestParam(float _tmpVal) const;

	//////////////////////////////////////////////////////////////////////////
	//Here are the actual delegates

	UPROPERTY(BlueprintAssignable,Category = "C2I")
		FTestDelegate OnTestDelegate;

	UPROPERTY(BlueprintAssignable, Category = "C2I")
		FTestDelegateParam OnTestDelegateParam;
	
	//////////////////////////////////////////////////////////////////////////
	//The function executed in cpp after the delegate has been called
	UFUNCTION()
		void TestFunction();

	UFUNCTION(BlueprintCallable, Category ="C2I")
		void TestFunctionParam(float _val);



	//////////////////////////////////////////////////////////////////////////
	//This is a function which can be called in the level blueprint.
	UFUNCTION(BlueprintCallable, Category = "C2I")
		FString TestFunctionRetVal(FString _testval);

	FString TestVal;

	//////////////////////////////////////////////////////////////////////////
	//This is an event in the blueprint of the actor
	UFUNCTION(BlueprintImplementableEvent, Category = "C2I")
		void TestImplementableEvent(float CurrentHealth);
};