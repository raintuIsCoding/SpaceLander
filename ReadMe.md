Space Lander

Programmer: Robert Umali
Date: July 22, 2024

To compile, use the following command:
g++ -std=c++17 SPACELANDER.cpp startScreen.cpp mainMenu.cpp startGame.cpp landersCarousel.cpp planetsCarousel.cpp statsMenu.cpp infoMenu.cpp howToPlay.cpp reportIssue.cpp screenUtils.cpp -o SPACELANDER

To run the game, use the command:
./SPACELANDER.exe or SPACELANDER depending on your terminal

Rubric checklist:
> interactive components - CHECK
> NPC (found when user completes game attempt and conditionally if user selects start game too soon) - CHECK
> Game Stats - CHECK
> Moving visual component - CHECK
> Menus - CHECK
> Sub menus - CHECK
> Menu random numerical component - CHECK
> Menu random percentage component - kind of CHECK
> 2D map - CHECK
> 4+ classes - CHECK (I think)
> 6+ if-else statements - CHECK
> 6+ loops - CHECK
> 2+ nested loops - CHECK
> File I/O (report screen and stats screen) - CHECK

Extra Credit:
> Project showcase - Sign me up!
> Final battle - No time...
> Persistant scoreboard - CHECK
> Colors - CHECK

How to Play
Controls:
W - Full Thrust
X - Cut Engines
D - Throttle Up
A - Throttle Down
Q - Quit

Gameplay Instructions:
When the game starts, the lander will immediately fall to the surface.
If no action is taken, the lander will crash into the surface within a few seconds.
Use the controls to slow the descent of the lander to a safe velocity.
Different landers have varying thrust outputs, masses, and starting fuel levels.
You can select different planets with unique gravitational pulls and surface characteristics.
Aim to land the lander safely by managing your fuel and controlling your descent speed.

Objectives:
The main goal is to land the lander safely on the planet's surface.
Your final score is based on the remaining fuel and your landing speed.
A higher remaining fuel indicates a more efficient landing.
A lower landing speed results in a higher score, as long as the lander doesn't crash.

Lander Selection:
Different landers have different thrust outputs and masses.
Choose a lander based on your preference for thrust and fuel capacity.

Planet Selection:
Each planet has a unique gravitational pull that affects your lander's descent.
Planets also have different surface types that impact the difficulty of landing.