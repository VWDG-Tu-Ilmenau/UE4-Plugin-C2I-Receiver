// Fill out your copyright notice in the Description page of Project Settings.

#include "C2IReceiverPlugin.h"
#include "GPBDataDispatcher.h"


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

void UGPBDataDispatcher::SetValue(float _val)
{
	FScopeLock lock(&FloatCriticalSection); 
	
	UE_LOG(LogTemp, Warning, TEXT("Set: %f"), val_float);
	val_float = _val;

}

float UGPBDataDispatcher::GetValueFloat()
{
	FScopeLock lock(&FloatCriticalSection);
	UE_LOG(LogTemp, Warning, TEXT("Get: %f"), val_float);
	return val_float;
}

void UGPBDataDispatcher::InsertValueIntoRegistry(c2ipb::Call _inputGPB)
{
	FScopeLock lock(&MapCriticalSection);
	CallValueRegistry.Add(TPair<FString, FString>(_inputGPB.targetcommand().c_str(), _inputGPB.targetcomponent().c_str()), _inputGPB);
}

float UGPBDataDispatcher::GetFloatValueFromRegistry(FString _targetcomponent, FString _targetcommand)
{
	FScopeLock lock(&MapCriticalSection);
	c2ipb::Call* _tmpGPB = CallValueRegistry.Find(TPair<FString, FString>(_targetcomponent, _targetcommand));
	if(_tmpGPB != nullptr)
		val_float = _tmpGPB->event().val_float();
	return val_float;
}
