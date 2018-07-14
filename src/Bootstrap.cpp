#include <Ogre.h>
#include <OgreApplicationContext.h>
#include "DotSceneLoader.h"
#include "CollisionTools.h"

class MyTestApp : public OgreBites::ApplicationContext, public OgreBites::InputListener
{
public:
    MyTestApp();
    void setup();  
    bool keyPressed(const OgreBites::KeyboardEvent& evt);
    bool mouseMoved(const OgreBites::MouseMotionEvent& evt);
    Ogre::Camera* cam;
    MOC::CollisionTools* mCollisionTools;
};

//! [constructor]
MyTestApp::MyTestApp() : OgreBites::ApplicationContext("OgreTutorialApp")
{

}
//! [constructor]



//! [setup]
void MyTestApp::setup(void)
{
    // do not forget to call the base first
    OgreBites::ApplicationContext::setup();
    
    // register for input events
    addInputListener(this);
    setWindowGrab(true);

    //Ogre::RenderWindow* mRenderWin = mRoot->getAutoCreatedWindow();

    // get a pointer to the already created root
    Ogre::Root* root = getRoot();
    Ogre::SceneManager* scnMgr = root->createSceneManager(ST_GENERIC);

    //Viewport* viewport = mRenderWin->addViewport(cam);
    //viewport->setBackgroundColour(ColourValue(0.5, 0.5, 0.5));

    // register our scene with the RTSS
    Ogre::RTShader::ShaderGenerator* shadergen = Ogre::RTShader::ShaderGenerator::getSingletonPtr();
    shadergen->addSceneManager(scnMgr);

    // without light we would just get a black screen    
    Ogre::Light* light = scnMgr->createLight("MainLight");
    Ogre::SceneNode* lightNode = scnMgr->getRootSceneNode()->createChildSceneNode();
    light->setType(Ogre::Light::LT_DIRECTIONAL);
    light->setDiffuseColour(1, 1, 1);
    light->setSpecularColour(1, 1, 1);
    lightNode->setDirection(Ogre::Vector3(0,0,-1));
    lightNode->attachObject(light);

    DotSceneLoader* pDotSceneLoader = new DotSceneLoader();
    pDotSceneLoader->parseDotScene("Level.scene", "General", scnMgr, scnMgr->getRootSceneNode());
    delete pDotSceneLoader;

    scnMgr->setAmbientLight(ColourValue(0.2, 0.2, 0.2));
    mCollisionTools = new MOC::CollisionTools(scnMgr);

    // also need to tell where we are
    Ogre::SceneNode* cameraNode = scnMgr->getRootSceneNode()->createChildSceneNode();

    cameraNode->setPosition(0, 0, 9.1f);
    cameraNode->lookAt(Ogre::Vector3(0, 1, 9.1f), Ogre::Node::TS_PARENT);

    // create the camera
    cam = scnMgr->createCamera("myCam");
    cam->setNearClipDistance(0.2f); // specific to this sample
    cam->setAutoAspectRatio(true);
    cameraNode->attachObject(cam);

    // and tell it to render into the main window

    Ogre::RenderWindow* mRenderWin = getRenderWindow();
    Viewport* viewport = mRenderWin->addViewport(cam);
    viewport->setBackgroundColour(ColourValue(0.5, 0.5, 1));



    // finally something to render
    //ent = scnMgr->createEntity("Sinbad.mesh");
    //Ogre::SceneNode* node = scnMgr->getRootSceneNode()->createChildSceneNode();
    //node->attachObject(ent);
}
//! [setup]

//! [key_handler]
bool MyTestApp::keyPressed(const OgreBites::KeyboardEvent& evt)
{
    Ogre::uint32 mask = 1<<8;
    if (evt.keysym.sym == OgreBites::SDLK_ESCAPE)
    {
        getRoot()->queueEndRendering();
    }
    if (evt.keysym.sym == OgreBites::SDLK_UP)
    {
        Ogre::Vector3 pos = cam->getRealPosition();
        pos.z=3;
        cam->moveRelative(Ogre::Vector3(0, 0, -0.1));
        Ogre::Vector3 apos = cam->getRealPosition();
        apos.z=3;
        bool ret = mCollisionTools->collidesWithEntity(pos, apos, 1.5f, 0, mask);
        if (ret)
            cam->moveRelative(Ogre::Vector3(0, 0, +0.1));
    }
    if (evt.keysym.sym == OgreBites::SDLK_DOWN)
    {
        Ogre::Vector3 pos = cam->getRealPosition();
        pos.z=3;
        cam->moveRelative(Ogre::Vector3(0, 0, +0.1));
        Ogre::Vector3 apos = cam->getRealPosition();
        apos.z=3;
        bool ret = mCollisionTools->collidesWithEntity(pos, apos, 1.5f, 0, mask);
        if (ret)
            cam->moveRelative(Ogre::Vector3(0, 0, -0.1));
    }
    if (evt.keysym.sym == OgreBites::SDLK_LEFT)
    {
        Ogre::Vector3 pos = cam->getRealPosition();
        pos.z=3;
        cam->moveRelative(Ogre::Vector3(-0.1, 0, 0));
        Ogre::Vector3 apos = cam->getRealPosition();
        apos.z=3;
        bool ret = mCollisionTools->collidesWithEntity(pos, apos, 1.5f, 0, mask);
        if (ret)
            cam->moveRelative(Ogre::Vector3(+0.1, 0, 0));
    }
    if (evt.keysym.sym == OgreBites::SDLK_RIGHT)
    {
        Ogre::Vector3 pos = cam->getRealPosition();
        pos.z=3;
        cam->moveRelative(Ogre::Vector3(+0.1, 0, 0));
        Ogre::Vector3 apos = cam->getRealPosition();
        apos.z=3;
        bool ret = mCollisionTools->collidesWithEntity(pos, apos, 1.5f, 0, mask);
        if (ret)
            cam->moveRelative(Ogre::Vector3(-0.1, 0, 0));
    }
    Ogre::Vector3 pos = cam->getPosition();
    pos.y=0;
    cam->setPosition(pos);
    return true;
}
//! [key_handler]

bool MyTestApp::mouseMoved(const OgreBites::MouseMotionEvent& evt)
{
    cam->yaw(Ogre::Degree(-evt.xrel*0.5));
    cam->pitch(Ogre::Degree(-evt.yrel*0.5));
    Quaternion q = cam->getOrientation();
    q.normalise();
    cam->setOrientation(q);
    return true;
}

//! [main]
int main(int argc, char *argv[])
{
    MyTestApp app;
    app.initApp();
    app.getRoot()->startRendering();
    app.closeApp();
    return 0;
}
//! [main]
