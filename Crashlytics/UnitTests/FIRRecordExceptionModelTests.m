//
//  FIRRecordExceptionModelTests.m
//  FirebaseCrashlytics-iOS-Unit-unit
//
//  Created by Sam Edson on 3/11/20.
//

#import <XCTest/XCTest.h>

#import "FIRExceptionModel.h"
#import "FIRStackFrame.h"

#import "FABMockApplicationIdentifierModel.h"
#import "FIRCLSContext.h"
#import "FIRCLSInstallIdentifierModel.h"
#import "FIRCLSInternalReport.h"
#import "FIRCLSMockFileManager.h"
#import "FIRCLSMockSettings.h"
#import "FIRMockInstallations.h"

#define TEST_BUNDLE_ID (@"com.crashlytics.test")

@interface FIRRecordExceptionModelTests : XCTestCase

@property(nonatomic, strong) FIRCLSMockFileManager *fileManager;
@property(nonatomic, strong) FIRCLSMockSettings *mockSettings;
@property(nonatomic, strong) NSString *reportPath;

@end

@implementation FIRRecordExceptionModelTests

- (void)setUp {
  self.fileManager = [[FIRCLSMockFileManager alloc] init];
  [self.fileManager setPathNamespace:TEST_BUNDLE_ID];

  FABMockApplicationIdentifierModel *appIDModel = [[FABMockApplicationIdentifierModel alloc] init];
  self.mockSettings = [[FIRCLSMockSettings alloc] initWithFileManager:self.fileManager
                                                           appIDModel:appIDModel];

  FIRMockInstallations *iid = [[FIRMockInstallations alloc] initWithFID:@"test_instance_id"];

  FIRCLSInstallIdentifierModel *installIDModel =
      [[FIRCLSInstallIdentifierModel alloc] initWithInstallations:iid];

  NSString *name = @"exception_model_report";
  self.reportPath = [self.fileManager.rootPath stringByAppendingPathComponent:name];
  [self.fileManager createDirectoryAtPath:self.reportPath];

  FIRCLSInternalReport *report =
      [[FIRCLSInternalReport alloc] initWithPath:self.reportPath
                             executionIdentifier:@"TEST_EXECUTION_IDENTIFIER"];

  FIRCLSContextInitialize(report, self.mockSettings, installIDModel, self.fileManager);
}

- (void)tearDown {
  [[NSFileManager defaultManager] removeItemAtPath:self.fileManager.rootPath error:nil];
}

- (void)testWrittenCLSRecordFile {
  NSArray *stackTrace = @[
    [FIRStackFrame stackFrameWithSymbol:@"CrashyFunc" file:@"AppLib.m" line:504],
    [FIRStackFrame stackFrameWithSymbol:@"ApplicationMain" file:@"AppleLib" line:1],
    [FIRStackFrame stackFrameWithSymbol:@"main()" file:@"main.m" line:201],
  ];
  NSString *name = @"FIRExceptionModelTestsCrash";
  NSString *reason = @"Programmer made an error";

  FIRExceptionModel *exceptionModel = [FIRExceptionModel exceptionModelWithName:name reason:reason];
  exceptionModel.stackTrace = stackTrace;

  FIRCLSExceptionRecordModel(exceptionModel);

  NSData *data = [NSData
      dataWithContentsOfFile:[self.reportPath
                                 stringByAppendingPathComponent:@"custom_exception_a.clsrecord"]];
  NSDictionary *json = [NSJSONSerialization JSONObjectWithData:data options:kNilOptions error:nil];
  NSDictionary *exception = json[@"exception"];
  NSArray *frames = exception[@"frames"];
  XCTAssertEqualObjects(exception[@"name"],
                        @"464952457863657074696f6e4d6f64656c54657374734372617368");
  XCTAssertEqualObjects(exception[@"reason"], @"50726f6772616d6d6572206d61646520616e206572726f72");
  XCTAssertEqual(frames.count, 3);
  XCTAssertEqualObjects(frames[2][@"file"], @"6d61696e2e6d");
  XCTAssertEqual([frames[2][@"line"] intValue], 201);
  XCTAssertEqual([frames[2][@"offset"] intValue], 0);
  XCTAssertEqual([frames[2][@"pc"] intValue], 0);
  XCTAssertEqualObjects(frames[2][@"symbol"], @"6d61696e2829");
}

@end
