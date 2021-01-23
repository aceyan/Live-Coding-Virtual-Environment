// Fill out your copyright notice in the Description page of Project Settings.

#include "ConvertToNumber.h"

const TMap<FString, int32> UConvertToNumber::NumberMap =
{
	{TEXT("one"), 1},
	{TEXT("two"), 2 },
	{TEXT("three"), 3},
	{TEXT("four"), 4 },
	{TEXT("five"), 5},
	{TEXT("six"), 6},
	{TEXT("seven"), 7},
	{TEXT("eight"), 8},
	{TEXT("nine"), 9},
	{TEXT("ten"), 10},
	{TEXT("eleven"), 11},
	{TEXT("twelve"), 12},
	{TEXT("thirteen"), 13},
	{TEXT("fourteen"), 14 },
	{TEXT("fifteen"), 15},
	{TEXT("sixteen"), 16},
	{TEXT("seventeen"), 17},
	{TEXT("eighteen"), 18},
	{TEXT("nineteen"), 19},
	{TEXT("twenty"), 20},
	{TEXT("thirty"), 30},
	{TEXT("forty"), 40},
	{TEXT("fifty"), 50},
	{TEXT("sixty"), 60},
	{TEXT("seventy"), 70},
	{TEXT("eighty"), 80},
	{TEXT("ninety"), 90}
};

int UConvertToNumber::Convert(TArray<FString> InputString)
{

	/*
	TArray<FString> InputString;
	InputString.Emplace(TEXT("four"));
	InputString.Emplace(TEXT("hundred"));
	InputString.Emplace(TEXT("fifty"));
	InputString.Emplace(TEXT("six"));
	InputString.Emplace(TEXT("thousand"));
	InputString.Emplace(TEXT("three"));
	InputString.Emplace(TEXT("hundred"));
	InputString.Emplace(TEXT("twenty"));
	InputString.Emplace(TEXT("one"));
	*/

	FString a;
	for (auto& Str : InputString)
	{
		a += Str;
		a += TEXT(" ");
	}
	UE_LOG(LogClass, Warning, TEXT("Input:%s"), *a);

	int32 result = 0;
	int32 partical_result = 0;
	for (int32 i = 0; i < InputString.Num(); i++)
	{
		if (InputString[i].Equals(TEXT("thousand")))
		{
			if (partical_result == 0)
			{
				partical_result = 1;
			}
			partical_result *= 1000;
			result += partical_result;
			partical_result = 0;
		}
		else
		{
			if (InputString[i].Equals(TEXT("hundred")))
			{
				if (partical_result == 0)
				{
					partical_result = 1;
				}
				partical_result *= 100;
			}
			else
			{
				const int32* temp = NumberMap.Find(InputString[i]);
				if (temp!=nullptr)
				{
					partical_result += *temp;
				}
			}
		}
	}
	result += partical_result;

	FString res = FString::FromInt(result);

	UE_LOG(LogClass, Warning, TEXT("Result:%s"), *res);
	if (result == 0) return 1;
	else return result;
}
