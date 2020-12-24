// Fill out your copyright notice in the Description page of Project Settings.


#include "CSTestActor.h"
#include "FlockingComputeShaderObj.h"
#include "Kismet/KismetMathLibrary.h"

// Sets default values
ACSTestActor::ACSTestActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	SeparationForceScaler = 1.0;
	CohesionForceScaler = 1.0;
	AlignForceScaler = 1.0;
}

// Called when the game starts or when spawned
void ACSTestActor::BeginPlay()
{
	Super::BeginPlay();
	shaderObj.BeginRendering();

	if (PositionRenderTarget != NULL) posTextureResource = (FTextureRenderTarget2DResource*)PositionRenderTarget->Resource;
	if (VelocityRenderTarget != NULL) velTextureResource = (FTextureRenderTarget2DResource*)VelocityRenderTarget->Resource;
	
}

void ACSTestActor::BeginDestroy()
{
	shaderObj.EndRendering();
	Super::BeginDestroy();
}

// Called every frame
void ACSTestActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//draw position and velocity rendertarget
	FShaderUsageExampleParameters DrawParameters(VelocityRenderTarget, PositionRenderTarget);
	{
		DrawParameters.RangeMax = RangeMax;
		DrawParameters.RangeMin = RangeMin;
		DrawParameters.AlignScaler = AlignForceScaler;
		DrawParameters.CohesionScaler = CohesionForceScaler;
		DrawParameters.SeparationScaler = SeparationForceScaler;
	}
	shaderObj.UpdateParameters(DrawParameters);


	
	if (posTextureResource != NULL)
	{
		
		//fetch position buffer from rendertarget to cpu
		if (posTextureResource->ReadFloat16Pixels(posColorBuffer16) && velTextureResource->ReadFloat16Pixels(velColorBuffer16))
		{
		

			for (int i = 0; i < actorList.Num() && i < posColorBuffer16.Num(); i++)
			{
				AActor* p = actorList[i];

				float x = posColorBuffer16[i].R.GetFloat();
				float y = posColorBuffer16[i].G.GetFloat();
				float z = posColorBuffer16[i].B.GetFloat();
				
				p->SetActorLocation(FVector(x, y, z));


				float vx = velColorBuffer16[i].R.GetFloat();
				float vy = velColorBuffer16[i].G.GetFloat();
				float vz = velColorBuffer16[i].B.GetFloat();

				FVector velocity = FVector(vx, vy, vz);


				FRotator PlayerRot = UKismetMathLibrary::FindLookAtRotation(p->GetActorLocation(), p->GetActorLocation() + velocity);
				p->SetActorRotation(PlayerRot);
			}
			



		}
	}

}

