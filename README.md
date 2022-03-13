[![rythe logo banner](https://cdn.discordapp.com/attachments/682321169541890070/767684570199359499/banner.png)](https://legion-engine.com)
[![License-MIT](https://img.shields.io/github/license/Rythe-Interactive/Rythe-Module-Template)](https://github.com/Rythe-Interactive/Rythe-Module-Template/blob/main/LICENSE)
[![Discord](https://img.shields.io/discord/682321168610623707.svg?label=&logo=discord&logoColor=ffffff&color=7389D8&labelColor=6A7EC2)](https://discord.gg/unVNRbd)

# Module Template
This is a template for Rythe-Engine modules. 

# Usage
Follow the steps at https://docs.github.com/en/repositories/creating-and-managing-repositories/creating-a-repository-from-a-template.

We recommend to create the repository with every branch in this current repository, as it'll copy over the full git-flow setup from the template.

Change:
* CMakeLists.txt -> Change all occurences of MODULE_NAME
* Rename src/MODULE_NAME
* Rename src/MODULE_NAME/MODULE_NAME.hpp
* Rename src/MODULE_NAME/MODULE_NAME.cpp
* applications/sandbox/CMakeLists.txt -> Change MODULE\_NAME\_sandbox
* Remove this usage guide and other template-related info in README.
* Update this README with accurate information (view existing modules for reference).
