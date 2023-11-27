#include"Game.hpp"

#include"../Hero/Core/Core.hpp"
#include"../Actors/Player.hpp"
#include"../Hero/Actors/Systems/ForwardRenderer.hpp"
#include"../Hero/Systems/Resources.hpp"
#include"../Hero/Actors/Graphics/Skybox.hpp"
#include"../Hero/Actors/Light/DirectionalLight.hpp"
#include"../Hero/Core/Math.hpp"
#include"../Hero/Core/Time.hpp"
#include "../Actors/Cliff.hpp"

Hero::DirectionalLight* light;
Hero::ForwardRenderer* renderer;

void Game::Start()
{
  Scene::Start();

  window = Hero::Core::getSystem<Hero::System::Window>(SID("Window"));
  window->setBackgroundColor((Hero::Color){0,0,0,255});
  window->setDepthTest(true);

  input = Hero::Core::getSystem<Hero::System::Input>(SID("input"));

  glEnable(GL_CULL_FACE);
  glCullFace(GL_FRONT); 

  Hero::Resources* resources = Hero::Core::getSystem<Hero::Resources>(SID("resources"));

  resources->Add(SID("standardShader"), "bin/assets/standardShader.he");
  resources->Add(SID("skyShader"), "bin/assets/cubemapShader.he");
  resources->Add(SID("M_Skybox"), "bin/assets/skybox.he");
  resources->Add(SID("Cubemap"), "bin/assets/cubemap.he");
  resources->Add(SID("simpleShader"), "bin/assets/simpleShader.he");
  resources->Add(SID("simple"), "bin/assets/simple.he");
  resources->Add(SID("arrow"), "bin/assets/arrow.he");
  resources->Add(SID("rendererShader"), "bin/assets/rendererShader.he");

  AddReflection<Cliff>();

  renderer = new Hero::ForwardRenderer(SID("Renderer"));
  AddActor(renderer);

  Hero::Skybox*sky = new Hero::Skybox(SID("Sky"));
  sky->SetMaterial((Hero::Material*)resources->Get(SID("M_Skybox")));
  sky->SetCubemap((Hero::Cubemap*)resources->Get(SID("Cubemap")));
  AddActor(sky);

  AddActor(new Player(SID("Player")));

  light = new Hero::DirectionalLight(SID("Sun"));
  light->SetColor(Hero::ColorRGB(255,0,0,255));
  AddActor(light);

  AddActor(Spawn<Cliff>(SID("Cliff_0"),
    Hero::Transform(
      Hero::Float3(0.0f, 0.0f, 50.0f), 
      Hero::Quaternion(), 
      Hero::Float3::one()
    )));

}

float angle = 0.0f;

void Game::Update()
{
  angle += 30.0f * Hero::Time::getDeltaTime();
  light->SetRotation(Hero::Quaternion(Hero::deg2rad(angle), Hero::deg2rad(0.0f), Hero::deg2rad(0.0f)));

  Hero::System::Window::clear();
  Scene::Update();

  window->render();
}

void Game::End()
{
  Scene::End();
}