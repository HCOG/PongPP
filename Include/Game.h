#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <unordered_map>
#include <string>
#include <vector>

class Game
{
public:
	//Default constructor
	Game();
	//Three principle functions: Initialize; run; shutdown the game
	bool Initialize();
	void RunLoop();
	void Shutdown();

	//Add/remove actors to the game
	void AddActor(class Actor* actor);
	void RemoveActor(class Actor* actor);

	//Add/remove sprite to the game
	void AddSprite(class SpriteComponent* sprite);
	void RemoveSprite(class SpriteComponent* sprite);

	//Load textures needed for sprites
	SDL_Texture* GetTexture(const std::string& fileName);

private:
	//Three helper functions that will update each frame to help run the game
	void ProcessInput();
	void UpdateGame();
	void GenerateOutput();

	//Load/unload actors
	void LoadData();
	void UnloadData();

	// Map of textures loaded
	std::unordered_map<std::string, SDL_Texture*> mTextures;

	// All the actors in the game
	std::vector<class Actor*> mActors;
	// Any pending actors
	std::vector<class Actor*> mPendingActors;

	// All the sprite components drawn
	std::vector<class SpriteComponent*> mSprites;

	//Window created by SDL
	SDL_Window* mWindow;
	SDL_Renderer* mRenderer;

	//Game should continue to run
	bool mIsRunning;

	//Time ticks from begin of game
	Uint32 mTicksCount;

	// Track if we're updating actors right now
	bool mUpdatingActors;

	//Game-Specific
	class Paddle* LPaddle;	//Player 1's paddle
	class Paddle* RPaddle;	//Player 2's paddle
	class Ball* ball;		//Ball
};

