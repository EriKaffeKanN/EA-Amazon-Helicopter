#include "menu.h"
#include "game.h"

#include <iostream>
#include <string>

Menu::Menu (sf::RenderTarget& renderTarget, std::vector<MenuItem> menuItems)
    : target (renderTarget), items (menuItems), lastPressed (0), currSelected (0) {  }

void Menu::update ()
{
    this->items [this->currSelected].onDeselect ();

    if (sf::Keyboard::isKeyPressed (sf::Keyboard::Key::U))
    {
        if (!(this->lastPressed & static_cast<int> (Menu::menuInputs::UP)))
        {
            this->currSelected -= 1;
            this->lastPressed |= static_cast<int> (Menu::menuInputs::UP);
        }
    }
    else
    {
        this->lastPressed &= ~(static_cast<int> (Menu::menuInputs::UP));
    }

    if (sf::Keyboard::isKeyPressed (sf::Keyboard::Key::S))
    {
        if (!(this->lastPressed & static_cast<int> (Menu::menuInputs::DOWN)))
        {
            this->currSelected -= 1;
            this->lastPressed |= static_cast<int> (Menu::menuInputs::DOWN);
        }
    }
    else
    {
        this->lastPressed &= ~(static_cast<int> (Menu::menuInputs::DOWN));
    }

    // This actually needs to be debounced as well since it can be returned to
    // from the pause menu
    if (sf::Keyboard::isKeyPressed (sf::Keyboard::Key::Enter))
    {
        if (!(this->lastPressed & static_cast<int> (Menu::menuInputs::CLICK)))
        {
            this->items [this->currSelected].call ();
            this->lastPressed |= static_cast<int> (Menu::menuInputs::CLICK);

            // This return is absolutely neccesary to avoid segfaults, should the menu
            // be deleted by the callback
            return;
        }
    }
    else
    {
        this->lastPressed &= ~(static_cast<int> (Menu::menuInputs::CLICK));
    }

    if (this->currSelected < 0)
    {
        this->currSelected = this->items.size () - 1;
    }

    this->items [this->currSelected].onSelect ();

    sf::Font font;
    font.loadFromFile ("../resources/fonts/LiberationSans-Regular.ttf");
    for (int i = 0,
        pos = this->target.getView ().getCenter ().y -
            ((this->items.size () / 2 + 1) * this->items [0].text.getCharacterSize ());
        i < this->items.size (); i++, pos += 50)
    {
        this->items [i].text.setFont (font);
        uint16_t textWidth = this->items [i].text.getLocalBounds ().width;
        this->items [i].text.setPosition (
                (target.getView ().getCenter ().x) - textWidth / 2, pos);
        this->items [i].draw (this->target);
    }
}

Menu::MenuItem::MenuItem (const std::string& text, std::function<void ()> callback)
{
    // TODO: Maybe have a global variable somewhere for settings like fonts
    // instead of hardcoding paths everywhere. Perhaps as a part of SceneSettings?
    this->text.setString (text);
    this->text.setCharacterSize (24);
    this->text.setFillColor (sf::Color::Black);

    this->onClick = callback;
}

void Menu::MenuItem::call ()
{
    this->onClick ();
}

void Menu::MenuItem::onSelect ()
{
    // this->text.setStyle (sf::Text::Bold | sf::Text::Underlined);
    this->text.setStyle (sf::Text::Bold);
}

void Menu::MenuItem::onDeselect ()
{
    this->text.setStyle (sf::Text::Regular);
}

// void Menu::MenuItem::draw (sf::RenderTarget& target, sf::RenderStates states) const
void Menu::MenuItem::draw (sf::RenderTarget& target)
{
    sf::Font font;
    font.loadFromFile ("../resources/fonts/LiberationSans-Regular.ttf");
    this->text.setFont (font);

    // Rectangle around menuitem (maybe store this instead of creating it every time?)
    sf::FloatRect bounds = this->text.getGlobalBounds ();
    sf::RectangleShape rect (sf::Vector2f (bounds.width + 10, bounds.height + 10));
    rect.setOutlineColor (sf::Color::Black);
    rect.setOutlineThickness (1);
    rect.setFillColor (sf::Color::White);
    rect.setPosition (bounds.left - 5, bounds.top - 5);
    target.draw (rect);

    target.draw (this->text);
}
