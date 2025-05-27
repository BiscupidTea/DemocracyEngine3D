#include "Light.h"

using namespace DemoEngine_Entities;

Light::Light(LightType type, vec3 position, vec3 rotation, vec3 scale)
    : Entity(position, rotation, scale), type(type)
{
    ambientStrength = 0.2f;
    specularStrength = 0.5f;
    shininess = 32;

    lightColor = vec3(1.0f);
    direction = vec3(0.0f, -1.0f, 0.0f);

    constant = 1.0f;
    linear = 0.09f;
    quadratic = 0.032f;

    cutOff = cos(radians(12.5f));
    outerCutOff = cos(radians(17.5f));
}

void Light::ApplyToShader(Shader* shader, const std::string& prefix)
{
    // shader->SetInt(prefix + ".type", static_cast<int>(type));
    // shader->SetVec3(prefix + ".position", getPosition());
    // shader->SetVec3(prefix + ".direction", direction);
    // shader->SetVec3(prefix + ".color", lightColor);
    // shader->SetFloat(prefix + ".ambientStrength", ambientStrength);
    // shader->SetFloat(prefix + ".specularStrength", specularStrength);
    // shader->SetInt(prefix + ".shininess", shininess);
    //
    // if (type == LightType::Point || type == LightType::Spot)
    // {
    //     shader->SetFloat(prefix + ".constant", constant);
    //     shader->SetFloat(prefix + ".linear", linear);
    //     shader->SetFloat(prefix + ".quadratic", quadratic);
    // }
    //
    // if (type == LightType::Spot)
    // {
    //     shader->SetFloat(prefix + ".cutOff", cutOff);
    //     shader->SetFloat(prefix + ".outerCutOff", outerCutOff);
    // }
}

void Light::setLightColor(vec3 color)
{
    lightColor = color;
}

void Light::setDirection(vec3 dir)
{
    direction = glm::normalize(dir);
}

void Light::setAttenuation(float c, float l, float q)
{
    constant = c;
    linear = l;
    quadratic = q;
}

void Light::setSpotCutOff(float innerDeg, float outerDeg)
{
    cutOff = cos(radians(innerDeg));
    outerCutOff = cos(radians(outerDeg));
}

LightType Light::getType() const
{
    return type;
}
