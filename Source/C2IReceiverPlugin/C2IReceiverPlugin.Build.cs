// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;
using System.IO;
using System;

public class C2IReceiverPlugin : ModuleRules
{
    public C2IReceiverPlugin(ReadOnlyTargetRules Target) : base(Target)
    {

        PublicIncludePaths.AddRange(
            new string[] {
                "C2IReceiverPlugin/Public"
				// ... add public include paths required here ...
			}
            );


        PrivateIncludePaths.AddRange(
            new string[] {
                "C2IReceiverPlugin/Private",
				// ... add other private include paths required here ...
			}
            );


        PublicDependencyModuleNames.AddRange(
            new string[]
            {
                "Core",
                "Networking",
                "Sockets"
				// ... add other public dependencies that you statically link with here ...
			}
            );


        PrivateDependencyModuleNames.AddRange(
            new string[]
            {
                "CoreUObject",
                "Engine",
                "Slate",
                "SlateCore",
				// ... add private dependencies that you statically link with here ...	
			}
            );


        DynamicallyLoadedModuleNames.AddRange(
            new string[]
            {
				// ... add any modules that your module loads dynamically here ...
			}
            );

        LoadGoogleProtocolBuffers(Target);

    }

    //Method which loads our plugin
    public bool LoadGoogleProtocolBuffers(ReadOnlyTargetRules Target)
    {
        bool isLibrarySupported = false;

        if ((Target.Platform == UnrealTargetPlatform.Win64) || (Target.Platform == UnrealTargetPlatform.Win32))
        {
            isLibrarySupported = true;

            string PlatformString = (Target.Platform == UnrealTargetPlatform.Win64) ? "x64" : "x86";
            string LibrariesPath = Path.Combine(ThirdPartyPath, "GoogleProtocolBuffers", "lib");

            //test your path with:
            Console.WriteLine("");
            Console.WriteLine("... LibrariesPath -> " + LibrariesPath);
            /*
            */

            PublicAdditionalLibraries.Add(Path.Combine(LibrariesPath, "libprotobufd" + ".lib"));
        }

        if (isLibrarySupported)
        {
            // Include path
            PublicIncludePaths.Add(Path.Combine(ThirdPartyPath, "GoogleProtocolBuffers", "Include"));
        }

        Definitions.Add(string.Format("WITH_GPB_BINDING={0}", isLibrarySupported ? 1 : 0));

        return isLibrarySupported;
    }

    /// <summary>
    /// Convinience method for path access
    /// </summary>

    private string ModulePath
    {
        get { return ModuleDirectory; }
    }

    private string ThirdPartyPath
    {
        get { return Path.GetFullPath(Path.Combine(ModulePath, "../../ThirdParty/")); }
    }
}
