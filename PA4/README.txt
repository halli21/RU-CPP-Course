PA4 - Character sheets
by
Arnar Bragi Bragason   -   arnarbb21@ru.is
Haraldur Jón Friðriksson - haraldur21@ru.is


We implemented everything from the program description as well as the 10% bonus at the bottom.
Being, Person, Creature, Investigator and EldritchHorror are all classes. Person and Creature 
inherit from Being and then EldritchHorror inherits from creature and investigator inherits 
from Person. When you start the program it already has data. That data can be found in "roles.txt"
and "characters.txt". "roles.txt" has both roles and species, while "character.txt" has
the roster of characters. You can change roster by choosing "Switch Roster" in the main menu
and you will have to input the name of an existing txt file(can be empty). 

If anything is unclear then you can contact us at any time with the emails at the top.

----------------------------------------------------------------------------------------------
Simple explanation of each file in alphabetical order:

being.cpp / being.h:
Contains the class for Being.

character.cpp:
Super for the Species and Role classes. Used to keep both Species and Roles in the same list.

characters.txt:
Our file containing the roster of all characters.

creature.cpp / creature.h:
Contains the class for Creature.

eldritchHorror.cpp / eldritchHorror.h:
Contains the class for EldritchHorror.

investigator.cpp / investigator.h:
Contains the class for Investigator.

main.cpp:
The start point of the program. It uses functions from "menu.cpp" to get instructions and 
execute them. This is essentially the "main menu"

menu.cpp / menu.h:
Contains all of the functionality of the menu screen.

new_roster.txt:
An extra roster file that you can switch to.

person.cpp / person.h:
Contains the class for Person.

role.cpp:
Contains the class for Role.

roles.txt:
Our file containing all the roles and species.

species.cpp:
Contains the class for Species.

----------------------------------------------------------------------------------------------
How to compile and run:

1st do:
    g++ -o pa4 *.cpp -std=c++11

then run using this command:
    ./pa4