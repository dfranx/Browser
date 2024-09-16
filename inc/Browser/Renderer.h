#ifndef __BROWSERJAM_RENDERER_H__
#define __BROWSERJAM_RENDERER_H__

#include <windows.h>
#include <d2d1.h>
#include <dwrite.h>


namespace sb
{

////////////////////////////////////////////////////////////////////////////////////////////////////
class Renderer
{
public:
    Renderer();

    // Create a Direct2D renderer for the given window
    bool Create(HWND hWnd);

    // Clean up the memory / destroy D2D/DWrite factories
    void Shutdown();

    inline ID2D1Factory* Get2DFactory() const { return mD2DFactory; }
    inline IDWriteFactory* GetWriteFactory() const { return mDWriteFactory; }
    inline ID2D1HwndRenderTarget* GetRenderTarget() const { return mRenderTarget; }

private:
    ID2D1Factory* mD2DFactory;
    ID2D1HwndRenderTarget* mRenderTarget;
    IDWriteFactory* mDWriteFactory;
};

}

#endif //__BROWSERJAM_RENDERER_H__
