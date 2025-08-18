# Changelog

All notable changes to this project will be documented in this file.


## [0.2.0] - 2025-08-18


### :rocket: New Features

* - Added gitignore and gitattributes template files for Unity.- Added gitignore and gitattributes template files for Unity.


### :cat: Note

* Cleanup pass on the entire repo to prepare it for more active support.Cleanup pass on the entire repo to prepare it for more active support.
* - Updated git templates; git attributes and git ignore were updated for UE and have a Unity template now too.- Updated git templates; git attributes and git ignore were updated for UE and have a Unity template now too.
* - Updated gitconfig template.- Updated gitconfig template.
* - Updated the actual- Updated the actual
* - Deprecated the UE4 asset library and the paltry single source file set that was there.- Deprecated the UE4 asset library and the paltry single source file set that was there.
* 631bee631bee
* Update README.md with information on the git-cliff template.Update README.md with information on the git-cliff template.
* Updated README.md with updated repo url.Updated README.md with updated repo url.
* Updated README.md with unity link and replaced joymachine-public references.Updated README.md with unity link and replaced joymachine-public references.
* Added a Tera Template for generating changelogs with git-cliff. It doesn't adhere to the keepachangelog conventions very well but I'm okay with that.Added a Tera Template for generating changelogs with git-cliff. It doesn't adhere to the keepachangelog conventions very well but I'm okay with that.
* Added oren-nayer HDRP shader for Unity.Added oren-nayer HDRP shader for Unity.
* Added a Powershell one-liner for filename substring replacement.Added a Powershell one-liner for filename substring replacement.
* Updated README to note maintenance status. Namely that it isn't being maintained.Updated README to note maintenance status. Namely that it isn't being maintained.
* Removing joy-create given the amount of vulnerabilities and issues.Removing joy-create given the amount of vulnerabilities and issues.
* Bump three from 0.89.0 to 0.125.0 in /joy-createBump three from 0.89.0 to 0.125.0 in /joy-create
* Bumps [three](https://github.com/mrdoob/three.js) from 0.89.0 to 0.125.0.Bumps [three](https://github.com/mrdoob/three.js) from 0.89.0 to 0.125.0.
* - [Release notes](https://github.com/mrdoob/three.js/releases)- [Release notes](https://github.com/mrdoob/three.js/releases)
* - [Commits](https://github.com/mrdoob/three.js/commits)- [Commits](https://github.com/mrdoob/three.js/commits)
* ------
* updated-dependencies:Updated-dependencies:
* - dependency-name: three- dependency-name: three
*   dependency-type: direct:productionDependency-type: direct:production
* ......
* dependabot[bot] <support@github.com>Dependabot[bot] <support@github.com>
* Bump npm from 5.8.0 to 6.14.6 in /joy-createBump npm from 5.8.0 to 6.14.6 in /joy-create
* Bumps [npm](https://github.com/npm/cli) from 5.8.0 to 6.14.6.Bumps [npm](https://github.com/npm/cli) from 5.8.0 to 6.14.6.
* - [Release notes](https://github.com/npm/cli/releases)- [Release notes](https://github.com/npm/cli/releases)
* - [Changelog](https://github.com/npm/cli/blob/v6.14.6/CHANGELOG.md)- [Changelog](https://github.com/npm/cli/blob/v6.14.6/CHANGELOG.md)
* - [Commits](https://github.com/npm/cli/compare/v5.8.0...v6.14.6)- [Commits](https://github.com/npm/cli/compare/v5.8.0...v6.14.6)
* ------
* updated-dependencies:Updated-dependencies:
* - dependency-name: npm- dependency-name: npm
*   dependency-type: direct:productionDependency-type: direct:production
* ......
* dependabot[bot] <support@github.com>Dependabot[bot] <support@github.com>
* Bump electron from 1.8.4 to 9.4.0 in /joy-createBump electron from 1.8.4 to 9.4.0 in /joy-create
* Bumps [electron](https://github.com/electron/electron) from 1.8.4 to 9.4.0.Bumps [electron](https://github.com/electron/electron) from 1.8.4 to 9.4.0.
* - [Release notes](https://github.com/electron/electron/releases)- [Release notes](https://github.com/electron/electron/releases)
* - [Changelog](https://github.com/electron/electron/blob/main/docs/breaking-changes.md)- [Changelog](https://github.com/electron/electron/blob/main/docs/breaking-changes.md)
* - [Commits](https://github.com/electron/electron/compare/v1.8.4...v9.4.0)- [Commits](https://github.com/electron/electron/compare/v1.8.4...v9.4.0)
* ------
* updated-dependencies:Updated-dependencies:
* - dependency-name: electron- dependency-name: electron
*   dependency-type: direct:developmentDependency-type: direct:development
* ......
* dependabot[bot] <support@github.com>Dependabot[bot] <support@github.com>
* Added a debug drawing library which is, mostly, a wrapped around UE4 functionality, but has some other features (and a setup for consistently-colored debug draws, which I've found stupidly useful) that I'll eventually expand on. Primarily, the line trace drawing method is the love of my life. Also: I removed all other source code; it was either out-of-date, useless, or broken.Added a debug drawing library which is, mostly, a wrapped around UE4 functionality, but has some other features (and a setup for consistently-colored debug draws, which I've found stupidly useful) that I'll eventually expand on. Primarily, the line trace drawing method is the love of my life. Also: I removed all other source code; it was either out-of-date, useless, or broken.
* Added a powershell cmdlet for finding file conflicts in a git merge and calling 'git mergetool' on them (individually). I have no idea how well this works, but I know it was a thing that was pending in the repo folder so I'm adding it.Added a powershell cmdlet for finding file conflicts in a git merge and calling 'git mergetool' on them (individually). I have no idea how well this works, but I know it was a thing that was pending in the repo folder so I'm adding it.
* Adding the meshes/content that are seen... basically everywhere (courtesy of Morgan McGuire). Stanford bunny (and cornell box and sponza and etc).Adding the meshes/content that are seen... basically everywhere (courtesy of Morgan McGuire). Stanford bunny (and cornell box and sponza and etc).
* Update README.md for commit_counterUpdate README.md for commit_counter
* Add support for -o/--output (specify output file)Add support for -o/--output (specify output file)
* Fix typo for one of the BOM signaturesFix typo for one of the BOM signatures
* Auto detect UTF-8 vs UTF-16 encodingAuto detect UTF-8 vs UTF-16 encoding
* Requiring two spaces after a character to mandate a line break is dumb.Requiring two spaces after a character to mandate a line break is dumb.
* Created pull request template... Well, not really.Created pull request template... Well, not really.
* Update issue templatesUpdate issue templates
* UE4 build times are really, really long sometimes. So I made templates.UE4 build times are really, really long sometimes. So I made templates.
* Cleaned up some of the older Visual Studio extensions for build timers and status bars with file paths and added extensions to pop up a confirmation dialog if: you select rebuild, clean, or try to build your project while UE4 is running (I hate hot reload). NOTE: All of these require VCmd to use.Cleaned up some of the older Visual Studio extensions for build timers and status bars with file paths and added extensions to pop up a confirmation dialog if: you select rebuild, clean, or try to build your project while UE4 is running (I hate hot reload). NOTE: All of these require VCmd to use.
* Create README.md for commit counterCreate README.md for commit counter
* Tool for converting commit info JSON between two formats for TrentTool for converting commit info JSON between two formats for Trent
* Added a link to the assets and assets/terrain folders to the main page's README.Added a link to the assets and assets/terrain folders to the main page's README.
* Added a link to the blog post about this repo to the main README .Added a link to the blog post about this repo to the main README .
* Few fixes to the maya object centering script.Few fixes to the maya object centering script.
* Added a Maya python script to center all objects; this assumes a Z-up scene (and that all selected objects should be placed above the origin on Z with their pivots at the bottom of the object (the origin).Added a Maya python script to center all objects; this assumes a Z-up scene (and that all selected objects should be placed above the origin on Z with their pivots at the bottom of the object (the origin).
* Since not everyone has access to world machine/geoglyph, I added some of the outputs: the height map, layer output, and high-poly mesh output (which aren't *directly* in sync with the WM graph, but it's close-ish). Unfortunately, I wasn't able to track down the mesh's albedo/normal map output and building the graph is... Time consuming. But, if I find idle time, I'll rebuild everything and upload those too.Since not everyone has access to world machine/geoglyph, I added some of the outputs: the height map, layer output, and high-poly mesh output (which aren't *directly* in sync with the WM graph, but it's close-ish). Unfortunately, I wasn't able to track down the mesh's albedo/normal map output and building the graph is... Time consuming. But, if I find idle time, I'll rebuild everything and upload those too.
* Added an old version of my Steel Hunters nevada terrain node graph (using World Machine and GeoGlyph) in case anyone was curious on how it was generated.Added an old version of my Steel Hunters nevada terrain node graph (using World Machine and GeoGlyph) in case anyone was curious on how it was generated.
* Updated all of the standard shader's PBR data samplers (with the exception of the albedo texture -- and the subsurface color texture, though that's not in this shader anyway) to be sampled linearly because, as it turns out, even AO maps shouldn't be sampled in sRGB space (which I was always kind of on the fence about, but I finally took a stand on IT'S LINEAR OKAY).Updated all of the standard shader's PBR data samplers (with the exception of the albedo texture -- and the subsurface color texture, though that's not in this shader anyway) to be sampled linearly because, as it turns out, even AO maps shouldn't be sampled in sRGB space (which I was always kind of on the fence about, but I finally took a stand on IT'S LINEAR OKAY).
* Added the JM_TODO gist link.Added the JM_TODO gist link.
* Adding v0.1.5 change log.Adding v0.1.5 change log.

## [0.1.5] - 2018-04-06


### :cat: Note

* Updating README for some clarifications.Updating README for some clarifications.
* jshint added for linting, packages cleaned upJshint added for linting, packages cleaned up
* Fixed some wind issues with the speedtree shaders; added static switch support in the standard shader for UV coord sets 1 and 2 (with 0 being the default, natch).Fixed some wind issues with the speedtree shaders; added static switch support in the standard shader for UV coord sets 1 and 2 (with 0 being the default, natch).
* Added a bunch of older-but-since-lost procedural water shaders along with gerstner wave/wave cluster generation functions (all use UE4 engine content for textures, so hopefully no errors on that front now). Also removed some deprecated procedural shaders (including the former bad water one).Added a bunch of older-but-since-lost procedural water shaders along with gerstner wave/wave cluster generation functions (all use UE4 engine content for textures, so hopefully no errors on that front now). Also removed some deprecated procedural shaders (including the former bad water one).
* Updating all foliage shaders (standard and speedtree-related ones), updated material functions, updated the environment simulation material parameter collection, added some additional material functions, and added all generic textures for material placeholders.Updating all foliage shaders (standard and speedtree-related ones), updated material functions, updated the environment simulation material parameter collection, added some additional material functions, and added all generic textures for material placeholders.
* Adding some new material functions: albedo tinting, three types of normal blending operations.Adding some new material functions: albedo tinting, three types of normal blending operations.
* Updated NPM and then updated every package except gulp-watch's own reliance on gulp-util which gulp says should be removed.Updated NPM and then updated every package except gulp-watch's own reliance on gulp-util which gulp says should be removed.
* Okay. Maybe this time the security warning box will go away forever.Okay. Maybe this time the security warning box will go away forever.
* Updating silly things because.Updating silly things because.
* More potential security fixes maybe maybe?More potential security fixes maybe maybe?
* Update package-lockUpdate package-lock
* ... Okay. Actually fixed it this time.... Okay. Actually fixed it this time.
* Er. Properly addressed the security vulnerability in joy-create since, hey, it's handy to run npm update.Er. Properly addressed the security vulnerability in joy-create since, hey, it's handy to run npm update.
* Merged feature/joy-create-v0.1 as the one in master is woefully out of date and the feature branch was stable last I checked (the old master branch version was vulnerable to a security vulnerability).Merged feature/joy-create-v0.1 as the one in master is woefully out of date and the feature branch was stable last I checked (the old master branch version was vulnerable to a security vulnerability).
* Watch task bails out after setting up watches, so devstart can complete, although the gulp task will keep running since the watches themselves haven't endedWatch task bails out after setting up watches, so devstart can complete, although the gulp task will keep running since the watches themselves haven't ended
* Add done-signalling to devstart, but something else is holding it upAdd done-signalling to devstart, but something else is holding it up
* joy-create work; removed codemirror in favor of monaco-editor, updated gulp to v4, cleaned up dependencies, started removing npm run-scripts in favor of proper gulpfile and task setup. Broke a lot of things.Joy-create work; removed codemirror in favor of monaco-editor, updated gulp to v4, cleaned up dependencies, started removing npm run-scripts in favor of proper gulpfile and task setup. Broke a lot of things.
* Apparently had joy-create files I never checked in.Apparently had joy-create files I never checked in.
* YES. I FINALLY FIGURED OUT WHAT SYNTAX I WAS SUPPOSED TO USE.YES. I FINALLY FIGURED OUT WHAT SYNTAX I WAS SUPPOSED TO USE.
* More of me trying to figure out the syntax here.More of me trying to figure out the syntax here.
* About two minutes worth of work on getting the new structure to work.About two minutes worth of work on getting the new structure to work.
* Alternate electron setup for joy-create since, hey, my experience with javascript/node is entirely HEY WHAT DOES THIS DO *PRESS ENTER*.Alternate electron setup for joy-create since, hey, my experience with javascript/node is entirely HEY WHAT DOES THIS DO *PRESS ENTER*.
* Started maybe figuring more things out and structuring appropriately?Started maybe figuring more things out and structuring appropriately?
* WHITESPACE CLEANING WOOOOO.WHITESPACE CLEANING WOOOOO.
* Reworked/styled/themed the electron window a bit, refactored things. Though I'm not sure what I refactored them into since I'm still figuring out what the hell is happening.Reworked/styled/themed the electron window a bit, refactored things. Though I'm not sure what I refactored them into since I'm still figuring out what the hell is happening.
* Got everything working slightly better than it did in the last check-in (less horrifying hacks).Got everything working slightly better than it did in the last check-in (less horrifying hacks).
* Removing ace from the vendors/ subdirectory (it's handled in the install/postinstall step now). Added rimraf and vendor-copy to package.json.Removing ace from the vendors/ subdirectory (it's handled in the install/postinstall step now). Added rimraf and vendor-copy to package.json.
* Reworked the entire SHEBANG to be a bit more properly setup (except the mad dash to get the viewport working at the end). Got the three.js viewport working even though it's just pitch black. The editor pane isn't coorperating yet, but that's not far off.Reworked the entire SHEBANG to be a bit more properly setup (except the mad dash to get the viewport working at the end). Got the three.js viewport working even though it's just pitch black. The editor pane isn't coorperating yet, but that's not far off.
* Refactored files and filenames to make more sense; worked to get the old page working properly with the viewport/editor.Refactored files and filenames to make more sense; worked to get the old page working properly with the viewport/editor.
* Updated the app, added webpack-dashboard telemetry support.Updated the app, added webpack-dashboard telemetry support.
* Setting up a proper procgen system (l-system, turtle placement, and first-order shapes). Also moving over to three.js. Nothing about this commit will work at all right now.Setting up a proper procgen system (l-system, turtle placement, and first-order shapes). Also moving over to three.js. Nothing about this commit will work at all right now.
* Miscellaneous blend and layer fixes (though something still isn't adding up. Literally and figuratively.Miscellaneous blend and layer fixes (though something still isn't adding up. Literally and figuratively.
* Adding a first-pass at some rough material layers and blending functionality (based on car paints). It's... Not right yet, but it's something.Adding a first-pass at some rough material layers and blending functionality (based on car paints). It's... Not right yet, but it's something.
* More updates to the speedtree shaders; some fixes here and there and also made the per-instance fade parameter a static switch option.More updates to the speedtree shaders; some fixes here and there and also made the per-instance fade parameter a static switch option.
* Rewrote the speedtree foliage shaders and added a new one for speedtree billboards. They are wonderful now.Rewrote the speedtree foliage shaders and added a new one for speedtree billboards. They are wonderful now.
* Added a note on the unreliability of the object pooling code and made a Little Red Riding Hood metaphor for some reason.Added a note on the unreliability of the object pooling code and made a Little Red Riding Hood metaphor for some reason.
* Updates to the speedtree shaders based on iteration (after iteration (after iteration)) on Steel Hunters.Updates to the speedtree shaders based on iteration (after iteration (after iteration)) on Steel Hunters.
* Updated the README.Updated the README.
* Updated Joy Create in the README.Updated Joy Create in the README.
* Added Joy Create with notes to the UE4 README.Added Joy Create with notes to the UE4 README.
* Added procedural street/intersection tool plugin (from @ydrive).Added procedural street/intersection tool plugin (from @ydrive).
* From @ydrive: https://github.com/ydrive/StreetArchFrom @ydrive: https://github.com/ydrive/StreetArch
* Replaced m_shader_foliage_speedtree with m_shader_speedtree_foliage (along with some minor tweaks). Added m_shader_speedtree_foliage_body for foliage with wrapping textures (mostly bark/stems/etc.).Replaced m_shader_foliage_speedtree with m_shader_speedtree_foliage (along with some minor tweaks). Added m_shader_speedtree_foliage_body for foliage with wrapping textures (mostly bark/stems/etc.).
* Overhauled the speedtree foliage shader in conjunction with the new speedtree for UE4. Also fixed some albedo tinting/coloring issues in the standard shader. Tweaks to the standard POM shader.Overhauled the speedtree foliage shader in conjunction with the new speedtree for UE4. Also fixed some albedo tinting/coloring issues in the standard shader. Tweaks to the standard POM shader.
* Updated standard shader and added a POM shader (with *roughly* equivalent features to the standard shader).Updated standard shader and added a POM shader (with *roughly* equivalent features to the standard shader).
* Updates to the object pooling system (given some issues in the use of it with my test case).Updates to the object pooling system (given some issues in the use of it with my test case).
* Convert some debug print statements to Python3-styleConvert some debug print statements to Python3-style
* Rename familyRoot to outputRoot, filenameRoot to inputRoot; closes #1Rename familyRoot to outputRoot, filenameRoot to inputRoot; closes #1
* Revamped the markdown for this page so I didn't have to commit every stupid change individually.Revamped the markdown for this page so I didn't have to commit every stupid change individually.
* Updated UE4 project conventions (todo: source asset conventions).Updated UE4 project conventions (todo: source asset conventions).
* Yes, I'm dumb.Yes, I'm dumb.
* Updating markdown style to Ulysses'.Updating markdown style to Ulysses'.
* RenderDoc section needed a lower heading.RenderDoc section needed a lower heading.
* Forgot about the miscellaneous code snippets index link.Forgot about the miscellaneous code snippets index link.
* An extensive UE4 infostorm update on content creation (material-focused atm), rendering/shading skeleton, and graphics debugging.An extensive UE4 infostorm update on content creation (material-focused atm), rendering/shading skeleton, and graphics debugging.
* Removed the asset library information into its own page; general UE4 info/resources-only here now.Removed the asset library information into its own page; general UE4 info/resources-only here now.
[0.2.0]: https://github.com/trentpolack/CALVINBALL/compare/v0.1.5..v0.2.0

[0.1.5]: https://github.com/trentpolack/CALVINBALL/compare/v0.1.1..v0.1.5

<!-- generated by git-cliff -->
