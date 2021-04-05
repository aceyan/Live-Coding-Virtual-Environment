// Fill out your copyright notice in the Description page of Project Settings.

using UnrealBuildTool;
using System.Collections.Generic;

public class MyVRDemoTarget : TargetRules
{
	public MyVRDemoTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Game;
		bForceEnableExceptions = true;
		bOverrideBuildEnvironment = true;
		ExtraModuleNames.AddRange( new string[] { "MyVRDemo" } );
	}
}
