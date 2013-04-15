#import <UIKit/UIKit.h>
#import <QuartzCore/QuartzCore.h>
#import <string>
#import <iostream>
#import "Interfaces.h"
#include "TextureManager.h"
#include <OpenGLES/ES2/gl.h>



namespace ResourceEngine
{
    
class ResourceManager : public IResourceManager {
public:
    string GetResourcePath() const
    {
        NSString* bundlePath =[[NSBundle mainBundle] resourcePath];
        return [bundlePath UTF8String];
    }
    
    static ResourceManager &Instance()
    {
        static ResourceManager rm;
        return rm;
    }
    
    TextureDescription* LoadImage(const string& filename)
    {
        NSString* basePath = [NSString stringWithUTF8String:filename.c_str()];
        NSString* resourcePath = [[NSBundle mainBundle] resourcePath];
        NSString* fullPath = [resourcePath stringByAppendingPathComponent:basePath];
        UIImage* uiImage = [UIImage imageWithContentsOfFile:fullPath];
        CGImage* cgImg = uiImage.CGImage;
        
        //读取位图数据
        TextureDescription *td = (TextureDescription *)malloc(sizeof(TextureDescription));
        td->width = CGImageGetWidth(cgImg);
        td->height = CGImageGetHeight(cgImg);
        td->BitsPerComponent = 8;
        td->Format = TextureFormatRgba;
        td->MipCount = 1;
        
        
        
        //将位图信息绑定到 opengl
        int bpp = td->BitsPerComponent / 2;
        int byteCount = td->width * td->height * bpp;
        unsigned char* data = (unsigned char*) calloc(byteCount, 1);
        
        CGColorSpaceRef colorSpace = CGColorSpaceCreateDeviceRGB();
        CGBitmapInfo bitmapInfo = kCGImageAlphaPremultipliedLast | kCGBitmapByteOrder32Big;
        CGContextRef context = CGBitmapContextCreate(data,td->width,td->height,
                                                     td->BitsPerComponent,bpp * td->width,
                                                     colorSpace,bitmapInfo);
        
        CGRect rect = CGRectMake(0, 0, td->width, td->height);
        CGContextDrawImage(context, rect, cgImg);        
        CGColorSpaceRelease(colorSpace);
        CGContextRelease(context);
        
        glGenTextures(1, &(td->textureID));        
        glBindTexture(GL_TEXTURE_2D, td->textureID);
        //目前暂时只是支持一种png格式图片
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, td->width, td->height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
        free(data);
        
        //存储管理位图
        TextureManager *tm = (TextureManager *)&TextureManager::Instance();
        tm->SetTexture(filename, td);
        return td;
    }
    
    

};
    

IResourceManager* CreateResourceManager()
{
    return  &ResourceManager::Instance();
}
    
    

    
    
}





























































