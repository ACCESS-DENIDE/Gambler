
# ONE ARMED BANDIT

Test task for Octavian Gaming



## Random providers

- Random max speed of drum
- Random axeleration/Slow down speed of drum
- (If enabled) Bundle mode symbol provider


## Bundle mode

Before poping symbols from array, they will be shuffled.

#### Example

- Standart mode
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



## Required Libs

##### OpenGL2
##### GLFW3

## Flexibility

This app has high flexibility through defines.
You can cahnge:
- Amount of drums
- Min/Max speed of drums
- Amount of symbols on drums
- Value of each symbol
- Apearence of drums and info window
- Min/Max bet
- Initial chips amount

## Apearence
I've tried my best, to show standart symbols of slot machines, but you can use default colored squeres, to chech, if all textures proper sized (Images, "Old" folder)

## Scoring system
Player's win calculated as multiplication between player's bet and total multiplyer. Total multiplyer calculated as multiplication of all symbols with combos (if two exact symbols stops near each other, they add, and not multiply). I chose this system because of flexibility(you can change amount of drums, without changing system), additionaly it provides combo mechanik.

#### Example
- [0.4; 0.4; 0.4; 1; 1.5]=(0.4+0.4+0.4)x1.5x1=1.8
- [0.4; 1; 0.4; 1.5; 0.4]=0.4x1x0.4x1.5x0.4=0.096
- [2; 2; 2; 2; 2]=2+2+2+2+2=10
- [7; 2; 7; 2; 7]=7x2x7x2x7=1372
 
 This system provides wide abilities to combine symbols

 ## Additional features
 - This program has spetial test mode. In this mode program wil automaticaly calculate amount of possible coombinations, and average win multiplyer. To access this mode launch program with additional "-t" parametr (all output wil be provided through console stream)
- Input buffering. If you press "Stop", until all drums fully accelerated, program will buffer this input, and use it right after switching to Working mode.
- Storing personal best in file.  Players can track their high scores between runs.

