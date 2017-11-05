#pragma once

class GameEngine;

class FantasyGame
{
public:
    FantasyGame();
    ~FantasyGame();


    void Init();

    GameEngine* Engine;

    void Play();
};


