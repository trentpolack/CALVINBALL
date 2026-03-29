# [CALVINBALL](https://trentpolack.com) - Repo of *Things*
Much like Calvinball, this repository has no real rhyme or reason for what happens in its walls. It's just filled with _things_ that I've found useful and been able to easily separate from larger repositories.

## Overview
Most recent changelog: [CHANGELOG.md](https://github.com/trentpolack/CALVINBALL/blob/main/CHANGELOG.md).

* [**`assets`**](https://github.com/trentpolack/CALVINBALL/tree/main/assets) — General-purpose game assets to do with as you please.
    * [**`terrain`**](https://github.com/trentpolack/CALVINBALL/tree/main/assets/terrain) — An older iteration of the landscape that I was using for the Nevada environment (the current one is much better, but I need to keep some things internal for obvious reasons). The main attraction here is the node graph for the entire landscape build... but it requires both World Machine 3 and GeoGlyph 2. So, in the spirit of things, I included the output of a previous build I did with that graph. *However*: the output is not as good as the actual node graph will export (I made did cleanup and made some improvements before putting it in this repo); I'll try and update these files with shiny, new data if I get a spare eight hours to build the thing.
    * [**`meshes`**](https://github.com/trentpolack/CALVINBALL/tree/main/assets/meshes) — A collection of go-to meshes used in graphics research and rendering demos. 
* [**`git`**](https://github.com/trentpolack/CALVINBALL/tree/main/git) — Some git configurations for ignoring files, LFS-managed files, and then detailed config settings for everyday interaction with git on the command line.
* [**`scripts`**](https://github.com/trentpolack/CALVINBALL/tree/main/scripts) — Miscellaneous scripts (tools, powershell, visual studio extensions, batch files, etc.) 
* [**`unity`**](https://github.com/trentpolack/CALVINBALL/tree/main/unity) — Unity-specific content developed alongside my current project; this is pretty anemic at the time of writing but should fill out soon.
* [**`ue4_unsupported`**](https://github.com/trentpolack/CALVINBALL/tree/main/ue4_unsupported) — Whatever C++ actors/components/utilities/etc. we end up being able to easily divorce from past Unreal projects. Or, if not easily divorced, whatever seems worth divorcing so others never have to know the pain that we did. This will likely be the least frequently-updated part of the repo. This is considered unsupported now given that most of the work done was around 4.17-18 and I don't have a great setup right now to bring it up to snuff.
   * **NOTE**: The source is kind of a free-for-all; I infrequently add some of the more generic/widely-useful stuff I can, but I can't include the full source integrations (such as, in the case of the anamorphic lens flares, the updated `Scene.h`|`.cpp` nor `PostProcessing.cpp`) due to a whole lot of custom work done.
   * The anamorphic lens flare code is also a very rough first-draft.
   * The object pooling code is _not_ ready for production use by any means at the moment; it looked like it would be lovely and fine, but it is not. It is a wolf dressed up as a friendly grandmother and it will eat all joy from you.

### Companion Repositories
I have a couple of content-only repos that would fit well here but they get a bit on the heavy side on their own, so they live seperately:
* [**Gaea 2.0 Graphs**](https://github.com/trentpolack/GaeaSandbox) — This contains a variety of graphics for [**Gaea 2.0**](https://quadspinner.com/Gaea/) for what feel like create landscapes for good gameplay spaces. Most have the output files in case of not having Gaea 2.0 or not being familiar enough with it to grab them separately. 
* [**World Creator Levels**](https://github.com/trentpolack/WorldCreator) — This repo contains files and output from the next step in my world building workflow; after generating the Gaea heightmap, I take it into [**World Creator**](https://www.world-creator.com/) for further detailing, texturing, object population, and final postprocessing to be in a gameplay-ready state.
   * Sometimes I follow-up the Gaea step with work in Houdini but that's a bit more time-consuming and not quite as fun to iterate with.

### Other Things of Note:
* [**RESEARCH PAPERS**](https://github.com/trentpolack/CALVINBALL/blob/main/RESEARCH_PAPERS.md) — For the nerdier among us (like me), here are some of the better research papers/presentations I've come across over the years. That have survived over time.
* [**RESOURCES**](https://github.com/trentpolack/CALVINBALL/blob/main/RESOURCES.md) — A list of general resources for game development across a number of disciplines. (Work-in-Progress at the moment)
* [**AWESOME_SOFTWARE**](https://github.com/trentpolack/CALVINBALL/blob/main/AWESOME_SOFTWARE.md) — Has a list of all of the software that I (trent) have found to be the best solution within its given context.
* [**AWESOME_GAMEDEV_MENTORS**](https://ishansharma.github.io/twitter-mentors/) — Technically, it's "twitter-mentors", but I like my name better. Anyway, this is [@ishansharma](https://github.com/ishansharma)'s compilation of people ([@trentpolack](https://github.com/trentpolack) included) who offer game development mentoring to anyone that seeks it.
* [**Unreal Engine 4 - General Information**](https://github.com/trentpolack/CALVINBALL/blob/main/unrealengine/ue4_unsupported/content/README.md) — A collection of information, links, and whatever else seems helpful to include. It also contains a summary of the UE4 content contained therein.
* [**Unreal Engine 4 - Joy Machine Conventions**](https://github.com/trentpolack/CALVINBALL/blob/main/unrealengine/ue4_unsupported/content/CONVENTIONS.md) — Our internal development conventions for working with UE4.

### More to Come!
hugs,
trent

If you have any questions, feel free to email me: [me@trentpolack.com](mailto:me@trentpolack.com).
