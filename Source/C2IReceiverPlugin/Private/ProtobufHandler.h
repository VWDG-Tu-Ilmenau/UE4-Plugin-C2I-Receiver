// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"

#include "AllowWindowsPlatformTypes.h"
#include "MessageC2I_to_Dispatcher.pb.h"
#include "HideWindowsPlatformTypes.h"

#include "ProtobufHandler.generated.h"

/**
 * 
 */
UCLASS()
class UProtobufHandler : public UObject
{
	GENERATED_BODY()
	
public:
	bool GetNewProtocolBuffer(TArray<uint8> _receivedData, c2ipb::Call* _inputGPB);
	
	
};
