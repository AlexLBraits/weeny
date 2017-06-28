#import "renderer.h"

#import <application.h>
extern Application* application;

@interface Renderer ()
{
    bool _initialized;
    long long _lastTime;
    GLuint _defaultFBOName;
    EAGLContext* _context;
    
    // The OpenGL names for the framebuffer and renderbuffer used to render
    // to this view
    GLuint _colorRenderbuffer;
    GLuint _depthRenderbuffer;
}
@end

@implementation Renderer

// Create an ES 2.0 context
- (instancetype)initWithContext:(EAGLContext*)context AndDrawable:(id<EAGLDrawable>)drawable
{
    _initialized = false;
    _lastTime = (long long)([[NSDate date] timeIntervalSince1970] * 1000.0);
    _context = context;
    
    // Create default framebuffer object. The backing will be allocated for the
    // current layer in -resizeFromLayer
    glGenFramebuffers(1, &_defaultFBOName);
    glGenRenderbuffers(1, &_colorRenderbuffer);
    
    glBindFramebuffer(GL_FRAMEBUFFER, _defaultFBOName);
    glBindRenderbuffer(GL_RENDERBUFFER, _colorRenderbuffer);
    
    // This call associates the storage for the current render buffer with the
    // EAGLDrawable (our CAEAGLLayer) allowing us to draw into a buffer that
    // will later be rendered to the screen wherever the layer is (which
    // corresponds with our view).
    [_context renderbufferStorage:GL_RENDERBUFFER fromDrawable:drawable];
    
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_RENDERBUFFER, _colorRenderbuffer);
    
    // Get the drawable buffer's width and height so we can create a depth buffer for the FBO
    GLint backingWidth;
    GLint backingHeight;
    glGetRenderbufferParameteriv(GL_RENDERBUFFER, GL_RENDERBUFFER_WIDTH, &backingWidth);
    glGetRenderbufferParameteriv(GL_RENDERBUFFER, GL_RENDERBUFFER_HEIGHT, &backingHeight);
    
    // Create a depth buffer to use with our drawable FBO
    glGenRenderbuffers(1, &_depthRenderbuffer);
    glBindRenderbuffer(GL_RENDERBUFFER, _depthRenderbuffer);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT16, backingWidth, backingHeight);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, _depthRenderbuffer);
    
    if(glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
    {
        NSLog(@"failed to make complete framebuffer object %x", glCheckFramebufferStatus(GL_FRAMEBUFFER));
        return nil;
    }
    
    return self;
}

- (void)render
{
    // Replace the implementation of this method to do your own custom drawing
    glBindFramebuffer(GL_FRAMEBUFFER, _defaultFBOName);
    
    long long t = (long long)([[NSDate date] timeIntervalSince1970] * 1000.0);
    float dt = (t - _lastTime) / 1000.0f;
    if(dt > 5.0f) dt = 1.0f / 60.0f;
    application->update(dt);
    _lastTime = t;
    
    application->draw();
    
    glBindRenderbuffer(GL_RENDERBUFFER, _colorRenderbuffer);
    [_context presentRenderbuffer:GL_RENDERBUFFER];
}

- (BOOL)resizeFromLayer:(CAEAGLLayer*)layer
{
    // The pixel dimensions of the CAEAGLLayer
    GLint backingWidth;
    GLint backingHeight;
    
    // Allocate color buffer backing based on the current layer size
    glBindRenderbuffer(GL_RENDERBUFFER, _colorRenderbuffer);
    [_context renderbufferStorage:GL_RENDERBUFFER fromDrawable:layer];
    glGetRenderbufferParameteriv(GL_RENDERBUFFER, GL_RENDERBUFFER_WIDTH, &backingWidth);
    glGetRenderbufferParameteriv(GL_RENDERBUFFER, GL_RENDERBUFFER_HEIGHT, &backingHeight);
    
    glGenRenderbuffers(1, &_depthRenderbuffer);
    glBindRenderbuffer(GL_RENDERBUFFER, _depthRenderbuffer);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT16, backingWidth, backingHeight);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, _depthRenderbuffer);
    
    application->resize(backingWidth, backingHeight);
    
    if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
    {
        NSLog(@"Failed to make complete framebuffer object %x", glCheckFramebufferStatus(GL_FRAMEBUFFER));
        return NO;
    }
    
    if(_initialized == false)
    {
        application->initialize();
        _initialized = true;
    }
    
    return YES;
}

- (void)dealloc
{
    // tear down GL
    if (_defaultFBOName)
    {
        GLuint defaultFBOName = _defaultFBOName;
        glDeleteFramebuffers(1, &defaultFBOName);
        _defaultFBOName = 0;
    }
    
    if (_colorRenderbuffer)
    {
        glDeleteRenderbuffers(1, &_colorRenderbuffer);
        _colorRenderbuffer = 0;
    }
    
    [super dealloc];
}

@end
