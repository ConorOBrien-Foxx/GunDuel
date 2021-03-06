# GunDuel

Futuristic Gun Duel Tournament at [Programming Puzzles & Code Golf at Stack Exchange][1]

## C++ Submissions

Please :

 - Post your submission as an answer to the PPCG.SE post.
 - Fork this project and request your files to be pulled.

## Python Submissions

Edit `PythonPlayer\<architecture>\PythonPlayer.py` to test your submission.

 - You can save state files, which are subject to removal at the beginning of a tournament.
 - Your script is called once per turn.
 - Commandline interface may change before Jan. 7, 2017.

## Other Submissions

Language Allowed: Java.

Executables Allowed.

Command Line and Return Code Requirements

    Expected Command Line Argument Format:
    	<opponent-id> <turn> <status> <ammo> <ammo-opponent> <history> <history-opponent>

    Expected Return Code: The ascii value of a valid action character.
    	'0' = 48, '1' = 49, '2' = 50, '-' = 45, '=' = 61
    
    Player identifier is an integer in [0, N), where N is size of tournament.
    Turn is 0-based.
    If duel is in progress, status is 3.
    If duel is draw / won / lost, status is 0 / 1 / 2.
    If turn is 0, <history> and <history-opponent> are not provided.
    Histories are strings of actions, e.g. 002 0-=
    You can ignore arguments you don't particularly need.

The binaries will be added to the repository if they meet the requirements and does no harm to any computer.

## Current Standing (update upon new submission)

08:38 AM Saturday, December 31, 2016 Coordinated Universal Time (UTC)

| Player                           | Language   | Survival  | Points |
|:-------------------------------- |:---------- | ---------:| ------:|
| [MontePlayer][16]                | C++        | 12 rounds |   6152 |
| [CBetaPlayer][15]                | C++        | 11 rounds |   3903 |
| [StudiousPlayer][12]             | C++        | 10 rounds |   5513 |
| [FatedPlayer][14]                | C++        |  9 rounds |   3462 |
| [BarricadePlayer][7]             | C++        |  8 rounds |   3125 |
| [BotRobotPlayer][8]              | C++        |  7 rounds |   2624 |
| [SadisticShooter][10]            | C++        |  6 rounds |   2806 |
| [SurvivorPlayer][13]             | C++        |  5 rounds |   2282 |
| [TurtlePlayer][6]                | C++        |  4 rounds |   1888 |
| [GunClubPlayer][4]               | C++        |  3 rounds |   1550 |
| [DeceptivePlayer][11]            | C++        |  2 rounds |   1125 |
| [PlasmaPlayer][9]                | C++        |  1 round  |    694 |
| [OpportunistPlayer][5]           | C++        |  0 rounds |    380 |

Disqualified Players (Honorable Mentions)

 - [BlackHatPlayer][2] (Locates and modifies [vtable][3] of rival entries)

 [1]: http://codegolf.stackexchange.com/q/104896/11933
 [2]: http://codegolf.stackexchange.com/a/105061/11933
 [3]: https://en.wikipedia.org/wiki/Vtable
 [4]: http://codegolf.stackexchange.com/a/104899/11933
 [5]: http://codegolf.stackexchange.com/a/104902/11933
 [6]: http://codegolf.stackexchange.com/a/104905/11933
 [7]: http://codegolf.stackexchange.com/a/104909/11933
 [8]: http://codegolf.stackexchange.com/a/104910/11933
 [9]: http://codegolf.stackexchange.com/a/104933/11933
 [10]: http://codegolf.stackexchange.com/a/104947/11933
 [11]: http://codegolf.stackexchange.com/a/104972/11933
 [12]: http://codegolf.stackexchange.com/a/105066/11933
 [13]: http://codegolf.stackexchange.com/a/105084/11933
 [14]: http://codegolf.stackexchange.com/a/105131/11933
 [15]: http://codegolf.stackexchange.com/a/105154/11933
 [16]: http://codegolf.stackexchange.com/a/105175/11933
