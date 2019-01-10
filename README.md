## Dungeons and Dragons Stats Generator

#### Disclaimer

This program is not intended to represent an official *Dungeons and Dragons* nor *Wizards of the Coast* product. All product and company names are trademarks™ or registered® trademarks of their respective holders. Use of them does not imply any affiliation with or endorsement by them.

#### Vocabulary Notes
* The game referenced: `Dungeons and Dragons` (`DnD`)
* Players have adventures/sessions created/led/guided by a `Dungeon Master` (`DM`)
* Engaging in the fantasy adventure, each player acts as a `Player Character` (`PC`)

### Dice Roller
This command-line program includes a dice roller which performs random dice rolls of any "ndm" type. 
> * **n** is the number of die to be rolled
> * **d** is a non-functional shorthand ("**d**ice"), spoken as just the letter 
> * **m** represents each dice's face count

##### Future Development Notes
Eventually, this part of the program will be expanded to account for "special" die and rolls (relative to DnD). Take, for example, the "faux" d100 roll, wherein the results of percentile and d10 die rolls are combined such that the range of outputs is 1 - 100, mimicking a 100-sided dice. (There are a variety of reasons why this method might be preferred.) Even disregarding the faux d100 method, the dice roller should account for percentile `(00, 10, 20, ... 90)` dice; it should also properly display the face values of a d10 as `0 - 9`, not `1 - 10`.

### Ability Score Generation
Dungeons and Dragons characters have 6 point-valued *abilities*:
> **Strength** || **Dexterity** || **Constitution** || **Intelligence** || **Wisdom** || **Charisma**

When creating a new character, a player (or their DM) must determine what point values are available to assign to said character's abilities. Some of the most popular methods to generate these values involve rolling several six-sided die (d6) and summing their rolls in some fashion. Currently, this program features two of the more standard random-value methods:
* **3d6** -- wherein the values are the sums from 6 separate *3d6* rolls
* **4d6-drop-1** -- like the 3d6 method, except 6 *4d6* rolls are performed, with the lowest of the 4 die discarded
  * Generally increases scores, lowering potential of generating "dud" abilities

After score generation, the program interacts with you to assign the rolled scores to a PC's abilities. Afterwards, a pretty-printed summary of the abilities will be shown.

##### Future Development Notes
Assigned ability scores will eventually be affected by PC `race` chosen upon character creation. Support for 2 or more races may or may not be provided.
> `Human` PCs receive +1 for all abilities, `Dwarf` PCs get +2 for *Constitution* only, etc.

### Saving Work
After a user completes their ability assignment, the program offers to write out a summary to a `.txt` file: if you accept, the program prompts you to name the file.
> Note: the file will likely save to the current working directory, but depending on OS and other factors, may save to the program's "binary" directory.

### Note to DnD Players & DMs
All features of the program are/will be based on the latest edition of "Dungeons and Dragons" and its *Wizards of the Coast* expansions. The `master` branch of this repo will not attempt to account for older editions nor include third-party expansions. If the program ever appears to have erroneously done so, please report discrepancies.
