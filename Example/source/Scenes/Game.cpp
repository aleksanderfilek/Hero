#include"Game.hpp"

#include"../Hero/Core/Core.hpp"
#include"../Actors/Player.hpp"
#include"../Hero/Components/StaticMesh.hpp"
#include"../Hero/Actors/Systems/ForwardRenderer.hpp"
#include"../Hero/Systems/Resources.hpp"
#include"../Hero/Actors/Graphics/Skybox.hpp"
#include"../Hero/Actors/Light/DirectionalLight.hpp"
#include"../Hero/Core/Math.hpp"
#include"../Hero/Core/Time.hpp"

Hero::DirectionalLight* light;

void Game::Start()
{
  Scene::Start();

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
  resources->Add(SID("rendererShader"), "bin/assets/rendererShader.he");

  AddActor(new Hero::ForwardRenderer(SID("Renderer")));
  Hero::Skybox*sky = new Hero::Skybox(SID("Sky"));
  sky->SetMaterial((Hero::Material*)resources->Get(SID("M_Skybox")));
  sky->SetCubemap((Hero::Cubemap*)resources->Get(SID("Cubemap")));
  AddActor(sky);

  AddActor(new Player(SID("Player")));

  light = new Hero::DirectionalLight(SID("Sun"));
  light->SetColor(Hero::ColorRGB(255,0,0,255));
  AddActor(light);

  Hero::Actor* cliff = new Hero::Actor(SID("Cliff"));
  Hero::StaticMesh* staticMesh = new Hero::StaticMesh();
  staticMesh->SetMesh((Hero::Mesh*)resources->Get(SID("cliffmesh")));
  staticMesh->SetMaterial((Hero::Material*)resources->Get(SID("material")));
  cliff->SetPosition(Hero::Float3(0.0f, 0.0f, 50.0f));
  cliff->AddComponent(staticMesh);
  AddActor(cliff);

}

float angle = 0.0f;
void Game::Update()
{
  Hero::System::Window::clear();

  angle += 30.0f * Hero::Time::getDeltaTime();
  light->SetRotation(Hero::Quaternion(Hero::deg2rad(angle), Hero::deg2rad(0.0f), Hero::deg2rad(0.0f)));

  Scene::Update();

  window->render();
}

void Game::End()
{
  Scene::End();
}