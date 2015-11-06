//
//  YUVcardImporter.h
//  VCF
//
//  Created by EverZones on 15/11/6.
//  Copyright (c) 2015年 EverZones. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <AddressBook/AddressBook.h>
@interface YUVcardImporter : NSObject {
    ABAddressBookRef addressBook;
    ABRecordRef personRecord;
    ABMutableMultiValueRef multiValue;
    
    NSString *base64image;
    
}

@property (nonatomic ,strong)NSMutableArray *phoneNumbers;
@property (nonatomic ,strong)NSMutableArray *labels;

- (void)parse;
- (void)parseLine:(NSString *)line;
- (void)parseNumberLabel:(NSString *)line;


@end
