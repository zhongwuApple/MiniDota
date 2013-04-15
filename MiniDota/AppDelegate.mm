//
//  AppDelegate.m
//  MiniDota
//
//  Created by apple on 12-12-10.
//  Copyright (c) 2012年 apple. All rights reserved.
//

#import "AppDelegate.h"
#import "MatrixCustom.h"
#import "VectorCustom.h"
#import "Interfaces.h"
#include <iostream>
#include "ShaderManager.h"
#include "Singleton.h"
#include "TextureManager.h"
#include "EAGLView.h"
#include "Global.h"
#include "RenderData.h"
#include "MatrixCustom.h"
#include "CGutModel.h"
#include "GutModel_OpenGL.h"


@implementation AppDelegate
@synthesize window;

- (void)dealloc
{
    
    [eaglView release];
    [window release];
    [super dealloc];
}





static const float time_diff = 0.016;
-(void)handelPan:(UIPanGestureRecognizer*)gestureRecognizer
{
    CGPoint point = [gestureRecognizer translationInView:eaglView];
    float speed = 0.016f;
    
    if (point.y > 0) speed = -speed;
    {
        Matrix4x4 rotate ;
        rotate.RotateX_Replace(-speed);
        g_world_matrix = rotate * g_world_matrix;
        
        
            }
    
    if (point.x > 0)
    {
        Matrix4x4 rotate ;
        rotate.RotateY_Replace(-speed);
        g_world_matrix = rotate * g_world_matrix;
        
    }
    
    
    static int s = 0;
    
    if ( s < 6)
    {
        Matrix4x4 scale;
        scale.Identity();
        scale.Scale_Replace(0.8, 0.8, 0.8);
        g_world_matrix = scale * g_world_matrix;
        s++;
    }

    
    
    
}






#pragma mark 初始化手势
-(void) initGesture
{
    UIPanGestureRecognizer *panGes = [[UIPanGestureRecognizer alloc] initWithTarget:self action:@selector(handelPan:)];
    [eaglView addGestureRecognizer:panGes];
    [panGes release];
    
    g_world_matrix.Identity();
    
    GenerateGrids(100, 100,
                  &g_pGridVertices, g_iNumGridVertices,
                  &g_pGridIndices, g_iNumGridIndices,
                  g_iNumGridTriangles);
}



- (BOOL)application:(UIApplication *)application didFinishLaunchingWithOptions:(NSDictionary *)launchOptions
{
    



    
//	g_Lights[1].m_iLightType = LIGHT_DIRECTIONAL;
//	g_Lights[1].m_bEnabled = true;
//	g_Lights[1].m_vDirection.Set(-1.0f, 0.0f, 0.0f, 0.0f); g_Lights[1].m_vDirection.Normalize();
//	g_Lights[1].m_vDiffuse.Set(0.7f);
//	g_Lights[1].m_vSpecular.Set(0.8f);
//	g_Lights[1].m_vAmbient.Set(0.0f);
    
    


    


    
    
//    g_Simulation.m_vMaterialAmbient.Set(1.0f);
//    g_Simulation.m_vMaterialDiffuse.Set(1.0f);
//    g_Simulation.m_vMaterialSpecular.Set(1.0f);
//    g_Simulation.m_vMaterialEmissive.Set(0.0f);
//    g_Simulation.m_fMaterialShininess = 100.0f;
    
    
//  设置光源
    
    
//    g_Simulation.m_vAmbientLight.Set(0.1f);
    
    
    {
        //平行光
//        g_lights[0].lightDirection.Set(0.0f, 0.0f, 1.0f);
//        g_lights[0].lightAmbientColor.Set(0.0f, 0.0f, 0.0f);
//        g_lights[0].lightDiffuseColor.Set(0.6f, 0.0f, 0.0f);
//        g_lights[0].lightSpecularColor.Set(1.0f, 0.0f, 0.0f);
        
        
        g_lights[0].lightDirection.Set(0.0f, 1.0f, -1.0f);
        g_lights[0].lightDirection.Normalize();
        g_lights[0].lightDiffuseColor.Set(0.7f);
        g_lights[0].lightSpecularColor.Set(0.8f);
        g_lights[0].lightAmbientColor.Set(0.1f, 0.1f, 0.1f);
        
//        g_lights[1].lightDirection.Set(-1.0f, 0.0f, 0.0f);
//        g_lights[1].lightDirection.Normalize();
//        g_lights[1].lightDiffuseColor.Set(0.7f);
//        g_lights[1].lightSpecularColor.Set(0.8f);

        
    }
    
     
    /*
    {
        //point light
        g_lights[0].lightPosition.Set(0.0f, 0.0f, 1.0f,1.0f);
        
        g_lights[0].lightAmbientColor.Set(0.0f, 0.0f, 0.0f);
        g_lights[0].lightDiffuseColor.Set(0.0f, 0.6f, 0.0f);
        g_lights[0].lightSpecularColor.Set(0.0f, 1.0f, 0.0f);
        g_lights[0].lightAttenuation.Set(1.0f, 0.0f, 1.0f);
    }
    
    
    {
        //Spot Light
        g_lights[0].lightPosition.Set(0.0f, 0.0f, 1.0f, 1.0f);
        g_lights[0].lightDirection.Set(0.0f, 0.0f, -1.0f);
        
        g_lights[0].lightAmbientColor.Set(0.0f, 0.0f, 0.0f);
        g_lights[0].lightDiffuseColor.Set(0.0f, 0.0f, 0.6f);
        g_lights[0].lightSpecularColor.Set(0.0f, 0.0f, 1.0f);
        g_lights[0].lightAttenuation.Set(1.0f, 0.0f, 1.0f);
        
        
        
        g_lights[0].lightSpotLightCutoff = FastMath::Cos(FastMath::DegreeToRadian(60.0f)) ;
        g_lights[0].lightSpotLightExponent = 20.0f;
        g_lights[0].lightSpotlightHalfCutoffCosine =  FastMath::Cos( FastMath::DegreeToRadian( 60.0f * 0.5f) );
    }
    */
    
    

    
    
    

    
    
    
    
    

    
//    Matrix4x4 m1 = Matrix4x4(1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16);
//    Matrix4x4 m2 = Matrix4x4(12,22,33,44,5,6,7,8,9,10,11,12,13,14,15,16);
//    Matrix4x4 m3 = m1 * m2;
//    
//    m3.ConsoleOutput();
    
//
//    m1.ConsoleOutput();
//    
//    Vector3 v3 = m1.GetColumn_3(1);
//    v3.ConsoleOutput();
//    
//    Vector4 v4 = m1.GetColumn(1);
//    v4.ConsoleOutput();
//    
//    
//    Vector3 v5 = m1.GetRow_3(1);
//    v5.ConsoleOutput();
//    
//    
//    Vector4 v6 = m1.GetRow(1);
//    v6.ConsoleOutput();
    
    
//    vec3 v1 = vec3(11, 22, 33);
//
//    m1.ConsoleOutput();
//    v1.ConsoleOutput();
    
//    IResourceManager *rs1 = ResourceEngine::CreateResourceManager();
//    TextureDescription *td1 = rs1->LoadImage("Button.png");
//    TextureDescription *td2 = rs1->LoadImage("Dial.png");
//    TextureDescription *td3 = rs1->LoadImage("Title.png");
//    
//    printf("t1 is %d \n",td1->textureID );
//    
//    const string &vName = rs1->GetResourcePath() + "/SimpleLighting.es2.vert";
//    const string &fName = rs1->GetResourcePath() + "/SimpleLighting.es2.frag";
    


    
//    ShaderManager *sg = (ShaderManager *)&ShaderManager::Instance();
//    ShaderObject *obj1 = sg->LoadShader(vName,fName);

    
    
//    Vector2 v2 = Vector2(1.0f, 2.0f);
//    v2.ConsoleOutput();
//    
//    return YES;
    
    
    self.window = [[[UIWindow alloc] initWithFrame:[[UIScreen mainScreen] bounds]] autorelease];
    // Override point for customization after application launch.
    self.window.backgroundColor = [UIColor whiteColor];
    
    
    
    eaglView = [[EAGLView alloc] initWithFrame:CGRectMake(0, 0, 320, 480)];
    [self.window addSubview:eaglView];
    [eaglView startAnimation];
    [eaglView setUserInteractionEnabled:YES];
    
    
    [self initGesture];
    
    [self.window makeKeyAndVisible];
    return YES;
}

- (void)applicationWillResignActive:(UIApplication *)application
{
   
}

- (void)applicationDidEnterBackground:(UIApplication *)application
{
    // Use this method to release shared resources, save user data, invalidate timers, and store enough application state information to restore your application to its current state in case it is terminated later. 
    // If your application supports background execution, this method is called instead of applicationWillTerminate: when the user quits.
}

- (void)applicationWillEnterForeground:(UIApplication *)application
{
    // Called as part of the transition from the background to the inactive state; here you can undo many of the changes made on entering the background.
}

- (void)applicationDidBecomeActive:(UIApplication *)application
{
    // Restart any tasks that were paused (or not yet started) while the application was inactive. If the application was previously in the background, optionally refresh the user interface.
}

- (void)applicationWillTerminate:(UIApplication *)application
{
    // Called when the application is about to terminate. Save data if appropriate. See also applicationDidEnterBackground:.
}

@end























































