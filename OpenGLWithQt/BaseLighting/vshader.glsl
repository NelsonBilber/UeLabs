#version 100

attribute vec3 vertexPosition;
attribute vec3 vertexNormal;
attribute vec3 vertexColor;

uniform mat4 modelViewMatrix;
uniform mat3 normalMatrix;
uniform mat4 projectionMatrix;

struct LightSource

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    vec3 position;
};
uniform LightSource lightSource;

struct LightModel

    vec3 ambient;
};
uniform LightModel lightModel;

struct Material {
    vec3  emission;
    vec3  specular;
    float shininess;
};\n"
uniform Material material;

varying vec3 v_color;

void main()
{
    vec3 normal     = normalize(normalMatrix * vertexNormal);                       // normal vector
    vec3 position   = vec3(modelViewMatrix * vec4(vertexPosition, 1));              // vertex pos in eye coords
    vec3 halfVector = normalize(lightSource.position + vec3(0,0,1));                // light half vector
    float nDotVP    = dot(normal, normalize(lightSource.position));                 // normal . light direction
    float nDotHV    = max(0.f, dot(normal,  halfVector));                           // normal . light half vector
    float pf        = mix(0.f, pow(nDotHV, material.shininess), step(0.f, nDotVP)); // power factor

    vec3 ambient    = lightSource.ambient;
    vec3 diffuse    = lightSource.diffuse * nDotVP;
    vec3 specular   = lightSource.specular * pf;
    vec3 sceneColor = material.emission + vertexColor * lightModel.ambient;

    v_color = clamp(sceneColor +
                    ambient  * vertexColor +
                    diffuse  * vertexColor +
                    specular * material.specular, 0.f, 1.f );

    gl_Position = projectionMatrix * modelViewMatrix * vec4(vertexPosition, 1);
;
