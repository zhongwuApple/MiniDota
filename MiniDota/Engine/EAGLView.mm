//
//  EAGLView.m
//  MiniDota
//
//  这里主要是设置OPENGL的初始化问题，注意 frameBuffer colorBuffer, depthBuffer 设置顺序
//
//

#import "EAGLView.h"
#include "SceneController.h"

@implementation EAGLView
@synthesize animationFrameInterval;

- (void)dealloc
{
    [displayLink invalidate];
    displayLink = nil;
    [m_context release];
    [super dealloc];
}

+ (Class) layerClass
{
    return [CAEAGLLayer class];
}

-(void) layoutSubviews
{
    [self resizeFromLayer:(CAEAGLLayer*)self.layer];
}


- (id) initWithFrame: (CGRect) frame
{
    if (self = [super initWithFrame:frame])
    {
        CAEAGLLayer* eaglLayer = (CAEAGLLayer*) self.layer;
        eaglLayer.opaque = YES;
        
        EAGLRenderingAPI api = kEAGLRenderingAPIOpenGLES2;
        m_context = [[EAGLContext alloc] initWithAPI:api];
        
        if (!m_context || ![EAGLContext setCurrentContext:m_context])
        {
            [self release];
            return nil;
        }
        glGenFramebuffers(1, &framebuffer);
		glGenRenderbuffers(1, &colorRenderbuffer);
		glBindFramebuffer(GL_FRAMEBUFFER, framebuffer);
		glBindRenderbuffer(GL_RENDERBUFFER, colorRenderbuffer);
		glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_RENDERBUFFER, colorRenderbuffer);
        
        animating = FALSE;
        animationFrameInterval = 2;
        displayLink = nil;
    }
    return self;
}





-(void) initSceneController
{
    glViewport(0, 0, backingWidth, backingHeight);

    sharedSceneController = SceneController::sharedSceneController();
    sharedSceneController->Initialize();
}


- (BOOL) resizeFromLayer:(CAEAGLLayer *)layer
{
    glBindRenderbuffer(GL_RENDERBUFFER, colorRenderbuffer);
    [m_context renderbufferStorage:GL_RENDERBUFFER fromDrawable:layer];
    glGetRenderbufferParameteriv(GL_RENDERBUFFER, GL_RENDERBUFFER_WIDTH, &backingWidth);
    glGetRenderbufferParameteriv(GL_RENDERBUFFER, GL_RENDERBUFFER_HEIGHT, &backingHeight);
    if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
        return NO;
    
    //开启深度缓冲
    {
        glGenRenderbuffers(1, &depthRenderbuffer);
        glBindRenderbuffer(GL_RENDERBUFFER, depthRenderbuffer);
        glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT16, backingWidth, backingHeight);
        glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, depthRenderbuffer);
    }
    
    glBindRenderbuffer(GL_RENDERBUFFER, colorRenderbuffer);
    
    [self initSceneController];
    return YES;
}





#pragma mark -
#pragma mark Main Game Loop

#define MAXIMUM_FRAME_RATE 30.0f		
#define MINIMUM_FRAME_RATE 15.0f
#define UPDATE_INTERVAL (1.0 / MAXIMUM_FRAME_RATE)
#define MAX_CYCLES_PER_FRAME (MAXIMUM_FRAME_RATE / MINIMUM_FRAME_RATE)

- (void)gameLoop {
    
	static double lastFrameTime = 0.0f;
	static double cyclesLeftOver = 0.0f;
	double currentTime;
	double updateIterations;
	
	currentTime = CACurrentMediaTime();
	updateIterations = ((currentTime - lastFrameTime) + cyclesLeftOver);
	
	if(updateIterations > (MAX_CYCLES_PER_FRAME * UPDATE_INTERVAL))
		updateIterations = (MAX_CYCLES_PER_FRAME * UPDATE_INTERVAL);
	
	while (updateIterations >= UPDATE_INTERVAL)
    {
		updateIterations -= UPDATE_INTERVAL;
		sharedSceneController->updateCurrentSceneWithDelta(UPDATE_INTERVAL);
	}
	
	cyclesLeftOver = updateIterations;
	lastFrameTime = currentTime;
    
    sharedSceneController->renderCurrentScene();
    [m_context presentRenderbuffer:GL_RENDERBUFFER];
}



-(void) startAnimation
{
    if (!animating)
    {
        displayLink = [CADisplayLink displayLinkWithTarget:self selector:@selector(gameLoop)];
        [displayLink setFrameInterval:animationFrameInterval];
        [displayLink addToRunLoop:[NSRunLoop currentRunLoop] forMode:NSDefaultRunLoopMode];
        animating = TRUE;
    }
}


-(void) stopAnimation
{
    if (animating)
    {
        [displayLink invalidate];
        displayLink = nil;
        animating = FALSE;
    }
}





































@end








































































































