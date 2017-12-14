// Fill out your copyright notice in the Description page of Project Settings.

#include "ProtobufHandler.h"
#include "C2IReceiverPlugin.h"




bool UProtobufHandler::GetNewProtocolBuffer(TArray<uint8> _receivedData, c2ipb::Call* _inputGPB)
{
	
	bool parseSuccessful = _inputGPB->ParseFromArray(_receivedData.GetData(), _receivedData.Num());
	if (!parseSuccessful)
	{
		UE_LOG(C2SLog, Warning, TEXT("Can not convert GPB input stream to GPB object.\n %s"), *FString(_inputGPB->DebugString().c_str()));
		return false;
	}
	bool isInitialized = _inputGPB->IsInitialized();

	if (!isInitialized)
	{
		UE_LOG(C2SLog, Warning, TEXT("Can not initialize GPB input stream to GPB object.\n %s"), *FString(_inputGPB->DebugString().c_str()));
		return false;
	}

	return true;
}
