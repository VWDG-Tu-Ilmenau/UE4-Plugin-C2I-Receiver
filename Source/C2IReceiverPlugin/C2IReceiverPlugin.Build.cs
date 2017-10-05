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
                "Sockets",
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
       // LoadC2IExchangeFormat(Target);

    }

    //Method which loads our Google Protocol Buffers 
    public bool LoadGoogleProtocolBuffers(ReadOnlyTargetRules Target)
    {
        bool isLibrarySupported = false;

        if ((Target.Platform == UnrealTargetPlatform.Win64))
        {
            isLibrarySupported = true;

            string LibrariesPath = Path.Combine(ThirdPartyPath, "libprotobuf", "lib");

            Console.WriteLine("... LibrariesPath -> " + LibrariesPath);
            PublicAdditionalLibraries.Add(Path.Combine(LibrariesPath, "libprotobuf" + ".lib"));
        }

        if (isLibrarySupported)
        {
            string IncludePath= Path.Combine(ThirdPartyPath, "libprotobuf", "include");

            Console.WriteLine("... IncludePath -> " + IncludePath);
            PrivateIncludePaths.Add(IncludePath);
        }

        Definitions.Add(string.Format("WITH_GPB_BINDING={0}", isLibrarySupported ? 1 : 0));

        return isLibrarySupported;
    }

    //Method which loads our C2I Exchange Formats
    public bool LoadC2IExchangeFormat(ReadOnlyTargetRules Target)
    {
        bool isLibrarySupported = false;

        if ((Target.Platform == UnrealTargetPlatform.Win64) || (Target.Platform == UnrealTargetPlatform.Win32))
        {
            isLibrarySupported = true;

            //string PlatformString = (Target.Platform == UnrealTargetPlatform.Win64) ? "x64" : "x86";
            //string LibrariesPath = Path.Combine(ThirdPartyPath, "C2IExchangeFormats", "lib");

            //test your path with:
            //Console.WriteLine("");
            //Console.WriteLine("... LibrariesPath -> " + LibrariesPath);
            /*
            */

            //PublicAdditionalLibraries.Add(Path.Combine(LibrariesPath, "MessageInput_to_C2I.pb" + ".cc"));
        }

        if (isLibrarySupported)
        {
            // Include path

            string PlatformString = (Target.Platform == UnrealTargetPlatform.Win64) ? "x64" : "x86";
            PublicIncludePaths.Add(Path.Combine(ThirdPartyPath, "C2IExchangeFormats", PlatformString, "include"));
        }

        Definitions.Add(string.Format("WITH_C2I_BINDING={0}", isLibrarySupported ? 1 : 0));

        return isLibrarySupported;
    }

    private string ModulePath
    {
        get { return ModuleDirectory; }
    }

    private string ThirdPartyPath
    {
        get { return Path.GetFullPath(Path.Combine(ModulePath, "../../ThirdParty/")); }
    }
}
