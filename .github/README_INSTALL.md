# Installation:

### Install using the installer:
1. Download `<LINK_TO_MOD_ZIP>`
2. Download `<LINK_TO_INSTALLER>`

3. Place both files in the same folder (_no need to copy them to your game folder_) and run `GTAIV-Remix-CompMod-Installer.exe` 
4. Use the File Dialog to select your `GTAIV.exe` which is located in your GTAIV install folder
5. If this is your first time installing, the installer will ask if you want to install a custom Fork of [FusionFix](https://github.com/xoxor4d/GTAIV.EFLC.FusionFix.RTXRemix/releases/tag/4)
  If you already have FusionFix installed, it's definitely recommended to install this because the original, unmodified version has a few incompatibilities with RTX Remix. If you do not have FusionFix installed, you are free to choose. It's not a requirement.
6. Make sure that you remove all custom launch arguments for GTAIV in Steam (if you have any set)

<br>

### OR Install manually (no need to do this if you've used the installer):
1. Download `<LINK_TO_MOD_ZIP>`

3. Open the zip and extract all files contained inside the `GTAIV-Remix-CompatibilityMod` folder into your GTAIV directory (next to the `GTAIV.exe`). Overwrite all when prompted.
4. If you want to use FusionFix or have it installed already, it's definitely recommended to install my custom fork of [FusionFix](https://github.com/xoxor4d/GTAIV.EFLC.FusionFix.RTXRemix/releases/tag/4) because the original, unmodified version has a few incompatibilities with RTX Remix.  
You can find the files inside `_installer_options/FusionFix_RTXRemixFork`. Extract the `plugins` & `update` into your GTAIV directory and override any existing files.

<br>

## Usage and general Info
- Run the game like normal or use the provided batch files (mentioned further down) if you notice heavy stuttering.

- It's recommended to adjust distance and quality sliders in the GTA4 **graphic options** (higher values => earlier CPU bottleneck).
   Try 30 for view distance and 50 for quality and adjust from there. The first launch might cause problems, simply re-try a second time.

  > Press Alt + X to open the Remix menu
  > Press F4 to open the Compatibility Mod menu

<br>

## Troubleshooting / Tips

- **Running Windowed**
  Open the `commandline.txt` in the main game folder and add `-windowed`
  
  **If using FF:** Adjust the Borderless setting in the game options to your liking  
  (`plugins/GTAIV.EFLC.FusionFix.cfg` -> `BorderlessWindowed = 0/1`)

<br>

- **Forcing a Resolution (if something goes wrong with resolution selection)**
  Either go to your GTAIV folder and open `rtx_comp/game_settings.toml` (after running the game once)
  > - Set `manual_game_resolution_enabled` to `true`
  > - Adjust the resolution using `manual_game_resolution = [ .. ]`
  
  OR Open the `commandline.txt` in the main game folder and add `-width 1920` and `-height 1080` (adjust for your resolution)

<br>

- **Crashing on startup or similar**
  Please try the following before creating an issue on GitHub:
  1) Make sure that you try the mod on a fresh, clean install - do not install FusionFix before installing the mod
  2) Try to install the game in a path that is not inside `Program Files`
  3) Make sure that you have no custom launch arguments for GTAIV defined in steam

<br>

## Issues / Performance / Tweaks
- **Stuttering**
  If you notice heavy stuttering, launch the game with the included `_LaunchWithProcessorAffinity_2Cores_GTA4.bat`
  Doing this will assign 2 cores to GTA4 and the rest to Remix. 
  If you want a 50/50 split, use `_LaunchWithProcessorAffinity_Half_GTA4__Half_Remix.bat`

- **Lower Pathtracing settings**
  Open the Remix menu by pressing `Alt + X` and use `Graphics Settings Menu` at the top. 
  Switch to the `Graphics` tab and adjust the `Graphics Preset` dropdown to adjust various quality settings

- **Alpha Settings for Trees**
  Open the CompMod menu by pressing `F4` and open the `Rendering Related Settings` container under the `Game Settings` tab. 
  Increasing the `Tree Alpha Cutout Value` value will improve performance but will make leafs look more blocky.
  
<br>

  ## Notes
  - The release includes a custom remix runtime build that contains a few necessary changes.
     Current active branch is this one: https://github.com/xoxor4d/dxvk-remix/tree/game/gta4_rebase5


