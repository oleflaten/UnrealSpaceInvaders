// Fill out your copyright notice in the Description page of Project Settings.

using UnrealBuildTool;
using System.Collections.Generic;

public class Uke3_UEEditorTarget : TargetRules
{
	public Uke3_UEEditorTarget(TargetInfo Target) : base (Target)
	{
		Type = TargetType.Editor;
		DefaultBuildSettings = BuildSettingsVersion.V2;
		
		ExtraModuleNames.AddRange( new string[] { "Uke3_UE" } );
	}
}
