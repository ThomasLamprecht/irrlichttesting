#ifndef CSAMPLESCENENODE_H
#define CSAMPLESCENENODE_H

#include <irrlicht.h>
using namespace irr;
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

class CSampleSceneNode : public scene::ISceneNode
{

    /*
    First, we declare some member variables:
    The bounding box, 4 vertices, and the material of the tetraeder.
    */
    core::aabbox3d<f32> Box;
    video::S3DVertex Vertices[4];
    video::SMaterial Material;

    /*
    The parameters of the constructor specify the parent of the scene node,
    a pointer to the scene manager, and an id of the scene node.
    In the constructor we call the parent class' constructor,
    set some properties of the material, and
    create the 4 vertices of the tetraeder we will draw later.
    */

public:

    CSampleSceneNode(scene::ISceneNode* parent, scene::ISceneManager* mgr, s32 id);
    //        : scene::ISceneNode(parent, mgr, id)



    virtual void OnRegisterSceneNode()
    {
        if (IsVisible)
            SceneManager->registerNodeForRendering(this);

        ISceneNode::OnRegisterSceneNode();
    }

    /*
    In the render() method most of the interesting stuff happens: The
    Scene node renders itself. We override this method and draw the
    tetraeder.
    */
    virtual void render()
    {
        u16 indices[] = {	0,2,3, 2,1,3, 1,0,3, 2,0,1	};
        video::IVideoDriver* driver = SceneManager->getVideoDriver();

        driver->setMaterial(Material);
        driver->setTransform(video::ETS_WORLD, AbsoluteTransformation);
        driver->drawVertexPrimitiveList(&Vertices[0], 4, &indices[0], 4, video::EVT_STANDARD, scene::EPT_TRIANGLES, video::EIT_16BIT);
    }

    /*
    And finally we create three small additional methods.
    irr::scene::ISceneNode::getBoundingBox() returns the bounding box of
    this scene node, irr::scene::ISceneNode::getMaterialCount() returns the
    amount of materials in this scene node (our tetraeder only has one
    material), and irr::scene::ISceneNode::getMaterial() returns the
    material at an index. Because we have only one material here, we can
    return the only one material, assuming that no one ever calls
    getMaterial() with an index greater than 0.
    */
    virtual const core::aabbox3d<f32>& getBoundingBox() const
    {
        return Box;
    }

    virtual u32 getMaterialCount() const
    {
        return 1;
    }

    virtual video::SMaterial& getMaterial(u32 i)
    {
        return Material;
    }
};


#endif // CSAMPLESCENENODE_H
