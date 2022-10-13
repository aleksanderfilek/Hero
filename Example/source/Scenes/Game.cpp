#include"Game.hpp"

#include"../Hero/Core/Core.hpp"
#include"../Actors/Player.hpp"
#include"../Hero/Actors/Graphics/StaticMesh.hpp"
#include"../Hero/Actors/Systems/ForwardRenderer.hpp"
#include"../Hero/Systems/Resources.hpp"
#include"../Hero/Actors/Graphics/Skybox.hpp"

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

  AddActor(new Hero::ForwardRenderer(SID("Renderer")));
  Hero::Skybox* sky = new Hero::Skybox(SID("Sky"));
  sky->SetMaterial((Hero::Material*)resources->Get(SID("M_Skybox")));
  sky->SetCubemap((Hero::Cubemap*)resources->Get(SID("Cubemap")));
  std::cout<<(Hero::Cubemap*)resources->Get(SID("Cubemap"))<<std::endl;
  AddActor(sky);

  AddActor(new Player(SID("Player")));
  //AddActor(new Terrain(SID("Terrain")));
  //AddActor(new DirectionalSun(this, SID("Sun")));

  Hero::StaticMesh* staticMesh = new Hero::StaticMesh(SID("Stones"));
  staticMesh->SetMesh((Hero::Mesh*)resources->Get(SID("cliffmesh")));
  staticMesh->SetMaterial((Hero::Material*)resources->Get(SID("material")));
  Hero::TransformComponent transform;
  staticMesh->AddInstance(transform);
  AddActor(staticMesh);
}

void Game::Update()
{
  Hero::System::Window::clear();

  ActorScene::Update();

  window->render();
}

void Game::End()
{
  ActorScene::End();
}