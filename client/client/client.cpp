#include "stdafx.h"
#include "binaryConverter.h"
#include "Messages.h"
#include "dataBuffer.h"
#include "messageQueue.h"
#include "constants.h"
#include "streamReader.h"
#include <cstdint>
#include <SDL_net.h>
#include <stdio.h>
#include <string>
#include <SDL.h>
#include <iostream>
#include <SDL_ttf.h>
#include <thread>
using namespace std;

void initSDL() {
	if (SDL_Init(SDL_INIT_VIDEO) != 0) {
		cerr << "SDL_Init() Failed: " <<
			SDL_GetError() << endl;
		exit(1);
	}
}
void initTTF() {
	if (TTF_Init() != 0)
	{
		cerr << "TTF_Init() Failed: " << TTF_GetError() << endl;
		SDL_Quit();
		exit(1);
	}
}

SDL_Window* createWindow() {
	auto window = SDL_CreateWindow("Pong++", 100, 100, constants::boardWidth,
		constants::boardHeight, SDL_WINDOW_SHOWN);
	if (window == NULL) {
		cerr << "Failed to create window" << endl;
		exit(1);
	}
	return window;
}

SDL_Renderer* createRenderer(SDL_Window* window) {
	return SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
}

SDL_Surface* getText(string text, TTF_Font* font) {
	SDL_Surface *textSurface;
	SDL_Color text_color = { 255, 255, 255 };
	textSurface = TTF_RenderText_Solid(font,
		text.c_str(),
		text_color);

	if (textSurface == NULL)
	{
		cerr << "TTF_RenderText_Solid() Failed: " << TTF_GetError() << endl;
		exit(1);
	}
}

TTF_Font* getFont(string fontName, int size) {
	TTF_Font* font;
	font = TTF_OpenFont(fontName.c_str(), size);
	if (font == NULL)
	{
		cerr << "TTF_OpenFont() Failed: " << TTF_GetError() << endl;
		TTF_Quit();
		SDL_Quit();
		exit(1);
	}
	return font;
}

int main(int argc, char *argv[])
{
	SDLNet_Init();

	IPaddress ip;
	SDLNet_ResolveHost(&ip, constants::serverAddr.c_str(), constants::serverPort);
	TCPsocket conn = SDLNet_TCP_Open(&ip);
	
	thread listener(streamReader::startReader, conn);
	listener.detach();
	
	initSDL();
	initTTF();


	SDL_Window* window = createWindow();
	SDL_Renderer* renderer = createRenderer(window);
	SDL_Event mainEvent = SDL_Event();
	TTF_Font* font = getFont("Sans.ttf", 24);

	auto text = getText("This is text on a screen!", font);
	
	bool quit = false;
	while (!quit) {
		SDL_PollEvent(&mainEvent);
		if (mainEvent.type == SDL_QUIT) {
			quit = true;
		}

		SDL_RenderClear(renderer);
		auto textTexture = SDL_CreateTextureFromSurface(renderer, text);
		SDL_RenderPresent(renderer);
	}

	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	TTF_Quit();
	SDL_Quit();
	return 0;
}



