//
//  EAGLView.h
//  MiniDota
//
//  Created by apple on 12-12-10.
//  Copyright (c) 2012年 apple. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>
#import <QuartzCore/QuartzCore.h>

#import <OpenGLES/ES2/gl.h>
#import <OpenGLES/ES2/glext.h>


class SceneController;
@interface EAGLView : UIView
{
    SceneController *sharedSceneController;
    CADisplayLink   *displayLink;
    
    
    BOOL            animating;
    int             animationFrameInterval;
    
    
    EAGLContext     *m_context;
    GLuint          framebuffer;
    GLuint          colorRenderbuffer;
    GLuint          depthRenderbuffer;
    GLint           backingWidth;
    GLint           backingHeight;
    
}

@property(nonatomic)int animationFrameInterval;


- (void) startAnimation;


- (void) stopAnimation;


- (BOOL) resizeFromLayer:(CAEAGLLayer *)layer;

-(void) initSceneController;

@end

























































