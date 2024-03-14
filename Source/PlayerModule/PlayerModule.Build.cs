using UnrealBuildTool;

public class PlayerModule : ModuleRules
{
    public PlayerModule(ReadOnlyTargetRules Target) : base(Target)
    {

        PrivateDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "BaseModule" });

    }
}