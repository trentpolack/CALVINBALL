# [Joy Machine](http://joy-machine.com/) - Git Template Files
These are just some handy references for gitignore/gitattributes for handling a UE4 repo using git-lfs. And then the gitconfig has some of the best aliases ever in the world.

The entirety of this doc is for use with git on the command line (as a note: you do *not* have to use git bash; it can be easily integrated into the standard Powershell and Windows cmd prompt). The only *remotely* decent GUI client for git on Windows is [GitKraken](https://www.gitkraken.com) -- but the number of "quirks" that it has makes it unusable in my opinion. So: command line.

I also [wrote an article on my experience with source control](https://blog.joy-machine.com/working-with-git-for-games-and-in-general-a0efb78f3a01) on [*Steel Hunters*](http://steel-hunters.com) and general git *stuff*.

## `difftool` and `mergetool`
Setting up a difftool and mergetool for the git command line is a lovely thing to do, unless you like pain. Or *really* like text editors. Customizing these commands will allow you to use a GUI-based comparison tool to handle merges and differences between files. Up until yesterday, I'd have recommended [`p4merge`](https://www.perforce.com/product/components/perforce-visual-merge-and-diff-tools) (from Perforce). Then I found [Beyond Compare 4](https://www.scootersoftware.com/) -- ignore the site design, it's great software -- which I used at my first professional game development job and had *no* idea it was still around. Unlike `p4merge`, Beyond Compare offers an easy solution to simply compare two folders (whether they're in a repository or not) and git a list of files that are added/removed/changed/unchanged in the file hierarchy. And then you can go through and diff/merge what you want to.

Point being: these are great tools to build into the git command line. This is my personal global gitconfig:

```
[merge]
	tool = bc3

[mergetool "bc3"]
	path = C:\\Program Files\\Beyond Compare 4\\bcomp.exe
	prompt = false

[diff]
	tool = bc3

[difftool "bc3"]
	path = C:\\Program Files\\Beyond Compare 4\\bcomp.exe
	prompt = false
```

This allows me to use Beyond Compare whenever I enter `git difftool <file>` (which will check the remote version of the file); `prompt = false` ensures I don't have to agree to a (Y/N) question for every file I diff. And, alternatively, if you just enter `git difftool` to bring up a diff of all modified files. This is all true of mergetool as well. I tossed the `prompt = false` into the `gitconfig.template` for reference. 

## Colors
Additionally, I added some colors for varying results printed by `git status`, `git branch`, and `git diff`. Here's the list of valid colors:
* `normal`.
* `black`
* `red`.
* `green`.
* `yellow`.
* `blue`.
* `magenta`.
* `cyan`.
* `white`.

### Color Decorators
AND YOU CAN DECORATE THEM!
* `bold`.
* `dim`.
* `ul` (underline).
* `blink` (rock it like an Angelfire website).
* `reverse` (swap foreground/background colors).

## Aliases
* `git s` -- Short format `git status` (no lfs status report like `git state`, below). With colors!
* `git state` -- Does a full evaluation of your current repo state across git and git-lfs, with some decent formatting to separate the two. Does not display git-lfs info if the repo doesn't use lfs.
* `git lard` -- Lists the top 40 heaviest assets in your repository.
* `git last` -- Just print out the last commit to your command line.
* `git uncommit` -- Uncommit whatever you just did.
* `git prettylog` -- Pretty log with some branch graphics.
* `git tree` -- Just prints a pretty-formatted revision history in tree form.
* `git holy-fsck` -- Does a full and strict verification of the git repository.

## Git Changelog Generation Template
I really love writing changelogs and while I think [**Keep a Changelog**](https://keepachangelog.com/en/1.1.0/) is a very valuable resource... It also makes writing changelogs feel like _work_ work. So I typically just write a single summary message and detail out some more information in list form in the change body. I am also, coincidentally, incredibly lazy about documentation. With that in mind, I created I found [**git-cliff**](https://git-cliff.org/). 

Git-Cliff is the best of the changelog generators that I've found -- as there are quite a few that exist and are even pretty good -- and it uses a Tera-formatted template file as its guiding star when generating a changelog. You can grab the one I've written up, [**changelog-generator-template.toml**](https://github.com/trentpolack/CALVINBALL/blob/develop/git/changelog-generator-template.toml) on this repo for use if it's close to what you want. It allows for more detail than most of the changelog best practices which can get overwhelming in large releases but I tend to releases at a fairly quick cadence.

_NOTE_: Put an example link here.
