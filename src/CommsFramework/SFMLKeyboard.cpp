#include "SFMLKeyboard.h"

#include "Graphical.h"


SFMLKeyboard::SFMLKeyboard()
{
    currentFramePressedKeys = new BaseList<Key>();
    previousFramePressedKeys = new BaseList<Key>();
}


SFMLKeyboard::~SFMLKeyboard()
{
    delete(currentFramePressedKeys);
    delete(previousFramePressedKeys);
}

bool SFMLKeyboard::IsKeyPressed(Key key)
{
    sf::Keyboard::Key convert = (sf::Keyboard::Key)key;

    bool res = sf::Keyboard::isKeyPressed(convert);

    return res;
}

bool SFMLKeyboard::IsKeyClicked(Key key)
{
    if (!previousFramePressedKeys->ContainsItem(key) && currentFramePressedKeys->ContainsItem(key))
    {
        return true;
    }
    else
    {
        return false;
    }

    return false;
}

void SFMLKeyboard::UpdateKeyboardState()
{
    previousFramePressedKeys->Clear();

    auto it = currentFramePressedKeys->GetContainer()->begin();
    while (it != currentFramePressedKeys->GetContainer()->end())
    {
        Key oldCurrentKey = (*it);

        previousFramePressedKeys->Add(oldCurrentKey);

        it++;
    }

    currentFramePressedKeys->Clear();

    for (int i = 0; i < sf::Keyboard::KeyCount; i++)
    {
        bool keyClicked = sf::Keyboard::isKeyPressed((sf::Keyboard::Key)i);

        if (keyClicked)
        {
            this->currentFramePressedKeys->Add((Key)i);
        }
    }
}
