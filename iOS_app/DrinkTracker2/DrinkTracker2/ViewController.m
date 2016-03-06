//
//  ViewController.m
//  DrinkTracker2
//
//  Created by Kwan Khunkhet on 3/6/16.
//  Copyright © 2016 EggsandWine. All rights reserved.
//

#import "ViewController.h"
@import PebbleKit;
#import "PebbleKit/PebbleKit.h"



// PBWatch
@interface ViewController () <PBPebbleCentralDelegate>

@property (weak, nonatomic) PBWatch *watch;
@property (weak, nonatomic) PBPebbleCentral *central;

@property (weak, nonatomic) IBOutlet UILabel *outputLabel;


@end


@implementation ViewController


// modify viewDidLoad
- (void)viewDidLoad {
    [super viewDidLoad];
    
    // Set the delegate to receive PebbleKit events
    self.central = [PBPebbleCentral defaultCentral];
    self.central.delegate = self;
    
    // Register UUID
    self.central.appUUID = PBSportsUUID;
    
    // Begin connection
    [self.central run];
}

- (void)didReceiveMemoryWarning {
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}




-(void)pebbleCentral:(PBPebbleCentral *)central watchDidConnect:(PBWatch *)watch isNew:(BOOL)isNew {
    // Check AppMessage is supported by this watch
    [self.watch appMessagesGetIsSupported:^(PBWatch *watch, BOOL isAppMessagesSupported) {
        if (isAppMessagesSupported) {
            // Tell the user using the Label
            self.outputLabel.text = @"AppMessage is supported!";
        } else {
            self.outputLabel.text = @"AppMessage is NOT supported!";
        }
    }];

    
    
    if (self.watch) {
        return;
    }
    self.watch = watch;
}

-(void)pebbleCentral:(PBPebbleCentral *)central watchDidDisconnect:(PBWatch *)watch {
    
    // Check AppMessage is supported by this watch
    [self.watch appMessagesGetIsSupported:^(PBWatch *watch, BOOL isAppMessagesSupported) {
        if (isAppMessagesSupported) {
            // Tell the user using the Label
            self.outputLabel.text = @"AppMessage is supported!";
        } else {
            self.outputLabel.text = @"AppMessage is NOT supported!";
        }
    }];

    
    // Only remove reference if it was the current active watch
    if (self.watch == watch) {
        self.watch = nil;
    }
}




@end
