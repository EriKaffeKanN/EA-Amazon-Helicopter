#ifndef MENU_H
#define MENU_H

#include <SFML/Graphics.hpp>
#include <functional>
#include <vector>

// TODO: Make the menus more customizable with regards to for example padding
// and character size
// Also this currently doesn't check if all the menu items actually fit on the
// screen
class Menu
{
public:
    class MenuItem
    {
    public:
        MenuItem (const std::string& text, std::function<void ()> callback);

        // Called when the item is selected/deselected but not clicked (i.e on
        // hover)
        void onSelect ();
        void onDeselect ();
        void call ();

        void draw (sf::RenderTarget& target);

        // For some very strange reason the font has to be reinitialized all
        // the time before the text is used.
        // It does not work to store it in the menuItem class
        sf::Text text;
    private:
        std::function<void ()> onClick;
    };

    Menu (sf::RenderTarget& targer, std::vector<Menu::MenuItem> menuItems);
    void update ();

private:
    sf::RenderTarget& target;
    // Array of all items
    std::vector<Menu::MenuItem> items;

    enum class menuInputs
    {
        UP = 1,
        DOWN = 2,
        CLICK = 4
    };

    uint8_t lastPressed;
    int8_t currSelected;
};

#endif
