#import "view.h"
#import "renderer.h"

#import <WApplication.h>
extern WApplication* application;

@interface View ()
{
    Renderer* _renderer;
    EAGLContext* _context;
    CADisplayLink* _displayLink;
    bool _animating;
}
@end

@implementation View

// Must return the CAEAGLLayer class so that CA allocates an EAGLLayer backing
// for this view
+ (Class) layerClass
{
    return [CAEAGLLayer class];
}

- (id)initWithFrame:(CGRect)frame
{
    self = [super initWithFrame:frame];
    if (self)
    {
        UIScreen *screen = [UIScreen mainScreen];
        if ([screen respondsToSelector:@selector(scale)])
        {
            GLfloat scale;
            if ([screen respondsToSelector:@selector(nativeScale)])
            {
                scale = [screen nativeScale];
            }
            else
            {
                scale = [screen scale];
            }
            [self setContentScaleFactor:scale];
        }
        
        CAEAGLLayer *layer = (CAEAGLLayer *)self.layer;
        layer.opaque = YES;
        layer.drawableProperties = [NSDictionary dictionaryWithObjectsAndKeys:
                                    [NSNumber numberWithBool:NO],
                                    kEAGLDrawablePropertyRetainedBacking,
                                    kEAGLColorFormatRGBA8,
                                    kEAGLDrawablePropertyColorFormat,
                                    nil];
        
        _context = [[EAGLContext alloc] initWithAPI:kEAGLRenderingAPIOpenGLES2];
        
        if (_context == nil || ![EAGLContext setCurrentContext:_context]) {
            [self release];
            return nil;
        }
        
        _renderer = [[Renderer alloc] initWithContext:_context AndDrawable:(id<EAGLDrawable>)self.layer];

        if (!_renderer)
        {
            return nil;
        }
        
        _animating = FALSE;
    }
    return self;
}

- (void) drawView:(id)sender
{
    [EAGLContext setCurrentContext:_context];
    [_renderer render];
}

- (void) layoutSubviews
{
    [_renderer resizeFromLayer:(CAEAGLLayer*)self.layer];
    [self drawView:nil];
}

- (void) startAnimation
{
    if (!_animating)
    {
        // Create the display link and set the callback to our drawView method
        _displayLink = [CADisplayLink displayLinkWithTarget:self selector:@selector(drawView:)];
        
        // Have the display link run on the default runn loop (and the main thread)
        [_displayLink addToRunLoop:[NSRunLoop currentRunLoop] forMode:NSDefaultRunLoopMode];
        
        _animating = TRUE;
    }
}

- (void)stopAnimation
{
    if (_animating)
    {
        [_displayLink invalidate];
        _displayLink = nil;		
        _animating = FALSE;
    }
}

- (void) dealloc
{
    // tear down context
    if ([EAGLContext currentContext] == _context)
        [EAGLContext setCurrentContext:nil];
    
    [super dealloc];
}

@end
