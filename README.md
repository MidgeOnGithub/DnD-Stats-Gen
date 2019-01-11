## Dungeons and Dragons Stats Generator

#### Disclaimer
This program is not intended to represent an official *Dungeons and Dragons* nor *Wizards of the Coast* product. All product and company names are trademarks™ or registered® trademarks of their respective holders. Use of them does not imply any affiliation with or endorsement by them.

Any external packages used can be found in the `vendor` folder of the repo, along with their respective licenses, which will be included with any Releases of this program.

#### Vocabulary Notes
* The game referenced: `Dungeons and Dragons` (`DnD`)
* Players have adventures/sessions created/led/guided by a `Dungeon Master` (`DM`)
* Engaging in the fantasy adventure, each player acts as a `Player Character` (`PC`)
* The primary reference literature for DnD standards is the `Player's Handbook` (`PHB`)

### Command-line usage
This program accepts some command-line arguments!
Use `--help` to see the following screen:
> Options:
>
> * --help
>
> This help screen.
>                              
> * -v [ --verbose ]
>
> Verbose switch -- primarily affects the dice roller. Will trigger the default `slow` unless `no-slow` is also passed.
>                              
> * -x [ --no-slow ]
>
> A switch that disables `slow`. Only needed if  `verbose` is desired but without pauses between inputs.
>                              
> * -s [ --slow ] arg (=350)
>
> An optional value (milliseconds) to set a timer between die rolls. Depends on `verbose` and `no-slow`. Do not chain with other options.
>                              
> * -o [ --output-file-name ] arg
>
> Parameter to output a summary to `file_name`.txt (extension will be appended by 
> the program) to the working directory. Do not 
> chain with other options.
>                              
> * --no-output
>
> Switch to indicate the program should not 
> create any kind of output file(s).

### Dice Roller
This program includes a dice roller which performs random dice rolls of any "ndm" type. 
> * **n** is the number of die to be rolled
> * **d** is a non-functional shorthand ("**d**ice"), spoken as just the letter 
> * **m** represents each dice's face count

This also accounts for special die and roll cases discussed in the PHB in pages 6 and 7, namely:
> * **d100**, involving a combination of a percentile and d10 die
> * **d3**, the first method described, wherein the value is the ceiling of a d6 / 2
> * **d2**, wherein odd := 1, even := 2

### Ability Score Generation
Dungeons and Dragons characters have 6 point-valued *abilities*:
> **Strength** || **Dexterity** || **Constitution** || **Intelligence** || **Wisdom** || **Charisma**

When creating a new character, a player (or their DM) must determine what point values are available to assign to said character's abilities. Some of the most popular methods to generate these values involve rolling several six-sided die (d6) and summing their rolls in some fashion. Currently, this program features two of the more standard random-value methods:
* **3d6** -- wherein the values are the sums from 6 separate *3d6* rolls
* **4d6-drop-1** -- like the 3d6 method, except 6 *4d6* rolls are performed, with the lowest of the 4 die discarded
  * Generally increases scores, lowering potential of generating "dud" abilities

After score generation, the program interacts with you to assign the rolled scores to a PC's abilities. Afterwards, a pretty-printed summary of the abilities will be shown.

##### Future Development Notes
Assigned ability scores will eventually be affected by PC `race` chosen upon character creation. Support for 2 or more races will likely not be provided.
> `Human` PCs receive +1 for all abilities, `Dwarf` PCs get +2 for *Constitution* only, etc.

Also, the "point buy" method described in the PHB will be implemented.

### Saving Work
After a user completes their ability assignment, the program offers to write out a summary to a `.txt` file: if you accept, the program prompts you to name the file.
> Note: the file will likely save to the current working directory, but depending on OS and other factors, may save to the program's "binary" directory.

### Note to DnD Players & DMs
All features of the program are/will be based on the latest edition of "Dungeons and Dragons" and its *Wizards of the Coast* expansions. The `master` branch of this repo will not attempt to account for older editions nor include third-party expansions. If the program ever appears to have erroneously done so, or has failed to account for official content, please report discrepancies.
