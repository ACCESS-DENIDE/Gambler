
# ONE-ARMED BANDIT

Test task for Octavian Gaming


## Required Libs

##### OpenGL2
##### GLFW3

## Build

To build this project, run:


```bash
  git clone https://github.com/ACCESS-DENIDE/Gambler
  cd Gambler
  cmake .
  make
```

!IMPORTANT! Folder "Images" MUST be in the same directory, as executable.

## launch

Default launch
```bash
  ./Gambler
```

Launch in service mode (automaticly count all coombinations and average win multiplication)
```bash
  ./Gambler -t
```

## Random providers

- Random max speed of drum
- Random acceleration/slow down speed of drum
- (If enabled) Bundle mode symbol provider


## Bundle mode

Before popping symbols from the array, they will be shuffled.

#### Example

- Standard mode
[1, 2, 3, 4, 5];
pop()->1;
pop()->2;
pop()->3;
pop()->4;
pop()->5;
Renew();
[1, 2, 3, 4, 5]
- Bundle mode
Shuffle();
[3, 1, 2, 5, 4]
pop()->3;
pop()->1;
pop()->2;
pop()->5;
pop()->4;
Renew();
[5, 2, 1, 4, 3]



## Flexibility

This app has high flexibility through defines.
You can change:
- Amount of drums
- Min/Max speed of drums
- Amount of symbols on drums
- Value of each symbol
- Appearance of drums and info window
- Min/Max bet
- Initial chips amount

## Appearance
I've tried my best to show standard symbols of slot machines, but you can use default colored squares to check if all textures are properly sized (images, "Old" folder).

## Scoring system
Player's win calculated as multiplication between player's bet and total multiplier. Total multiplier calculated as multiplication of all symbols with combos (if two exact symbols stop near each other, they add, and not multiply). I chose this system because of its flexibility (you can change the amount of drums without changing the system); additionally, it provides a combo mechanic.

#### Example
- [0.4; 0.4; 0.4; 1; 1.5] = (0.4 + 0.4 + 0.4) x 1.5 x 1 = 1.8
- [0.4; 1; 0.4; 1.5; 0.4] = 0.4 x 1 x 0.4 x 1.5 x 0.4 = 0.096
- [2; 2; 2; 2; 2] = 2 + 2 + 2 + 2 + 2 = 10
- [7; 2; 7; 2; 7] = 7 x 2 x 7 x 2 x 7 = 1372
 
 This system provides wide abilities to combine symbols.
 (Information about symbol score can be acquired by hovering the mouse above the symbol on the "Info" subwindow, or above the symbol on a drum. Score will appear in the bottom left corner of the "Info" subwindow.)

 ## Additional features
 - This program has a special test mode. In this mode, the program will automatically calculate the amount of possible combinations and the average win multiplier. To access this mode, launch the program with the additional "-t" parameter (all output will be provided through the console stream)
- Input buffering. If you press "Stop," until all drums are fully accelerated, the program will buffer this input and use it right after switching to working mode.
- Storing personal best in file. Players can track their high scores between runs.


