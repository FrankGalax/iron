#include<data/componentbuilder.h>

#include <iron.h>
#include <graphics/animationcomponent.h>
#include <graphics/spritecomponent.h>
#include <input/inputcomponent.h>
#include <item/craftercomponent.h>
#include <item/inventorycomponent.h>
#include <item/resourcecomponent.h>
#include <movement/beltcomponent.h>
#include <movement/insertercomponent.h>
#include <movement/onbeltcomponent.h>
#include <movement/positioncomponent.h>
#include <ui/uibuttoncomponent.h>
#include <ui/uispritecomponent.h>
#include <ui/uitextcomponent.h>

ironBEGIN_NAMESPACE

Component* ComponentBuilder::BuildComponent(int classHash)
{
    switch (classHash)
    {
    case 757536853 : return new AnimationComponent();
    case -120479234 : return new SpriteComponent();
    case -1831897379 : return new InputComponent();
    case 1338292626 : return new CrafterComponent();
    case -308782219 : return new InventoryComponent();
    case 1835672005 : return new ResourceComponent();
    case 817766642 : return new BeltComponent();
    case 570334859 : return new InserterComponent();
    case 2124386125 : return new OnBeltComponent();
    case -110003308 : return new PositionComponent();
    case 164764677 : return new UIButtonComponent();
    case -651037376 : return new UISpriteComponent();
    case -615737482 : return new UITextComponent();
    }
    return nullptr;
}

ironEND_NAMESPACE