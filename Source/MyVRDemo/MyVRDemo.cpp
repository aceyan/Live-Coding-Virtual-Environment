// Copyright Epic Games, Inc. All Rights Reserved.

#include "MyVRDemo.h"
#include "Modules/ModuleManager.h"

#include "Misc/Paths.h"
#include "ShaderCore.h"


void FMyVRDemo::StartupModule()
{
	//mappinng shaders floder
	FString ShaderDirectory = FPaths::Combine(FPaths::ProjectDir(), TEXT("Shaders"));
	AddShaderSourceDirectoryMapping("/Project", ShaderDirectory);
}

void FMyVRDemo::ShutdownModule()
{
	ResetAllShaderSourceDirectoryMappings();
}

IMPLEMENT_PRIMARY_GAME_MODULE(FMyVRDemo, MyVRDemo, "MyVRDemo");


