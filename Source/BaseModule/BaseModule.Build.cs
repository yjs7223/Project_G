using UnrealBuildTool;

public class BaseModule : ModuleRules
{
    public BaseModule(ReadOnlyTargetRules Target) : base(Target)
    {

        PrivateDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine" });

    }
}