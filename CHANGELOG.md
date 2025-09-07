# Changelog
All notable changes to this project will be documented in this file.

## [0.2.1] - 2025-09-07

### :cat: Note
- Updated CHANGELOG for v0.2.0 release.
- Added changelog generation script which relies on git-cliff; provided my personal template.
	 - Updated changelog.
- Update README.md with a note about the changelog template's use.
- Updated some loose ends in the changelog template (hard-coded repo URL). There was no way around the postprocessor hard-coded repo URL but every other instance is fixed.


### :sparkles: Fun Facts
- 6 commit(s) contributed to the release.
- 20 day(s) passed between the first and last commit.
- 0 commit(s) parsed as conventional.
- 0 linked issue(s) detected in commits.
- 20 day(s) passed between releases.

## [0.2.0] - 2025-08-18

### :rocket: New Features
	 - Added gitignore and gitattributes template files for Unity.

### :cat: Note
- Adding v0.1.5 change log.
- Added the JM_TODO gist link.
- Updated all of the standard shader's PBR data samplers (with the exception of the albedo texture -- and the subsurface color texture, though that's not in this shader anyway) to be sampled linearly because, as it turns out, even AO maps shouldn't be sampled in sRGB space (which I was always kind of on the fence about, but I finally took a stand on IT'S LINEAR OKAY).
- Added an old version of my Steel Hunters nevada terrain node graph (using World Machine and GeoGlyph) in case anyone was curious on how it was generated.
- Since not everyone has access to world machine/geoglyph, I added some of the outputs: the height map, layer output, and high-poly mesh output (which aren't *directly* in sync with the WM graph, but it's close-ish). Unfortunately, I wasn't able to track down the mesh's albedo/normal map output and building the graph is... Time consuming. But, if I find idle time, I'll rebuild everything and upload those too.
- Added a Maya python script to center all objects; this assumes a Z-up scene (and that all selected objects should be placed above the origin on Z with their pivots at the bottom of the object (the origin).
- Few fixes to the maya object centering script.
- Added a link to the blog post about this repo to the main README .
- Added a link to the assets and assets/terrain folders to the main page's README.
- Tool for converting commit info JSON between two formats for Trent
- Create README.md for commit counter
- Cleaned up some of the older Visual Studio extensions for build timers and status bars with file paths and added extensions to pop up a confirmation dialog if: you select rebuild, clean, or try to build your project while UE4 is running (I hate hot reload). NOTE: All of these require VCmd to use.
- Update issue templates
- UE4 build times are really, really long sometimes. So I made templates.
- Created pull request template... Well, not really.
- Requiring two spaces after a character to mandate a line break is dumb.
- Auto detect UTF-8 vs UTF-16 encoding
- Fix typo for one of the BOM signatures
- Add support for -o/--output (specify output file)
- Update README.md for commit_counter
- Adding the meshes/content that are seen... basically everywhere (courtesy of Morgan McGuire). Stanford bunny (and cornell box and sponza and etc).
- Added a powershell cmdlet for finding file conflicts in a git merge and calling 'git mergetool' on them (individually). I have no idea how well this works, but I know it was a thing that was pending in the repo folder so I'm adding it.
- Added a debug drawing library which is, mostly, a wrapped around UE4 functionality, but has some other features (and a setup for consistently-colored debug draws, which I've found stupidly useful) that I'll eventually expand on. Primarily, the line trace drawing method is the love of my life. Also: I removed all other source code; it was either out-of-date, useless, or broken.
- Bump electron from 1.8.4 to 9.4.0 in /joy-create
- Bumps [electron](https://github.com/electron/electron) from 1.8.4 to 9.4.0.
	 - [Release notes](https://github.com/electron/electron/releases)
	 - [Changelog](https://github.com/electron/electron/blob/main/docs/breaking-changes.md)
	 - [Commits](https://github.com/electron/electron/compare/v1.8.4...v9.4.0)
- ---
- updated-dependencies:
	 - dependency-name: electron
-   dependency-type: direct:development
- ...
- dependabot[bot] <support@github.com>
- Bump npm from 5.8.0 to 6.14.6 in /joy-create
- Bumps [npm](https://github.com/npm/cli) from 5.8.0 to 6.14.6.
	 - [Release notes](https://github.com/npm/cli/releases)
	 - [Changelog](https://github.com/npm/cli/blob/v6.14.6/CHANGELOG.md)
	 - [Commits](https://github.com/npm/cli/compare/v5.8.0...v6.14.6)
- ---
- updated-dependencies:
	 - dependency-name: npm
-   dependency-type: direct:production
- ...
- dependabot[bot] <support@github.com>
- Bump three from 0.89.0 to 0.125.0 in /joy-create
- Bumps [three](https://github.com/mrdoob/three.js) from 0.89.0 to 0.125.0.
	 - [Release notes](https://github.com/mrdoob/three.js/releases)
	 - [Commits](https://github.com/mrdoob/three.js/commits)
- ---
- updated-dependencies:
	 - dependency-name: three
-   dependency-type: direct:production
- ...
- dependabot[bot] <support@github.com>
- Removing joy-create given the amount of vulnerabilities and issues.
- Updated README to note maintenance status. Namely that it isn't being maintained.
- Added a Powershell one-liner for filename substring replacement.
- Added oren-nayer HDRP shader for Unity.
- Added a Tera Template for generating changelogs with git-cliff. It doesn't adhere to the keepachangelog conventions very well but I'm okay with that.
- Updated README.md with unity link and replaced joymachine-public references.
- Updated README.md with updated repo url.
- Update README.md with information on the git-cliff template.
- Cleanup pass on the entire repo to prepare it for more active support.
	 - Updated git templates; git attributes and git ignore were updated for UE and have a Unity template now too.
	 - Updated gitconfig template.
	 - Updated the actual
	 - Deprecated the UE4 asset library and the paltry single source file set that was there.
- 631bee


### :sparkles: Fun Facts
- 79 commit(s) contributed to the release.
- 2691 day(s) passed between the first and last commit.
- 3 commit(s) parsed as conventional.
- 0 linked issue(s) detected in commits.
- 2691 day(s) passed between releases.

## [0.1.5] - 2018-04-06

### :cat: Note
- Fixed the broken-as-hell duplicate file logging PowerShell script.
- Added UObject-pooling interface and pool class functionality to ue4-source (NOTE: pool does not auto-add object instances if the pool fails to find a valid object; this is later work).
- Cleaned up the UE4 base README document, added link to enum gist.
- Er, misleading heading.
- Should probably remove the dependence on steelhunters.h as I'm willing to bet most people don't have that header.
- Prevent an infinite loop when deactivating a pooled object. Made IObjectPooled::Deactivate non-virtual. Reverted some code which assumed IObjectPooled was a UObject derivative.
- Added an ::Empty method to the object pooling system because... That's helpful. Argument to separate out instances that are still active. Removed auto-execution of IObjectPooled::Activate, as that's more useful to manually call. Added safety checks and asserts.
- Why is it that the small, general classes are always the most nitpicky and complex. Renamed IObjectPooled::Destroy to ::DestroyInstance, so it doesn't conflict with actors/components' ::Destroy.
- UE4 didn't like my interface not inheriting from UObject so I did awful things to make the Unreal Header Tool believe that this was a legit setup (I crashed UHT a couple times). Anyway, pool should work now.
- Added UObjectPool::GenerateName for pool object creation time help.
- I swear, this object pooling thing was so much prettier and simpler when I started it. UHT/UE4 do not make non-UObject interfaces easy to deal with whatsoever.
- The UE4 buildchain really likes piecemealing out those errors one-by-one, huh.
- Fixed an occasional first-run crash with the pooling system.
- Updating metallic and metallic-clear coat shaders.
- More object pooling fixes.
- Very, very rough first pass anamorphic lens flare postprocessing effect (intended to be integrated into PostProcessing.cpp).
- Added IObjectPooling for any object using a pool to be able to override an instantiation method that will be used by the object pool for creating new instances.
- Added some information on the anamorphic lens flare code.
- I suck at formatting.
- Updated the metallic clearcoat shader with the customized fresnel term; cleanup on standard shader and tossed an alpha-masked standard shader in.
- Updates to the standard shader.
- Initial update to Unreal Engine 4 information and resources page.
- This is not a complete set of changes, but I needed to test some GitHub markdown syntax (it's a bit different than the standard syntax) on a live document.
- Setup the page index.
- GitHub markdown lists are a pain in the ass.
- Updating the license copyright year.
- Separating out asset information and "documentation" (lol) from the UE4 megafile.
- Removed the asset library information into its own page; general UE4 info/resources-only here now.
- An extensive UE4 infostorm update on content creation (material-focused atm), rendering/shading skeleton, and graphics debugging.
- Forgot about the miscellaneous code snippets index link.
- RenderDoc section needed a lower heading.
- Updating markdown style to Ulysses'.
- Yes, I'm dumb.
- Updated UE4 project conventions (todo: source asset conventions).
- Revamped the markdown for this page so I didn't have to commit every stupid change individually.
- Rename familyRoot to outputRoot, filenameRoot to inputRoot; closes #1
- Convert some debug print statements to Python3-style
- Updates to the object pooling system (given some issues in the use of it with my test case).
- Updated standard shader and added a POM shader (with *roughly* equivalent features to the standard shader).
- Overhauled the speedtree foliage shader in conjunction with the new speedtree for UE4. Also fixed some albedo tinting/coloring issues in the standard shader. Tweaks to the standard POM shader.
- Replaced m_shader_foliage_speedtree with m_shader_speedtree_foliage (along with some minor tweaks). Added m_shader_speedtree_foliage_body for foliage with wrapping textures (mostly bark/stems/etc.).
- Added procedural street/intersection tool plugin (from @ydrive).
- From @ydrive: https://github.com/ydrive/StreetArch
- Added Joy Create with notes to the UE4 README.
- Updated Joy Create in the README.
- Updated the README.
- Updates to the speedtree shaders based on iteration (after iteration (after iteration)) on Steel Hunters.
- Added a note on the unreliability of the object pooling code and made a Little Red Riding Hood metaphor for some reason.
- Rewrote the speedtree foliage shaders and added a new one for speedtree billboards. They are wonderful now.
- More updates to the speedtree shaders; some fixes here and there and also made the per-instance fade parameter a static switch option.
- Adding a first-pass at some rough material layers and blending functionality (based on car paints). It's... Not right yet, but it's something.
- Miscellaneous blend and layer fixes (though something still isn't adding up. Literally and figuratively.
- Setting up a proper procgen system (l-system, turtle placement, and first-order shapes). Also moving over to three.js. Nothing about this commit will work at all right now.
- Updated the app, added webpack-dashboard telemetry support.
- Refactored files and filenames to make more sense; worked to get the old page working properly with the viewport/editor.
- Reworked the entire SHEBANG to be a bit more properly setup (except the mad dash to get the viewport working at the end). Got the three.js viewport working even though it's just pitch black. The editor pane isn't coorperating yet, but that's not far off.
- Removing ace from the vendors/ subdirectory (it's handled in the install/postinstall step now). Added rimraf and vendor-copy to package.json.
- Got everything working slightly better than it did in the last check-in (less horrifying hacks).
- Reworked/styled/themed the electron window a bit, refactored things. Though I'm not sure what I refactored them into since I'm still figuring out what the hell is happening.
- WHITESPACE CLEANING WOOOOO.
- Started maybe figuring more things out and structuring appropriately?
- Alternate electron setup for joy-create since, hey, my experience with javascript/node is entirely HEY WHAT DOES THIS DO *PRESS ENTER*.
- About two minutes worth of work on getting the new structure to work.
- More of me trying to figure out the syntax here.
- YES. I FINALLY FIGURED OUT WHAT SYNTAX I WAS SUPPOSED TO USE.
- Apparently had joy-create files I never checked in.
- joy-create work; removed codemirror in favor of monaco-editor, updated gulp to v4, cleaned up dependencies, started removing npm run-scripts in favor of proper gulpfile and task setup. Broke a lot of things.
- Add done-signalling to devstart, but something else is holding it up
- Watch task bails out after setting up watches, so devstart can complete, although the gulp task will keep running since the watches themselves haven't ended
- Merged feature/joy-create-v0.1 as the one in master is woefully out of date and the feature branch was stable last I checked (the old master branch version was vulnerable to a security vulnerability).
- Er. Properly addressed the security vulnerability in joy-create since, hey, it's handy to run npm update.
- ... Okay. Actually fixed it this time.
- Update package-lock
- More potential security fixes maybe maybe?
- Updating silly things because.
- Okay. Maybe this time the security warning box will go away forever.
- Updated NPM and then updated every package except gulp-watch's own reliance on gulp-util which gulp says should be removed.
- Adding some new material functions: albedo tinting, three types of normal blending operations.
- Updating all foliage shaders (standard and speedtree-related ones), updated material functions, updated the environment simulation material parameter collection, added some additional material functions, and added all generic textures for material placeholders.
- Added a bunch of older-but-since-lost procedural water shaders along with gerstner wave/wave cluster generation functions (all use UE4 engine content for textures, so hopefully no errors on that front now). Also removed some deprecated procedural shaders (including the former bad water one).
- Fixed some wind issues with the speedtree shaders; added static switch support in the standard shader for UV coord sets 1 and 2 (with 0 being the default, natch).
- jshint added for linting, packages cleaned up
- Updating README for some clarifications.


### :sparkles: Fun Facts
- 91 commit(s) contributed to the release.
- 255 day(s) passed between the first and last commit.
- 0 commit(s) parsed as conventional.
- 0 linked issue(s) detected in commits.
- 122 day(s) passed between releases.

## [0.1.1] - 2017-12-05

### :rocket: New Features
	 - Adding updated UE4 assets (NOTE: created by 4.18; 4.17 assets are archived in a subfolder) and a PowerShell script for finding duplicate files recursively from a working directory.

### :cat: Note
- v0.1.0 changelog.
- clarifying the state of joy-create a bit better.
- Added a template ConsoleVariables.ini file to show what we use internally.
- Finally starting to list out research papers. Links forthcoming once I track down original sources.
- Added the RESEARCH_PAPERS.md link.
- Fixing note display.
- Added Atrix256's random source code repo to the resources list.
- Added a note that the UE4 assets are saved from UE 4.17.2, so anything lower won't jive.
- Updated base repo README with change information for the UE4 assets.
- Removed the tools subdirectory as the kernel generator was not anywhere near properly conceived (my fault).
- Updated the CHANGELOG for the v0.1.1 release.


### :sparkles: Fun Facts
- 13 commit(s) contributed to the release.
- 56 day(s) passed between the first and last commit.
- 0 commit(s) parsed as conventional.
- 0 linked issue(s) detected in commits.
- 56 day(s) passed between releases.

## [0.1.0] - 2017-10-10

### :cat: Note
- Fixed the awful mf_normal_lerp. Updated mf_wind (and mpc_world).
- Added a whole bunch of fancy new aliases to the gitconfig template.
- Added get-extension-files to list all files of a given extension in a directory. Updated the sample powershell profile with some new commands.
- Ignore .DS_Store on OSX.
- Added an .inputrc for OSX/bash that make terminals... Much better.
- Removed specific folder filters for LFS; now blanket applied to UASSET/UMAP files.
- Added an 's' alias for showing a colored, minimal git status
- Stupid vi. No one likes vi.
- Attribution is nice sometimes.
- Fixed the wonky tabs going on, what the hell, git.
- Updating README with new aliases and colors/decorators.
- Removed `git cl` as I didn't want to include things with dependencies.
- Moved jmkernels up a directory; renamed it to joy-kernels.
- Added alias `holy-fsck`. What? It's useful.
- Documenting holy-fsck.
- Updating the gitattributes template with DLL/PDB/LIB.
- Added article link.
- Create CODE_OF_CONDUCT.md
- Create CONTRIBUTING.md
- Updating foliage and standard (+ standard metallic) master materials.
- Added generate-changelog.ps1 and updated README.
- Moved generate-changelog.ps1 to the scripts folder. Like it should have been initially. If I wasn't dumb.
- Moved generate-changelog.ps1 to scripts-standalone subdirectory (scripts subdirectory is automatically searched/executed at startup if you use the existing powershell profile from this repo.
- Added a powershell alias for printing out a file directory tree to a text file (it's handy, okay); needs a text file as its one and only argument.
- Added TAA sharpening link.
- Apparently mentions aren't a thing in READMEs.
- Added the beginning of a new foliage master shader; it's... Costly. Maybe decent ideas, but not practical yet.
- Starting a general resources file; currently only has one link.
- Much, much more handy way to get environment variables (yay table wrapping).
- Added syntax highlighting for shaders links.
- Added a link to the RESOURCES.md page in the README.
- Moved joy-create back to the repo root as I want to give it some love during these painful SH build times lately.
- Added a material function for angle-based roughness; while this functionality exists at a high-level in UE 4.17, it doesn't allow for any customization.
- Updated the speedtree master shader as well as the master triplanar one.
- Updated the RESOURCES page with some additional links.
- Added email address.
- Adding information about joy-create.
- Actually for-realsies updating the README to reflect the state of the repo.
- Megascan assembler has a dynamic strategy now and no longer generates RGBA textures because those were huge.
- Update readme for clarification
- Forgot to add the trailing _ on the suffixes
- Updated a bunch of material functions: mf_truesky_directional_light (which is actually a light function material), mf_luminance, mf_radial_color, and mf_radial_normal.
- Added support for opacity masks and subsurface (translucency) textures -- each as their own output. I haven't tested these changes yet, but what could go wrong.
- Good news: I was right to think I was stupid and kind of fixed the python script (I don't know python). Bad news: normal maps are wonked up on output and the powershell script is all sorts of sideways bad.
- Fixed the albedo/normal maps being output as single-channel images. BOOSH. I KNOW PYTHON NOW.
- Balls. Forgot about the transparency/SSS map.
- I also apparently REALLY wanted to handle the normal map case an extra time or so.
- Completely rewrote the master foliage shader, the material functions for handling wind, added an easy hue-saturation-luminance material function, and other fun stuff. Will document later.
- Added a 'deletebranch' alias to help with deleting branches locally and remotely.
- Add 'rgb' texture build rule, which just copies the texture using the do_saveas function
- Remove references to 'normal' in the do_saveas code, since it is not just for normals
- ue4 asset folder hierarchy will invalidate old assets. Changed the hierarchy/naming conventions for the ue4 asset folder. Which also means that I had to delete all the old assets or they would no longer work anyway, so this is kind of a clean slate. On the plus side: lot's of new, rewritten, tweaked, improved, added etc. material functions/shaders/etc.


### :sparkles: Fun Facts
- 58 commit(s) contributed to the release.
- 77 day(s) passed between the first and last commit.
- 1 commit(s) parsed as conventional.
- 0 linked issue(s) detected in commits.
- 79 day(s) passed between releases.

## [0.0.7] - 2017-07-23

### :cat: Note
- Adding some additional powershell scripts/aliases.
- Add PNG compressor script.
- Added gamedev mentors link.
- Added @ishansharma callout proper.
- I think I used the @ishansharma and @trentpolack mentions right this time? Maybe.
- Fixed mentor link to go to the site, not the repo for the site.
- Adding v0.0.7 changelog.


### :sparkles: Fun Facts
- 7 commit(s) contributed to the release.
- 2 day(s) passed between the first and last commit.
- 0 commit(s) parsed as conventional.
- 0 linked issue(s) detected in commits.
- 18 day(s) passed between releases.

## [0.0.6] - 2017-07-05

### :cat: Note
- Added Vector Field Generator (python), SmearFrame (UE4 material), reorganization.
- Updating README to reflect v0.0.5 repo changes.
- Fix bug that prevented sphere output from ever occurring.


### :sparkles: Fun Facts
- 4 commit(s) contributed to the release.
- 4 day(s) passed between the first and last commit.
- 0 commit(s) parsed as conventional.
- 0 linked issue(s) detected in commits.
- 4 day(s) passed between releases.

## [0.0.5] - 2017-07-01

### :cat: Note
- Renamed scripts/vcmd to scripts/visualstudio. Added an extension to show full path of active file in status bar.
- Updated the sample PowerShell profile with some new alises for counting lines of code in a folder (*.h, *.cpp, *.cs) as well as clipboard manipulation.
- Added section on collision filtering.
- Add script to create copies of PNG files w/ filenames prefixed with their creation time (Windows only)
- Tweaks to python image rename script to use modified date + support JPG/GIF. Moved tools to scripts folder.
- Renamed rename_by_timestamp.py to rename_images_by_timestamp.py
- Improved distance fade material function; fade SSS on foliage over distance.
- Add readme for rename_images_by_timestamp.py
- Updating README to reflect reorganized repo.
- Adding a batch file of limited-usefulness outside our terrain tile export process.
- Moved the kernels app into this repository
- Provide pre-compiled release binary for jmkernels.exe
- Moving .gitignore/attributes from kernel generator into root folder.
- Adding basic JSON serialization utility class (struct-oriented; UObject-based one is... Touchy still).
- Moved kernel generator and joy-create into a tools directory in the root folder.
- Adding v0.0.5 change log.


### :sparkles: Fun Facts
- 17 commit(s) contributed to the release.
- 32 day(s) passed between the first and last commit.
- 0 commit(s) parsed as conventional.
- 0 linked issue(s) detected in commits.
- 32 day(s) passed between releases.

## [0.0.4] - 2017-05-30

### :cat: Note
- Updated CHANGELOG for v0.0.3. I need to remember to do this before the tag.
- Adding stub AWESOME_SOFTWARE.md file. Which I will then fill out on the computer that has the file.
- Filling out AWESOME_SOFTWARE with... good... software?
- Removing dumb line.
- Adding software link to the readme.
- Adding mailmap to fix my name. This probably isn't supposed to be checked in.
- Added a simple overload of USpringArmComponent that can account for more than one ignored actor (the owner).
- Added a VS extension (for VSCMD and the source VB file) for outputting a build time start/end timestamp as well as total time taken.
- Moved the powershell scripts into the scripts folder because... Well. I mean. It makes sense, yeah?
- Updated CHANGELOG.


### :sparkles: Fun Facts
- 10 commit(s) contributed to the release.
- 2 day(s) passed between the first and last commit.
- 0 commit(s) parsed as conventional.
- 0 linked issue(s) detected in commits.
- 3 day(s) passed between releases.

## [0.0.3] - 2017-05-27

### :cat: Note
- Removed "all rights reserved" heading.
- Actually changing the name of the folder in the README like I should have.
- I'm not smart.
- Added an old material-based procedural water and wave generation/rendering asset set.
- Consistency fix in the powershell folder.
- Greatly elaborated on the standard practices and conventions.
- Fixed sub-lists because I'm an idiot.
- Also I'm doing everything possible to continue on my current task.
- Added reference and link to the conventions doc.
- Even more convention updates as I read an awful class.
- General-purpose collision shape set for computing box/sphere/capsule shapes (rather than having to choose a specific one at code-time).
- Fixed up CollisionShapeSet. Added basic blueprintable enum for basic shapes.
- Adding AutoHotkey script for Windows' SnippingTool.
- Added a brief summary on the ue4-source folder.
- Words are hard.


### :sparkles: Fun Facts
- 16 commit(s) contributed to the release.
- 22 day(s) passed between the first and last commit.
- 0 commit(s) parsed as conventional.
- 0 linked issue(s) detected in commits.
- 25 day(s) passed between releases.

[0.2.1]: https://github.com/trentpolack/CALVINBALL/compare/v0.2.0..v0.2.1

[0.2.0]: https://github.com/trentpolack/CALVINBALL/compare/v0.1.5..v0.2.0

[0.1.5]: https://github.com/trentpolack/CALVINBALL/compare/v0.1.1..v0.1.5

[0.1.1]: https://github.com/trentpolack/CALVINBALL/compare/v0.1.0..v0.1.1

[0.1.0]: https://github.com/trentpolack/CALVINBALL/compare/v0.0.7..v0.1.0

[0.0.7]: https://github.com/trentpolack/CALVINBALL/compare/v0.0.6..v0.0.7

[0.0.6]: https://github.com/trentpolack/CALVINBALL/compare/v0.0.5..v0.0.6

[0.0.5]: https://github.com/trentpolack/CALVINBALL/compare/v0.0.4..v0.0.5

[0.0.4]: https://github.com/trentpolack/CALVINBALL/compare/v0.0.3..v0.0.4

[0.0.3]: https://github.com/trentpolack/CALVINBALL/compare/v0.0.2..v0.0.3

<!-- generated by git-cliff -->
