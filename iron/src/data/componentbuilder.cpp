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
    case -1740904409 : return new AnimationComponent();
    case 1309780063 : return new SpriteComponent();
    case 475433204 : return new InputComponent();
    case 1448254106 : return new CrafterComponent();
    case 1315981302 : return new InventoryComponent();
    case -524183048 : return new ResourceComponent();
    case 1004248632 : return new BeltComponent();
    case 1842238107 : return new InserterComponent();
    case 1075717333 : return new OnBeltComponent();
    case -562460899 : return new PositionComponent();
    case -38539479 : return new UIButtonComponent();
    case -473184632 : return new UISpriteComponent();
    case 1343411703 : return new UITextComponent();
    }
    return nullptr;
}

ironEND_NAMESPACE