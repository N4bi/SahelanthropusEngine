# Sahelanthropus Engine
3D Game Engine created and developed by Iván Pérez Latorre for educational purposes.

You can find the source code on this [Github repository](https://github.com/N4bi/Sahelanthropus_Engine). This engine is under [MIT License](https://github.com/N4bi/Sahelanthropus_Engine/blob/master/LICENSE).

### Keys
 * W -> camera front
 * S -> camera back
 * D -> camera right
 * A -> camera left

 * Q -> Create the Quadtree 

# How it works 

 * IMPORTANT: when the scene is created, press Q to create the quadtree, if you dont do that picking and culling will not work 
 * You can save the scene in the menu file->save scene, this will create a Json archive in Library/Save folder. NOTE: if you put a name that is already in use, will overwrite the previous scene
 * If you have scenes saved, you can load in the menu file->load scene,
 * You can Play/pause/stop in engine, if you push play and modify the scene and then push stop, the scene will be back to his previous state.
 * All fbx must be in Assets/Meshes and all the textures must be in Assets/Textures.
 * You can try the frustum culling with the camera test that you will find in hierarchy, this cam will do culling when you activate the option culling in his component camera. 
   NOTE: there is a bug (reported on issues) that when you load scene camera culling stops working. So if you want to try camera culling, try before you press file -> Load scene.     
 * You can select objects with RMB. 




