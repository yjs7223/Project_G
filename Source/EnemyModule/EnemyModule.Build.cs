using UnrealBuildTool;

public class EnemyModule : ModuleRules
{
    public EnemyModule(ReadOnlyTargetRules Target) : base(Target)
    {

        PrivateDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "BaseModule", "AIModule" });

    }
}