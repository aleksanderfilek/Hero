#include"Game.hpp"

#include"../Hero/Core/Core.hpp"
#include"../Actors/Player.hpp"
#include"../Actors/Cubemap.hpp"
#include"../Actors/Terrain.hpp"
#include"../Actors/DirectionalSun.hpp"
#include"../Actors/Renderer.hpp"
#include"../Actors/StaticMesh.hpp"
#include"../Hero/Systems/Resources.hpp"

void Game::Start()
{
  ActorScene::Start();

  window = Hero::Core::getSystem<Hero::System::Window>(SID("Window"));
  window->setBackgroundColor((Hero::Color){0,0,0,255});
  window->setDepthTest(true);

  glEnable(GL_CULL_FACE);
  glCullFace(GL_FRONT); 

  Hero::Resources* resources = Hero::Core::getSystem<Hero::Resources>(SID("resources"));
  std::string cliffMeshPath("bin/assets/cliff.he");
  std::string cliffTexturePath("bin/assets/cliffAlbedo.he");
  std::string cliffTextureNormalPath("bin/assets/cliffNormal.he");
  std::string cliffTextureDisplacementPath("bin/assets/cliffDisplacement.he");
  std::string cliffTextureRoughnessPath("bin/assets/cliffRoughness.he");
  std::string shaderPath("bin/assets/standardShader.he");

  resources->Add(SID("cliffmesh"),cliffMeshPath);
  resources->Add(SID("cliffTexture"),cliffTexturePath);
  resources->Add(SID("cliffTextureNormal"),cliffTextureNormalPath);
  resources->Add(SID("cliffTextureDisplacement"),cliffTextureDisplacementPath);
  resources->Add(SID("cliffTextureRoughness"),cliffTextureRoughnessPath);
  resources->Add(SID("standardShader"),shaderPath);

  AddActor(new Renderer(SID("Renderer")));
  AddActor(new Cubemap(SID("Cubemap")));
  AddActor(new Player(SID("Player")));
  //AddActor(new Terrain(SID("Terrain")));
  AddActor(new DirectionalSun(SID("Sun")));

  StaticMesh* staticMesh = new StaticMesh(SID("Stones"));
  staticMesh->SetShader((Hero::Shader*)resources->Get(SID("standardShader")));
  staticMesh->SetMesh((Hero::Mesh*)resources->Get(SID("cliffmesh")));
  staticMesh->SetTexture((Hero::Texture*)resources->Get(SID("cliffTexture")), 0);
  staticMesh->SetTexture((Hero::Texture*)resources->Get(SID("cliffTextureNormal")), 1);
  staticMesh->SetTexture((Hero::Texture*)resources->Get(SID("cliffTextureRoughness")), 2);
  staticMesh->Load("bin/assets/cliffData.he");
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