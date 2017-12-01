// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/UserDefinedEnum.h"
#include "EGPBDataType.generated.h"

/**
 * 
 */
UENUM(BlueprintType)		//"BlueprintType" is essential to include
enum class EGPBTypeEnum : uint8
{
	TYPEINT 	UMETA(DisplayName = "Integer"),
	TYPEFLOAT UMETA(DisplayName = "Float"),
	TYPECALL UMETA(DisplayName = "Call")

};

UCLASS()
class C2IRECEIVERPLUGIN_API UEGPBDataType : public UUserDefinedEnum
{
public:
	GENERATED_BODY()

		EGPBTypeEnum GPBType;
};
