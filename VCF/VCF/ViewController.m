//
//  ViewController.m
//  VCF
//
//  Created by EverZones on 15/11/5.
//  Copyright (c) 2015年 EverZones. All rights reserved.
//

#import "ViewController.h"
#import "YUVcardImporter.h"
@interface ViewController ()

@end

@implementation ViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    // Do any additional setup after loading the view, typically from a nib.
    
//    NSString* str = [NSString stringWithContentsOfFile:[self getNumberPlatePath] encoding:NSUTF8StringEncoding error:nil];
//    [self parseVCardString:str];
    
    YUVcardImporter *importer = [[YUVcardImporter alloc] init];
    [importer parse];
    
    NSLog(@"写入成功");
    
}

- (void)didReceiveMemoryWarning {
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}

- (void)parseVCardString:(NSString *)vcardString {
    NSArray *lines = [vcardString componentsSeparatedByString:@"\n"];
    for(NSString* line in lines) {
        if ([line hasPrefix:@"CHARSET"]) {
            
        }
    }
    
}

- (NSString *)getNumberPlatePath{
    
    NSString * path = [[NSBundle mainBundle]pathForResource:@"ic" ofType:@"vcf"];
    
    return path;
    
}
@end
