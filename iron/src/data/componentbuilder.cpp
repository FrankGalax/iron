#include <data/componentbuilder.h>

#include <iron.h>
#include <ecs/entity.h>
#include <graphics/animationcomponent.h>
#include <graphics/spritecomponent.h>
#include <input/inputcomponent.h>
#include <item/craftercomponent.h>
#include <item/inventorycomponent.h>
#include <item/resourcecomponent.h>
#include <movement/beltcomponent.h>
#include <movement/insertercomponent.h>
#include <movement/onbeltcomponent.h>
#include <movement/pathcomponent.h>
#include <movement/pathtargetcomponent.h>
#include <movement/positioncomponent.h>
#include <ui/uibuttoncomponent.h>
#include <ui/uicomponent.h>
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
    case -639674736 : return new PathComponent();
    case -1243637833 : return new PathTargetComponent();
    case -110003308 : return new PositionComponent();
    case 164764677 : return new UIButtonComponent();
    case -79879393 : return new UIComponent();
    case -651037376 : return new UISpriteComponent();
    case -615737482 : return new UITextComponent();
    }
    return nullptr;
}

Component* ComponentBuilder::GetComponent(Entity* entity, int classHash)
{
    switch (classHash)
    {
    case 757536853 : return entity->GetComponent<AnimationComponent>();
    case -120479234 : return entity->GetComponent<SpriteComponent>();
    case -1831897379 : return entity->GetComponent<InputComponent>();
    case 1338292626 : return entity->GetComponent<CrafterComponent>();
    case -308782219 : return entity->GetComponent<InventoryComponent>();
    case 1835672005 : return entity->GetComponent<ResourceComponent>();
    case 817766642 : return entity->GetComponent<BeltComponent>();
    case 570334859 : return entity->GetComponent<InserterComponent>();
    case 2124386125 : return entity->GetComponent<OnBeltComponent>();
    case -639674736 : return entity->GetComponent<PathComponent>();
    case -1243637833 : return entity->GetComponent<PathTargetComponent>();
    case -110003308 : return entity->GetComponent<PositionComponent>();
    case 164764677 : return entity->GetComponent<UIButtonComponent>();
    case -79879393 : return entity->GetComponent<UIComponent>();
    case -651037376 : return entity->GetComponent<UISpriteComponent>();
    case -615737482 : return entity->GetComponent<UITextComponent>();
    }
    return nullptr;
}

ironEND_NAMESPACE