#include <circle.h>
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <vector>
#include <SDL.h>
#undef main // SDL defines main, so we need to undefine it
#include <SDL_mouse.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

constexpr auto SCREEN_WIDTH = 1280;
constexpr auto SCREEN_HEIGHT = 720;

bool checkIfMouseIsWithinWindowAndLeftMouseButtonIsPressed(SDL_Window* window) {
    int x, y;
    Uint32 mouseState = SDL_GetMouseState(&x, &y);
    Uint32 windowFlags = SDL_GetWindowFlags(window);
    return (mouseState & SDL_BUTTON(SDL_BUTTON_LEFT)) && (windowFlags & SDL_WINDOW_MOUSE_FOCUS) && (windowFlags & SDL_WINDOW_INPUT_FOCUS);
}

static void setWindowTitleAccordingToFramerateAndTimeElapsed(SDL_Window* window) {
    static int frameCount = 0;
    static Uint32 lastFrameTime = 0;
    static char title[100];

    // Increment frame count every loop
    frameCount++;

    Uint32 currentTime = SDL_GetTicks();
    if (currentTime - lastFrameTime >= 1000) {  // Every second
        // Calculate FPS by dividing frames by elapsed time in seconds
        int fps = frameCount;  // FPS = frames per second
        int timeElapsedInSeconds = (currentTime - lastFrameTime) / 1000;

        // Set window title with the calculated FPS
        int succ = sprintf_s(title, "Drawboard | FPS: %d", fps);
        if (succ < 0) {
            std::cerr << "sprintf_s Error: " << succ << std::endl;
        }
        SDL_SetWindowTitle(window, title);

        // Reset for the next frame
        lastFrameTime = currentTime;
        frameCount = 0;
    }
}

int main(int argc, char* argv[]) {
    // program start
    std::cout << "Hello, World!" << std::endl;

    // SDL2 initialization
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        std::cerr << "SDL_Init Error: " << SDL_GetError() << std::endl;
        return 1;
    }
    else {
        std::cout << "SDL_Init Success!" << std::endl;
    }
    if (IMG_Init(IMG_INIT_PNG) != IMG_INIT_PNG) {
        std::cerr << "IMG_Init Error: " << IMG_GetError() << std::endl;
        return 1;
    }
    else {
        std::cout << "IMG_Init Success!" << std::endl;
    }
    if (TTF_Init() != 0) {
        std::cerr << "TTF_Init Error: " << TTF_GetError() << std::endl;
        return 1;
    }
    else {
        std::cout << "TTF_Init Success!" << std::endl;
    }

    // SDL2 window creation
    SDL_Window* window = SDL_CreateWindow("Drawboard", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (window == nullptr || !window) {
        std::cerr << "SDL_CreateWindow Error: " << SDL_GetError() << std::endl;
        return 1;
    }
    else {
        std::cout << "SDL_CreateWindow Success!" << std::endl;
    }

    // SDL2 renderer creation
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (renderer == nullptr || !renderer) {
        std::cerr << "SDL_CreateRenderer Error: " << SDL_GetError() << std::endl;
        return 1;
    }
    else {
        std::cout << "SDL_CreateRenderer Success!" << std::endl;
    }

    // display the title of the window at top center of window as ttf text
	TTF_Font* font = TTF_OpenFont("assets/Roboto-Regular.ttf", 20);
	if (font == nullptr) {
		std::cerr << "TTF_OpenFont Error: " << TTF_GetError() << std::endl;
		return 1;
	}
	else {
		std::cout << "TTF_OpenFont Success!" << std::endl;
	}
   
    // text color
	SDL_Color textColor = { 0, 0, 0, 255 };
	SDL_Surface* textSurface = TTF_RenderText_Solid(font, "Drawboard", textColor);
	if (textSurface == nullptr) {
		std::cerr << "TTF_RenderText_Solid Error: " << TTF_GetError() << std::endl;
		return 1;
	}
	else {
		std::cout << "TTF_RenderText_Solid Success!" << std::endl;
	}
	SDL_Texture* textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
	if (textTexture == nullptr) {
		std::cerr << "SDL_CreateTextureFromSurface Error: " << SDL_GetError() << std::endl;
		return 1;
	}
	else {
		std::cout << "SDL_CreateTextureFromSurface Success!" << std::endl;
	}
	SDL_FreeSurface(textSurface);

	// now display some text regarding the color keybinds just below the title
	textSurface = TTF_RenderText_Solid(font, "Press 0-9 to change color", textColor);
	if (textSurface == nullptr) {
		std::cerr << "TTF_RenderText_Solid Error: " << TTF_GetError() << std::endl;
		return 1;
	}
	else {
		std::cout << "TTF_RenderText_Solid Success!" << std::endl;
	}
	SDL_Texture* textTexture2 = SDL_CreateTextureFromSurface(renderer, textSurface);
	if (textTexture2 == nullptr) {
		std::cerr << "SDL_CreateTextureFromSurface Error: " << SDL_GetError() << std::endl;
		return 1;
	}
	else {
		std::cout << "SDL_CreateTextureFromSurface Success!" << std::endl;
	}
	SDL_FreeSurface(textSurface);

	// now display some text regarding the clear keybind just beside the color keybinds
	textSurface = TTF_RenderText_Solid(font, "Press SPACE to clear", textColor);
	if (textSurface == nullptr) {
		std::cerr << "TTF_RenderText_Solid Error: " << TTF_GetError() << std::endl;
		return 1;
	}
	else {
		std::cout << "TTF_RenderText_Solid Success!" << std::endl;
	}
	SDL_Texture* textTexture3 = SDL_CreateTextureFromSurface(renderer, textSurface);
	if (textTexture3 == nullptr) {
		std::cerr << "SDL_CreateTextureFromSurface Error: " << SDL_GetError() << std::endl;
		return 1;
	}
	else {
		std::cout << "SDL_CreateTextureFromSurface Success!" << std::endl;
	}
	SDL_FreeSurface(textSurface);

	// Set the color keybinds text position
	SDL_Rect textRect;
	textRect.x = 10;
	textRect.y = 30;
	SDL_QueryTexture(textTexture, NULL, NULL, &textRect.w, &textRect.h);

	// Set the clear keybind text position
	SDL_Rect textRect2;
	textRect2.x = 10;
	textRect2.y = 60;
	SDL_QueryTexture(textTexture2, NULL, NULL, &textRect2.w, &textRect2.h);

	// Set the title text position
	SDL_Rect textRect3;
	textRect3.x = SCREEN_WIDTH - 200;
	textRect3.y = 30;
	SDL_QueryTexture(textTexture3, NULL, NULL, &textRect3.w, &textRect3.h);

    // Define the color palette with 10 colors
    SDL_Color colorPalette[10] = {
        {255, 0, 0, 255},    // red
        {0, 255, 0, 255},    // green
        {0, 0, 255, 255},    // blue
        {255, 255, 0, 255},  // yellow
        {0, 255, 255, 255},  // cyan
        {255, 0, 255, 255},  // magenta
        {128, 0, 0, 255},    // dark red
        {0, 128, 0, 255},    // dark green
        {0, 0, 128, 255},    // dark blue
        {128, 128, 0, 255}   // olive
    };

    // Pre-generate textures for each color
    SDL_Texture* circleTextures[10];
    for (int i = 0; i < 10; ++i) {
        SDL_Surface* surface = SDL_CreateRGBSurface(0, 40, 40, 32, 0x00FF0000, 0x0000FF00, 0x000000FF, 0xFF000000);
        SDL_FillRect(surface, NULL, SDL_MapRGBA(surface->format, colorPalette[i].r, colorPalette[i].g, colorPalette[i].b, colorPalette[i].a));

        circleTextures[i] = SDL_CreateTextureFromSurface(renderer, surface);
        SDL_FreeSurface(surface);
    }

    // vector to hold circles
    std::vector<Circle*> circlesVec;

    // Selected color index (0-9)
    int selectedColor = 0;

    // SDL2 event loop
    SDL_Event event;
    bool running = true;
    while (running) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = false;
            }
            if (event.type == SDL_KEYDOWN) {
                if (event.key.keysym.sym == SDLK_SPACE) {
                    // Empty the circleVec
                    for (int i = 0; i < circlesVec.size(); ++i) {
                        delete circlesVec[i];
                    }
                    circlesVec.clear();
                }
                if (event.key.keysym.sym >= SDLK_0 && event.key.keysym.sym <= SDLK_9) {
                    selectedColor = event.key.keysym.sym - SDLK_0;  // Set selected color based on key press
                }
            }
        }

        // Set window title according to framerate and time elapsed
        setWindowTitleAccordingToFramerateAndTimeElapsed(window);

        // Check if the mouse is inside the window and the left mouse button is pressed
        if (checkIfMouseIsWithinWindowAndLeftMouseButtonIsPressed(window)) {
            // Get mouse position
            int x, y;
            SDL_GetMouseState(&x, &y);

            // Create new circle with selected color
            circlesVec.push_back(new Circle(x, y, 10.0f, circleTextures[selectedColor], renderer));
        }

        // Clear the screen
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_RenderClear(renderer);

		// Render text
		SDL_RenderCopy(renderer, textTexture, NULL, &textRect);
		SDL_RenderCopy(renderer, textTexture2, NULL, &textRect2);
		SDL_RenderCopy(renderer, textTexture3, NULL, &textRect3);

        // Render circles
        for (int i = 0; i < circlesVec.size(); ++i) {
            circlesVec[i]->draw();
        }

        // Present the screen
        SDL_RenderPresent(renderer);

        // Check for SDL errors
        if (SDL_GetError() != nullptr && SDL_GetError()[0] != '\0') {
            std::cerr << "SDL Error: " << SDL_GetError() << std::endl;
        }
    }

    // Clean up textures
    for (int i = 0; i < 10; ++i) {
        SDL_DestroyTexture(circleTextures[i]);
    }

    // SDL2 cleanup
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    TTF_Quit();
    IMG_Quit();
    SDL_Quit();

    // Program end
    std::cout << "Goodbye, World!" << std::endl;

    return 0;
}
