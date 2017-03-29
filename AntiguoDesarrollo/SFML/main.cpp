#include <SFML/Graphics.hpp>
#include <irrlicht.h>

//#include <GL/glu.h>
#include <iostream>
#include <math.h>
#include <sstream>
#include <string>
#define M_PI           3.14159265358979323846

using namespace irr;
using namespace core;
using namespace scene;
using namespace video;
using namespace io;
using namespace gui;


template <typename T>
std::string to_string(T value)
{
    std::ostringstream oss;
    oss << value;
    return oss.str();
}

int main() {
    sf::ContextSettings settings;
    settings.depthBits = 16;
    settings.stencilBits = 8;
    settings.antialiasingLevel = 0;
    settings.majorVersion = 3;
    settings.minorVersion = 0;

    sf::RenderWindow window(sf::VideoMode(1280, 720), "OpenGL", sf::Style::Default, settings);

    IrrlichtDevice* device;
    SIrrlichtCreationParameters Parameters;
    Parameters.DriverType = video::EDT_OPENGL;
    Parameters.Bits = 16;
    Parameters.Fullscreen = false;
    Parameters.Stencilbuffer = true;
    Parameters.Vsync = true;
    Parameters.AntiAlias = false;
    Parameters.HighPrecisionFPU = false;
    Parameters.WindowId = window.getSystemHandle();
    device = createDeviceEx(Parameters);

    IVideoDriver* driver = device->getVideoDriver();
    ISceneManager* smgr = device->getSceneManager();
    IGUIEnvironment* guienv = device->getGUIEnvironment();

    sf::Font segoeui;
    if (!segoeui.loadFromFile("C:/codeSource/SFML/contrast.ttf"))  {
    // error...
    }

    IAnimatedMesh* mesh = smgr->getMesh("C:/codeSource/SFML/bird_final.md2");
    if (!mesh)
    {
        device->drop();
        return 1;
    }
    IAnimatedMeshSceneNode* node = smgr->addAnimatedMeshSceneNode( mesh );
/*
    if (node)
    {
        node->setMaterialFlag(EMF_LIGHTING, false);
        node->setMD2Animation(scene::EMAT_STAND);
        node->setMaterialTexture( 0, driver->getTexture("C:/SFML/irrlicht-1.8/media/sydney.bmp") );
    }
*/
    SKeyMap keyMap[9];
    keyMap[0].Action = EKA_MOVE_FORWARD;
    keyMap[0].KeyCode = KEY_UP;
    keyMap[1].Action = EKA_MOVE_FORWARD;
    keyMap[1].KeyCode = KEY_KEY_W;

    keyMap[2].Action = EKA_MOVE_BACKWARD;
    keyMap[2].KeyCode = KEY_DOWN;
    keyMap[3].Action = EKA_MOVE_BACKWARD;
    keyMap[3].KeyCode = KEY_KEY_S;

    keyMap[4].Action = EKA_STRAFE_LEFT;
    keyMap[4].KeyCode = KEY_LEFT;
    keyMap[5].Action = EKA_STRAFE_LEFT;
    keyMap[5].KeyCode = KEY_KEY_A;

    keyMap[6].Action = EKA_STRAFE_RIGHT;
    keyMap[6].KeyCode = KEY_RIGHT;
    keyMap[7].Action = EKA_STRAFE_RIGHT;
    keyMap[7].KeyCode = KEY_KEY_D;

    keyMap[8].Action = EKA_JUMP_UP;
    keyMap[8].KeyCode = KEY_KEY_J;

    scene::ICameraSceneNode* camera = smgr->addCameraSceneNodeFPS(0, 100.0f, .6f, -1, keyMap, 9, false, 4.f);
    camera->setPosition(core::vector3df(108,140,-140));
    camera->setFarValue(5000.0f);

    sf::Text position;
    position.setFont(segoeui); // font is a sf::Font
    position.setString(to_string(camera->getPosition().X));
    position.setCharacterSize(24); // in pixels, not points!
    position.setColor(sf::Color::Red);

    while (window.isOpen())
    {
        sf::Event event;
        device->run();
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear(sf::Color::Black);
            driver->beginScene();
                smgr->drawAll();
                guienv->drawAll();
                window.pushGLStates();
                window.draw(position);
                window.popGLStates();
                driver->endScene();
        window.display();
    }
    device->drop();
    return 0;
}
