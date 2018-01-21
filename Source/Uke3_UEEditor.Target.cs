// Fill out your copyright notice in the Description page of Project Settings.

using UnrealBuildTool;
using System.Collections.Generic;

public class Uke3_UEEditorTarget : TargetRules
{
	public Uke3_UEEditorTarget(TargetInfo Target) : base (Target)
	{
		Type = TargetType.Editor;
		ExtraModuleNames.Add("Uke3_UE");

        bUseUnityBuild = false;
        bUsePCHFiles = false;
	}
}