#include "db-util.hpp"
#include "demo.hpp"
#include "builder.hpp"
#include "testdemo.hpp"

class TestDemoBuilderLoadCallback: public BuilderLoadCallback
{
public:
    void loading(int numberOfSteps, int currentStep)
    {

    }
};

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	WindowInfo windowInfo = createD3DWindow(640, 480, true);
    TestDemoBuilderLoadCallback* builderCallback = new TestDemoBuilderLoadCallback();
    Builder builder;
    builder.device = windowInfo.device;
    builder.setLoadCallback(builderCallback);
    builder.load(testdemoBuilderData);

    Mesh* spaceShipMesh = builder.getMesh(DB_BUILDER_EXPORT_SPACESHIP);
    Mesh* torusMesh = builder.getMesh(DB_BUILDER_EXPORT_TORUS);

    float time = 0.0f;
    do
    {
        time += 0.0001f;
        //tick = getTick();
        MSG msg;
        PeekMessage(&msg, windowInfo.window, 0, 0, PM_REMOVE);
        
        windowInfo.device->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB(0,0,64), 1.0f, 0);
       

        D3DXMATRIX identity;
        D3DXMatrixIdentity(&identity);
        windowInfo.device->SetTransform(D3DTS_WORLD, &identity);

        D3DXMATRIX projection;
        D3DXMatrixPerspectiveFovLH(&projection, 
                                   D3DXToRadian(45.0f), 
                                   640 / (float)480, 
                                   0.1f, 
                                   100.0f);
        Builder::device->SetTransform(D3DTS_PROJECTION, &projection);
        Builder::device->SetFVF(D3DFVF_XYZ);

        D3DXMATRIX translation;
        D3DXMatrixTranslation(&translation, 0.0f, 0.0f, 10.0f);
        D3DXMATRIX rotationX;
        D3DXMatrixRotationX(&rotationX, time);
        D3DXMATRIX rotationY;
        D3DXMatrixRotationY(&rotationY, time);
        D3DXMATRIX lookat;
        D3DXMatrixLookAtLH(&lookat,
                           &Vec3(0.0f, 0.0f, -3.0f),
                           &Vec3(0.0f, 0.0f, 0.0f),
                           &Vec3(0.0f, 1.0f, 0.0f));
        D3DXMATRIX view = rotationX * rotationY * translation * lookat;
        windowInfo.device->SetTransform(D3DTS_VIEW, &view);

        windowInfo.device->SetRenderState(D3DRS_LIGHTING, FALSE);
        windowInfo.device->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);
        windowInfo.device->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);
       
        windowInfo.device->BeginScene();
        spaceShipMesh->render();

        D3DXMatrixTranslation(&translation, 0.0f, 0.0f, -2.0f);
        view = rotationX * rotationY * translation;
        windowInfo.device->SetTransform(D3DTS_WORLD, &view);
        torusMesh->render();
        windowInfo.device->EndScene();

        windowInfo.device->Present(NULL, NULL, NULL, NULL);
      
    } while (!GetAsyncKeyState(VK_ESCAPE));// && coreOperators[0]->ticks > tick);
}