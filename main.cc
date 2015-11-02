#include <iostream>
#include <fstream>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
struct MyKeys{
   //InputType myInputType;
   sf::Event::EventType myEventType =sf::Event::EventType(-1);
   sf::Keyboard::Key myKeyCode = sf::Keyboard::Key(-1);
   sf::Mouse::Button myMouseButton = sf::Mouse::Button(-1);
};

std::map<std::string,MyKeys> Keys;

void setKeys(sf::RenderWindow& window){
    bool keyboardBinded = false, mouseBinded = false;
    sf::Event e;
    while (not keyboardBinded or not mouseBinded){
        while (window.pollEvent(e)){
            MyKeys key;
            if (e.type == sf::Event::KeyPressed and !keyboardBinded){
                key.myEventType = e.type;
                key.myKeyCode = e.key.code;
                Keys["Key"] = key;
                std::cout << "Binded the keyboard" << std::endl;
                keyboardBinded = true;

            }
            else if (e.type == sf::Event::MouseButtonPressed and !mouseBinded){
                key.myEventType = e.type;
                key.myMouseButton = e.mouseButton.button;
                Keys["Click"] = key;
                std::cout << "Binded the mouse" << std::endl;
                mouseBinded = true;
            }

            if(keyboardBinded and mouseBinded) break;
        }
    }
}

bool testEvent(MyKeys k, sf::Event e){
    // Mouse event
    if (e.type == sf::Event::MouseButtonPressed and
        k.myMouseButton == e.mouseButton.button){
        return (true);
    }/*
    else if(e.type == sf::Event::MouseButtonReleased and
        k.myKeyCode == e.key.code){
        return (true);
    }*/

    // Keyboard event
    if (e.type == sf::Event::KeyPressed and
        k.myKeyCode == e.key.code){
        return (true);
    }/*
    else if(e.type == sf::Event::KeyReleased and
        k.myKeyCode == e.key.code){
        return (true);
    }*/

    //not an interesting event;
    return (false);
}

void Click(){
    std::cout << "Pressed the mouse!" << std::endl;
}

void Enter(){
    std::cout << "Pressed the keyboard!" << std::endl;
}

int main()
{
    sf::RenderWindow window;
    bool running = true;

    sf::Event Event;
/*
    //binding mouse left button to be able to click
    key.myInputType = MouseInput;
    key.myEventType = sf::Event::MouseButtonPressed;
    key.myMouseButton = sf::Mouse::Left;
    Keys["Click"] = key;

    //binding return to the action key
    key.myInputType = KeyboardInput;
    key.myEventType = sf::Event::KeyPressed;
    key.myKeyCode = sf::Keyboard::Return;
    Keys["Enter"] = key;
*/
    window.create(sf::VideoMode(768,768), "FFFFFF");
    std::cout << "please click the keyboard and mouse buttons you want to use" << std::endl;
    setKeys(window);
    std::cout << "keys succesfully set" << std::endl;
    //gameloop
    while (running){
        //manage events
        while (window.pollEvent(Event)){
            //Normal events

            if (Event.type == sf::Event::Closed){//Window closed
                running = false;
            }
            if (Event.type == sf::Event::KeyPressed){//Key pressed
                switch (Event.key.code)
                {
                    case sf::Keyboard::Escape :
                        running = false;
                        break;
                    default :
                        break;
                }
            }

            // Keybind events
            if (testEvent(Keys["Key"], Event)){
                if(Event.type == sf::Event::MouseButtonPressed)
                    std::cout << "oops pressed mouse" << std::endl;
                Enter();
            }

            if (testEvent(Keys["Click"], Event)){
                Click();
            }
        }

        //Clear the window
        window.clear();/*
        //Draw the sprites
        for(int i = 0; i < sprites.size(); ++i){
            window.draw(sprites[i]);
        }*/
        // Display the result
        window.display();
    }

    // End of application
    return EXIT_SUCCESS;
}
