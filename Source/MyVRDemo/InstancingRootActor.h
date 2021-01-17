// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "InstancingRootActor.generated.h"

UCLASS()
class MYVRDEMO_API AInstancingRootActor : public AActor
{
	GENERATED_BODY()
		
public:	
	// Sets default values for this actor's properties
	AInstancingRootActor();
	// Called every frame
	virtual void Tick(float DeltaTime) override;



protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Flocking")
		class UInstancedStaticMeshComponent* InstancedComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Flocking")
		class UStaticMeshComponent* rootStaticMesh;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Flocking")
		class UMaterial* DrawMat;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Flocking")
		class UMaterialInstanceDynamic* DrawMatInstance;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Flocking", Meta = (ExposeOnSpawn = "true"))
		int InstanceNum;

	UFUNCTION(BlueprintCallable)
		void InitInstances(int instatnceNum);

	UFUNCTION(BlueprintCallable)
		int GetInstanceCount();
};
