// Fill out your copyright notice in the Description page of Project Settings.

#include "GPBDataDispatcher.h"

#include "C2IReceiverPlugin.h"


// Sets default values for this component's properties
UGPBDataDispatcher::UGPBDataDispatcher()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}


// Called when the game starts
void UGPBDataDispatcher::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UGPBDataDispatcher::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

//deprecated
void UGPBDataDispatcher::SetValue(float _val)
{
	FScopeLock lock(&FloatCriticalSection); 
	
	//UE_LOG(C2SLog, Warning, TEXT("Set: %f"), val_float);
	val_float = _val;

}

//deprecated
float UGPBDataDispatcher::GetValueFloat()
{
	FScopeLock lock(&FloatCriticalSection);
	//UE_LOG(C2SLog, Warning, TEXT("Get: %f"), val_float);
	return val_float;
}

void UGPBDataDispatcher::InsertValueIntoRegistry(c2ipb::Call _inputGPB)
{
	FScopeLock lock(&MapCriticalSection);

	c2ipb::Call** tmpGPBptr = CallValueRegistry.Find(TPair<FString, FString>(_inputGPB.targetcomponent().c_str(), _inputGPB.targetcommand().c_str()));
	

	if (tmpGPBptr != nullptr)
	{
		c2ipb::Call* tmpGPB = *tmpGPBptr;
		tmpGPB->CopyFrom(_inputGPB);
		//UE_LOG(C2SLog, Warning, TEXT("Replace"));
		bool containsValue = CallValueRegistry.Contains(TPair<FString, FString>(_inputGPB.targetcomponent().c_str(), _inputGPB.targetcommand().c_str()));

	}
	else
	{
		c2ipb::Call* tmp2 = new c2ipb::Call();
		tmp2->CopyFrom(_inputGPB);
		CallValueRegistry.Add(TPair<FString, FString>(tmp2->targetcomponent().c_str(), tmp2->targetcommand().c_str()), tmp2);
		UE_LOG(C2SLog, Warning, TEXT("Add"));

		bool containsValue = CallValueRegistry.Contains(TPair<FString, FString>(_inputGPB.targetcomponent().c_str(), _inputGPB.targetcommand().c_str()));
		
	}
	TArray<TPair<FString, FString>> myArray;
	CallValueRegistry.GenerateKeyArray(myArray);
}

int UGPBDataDispatcher::GetIntValueFromRegistry(FString _targetcomponent, FString _targetcommand)
{
	FScopeLock lock(&MapCriticalSection);
	if (CallValueRegistry.Num() == 0)
		return -555;

	c2ipb::Call** tmpGPBptr = CallValueRegistry.Find(TPair<FString, FString>(_targetcomponent, _targetcommand));

	if (tmpGPBptr != nullptr)
	{
		c2ipb::Call* tmpGPB = *tmpGPBptr;
		return tmpGPB->event().val_int();
	}
	else
	{
		return -999;
	}
}

float UGPBDataDispatcher::GetFloatValueFromRegistry(FString _targetcomponent, FString _targetcommand)
{
	FScopeLock lock(&MapCriticalSection);
	if (CallValueRegistry.Num() == 0)
		return -777;

	c2ipb::Call** tmpGPBptr = CallValueRegistry.Find(TPair<FString, FString>(_targetcomponent, _targetcommand));
	
	if (tmpGPBptr != nullptr)
	{
		c2ipb::Call* tmpGPB = *tmpGPBptr;
		return tmpGPB->event().val_float();
	}
	else
	{
		return -666;
	}		
}

FString UGPBDataDispatcher::GetStringValueFromRegistry(FString _targetcomponent, FString _targetcommand)
{

	FScopeLock lock(&MapCriticalSection);
	if (CallValueRegistry.Num() == 0)
	{
		std::string tmp = "registry empty";
		return FString(UTF8_TO_TCHAR(tmp.c_str()));
	}

	c2ipb::Call** tmpGPBptr = CallValueRegistry.Find(TPair<FString, FString>(_targetcomponent, _targetcommand));

	if (tmpGPBptr != nullptr)
	{
		c2ipb::Call* tmpGPB = *tmpGPBptr;
		return FString(UTF8_TO_TCHAR(tmpGPB->event().val_string().c_str()));
	}
	else
	{
		std::string tmp2 = "null pointer";

		return FString(UTF8_TO_TCHAR(tmp2.c_str()));
	}
}
