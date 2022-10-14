#include"Game.hpp"

#include"../Hero/Core/Core.hpp"
#include"../Actors/Player.hpp"
#include"../Hero/Actors/Graphics/StaticMesh.hpp"
#include"../Hero/Actors/Systems/ForwardRenderer.hpp"
#include"../Hero/Systems/Resources.hpp"
#include"../Hero/Actors/Graphics/Skybox.hpp"
#include"../Hero/Actors/Light/DirectionalLight.hpp"
#include"../Hero/Core/Math.hpp"
#include"../Hero/Core/Time.hpp"

Hero::DirectionalLight* light;
Hero::StaticMesh* arrow;
void Game::Start()
{
  ActorScene::Start();

  window = Hero::Core::getSystem<Hero::System::Window>(SID("Window"));
  window->setBackgroundColor((Hero::Color){0,0,0,255});
  window->setDepthTest(true);

  glEnable(GL_CULL_FACE);
  glCullFace(GL_FRONT); 

  Hero::Resources* resources = Hero::Core::getSystem<Hero::Resources>(SID("resources"));

  resources->Add(SID("cliffmesh"), "bin/assets/cliff.he");
  resources->Add(SID("cliffTexture"), "bin/assets/cliffAlbedo.he");
  resources->Add(SID("cliffTextureNormal"), "bin/assets/cliffNormal.he");
  resources->Add(SID("cliffTextureDisplacement"), "bin/assets/cliffDisplacement.he");
  resources->Add(SID("cliffTextureRoughness"), "bin/assets/cliffRoughness.he");
  resources->Add(SID("standardShader"), "bin/assets/standardShader.he");
  resources->Add(SID("material"), "bin/assets/template.he");
  resources->Add(SID("skyShader"), "bin/assets/cubemapShader.he");
  resources->Add(SID("M_Skybox"), "bin/assets/skybox.he");
  resources->Add(SID("Cubemap"), "bin/assets/cubemap.he");
  resources->Add(SID("simpleShader"), "bin/assets/simpleShader.he");
  resources->Add(SID("simple"), "bin/assets/simple.he");
  resources->Add(SID("arrow"), "bin/assets/arrow.he");

  AddActor(new Hero::ForwardRenderer(SID("Renderer")));
  Hero::Skybox*sky = new Hero::Skybox(SID("Sky"));
  sky->SetMaterial((Hero::Material*)resources->Get(SID("M_Skybox")));
  sky->SetCubemap((Hero::Cubemap*)resources->Get(SID("Cubemap")));
  AddActor(sky);

  AddActor(new Player(SID("Player")));
  std::cout<<"Size: "<<sizeof(Hero::Float3)<<std::endl;
  light = new Hero::DirectionalLight(SID("Sun"));
  light->SetColor(Hero::ColorRGB(255,0,0,255));
  Hero::TransformRotationSet(light->Transform, Hero::Quaternion(Hero::deg2rad(0.0f), Hero::deg2rad(0.0f), Hero::deg2rad(0.0f)));
  AddActor(light);

  Hero::StaticMesh* staticMesh = new Hero::StaticMesh(SID("Stones"));
  staticMesh->SetMesh((Hero::Mesh*)resources->Get(SID("cliffmesh")));
  staticMesh->SetMaterial((Hero::Material*)resources->Get(SID("material")));
  Hero::TransformComponent transform;
  Hero::TransformPositionSet(transform, Hero::Float3(0.0f, 0.0f, 50.0f));
  Hero::TransformUpdate(transform);
  staticMesh->AddInstance(transform);
  AddActor(staticMesh);

  arrow = new Hero::StaticMesh(SID("arrow"));
  arrow->SetMesh((Hero::Mesh*)resources->Get(SID("arrow")));
  arrow->SetMaterial((Hero::Material*)resources->Get(SID("simple")));
  Hero::TransformComponent transform2;
  arrow->AddInstance(transform2);
  AddActor(arrow);
}

double timer = 0.0;
float angle = 0.0f;
void Game::Update()
{
  Hero::System::Window::clear();


  angle += 30.0f * Hero::Time::getDeltaTime();
  Hero::TransformRotationSet(light->Transform, Hero::Quaternion(Hero::deg2rad(angle), Hero::deg2rad(0.0f), Hero::deg2rad(0.0f)));
  Hero::TransformComponent transform2;
  Hero::TransformRotationSet(transform2, Hero::Quaternion(Hero::deg2rad(angle), Hero::deg2rad(0.0f), Hero::deg2rad(0.0f)));
  Hero::TransformScaleSet(transform2, Hero::Float3(5.0f, 5.0f, 5.0f));
  Hero::TransformUpdate(transform2);
  arrow->UpdateInstance(transform2, 0);

  ActorScene::Update();

  window->render();
}

void Game::End()
{
  ActorScene::End();
}