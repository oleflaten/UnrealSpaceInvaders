// Fill out your copyright notice in the Description page of Project Settings.

using UnrealBuildTool;
using System.Collections.Generic;

public class Uke3_UETarget : TargetRules
{
	public Uke3_UETarget(TargetInfo Target) : base (Target)
	{
		Type = TargetType.Game;
		DefaultBuildSettings = BuildSettingsVersion.V2;

		ExtraModuleNames.AddRange( new string[] { "Uke3_UE" } );
	}
}
