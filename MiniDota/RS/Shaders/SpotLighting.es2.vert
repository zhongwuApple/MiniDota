
/*
 这里 NormalMatrix  是 WorldMatrix 左上 3*3 矩阵 取反求逆获得的
 VLightDirection 的位置 没有经过任何处理， 是直接写死的
 
 简单思路是
 先计算  Normal 与 VLightDirection 的 dot ，然后 得出 光强(vIntensity)
 vIntensity * VlightColor 得出  lastColor
 真正的颜色 ==   环境光(VLightAmbient) + lastColor;
 
 shader 主要目的：检测 光照随角度变换而变化
 
 缺陷: 没有使用 VertexColor, 和 不清楚 VLightDirection 是否需要 坐标系转换
 */


// `计算点光源, 它和顶点位置, 顶点法线, 光源位置有关.`
//  点光源有衰减!     衰减 = 1/(a*1 + b*d + c*d^2);     公式中的 d 是指 顶点到光源的距离   其中 a,b,c 是提前给出来的
//  在球距离的时候  顶点指向光源方向(vVertex_to_Light) 本身要归一化

//  注意顶点指向光源方向      顶点指向光源方向 = 光源坐标 - 顶点坐标;    光强 = 顶点指向光源方向 dot 顶点法线
//   顶点颜色 += 光强 * 光线颜色 * 衰减
//  这个方程来看 点光源本质与 平行光的差别在于， 仅仅是在平行光的基础上 计算衰减而已
//  点光源 = 平行光 * 衰减系数




attribute vec4 VPosition;
attribute vec4 VColor;
attribute vec3 VNormal;

uniform mat4 Projection4x4;
uniform mat4 ViewMatrix4x4;
uniform mat4 WorldMatrix4x4;

uniform vec4 VLightPosition;  //光源位置

uniform vec3 VLightAmbientColor;
uniform vec3 VLightDirection;
uniform vec3 VDiffuseColor;
uniform vec3 VLightAttenuation;
uniform vec3 VSpecularColor;

uniform mat3 World3x3;
uniform mat3 View3x3;
uniform mat3 WorldView3x3;


uniform vec3 VMaterialAmbient;
uniform vec3 VMaterialDiffuse;
uniform vec3 VMaterialSpecular;
uniform vec3 VMaterialEmissive;

uniform float FMaterialShininess;
uniform float FSpotlightHalfCutoffCosine;
uniform float FSpotLightExponent;

varying vec4 colorVarying;



//这里光线 统一放到 view视图计算 里面计算

void main(void)
{
    //*************************************************************
    //start 初始化基本光源信息
    
    vec3 vDefaultCameraDir = vec3( 0.0, 0.0, 1.0);
    vec3 vAmbientLight = vec3(0.1);
    vec3 vMaterialEmissive = vec3(0.0);
    
    
    //光源信息处理
    vec3 l_Position = vec3(ViewMatrix4x4 * VLightPosition);
    
    vec3 l_Direction = View3x3 * VLightDirection;
    
    vec3 l_AmbientColor = VMaterialAmbient * VLightAmbientColor;
    vec3 l_DiffuseColor = VMaterialDiffuse * VDiffuseColor;
    vec3 l_SpecularColor = VMaterialSpecular * VSpecularColor;
    
    //基本光照值
    vec3 vGlobalAmbient = vAmbientLight * VMaterialAmbient;
    vec3 vInitialLighting = vMaterialEmissive + vGlobalAmbient;
    
    //end 初始化基本光源信息
    //*************************************************************
    
    
    vec3 result = vec3(0.0);
    result = vInitialLighting;
    
    
    vec3 vPosition, vNormal;
    vec3 vDiffuse, vSpecular;
    vec3 vAttenuation;
    vec3 vLightDir;
    vec3 vCameraDir;
    
    
    
    //注意 法线 和 顶点位置 转换到 同一个 空间,
    
    vPosition = vec3( ViewMatrix4x4 * WorldMatrix4x4 * VPosition );
    vNormal = WorldView3x3 * VNormal;
    vNormal = normalize(vNormal);
    
    vLightDir = l_Position - vPosition; //计算 顶点 指向光源的方向
    float light_distance = length(vLightDir);
    vLightDir = normalize(vLightDir);
    
    float vCosineValue = max( dot(l_Direction, -vLightDir), 0.0 ); //注意这里的  -vLightDir
    vec3 vCosine = vec3(vCosineValue);
    
    if ( vCosineValue >= FSpotlightHalfCutoffCosine )
    {
        {
            //衰减
            vec3 vDistance = vec3(1.0, light_distance, light_distance*light_distance);
            vAttenuation = vec3(dot(vDistance, VLightAttenuation));
        }
        
        
        {
            //漫反射
            float diffuseValue = max(dot(vNormal, vLightDir),0.0);
            vDiffuse = vec3(diffuseValue);
            vDiffuse *= l_DiffuseColor;
        }
        
        
        
        {
            //高光
            
            //假设 顶点永远在镜头的正前方
            vCameraDir = -vPosition;
            vCameraDir = normalize(vCameraDir);
            
            
            vec3 vHalfDir = vLightDir + vCameraDir;
            vHalfDir = normalize(vHalfDir);
            
            float vSpecularCosineValue = dot(vNormal, vHalfDir);
            vSpecularCosineValue = max(vSpecularCosineValue, 0.0);
            float fSpecular = pow( vSpecularCosineValue, FMaterialShininess);
            vSpecular = fSpecular * l_SpecularColor;
            
            
            float fFalloff = pow(vCosineValue, FSpotLightExponent);
            
            result +=  fFalloff * (vDiffuse + vSpecular) / vAttenuation ;
            
        }
        
        
        
    }
    
    
    

    

    

    
    
    
    
    
    colorVarying = vec4( result, 1.0 );
    gl_Position = Projection4x4 * ViewMatrix4x4 * WorldMatrix4x4 * VPosition;
}

































