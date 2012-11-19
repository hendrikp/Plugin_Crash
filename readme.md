Crash Plugin for Plugin SDK
===========================
Purpose is to supply a sample plugin that creates a way to reliable crash the process.

Extraction
==========
Extract the files to your Cryengine SDK Folder so that the Code and BinXX/Plugins directory match up.

CVars
=====
* ```pc_crash```
  Crashes the process

Flownodes
=========
Adds a new Flownode Crash_Plugin:Crash that will crash the game when triggered.

Sourcecode
==========
* Clone the repository to your local machine to your Code directory e.g. C:\cryengine3_3.4.0\Code

```
    git clone https://github.com/hendrikp/Plugin_Crash.git
```

Compiling
---------
Either add the project file to your CryGame solution and the plugin manager as dependency for this plugin.

Or use the supplied seperate solution to compile this plugin.