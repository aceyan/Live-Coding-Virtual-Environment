// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "TaskDataAsset.generated.h"

/**
 * 
 */

UENUM(BlueprintType)
enum class ETaskTypes : uint8 
{
	CreateMeshBased       UMETA(DisplayName = "CreateMeshBased"),
	CreateRayMarching        UMETA(DisplayName = "CreateRayMarching"),
	CreateRayMarchingOperation        UMETA(DisplayName = "CreateRayMarchingOperation"),
	CreateBigFlocking        UMETA(DisplayName = "CreateBigFlocking"),
	CreateSmallFlocking        UMETA(DisplayName = "CreateSmallFlocking"),
	CreateAreaFog        UMETA(DisplayName = "CreateAreaFog"),
	ChangeShapeMeshBased        UMETA(DisplayName = "ChangeShapeMeshBased"),
	ChangeShapeRayMarching      UMETA(DisplayName = "ChangeShapeRayMarching"),
	ChangeColorMeshBased      UMETA(DisplayName = "ChangeColorMeshBased"),
	ChangeColorRayMarching      UMETA(DisplayName = "ChangeColorRayMarching"),
	ScaleRayMarching      UMETA(DisplayName = "ScaleRayMarching"),
	ScaleCube      UMETA(DisplayName = "ScaleCube"),
	QuerySuccessUpdate            UMETA(DisplayName = "QuerySuccessUpdate"),
	TagsUpdate              UMETA(DisplayName = "TagsUpdate"),
	AdjustSmallFlocking       UMETA(DisplayName = "AdjustSmallFlocking"),
	AdjustBigFlocking             UMETA(DisplayName = "AdjustBigFlocking"),
	AdjustAreaFog             UMETA(DisplayName = "AdjustAreaFog"),
	QueryCancelUpdate            UMETA(DisplayName = "QueryCancelUpdate")
};

USTRUCT(BlueprintType)
struct FTaskStepData
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (MultiLine = true))
		FString Name;
		FString Description;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (MultiLine = true))
		FString Tips;
	//
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		ETaskTypes Type;
};


USTRUCT(BlueprintType)
struct FTaskData
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		FString Name;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (MultiLine = true))
		FString Description;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		TArray<FTaskStepData> TaskStepList;
};

UCLASS(BlueprintType)
class MYVRDEMO_API UTaskDataAsset : public UDataAsset
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		TArray<FTaskData> TaskDataList;
};
