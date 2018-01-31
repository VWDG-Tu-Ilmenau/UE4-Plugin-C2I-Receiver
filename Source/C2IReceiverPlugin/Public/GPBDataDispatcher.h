// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Runtime/Core/Public/Containers/Map.h "
#include "Components/ActorComponent.h"

#include "ProtobufHandler.h"

#include "GPBDataDispatcher.generated.h"

typedef TPair<FString, FString> IDofVC;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class C2IRECEIVERPLUGIN_API UGPBDataDispatcher : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UGPBDataDispatcher();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	//Sets the float value (for debug purposes). Is thread-safe via critical sections.
	void SetValue(float _val);
	
	//Returns the float value (for debug purposes). Is thread-safe via critical sections.
	float GetValueFloat();

	//Extracts targetcommand and targetcomponent, builds a key from them, and inserts the GPB in the map. Is thread-safe via critical sections.
	void InsertValueIntoRegistry(c2ipb::Call _inputGPB);

	//Retrieves the GPB associated with the key and returns the according int value. If no key was found, returns -999. Is thread-safe via critical sections.
	UFUNCTION(BlueprintCallable, Category = "Car2IXS|GPBReceiver")
		int GetIntValueFromRegistry(FString _targetcomponent, FString _targetcommand);

	//Retrieves the GPB associated with the key and returns the according float value. If no key was found, returns -666. Is thread-safe via critical sections.
	UFUNCTION(BlueprintCallable, Category = "Car2IXS|GPBReceiver")
		float GetFloatValueFromRegistry(FString _targetcomponent, FString _targetcommand);

	//Retrieves the GPB associated with the key and returns the according FString value. If no key was found, returns "null pointer". Is thread-safe via critical sections.
	UFUNCTION(BlueprintCallable, Category = "Car2IXS|GPBReceiver")
		FString GetStringValueFromRegistry(FString _targetComponent, FString _targetcommand);

	//Retrieves and removes the GPB associated with the key and returns the according FString value. If no key was found, returns "null pointer" . Is thread-safe via critical sections.
	UFUNCTION(BlueprintCallable, Category = "Car2IXS|GPBReceiver")
		FString GetAndRemoveStringValueFromRegistry(FString _targetComponent, FString _targetcommand);


private:
	float val_float;

	FCriticalSection FloatCriticalSection;

	FCriticalSection MapCriticalSection;
	TMap<IDofVC, c2ipb::Call*> CallValueRegistry;
};
