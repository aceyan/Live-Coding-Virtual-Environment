// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "ConvertToNumber.generated.h"

/**
 * 
 */
UCLASS()
class MYVRDEMO_API UConvertToNumber : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

private:
	static const TMap<FString, int32> NumberMap;

public:
	UFUNCTION(BlueprintCallable, Category = "Convert")
		static int Convert(TArray<FString> InputString);
};
