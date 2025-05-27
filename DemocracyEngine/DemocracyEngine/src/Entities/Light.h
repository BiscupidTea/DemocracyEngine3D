#pragma once
#include <string>

#include "Entity.h"

namespace DemoEngine_Entities
{
    enum class LightType
    {
        Directional,
        Point,
        Spot
    };
    
    class Light : public Entity
    {
    private:
        LightType type;

        float ambientStrength;
        float specularStrength;
        int shininess;

        vec3 lightColor;
        vec3 direction;
        
        float constant;
        float linear;
        float quadratic;

        float cutOff;
        float outerCutOff;

    public:
        Light(LightType type, vec3 position, vec3 rotation, vec3 scale);

        void ApplyToShader(class Shader* shader, const std::string& prefix);
        
        void setLightColor(vec3 color);
        void setDirection(vec3 dir);

        void setAttenuation(float constant, float linear, float quadratic);
        void setSpotCutOff(float innerDeg, float outerDeg);

        LightType getType() const;
    };
}
