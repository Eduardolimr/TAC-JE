#define INCLUDE_SDL
#define INCLUDE_SDL_IMAGE

#include "SDL_include.h"
#include "State.h"
#include <string>

State::State():bg(), music(){
    quitRequested = false;

    GameObject *go = new GameObject();
    go->box.x = 0;
    go->box.y = 0;
    go->box.w = bg->GetWidth();
    go->box.h= bg->GetHeight();

    bg = new Sprite(*go, ".././assets/img/ocean.jpg");
    go->AddComponent(go);

    objectArray.insert(objectsArray.end(), go);
}


State::~State(){
    objectArray.clear();
}



void State::Input() {
	SDL_Event event;
	int mouseX, mouseY;

	// Obtenha as coordenadas do mouse
	SDL_GetMouseState(&mouseX, &mouseY);

	// SDL_PollEvent retorna 1 se encontrar eventos, zero caso contrário
	while (SDL_PollEvent(&event)) {

		// Se o evento for quit, setar a flag para terminação
		if(event.type == SDL_QUIT) {
			quitRequested = true;
		}
		
		// Se o evento for clique...
		if(event.type == SDL_MOUSEBUTTONDOWN) {

			// Percorrer de trás pra frente pra sempre clicar no objeto mais de cima
			for(int i = objectArray.size() - 1; i >= 0; --i) {
				// Obtem o ponteiro e casta pra Face.
				GameObject* go = (GameObject*) objectArray[i].get();
				// Nota: Desencapsular o ponteiro é algo que devemos evitar ao máximo.
				// O propósito do unique_ptr é manter apenas uma cópia daquele ponteiro,
				// ao usar get(), violamos esse princípio e estamos menos seguros.
				// Esse código, assim como a classe Face, é provisório. Futuramente, para
				// chamar funções de GameObjects, use objectArray[i]->função() direto.

				if(go->box.Contains( {(float)mouseX, (float)mouseY} ) ) {
					Face* face = (Face*)go->GetComponent( "Face" );
					if ( nullptr != face ) {
						// Aplica dano
						face->Damage(std::rand() % 10 + 10);
						// Sai do loop (só queremos acertar um)
						break;
					}
				}
			}
		}
		if( event.type == SDL_KEYDOWN ) {
			// Se a tecla for ESC, setar a flag de quit
			if( event.key.keysym.sym == SDLK_ESCAPE ) {
				quitRequested = true;
			}
			// Se não, crie um objeto
			else {
				Vec2 objPos = Vec2( 200, 0 ).GetRotated( -PI + PI*(rand() % 1001)/500.0 ) + Vec2( mouseX, mouseY );
				AddObject((int)objPos.x, (int)objPos.y);
			}
		}
	}
}


void::Render(){
    Input();
    for(int i : objectArray){
        objectArray[i]->Render();
    }
}


void AddObject(int mouseX, int mouseY){

}


void State::LoadAssets(){
    std::string str1, str2;
    str1 = ".././assets/img/ocean.jpg";
    str2 = ".././assets/audio/stageState.ogg";

    bg.Open(str1);
    bg.Render(0,0);
    music.Open(str2);
    music.Play();
}


void State::Update(float dt){
    if(SDL_QuitRequested()){
        quitRequested = true;
    }
}


bool State::QuitRequested(){
    return quitRequested;
}