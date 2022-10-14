#include "DirectionalLight.hpp"

namespace Hero
{

HERO DirectionalLight::DirectionalLight(const Sid& NewId)
 : Actor(NewId)
{
  LightBuffer.Register<Float3>(SID("LightColor"));
  LightBuffer.Register<Float3>(SID("LightDirection"));
  LightBuffer.Apply(1);
}

HERO void DirectionalLight::Start()
{
  SetColor(ColorRGB(255,255,255,255));

  Float3 forward = TransformRight(Transform);
  LightBuffer.Set<Float3>(SID("LightDirection"), forward);
}

HERO void DirectionalLight::Update()
{
  if(Transform.isDirty)
  {
    Float3 forward = TransformRight(Transform);
    LightBuffer.Set<Float3>(SID("LightDirection"), forward);
  }
  TransformUpdate(Transform);
}

HERO void DirectionalLight::End()
{

}

HERO void DirectionalLight::SetColor(ColorRGB NewColor)
{
  CurrentColor = NewColor;

  Float3 color = { 
    (float)CurrentColor.r/(float)255, 
    (float)CurrentColor.g/(float)255,
    (float)CurrentColor.b/(float)255
    };

  LightBuffer.Set<Float3>(SID("LightColor"), color);
}

}