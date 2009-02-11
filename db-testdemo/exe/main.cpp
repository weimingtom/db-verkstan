#include <db-util.hpp>
#include <demo.hpp>


int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	WindowInfo windowInfo = createD3DWindow(640, 480, true);

	 do
    {
        //tick = getTick();
        MSG msg;
        PeekMessage(&msg, windowInfo.window, 0, 0, PM_REMOVE);
        /*
        for (int i = 0; i < coreNumberOfLights; i++)
            globalDirect3DDevice->LightEnable(i, FALSE);
*/
  //      coreNumberOfLights = 0;
//
  //      coreOperators[0]->cascadeProcess();
    //    coreOperators[0]->preRender(tick);

//        globalWorldMatrixStack->LoadIdentity();
  //      globalDirect3DDevice->SetTransform(D3DTS_WORLD, globalWorldMatrixStack->GetTop());
        
        windowInfo.device->BeginScene();
//        coreOperators[0]->render(tick);
        windowInfo.device->EndScene();

        windowInfo.device->Present(NULL, NULL, NULL, NULL);
      
    } while (!GetAsyncKeyState(VK_ESCAPE));// && coreOperators[0]->ticks > tick);
}