# IntoTheArena
1) Download GitHUb
2) Create new "third person project"
3) Name the project "MyProject" (Can be named anything)
4) Install Gameplay Ability Plugin: Settings -> Plugins -> Gameplay Abilities (Editor will restart)
5) Create Character C++ class.
5a) Right click in "Content Browser" -> Right Click -> "New C++ Class" -> "Show All Classes"(Top Right) -> Type "Character" -> Select Character (This creates a C++ subclass of "Character") -> click Next ->  Set class to "Public" -> Name c++ class "MyCharacter" - Select Create Class
6) Create AttributeSet C++ class.
6a) Right click in "Content Browser" -> Right Click -> "New C++ Class" -> "Show All Classes"(Top Right) -> Type "AttributeSet" -> Select AttributeSet(This creates a C++ subclass of "AttributeSet") -> click Next ->  Set class to "Public" -> Name c++ class "MyAttributeSet" - Select Create Class
7) Create GameplayEffectExecutionCalculation C++ class.
7a) Right click in "Content Browser" -> Right Click -> "New C++ Class" -> "Show All Classes"(Top Right) -> Type "GameplayEffectExecutionCalculation" -> Select GameplayEffectExecutionCalculation(This creates a C++ subclass of "GameplayEffectExecutionCalculation") -> click Next ->  Set class to "Public" -> Name c++ class "MyDamageExecutionCalculation" - Select Create Class
8) Select Compile in UE Editor (Top tool bar above editor view port).
9) Close UE Editor
10) Add gmaeplay abilities to the project .build.cs file
10a) Locate project source files. This is created in Unreal Project folder. This example would be /Unreal Projects/MyProject/Source/MyProject.
10b) Edit .build.cs file. This example MyProject.Build.cs
10c) Add - "Slate", "SlateCore", "GameplayAbilities", "GameplayAbilitiesEditor", "GameplayTags", "GameplayTagsEditor", "GameplayTasks" - to the PrivateDependencyModuleNames.AddRange(new string[] { });
this should look similar to public dependcy modules above
11) Copy GitHub "TheArena" files to the newly created unreal engine project files.
11a) Copy "DefaultGameplayTags.ini" to the unreal project "Config" folder. This example would be /Unreal Projects/MyProject/Config
11b) Copy "Public" Folder to project C++ folder /Unreal Projects/MyProject/Source/MyProject.
11c) Copy "Private" Folder to project C++ folder /Unreal Projects/MyProject/Source/MyProject.
12) Change c++ project header files.
12a) Edit MyCharacter.h, MyAttributeSet.h, MyDamageExecutionCalculation.h c++ header files. For this example the files are location in /Unreal Projects/MyProject/Source/MyProject/Public.
12b) Change "class INTOTHEARENA_API" -> "class MYPROJECT_API". This needs to be done on all 3 header files. Save all 3 header files.
13) Open UE Editor
14) Launch the new project "MyProject".
15) Compile