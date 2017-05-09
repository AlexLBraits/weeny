#import <QuartzCore/QuartzCore.h>

#import <OpenGLES/EAGL.h>
#import <OpenGLES/EAGLDrawable.h>
#import <Foundation/Foundation.h>
#import <OpenGLES/ES2/gl.h>
#import <OpenGLES/ES2/glext.h>

@interface Renderer : NSObject

//@property (nonatomic) GLuint defaultFBOName;


//- (instancetype) initWithDefaultFBO: (GLuint) defaultFBOName;
//- (void) resizeWithWidth:(GLuint)width AndHeight:(GLuint)height;
//- (void) dealloc;


- (instancetype)initWithContext:(EAGLContext*)context AndDrawable:(id<EAGLDrawable>)drawable;
- (void)render;
- (BOOL)resizeFromLayer:(CAEAGLLayer*)layer;

@end
