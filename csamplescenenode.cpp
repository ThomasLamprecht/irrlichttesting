#include "csamplescenenode.h"

/*
Here comes the more sophisticated part of this tutorial:
The class of our very own custom scene node. To keep it simple,
our scene node will not be an indoor portal renderer nor a terrain
scene node, but a simple tetraeder, a 3d object consisting of 4
connected vertices, which only draws itself and does nothing more.
Note that this scenario does not require a custom scene node in Irrlicht.
Instead one would create a mesh from the geometry and pass it to a
irr::scene::IMeshSceneNode. This example just illustrates creation of a custom
scene node in a very simple setting.

To let our scene node be able to be inserted into the Irrlicht
Engine scene, the class we create needs to be derived from the
irr::scene::ISceneNode class and has to override some methods.
*/


    CSampleSceneNode::CSampleSceneNode(scene::ISceneNode* parent, scene::ISceneManager* mgr, s32 id)
        : scene::ISceneNode(parent, mgr, id)
    {
        Material.Wireframe = false;
        Material.Lighting = false;

        Vertices[0] = video::S3DVertex(0,0,10, 1,1,0,
                video::SColor(255,0,255,255), 0, 1);
        Vertices[1] = video::S3DVertex(10,0,-10, 1,0,0,
                video::SColor(255,255,0,255), 1, 1);
        Vertices[2] = video::S3DVertex(0,20,0, 0,1,1,
                video::SColor(255,255,255,0), 1, 0);
        Vertices[3] = video::S3DVertex(-10,0,-10, 0,0,1,
                video::SColor(255,0,255,0), 0, 0);

    /*
    The Irrlicht Engine needs to know the bounding box of a scene node.
    It will use it for automatic culling and other things. Hence, we
    need to create a bounding box from the 4 vertices we use.
    If you do not want the engine to use the box for automatic culling,
    and/or don't want to create the box, you could also call
    irr::scene::ISceneNode::setAutomaticCulling() with irr::scene::EAC_OFF.
    */
        Box.reset(Vertices[0].Pos);
        for (s32 i=1; i<4; ++i)
            Box.addInternalPoint(Vertices[i].Pos);
    }
