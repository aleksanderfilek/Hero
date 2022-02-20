#include"MainToolBarWidget.hpp"
#include"Resources.hpp"

#include"UserInterface/Font.hpp"
#include"Core/Core.hpp"
#include"UserInterface/Label.hpp"
#include"UserInterface/HorizontalStack.hpp"
#include"Core/Events.hpp"
#include"UserInterface/VerticalStack.hpp"

#include"ThirdParty.hpp"

#include<iostream>

event(FileBtn_Click)
{
    std::cout<<"File"<<std::endl;
    auto stack = (Hero::UI::VerticalStack*)args;
    stack->setVisibility(true);
}

event(WindowBtn_Click)
{
    std::cout<<"Window"<<std::endl;
}

event(FilestackVB_OffHover)
{
    std::cout<<"off hover"<<std::endl;
    auto stack = (Hero::UI::VerticalStack*)args;
    stack->setVisibility(false);
}

MainToolBarWidget::MainToolBarWidget()
{
    Resources* resources = Hero::Core::getSystem<Resources>(SID("resources"));

    auto filestack = new Hero::UI::VerticalStack();
    filestack->addEvent(Hero::UI::Event::OffHover, FilestackVB_OffHover, filestack);
    filestack->setVisibility(false);

    auto label = new Hero::UI::Label();
    label->setSize({50,14});
    label->setText("File");
    label->setFont(resources->get<Hero::Font>(SID("montserrat28")), false);
    label->setColor(Hero::ColorRGB(0,0,0));
    label->setAlligment(Hero::UI::Alligment::CENTER);
    label->apply();
    label->addEvent(Hero::UI::Event::OnLeftClick, FileBtn_Click, filestack);

    auto label2 = new Hero::UI::Label();
    label2->setSize({80,14});
    label2->setText("Window");
    label2->setFont(resources->get<Hero::Font>(SID("montserrat28")), false);
    label2->setColor(Hero::ColorRGB(0,0,0));
    label2->setAlligment(Hero::UI::Alligment::CENTER);
    label2->apply();
    label2->addEvent(Hero::UI::Event::OnLeftClick, WindowBtn_Click, nullptr);

    auto toolbar = new Hero::UI::HorizontalStack();
    toolbar->add("label", label);
    toolbar->add("label2", label2);

    auto pos = label2->getAbsolutePosition();

    filestack->setPosition({pos.x, pos.y + 14});

    add("toolbar", toolbar);

    auto label3 = new Hero::UI::Label();
    label3->setSize({80,14});
    label3->setText("New File");
    label3->setFont(resources->get<Hero::Font>(SID("montserrat28")), false);
    label3->setColor(Hero::ColorRGB(0,0,0));
    label3->setAlligment(Hero::UI::Alligment::CENTER);
    label3->apply();

    filestack->add("label3",label3);

    add("filestack", filestack);

    std::cout<<getChildrenCount()<<std::endl;
}

MainToolBarWidget::~MainToolBarWidget()
{

}