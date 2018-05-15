#include "Container.h"
#include <iostream>
#include <string>

int main()
{

    Object Leonardo;
    Leonardo.Add("Name", "Leonardo");
    Leonardo.Add("Colour", "Blue");
    Leonardo.Add("Weapon", "Katanas");

    
    Object Michelangelo;
    Michelangelo.Add("Name", "Michelangelo");
    Michelangelo.Add("Colour", "Orange");
    Michelangelo.Add("Weapon", "Nunchucks");

    
    Object Raphael;
    Raphael.Add("Name", "Raphael");
    Raphael.Add("Colour", "Red");
    Raphael.Add("Weapon", "Sai");

    Object Donatello;
    Donatello.Add("Name", "Donatello");
    Donatello.Add("Colour", "Purple");
    Donatello.Add("Weapon", "Bo");


    Object Splinter;
    Splinter.Add("Name", "Splinter");
    Splinter.Add("Colour", "Brown");

    Object Shredder;
    Shredder.Add("Name", "Shredder");
    Shredder.Add("Weapon", "Armor");

    
    Container parser;

    parser.AddObject("Ninja1", Leonardo);
    parser.AddObject("Ninja2", Michelangelo);
    parser.AddObject("Ninja3", Raphael);
    parser.AddObject("Ninja4", Donatello);
    parser.AddObject("Ninja5", Splinter);
    parser.AddObject("Ninja6", Shredder);

    parser.Save("test.txt");

    
    Container parser2("test.txt");

    Object a = parser2.GetObject("Ninja1");

    std::cout << a.GetByKey("Name") << std::endl;
    std::cout << a.GetByKey("Colour") << std::endl;
    std::cout << a.GetByKey("Weapon") << std::endl;

    std::cout << "--------------------------------------" << std::endl;

    Object o = parser2.GetObject("Ninja6");

    std::cout << o.GetByKey("Name") << std::endl;
    std::cout << o.GetByKey("Weapon") << std::endl;
    

    system("pause");
    return 0;
}
