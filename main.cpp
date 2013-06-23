/** Example 003 Custom SceneNode

This Tutorial is more advanced than the previous ones.
If you are currently just playing around with the Irrlicht
engine, you may want to look at other examples first.
This tutorials shows how to create a custom scene node and
how to use it in the engine. A custom scene node is needed
if you want to implement a render technique the Irrlicht
Engine currently does not support. For example, you can write
an indoor portal based renderer or an advanced terrain scene
node with it. By creating custom scene nodes, you can
easily extend the Irrlicht Engine and adapt it to your own
needs.

I will keep the tutorial simple: Keep everything very
short, everything in one .cpp file, and I'll use the engine
here as in all other tutorials.

To start, I include the header files, use the irr namespace,
and tell the linker to link with the .lib file.
*/
#include <irrlicht.h>
#include "csamplescenenode.h"
//#include "driverChoice.h"

using namespace irr;

#ifdef _MSC_VER
#pragma comment(lib, "Irrlicht.lib")
#endif



/*
That's it. The Scene node is done. Now we simply have to start
the engine, create the scene node and a camera, and look at the result.
*/
int main()
{
    // create device
    IrrlichtDevice *device = createDevice(video::EDT_OPENGL, core::dimension2d<u32>(800, 600), 16, false);
    device->setResizable(false);


    if (device == 0)
        return 1; // could not create selected driver.

    // create engine and camera

    device->setWindowCaption(L"Custom Scene Node - OctopuStudio");

    video::IVideoDriver* driver = device->getVideoDriver();
    scene::ISceneManager* smgr = device->getSceneManager();

    smgr->addCameraSceneNode(0, core::vector3df(0,-40,0), core::vector3df(0,0,0));

    /*
    Create our scene node. I don't check the result of calling new, as it
    should throw an exception rather than returning 0 on failure. Because
    the new node will create itself with a reference count of 1, and then
    will have another reference added by its parent scene node when it is
    added to the scene, I need to drop my reference to it. Best practice is
    to drop it only *after* I have finished using it, regardless of what
    the reference count of the object is after creation.
    */
    CSampleSceneNode *myNode = new CSampleSceneNode(smgr->getRootSceneNode(), smgr, 666);
    //    myNode->setRotation(core::vector3df(60.0f, 90.0f, 45.0f));

    /*
    To animate something in this boring scene consisting only of one
    tetraeder, and to show that you now can use your scene node like any
    other scene node in the engine, we add an animator to the scene node,
    which rotates the node a little bit.
    irr::scene::ISceneManager::createRotationAnimator() could return 0, so
    should be checked.
    */
    scene::ISceneNodeAnimator* anim = smgr->createRotationAnimator(core::vector3df(.0f, 0.0f, .3f));

    device->getCursorControl()->setVisible(false);
    if(anim)
    {
        myNode->addAnimator( anim );

        /*
            I'm done referring to anim, so must
            irr::IReferenceCounted::drop() this reference now because it
            was produced by a createFoo() function. As I shouldn't refer to
            it again, ensure that I can't by setting to 0.
            */
        anim->drop();
        anim = 0;
    }

    /*
    I'm done with my CSampleSceneNode object, and so must drop my reference.
    This won't delete the object, yet, because it is still attached to the
    scene graph, which prevents the deletion until the graph is deleted or the
    custom scene node is removed from it.
    */
    myNode->drop();
    myNode = 0; // As I shouldn't refer to it again, ensure that I can't

    /*
    Now draw everything and finish.
    */
    u32 frames=0;
    while(device->run())
    {
        //if(device->isWindowActive())
        {
            driver->beginScene(true, true, video::SColor(0,100,100,127));
            core::position2d<s32> m = device->getCursorControl()->getPosition();
//            driver->draw2DRectangleOutline(core::rect<s32>(m.X-20, m.Y-20, m.X+20, m.Y+20));

            driver->draw2DRectangle(video::SColor(255,255,255,0), core::rect<s32>(m.X-20, m.Y-20, m.X+20, m.Y+20));
            driver->draw2DRectangle(video::SColor(255,0,0,255), core::rect<s32>(m.X-16, m.Y-15, m.X-10, m.Y-9));
            driver->draw2DRectangle(video::SColor(255,0,255,0), core::rect<s32>(m.X+10, m.Y-15, m.X+16, m.Y-9));

            //        driver->setFog(video::SColor(127,255,255,255), video::EFT_FOG_LINEAR, 10.f, 100.f, 0.01f, false, false);
            smgr->drawAll();

            driver->endScene();
            if (++frames==100)
            {
                core::stringw str = L"Irrlicht - OctopusStudio [";
                str += driver->getName();
                str += L"] FPS: ";
                str += (s32)driver->getFPS();

                device->setWindowCaption(str.c_str());
                frames=0;
            }
        }
    }

    device->drop();

    return 0;
}
