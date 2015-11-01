//
//  Macros.h
//  YUMacros
//
//  Created by EverZones on 15/10/16.
//
//

#ifndef YUMacros_Macros_h
#define YUMacros_Macros_h

#import <mach/mach_time.h>  // for mach_absolute_time() and friends
// adapted from http://blog.bignerdranch.com/316-a-timing-utility/

#import <CoreGraphics/CGBase.h>

// Adapted from Will Shipley http://blog.wilshipley.com/2005/10/pimp-my-code-interlude-free-code.html
static inline BOOL IsEmpty(id thing) {
    return thing == nil || [thing isEqual:[NSNull null]]
    || ([thing respondsToSelector:@selector(length)]
        && [(NSData *)thing length] == 0)
    || ([thing respondsToSelector:@selector(count)]
        && [(NSArray *)thing count] == 0);
}

static inline NSString *StringFromObject(id object) {
    if (object == nil || [object isEqual:[NSNull null]]) {
        return @"";
    } else if ([object isKindOfClass:[NSString class]]) {
        return object;
    } else if ([object respondsToSelector:@selector(stringValue)]){
        return [object stringValue];
    } else {
        return [object description];
    }
}

#pragma mark -
#pragma mark iOS Version

#define IOS_VERSION_EQUAL_TO(v)                  ([[[UIDevice currentDevice] systemVersion] compare:v options:NSNumericSearch] == NSOrderedSame)
#define IOS_VERSION_GREATER_THAN(v)              ([[[UIDevice currentDevice] systemVersion] compare:v options:NSNumericSearch] == NSOrderedDescending)
#define IOS_VERSION_GREATER_THAN_OR_EQUAL_TO(v)  ([[[UIDevice currentDevice] systemVersion] compare:v options:NSNumericSearch] != NSOrderedAscending)
#define IOS_VERSION_LESS_THAN(v)                 ([[[UIDevice currentDevice] systemVersion] compare:v options:NSNumericSearch] == NSOrderedAscending)
#define IOS_VERSION_LESS_THAN_OR_EQUAL_TO(v)     ([[[UIDevice currentDevice] systemVersion] compare:v options:NSNumericSearch] != NSOrderedDescending)

#pragma mark -
#pragma mark Syntactic sugar

#define NOT_ANIMATED NO
#define ANIMATED YES

#pragma mark -
#pragma mark UIColor

// example usage: UIColorFromHex(0x9daa76)
#define UIColorFromHexWithAlpha(hexValue,a) [UIColor colorWithRed:((float)((hexValue & 0xFF0000) >> 16))/255.0 green:((float)((hexValue & 0xFF00) >> 8))/255.0 blue:((float)(hexValue & 0xFF))/255.0 alpha:a]
#define UIColorFromHex(hexValue)            UIColorFromHexWithAlpha(hexValue,1.0)
#define UIColorFromRGBA(r,g,b,a)            [UIColor colorWithRed:r/255.0 green:g/255.0 blue:b/255.0 alpha:a]
#define UIColorFromRGB(r,g,b)               UIColorFromRGBA(r,g,b,1.0)

#pragma mark -
#pragma mark Collections

#define IDARRAY(...) (id []){ __VA_ARGS__ }
#define IDCOUNT(...) (sizeof(IDARRAY(__VA_ARGS__)) / sizeof(id))

#define ARRAY(...) [NSArray arrayWithObjects: IDARRAY(__VA_ARGS__) count: IDCOUNT(__VA_ARGS__)]

#define DICT(...) DictionaryWithIDArray(IDARRAY(__VA_ARGS__), IDCOUNT(__VA_ARGS__) / 2)

//The helper function unpacks the object array and then calls through to NSDictionary to create the dictionary:
static inline NSDictionary *DictionaryWithIDArray(id *array, NSUInteger count) {
    id keys[count];
    id objs[count];
    
    for(NSUInteger i = 0; i < count; i++) {
        keys[i] = array[i * 2];
        objs[i] = array[i * 2 + 1];
    }
    
    return [NSDictionary dictionaryWithObjects: objs forKeys: keys count: count];
}
#define POINTERIZE(x) ((__typeof__(x) []){ x })
#define NSVALUE(x) [NSValue valueWithBytes: POINTERIZE(x) objCType: @encode(__typeof__(x))]

#pragma mark -
#pragma mark Blocks

#define BLOCK_SAFE_RUN(block, ...) block ? block(__VA_ARGS__) : nil

#pragma mark -
#pragma mark Logging

#define LOG(fmt, ...) NSLog(@"%s: " fmt, __PRETTY_FUNCTION__, ## __VA_ARGS__)

#ifdef DEBUG
#define INFO(fmt, ...) LOG(fmt, ## __VA_ARGS__)
#else
// do nothing
#define INFO(fmt, ...)
#endif

#define ERROR(fmt, ...) LOG(fmt, ## __VA_ARGS__)
#define TRACE(fmt, ...) LOG(fmt, ## __VA_ARGS__)

#define METHOD_NOT_IMPLEMENTED() NSAssert(NO, @"You must override %@ in a subclass", NSStringFromSelector(_cmd))

#pragma mark -
#pragma mark NSNumber

#define NUM_INT(int) [NSNumber numberWithInt:int]
#define NUM_FLOAT(float) [NSNumber numberWithFloat:float]
#define NUM_BOOL(bool) [NSNumber numberWithBool:bool]

#pragma mark -
#pragma mark Frame Geometry

#define CENTER_VERTICALLY(parent,child) floor((parent.frame.size.height - child.frame.size.height) / 2)
#define CENTER_HORIZONTALLY(parent,child) floor((parent.frame.size.width - child.frame.size.width) / 2)

// example: [[UIView alloc] initWithFrame:(CGRect){CENTER_IN_PARENT(parentView,500,500),CGSizeMake(500,500)}];
#define CENTER_IN_PARENT(parent,childWidth,childHeight) CGPointMake(floor((parent.frame.size.width - childWidth) / 2),floor((parent.frame.size.height - childHeight) / 2))
#define CENTER_IN_PARENT_X(parent,childWidth) floor((parent.frame.size.width - childWidth) / 2)
#define CENTER_IN_PARENT_Y(parent,childHeight) floor((parent.frame.size.height - childHeight) / 2)

#define WIDTH(view) view.frame.size.width
#define HEIGHT(view) view.frame.size.height
#define X(view) view.frame.origin.x
#define Y(view) view.frame.origin.y
#define LEFT(view) view.frame.origin.x
#define TOP(view) view.frame.origin.y
#define BOTTOM(view) (view.frame.origin.y + view.frame.size.height)
#define RIGHT(view) (view.frame.origin.x + view.frame.size.width)

#pragma mark -
#pragma mark IndexPath

#define INDEX_PATH(a,b) [NSIndexPath indexPathWithIndexes:(NSUInteger[]){a,b} length:2]

#define ALWAYS_TRUE YES ||
#define NEVER_TRUE NO &&

#pragma mark -
#pragma mark Screen size

#define SCREEN_WIDTH [[UIScreen mainScreen] bounds].size.width
#define SCREEN_HEIGHT [[UIScreen mainScreen] bounds].size.height

#pragma mark -
#pragma mark Device type.
// Corresponds to "Targeted device family" in project settings
// Universal apps will return true for whichever device they're on.
// iPhone apps will return true for iPhone even if run on iPad.

#define TARGETED_DEVICE_IS_IPAD UI_USER_INTERFACE_IDIOM() == UIUserInterfaceIdiomPad
#define TARGETED_DEVICE_IS_IPHONE UI_USER_INTERFACE_IDIOM() == UIUserInterfaceIdiomPhone
#define TARGETED_DEVICE_IS_IPHONE_568 TARGETED_DEVICE_IS_IPHONE && SCREEN_HEIGHT == 568

#pragma mark -
#pragma mark Transforms

#define DEGREES_TO_RADIANS(degrees) degrees * M_PI / 180

static inline void TimeThisBlock (void (^block)(void), NSString *message) {
    mach_timebase_info_data_t info;
    if (mach_timebase_info(&info) != KERN_SUCCESS) {
        block();
        return;
    };
    
    uint64_t start = mach_absolute_time ();
    block ();
    uint64_t end = mach_absolute_time ();
    uint64_t elapsed = end - start;
    
    uint64_t nanos = elapsed * info.numer / info.denom;
    LOG(@"Took %f seconds to %@", (CGFloat)nanos / NSEC_PER_SEC, message);
}

#pragma mark -
#pragma mark Debug
#ifdef DEBUG
#define NSLog(args...) ConciseNSLog(__FILE__,__LINE__,__PRETTY_FUNCTION__,args);
#else
#define NSLog(x...)
#endif

void ConciseNSLog(const char *file, int lineNumber, const char *functionName, NSString *format, ...);

void ConciseNSLogWithoutTimeStamp(const char *file, int lineNumber, const char *functionName, NSString *format, ...);

// NSLogX(...) -> ExtendNSLog(...)
// Define NSLogX(), include function name, file name and line number
#define NSLogX(args...) ExtendNSLog(__FILE__,__LINE__,__PRETTY_FUNCTION__,args);

void ExtendNSLog(const char *file, int lineNumber, const char *functionName, NSString *format, ...);

// Log class name and method name
#define LogMethod NSLog(@"-[%@ %@]", NSStringFromClass(self.class),NSStringFromSelector(_cmd))

// NSInteger to NSString
#define NSIntegerToString(i) [NSString stringWithFormat:@"%lu", (unsigned long)i]

// Print an Object, to see if this object is nil
#define PrintNil(object) NSLog(@"%@ is %@", [object class], object == nil? @"nil" : @"not nil")

// Detect 4inch or 3.5inch
#define IS_IPHONE_5 ( fabs( ( double )[ [ UIScreen mainScreen ] bounds ].size.height - ( double )568 ) < DBL_EPSILON )

// Swap two numbers
#define OVERLOADABLE __attribute__((overloadable))
OVERLOADABLE void Swap(float *a, float *b);
OVERLOADABLE void Swap(NSInteger *a, NSInteger *b);
OVERLOADABLE void Swap(NSUInteger *a, NSUInteger *b);
OVERLOADABLE void Swap(double *a, double *b);

#endif

#pragma mark - 
#pragma mark - Quick Set Color

#define UIColorFromRGB(rgbValue) [UIColor colorWithRed:((float)((rgbValue & 0xFF0000) >> 16))/255.0 green:((float)((rgbValue & 0xFF00) >> 8))/255.0 blue:((float)(rgbValue & 0xFF))/255.0 alpha:1.0]
#define RGBA(r,g,b,a)         [UIColor colorWithRed:r/255.0 green:g/255.0 blue:b/255.0 alpha:a]
#define RGB(r,g,b)            [UIColor colorWithRed:r/255.0 green:g/255.0 blue:b/255.0 alpha:1.0]

















