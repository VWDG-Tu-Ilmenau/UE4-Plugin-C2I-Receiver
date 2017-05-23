// Fill out your copyright notice in the Description page of Project Settings.

using UnrealBuildTool;

public class PluginC2IReceiver : ModuleRules
{
	public PluginC2IReceiver(TargetInfo Target)
	{
		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "C2IReceiverPlugin" });

		//PrivateDependencyModuleNames.AddRange(new string[] { "C2IReceiverPlugin" });

		// Uncomment if you are using Slate UI
		// PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });
		
		// Uncomment if you are using online features
		// PrivateDependencyModuleNames.Add("OnlineSubsystem");

		// To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
	}
}
