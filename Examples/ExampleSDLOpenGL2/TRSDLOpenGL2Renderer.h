#include "Libs/SDL2/include/SDL.h"
#include "Libs/SDL2/include/SDL_syswm.h"
#include "Libs/SDL2/include/SDL_opengl.h"

#include "..\..\TextRenderer.h"

namespace TRImpl
{
	void NewFrame(SDL_Window* window);
	void Render();
}

namespace TRInternal
{
	int LoadTexture(TR_uchar* data, TRVec2 size);
	void UnloadTexture();

	void RenderShape(TRInternal::TRDrawShape shape);
}