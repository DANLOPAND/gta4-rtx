<h1 align="center">Grand Theft Auto IV - RTX Remix Compatibility Mod</h1>

<br>

<div align="center" markdown="1"> 

Made specifically for NVIDIA's [RTX Remix](https://github.com/NVIDIAGameWorks/rtx-remix).  
Compatible with __Grand Theft Auto IV: The Complete Edition (1.2.0.59)__ 

If you want to support my work,   
consider buying me a [Coffee](https://ko-fi.com/xoxor4d) or by becoming a [Patreon](https://patreon.com/xoxor4d)


Feel free to join the discord server: https://discord.gg/FMnfhpfZy9

<br>

![img](.github/img/overview.jpg)

</div>

<div align="center" markdown="1"> 

### Table of Contents

__[Overview](#overview)__  
__[Installing](#installing)__   
__[Uninstalling](#uninstalling)__   
__[Usage](#usage)__   
__[Compiling](#compiling)__   

<br>

</div>


## Overview
<div align="center" markdown="1"> 

First and foremost, __this is not a remaster__. It is a mod that allows the game to be modded with NVIDIA's 
[RTX Remix](https://github.com/NVIDIAGameWorks/rtx-remix)  
It does __NOT__ come with enhanced assets. That means no PBR materials nor higher quality meshes.

<br>

There are obvious drawbacks, and things that will not work with such a new title, don't expect this to be perfect.  
RTX Remix has a certain overhead because of how it works and intercepts the game's draw calls.  

You'll experience CPU bottlenecks because of the amount of detailed meshes the game is rendering,  
which means that the performance you'll see in certain places is not entirely due to pathtracing.  

The mod comes with a custom [Remix Runtime](https://github.com/xoxor4d/dxvk-remix/tree/game/gta4_rebase6) required for a few game specific features   
and with [Ultimate ASI Loader](https://github.com/ThirteenAG/Ultimate-ASI-Loader/releases/tag/v9.0.0) to load the Compatibility Mod itself. 

</div>


<br>

###### The good:  
- Most objects rendered via fixed function to increase performance
- Cascaded anti culling of static objects (__wip__)
- All game lights (including the sun) are translated to remix lights
- Ability to create overrides for translated game lights (change position, color, intensity etc.)
- Vehicles now feature two headlights and two rear lights instead of a single, centered ones
- Dynamic emissive surfaces work (vehicle lights, building-windows, shops etc.)
- Dynamic wetness that works similar to the original game  
  (only outdoors and with falloff on angled surfaces + raindroplets/impacts)
- Raindroplets on vehicles and character clothing
- Working vehicle dirt and livery
- Modification of remix runtime variables based on current timecycle settings
- Mobilephone works (but it is 3D and currently scales with the camera fov)
- Modified vertex shaders (based on FusionFix) so that remix is able to capture surface normals
- Ability to spawn unique _marker_ meshes that can be hidden based on distance, weather or time of day (these can be used to attach remix replacements or scene lights)
- Screenshot Mode and FreeCam Mode
- FusionFix compatible (custom fork: [GTAIV.EFLC.FusionFix.RTXRemix](https://github.com/xoxor4d/GTAIV.EFLC.FusionFix.RTXRemix))
- Many many tweakable settings via the in-game __F4__ menu
- A few PBR materials
- Installer

###### The bad:
- CPU Bottlenecked (reduce draw distance / quality)
- Mobilephone UI looks a little broken
- Anti-Culling is not perfect yet
- TV's are not working
- No blood on peds

<br>
<br>

<div align="center" markdown="1"> 

![img](.github/img/01.jpg)
![img](.github/img/02.jpg)
</div>

<br>

## Installing
- Grab the latest [Release](https://github.com/xoxor4d/gta4-rtx/releases) and follow the instructions found there


<br>

## Uninstalling
- Deleting the `d3d9.dll` and `a_gta4-rtx.asi` should be enough
- Re-install the official FusionFix mod if you used the custom Fork

<br>
<br>

## Usage
- Run the game like normal
- Press `F4` to open the in-game gui for some compatibility tweaks or debug settings
- If you notice heavy stuttering, launch the game with the included `_LaunchWithProcessorAffinity_2Cores_GTA4.bat`.  
  Doing this will assign 2 cores to GTA4 and the rest to Remix. If you want a 50/50 split, use `_LaunchWithProcessorAffinity_Half_GTA4__Half_Remix.bat`

<br>

> [!TIP]  
> **Troubleshooting / in-depth guides, usage information and remix runtime changes can be found in the [[Wiki]](https://github.com/xoxor4d/gta4-rtx/wiki)**

<br>

## Compiling
- Clone the repository `git clone --recurse-submodules https://github.com/xoxor4d/gta4-rtx.git`
- Optional: Setup a global path variable named `GTA4_ROOT` that points to your game folder (where GTAIV.exe is located)
- Run `generate-buildfiles_vs22.bat` to generate VS project files
- Compile the mod
- If you did not setup the global path variable:  
  rename `gta4-rtx.dll` to `a_gta4-rtx.asi` and copy it into your game directory (next to `GTAIV.exe`) 
- If you have not installed a release build before, make sure to copy everything within the `assets` folder into the game directory

<br>
<br>

##  Credits
- [NVIDIA - RTX Remix](https://github.com/NVIDIAGameWorks/rtx-remix)
- [People of the showcase discord](https://discord.gg/j6sh7JD3v9) - especially the nvidia engineers ✌️
- [Dear ImGui](https://github.com/ocornut/imgui)
- [imgui-blur-effect](https://github.com/3r4y/imgui-blur-effect)
- [minhook](https://github.com/TsudaKageyu/minhook)
- [toml11](https://github.com/ToruNiina/toml11)
- [miniz](https://github.com/richgel999/miniz)
- [Ultimate-ASI-Loader](https://github.com/ThirteenAG/Ultimate-ASI-Loader)
- [AssaultKifle47](https://github.com/akifle47)
- [FusionFix](https://github.com/ThirteenAG/GTAIV.EFLC.FusionFix)
- [FusionShaders](https://github.com/Parallellines0451/GTAIV.EFLC.FusionShaders)
- [Rage-Shader-Editor](https://github.com/ImpossibleEchoes/rage-shader-editor-cpp)
- [IV-SDK](https://github.com/Zolika1351/iv-sdk/)
- [IV-SDK-DotNet](https://github.com/ClonkAndre/IV-SDK-DotNet)
- [DayL](https://www.gtainside.de/de/user/falcogray)
- [Entity](https://www.youtube.com/@paprykszadolowski8796)
- [Gabdeg](https://www.youtube.com/@gabdeg793)
- [Hemry](https://www.youtube.com/@Hemry81)
- All 🍓 Testers

<div align="center" markdown="1"> 

And of course, all my fellow Ko-Fi and Patreon supporters  
and all the people that helped along the way!

<br>

![img](.github/img/03.jpg)

</div>
