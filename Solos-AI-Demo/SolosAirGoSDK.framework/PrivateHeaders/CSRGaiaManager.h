//
// Copyright 2016 Qualcomm Technologies International, Ltd.
//

#import <Foundation/Foundation.h>
#import "BTLibrary.h"
#import "CSRGaia.h"
#import "SolosGaia.h"
#import "SolosGaiaDelegate.h"


#define CSRGaiaError                    @"Aborting the Update"
#define CSRGaiaError_1                  @"Unknown command"
#define CSRGaiaError_2                  @"Bad length"
#define CSRGaiaError_3                  @"Wrong variant"
#define CSRGaiaError_4                  @"Wrong partition number"
#define CSRGaiaError_5                  @"Partition size mismatch"
#define CSRGaiaError_6                  @"Partition type not found"
#define CSRGaiaError_7                  @"Partition open failed"
#define CSRGaiaError_8                  @"Partition write failed"
#define CSRGaiaError_9                  @"Partition close failed"
#define CSRGaiaError_10                 @"SFS validation failed"
#define CSRGaiaError_11                 @"OEM validation failed"
#define CSRGaiaError_12                 @"Update failed"
#define CSRGaiaError_13                 @"App not ready"
#define CSRGaiaError_14                 @"App configuration version incompatible"
#define CSRGaiaError_15                 @"Loader error"
#define CSRGaiaError_16                 @"Unexpected loader error"
#define CSRGaiaError_17                 @"Missing loader error"
#define CSRGaiaError_18                 @"Battery low error"

#define CSRGaiaError_22                 @"Invalid Sync Id"
#define CSRGaiaError_23                 @"In Error State"
#define CSRGaiaError_24                 @"No Memory"
#define CSRGaiaError_30                 @"Bad Length Partition Parse"
#define CSRGaiaError_31                 @"Bad Length Too Short"
#define CSRGaiaError_32                 @"Bad Length Upgrade Header"
#define CSRGaiaError_33                 @"Bad Length Partition Header"
#define CSRGaiaError_34                 @"Bad Length Signature"
#define CSRGaiaError_35                 @"Bad Length Data Header Resume"
#define CSRGaiaError_38                 @"OEM Validation Failed Header"
#define CSRGaiaError_39                 @"OEM Validation Failed Upgrade Header"
#define CSRGaiaError_3A                 @"OEM Validation Failed Partition Header"
#define CSRGaiaError_3B                 @"OEM Validation Failed Partition Header2"
#define CSRGaiaError_3C                 @"OEM Validation Failed Partition Data"
#define CSRGaiaError_3D                 @"OEM Validation Failed Footer"
#define CSRGaiaError_3E                 @"OEM Validation Failed Memory"
#define CSRGaiaError_40                 @"Partition Close Failed 2"
#define CSRGaiaError_41                 @"Partition Close Failed Header"
#define CSRGaiaError_42                 @"Partition Close Failed PS Space"
#define CSRGaiaError_48                 @"Partition Type Not Matching"
#define CSRGaiaError_49                 @"Partition Type Two DFU"
#define CSRGaiaError_50                 @"Partition Write Failed Header"
#define CSRGaiaError_51                 @"Partition Write Failed Data"
#define CSRGaiaError_58                 @"File Too Small"
#define CSRGaiaError_59                 @"File Too Big"
#define CSRGaiaError_65                 @"Internal Error1"
#define CSRGaiaError_66                 @"Internal Error2"
#define CSRGaiaError_67                 @"Internal Error3"
#define CSRGaiaError_68                 @"Internal Error4"
#define CSRGaiaError_69                 @"Internal Error5"
#define CSRGaiaError_6A                 @"Internal Error6"
#define CSRGaiaError_6B                 @"Internal Error7"

#define CSRGaiaError_Unknown            @"Unknown error: %ld"
#define CSRGaiaError_UnknownResponse    @"Unknown response from Sync Request: %ld"

#define CSRGaiaCommandError_1           @"An invalid Command ID was specified"
#define CSRGaiaCommandError_2           @"The host is not authenticated to use a Command ID orcontrol a Feature Type"
#define CSRGaiaCommandError_3           @"The command was valid, but the device could not successfully carry out the command"
#define CSRGaiaCommandError_4           @"The device is in the process of authenticating the host"
#define CSRGaiaCommandError_5           @"An invalid parameter was used in the command"
#define CSRGaiaCommandError_6           @"The device is not in the correct state to process the command"
#define CSRGaiaCommandError_7           @"The command is already in progress"
#define CSRGaiaCommandError_FF          @"No stauts available"

#define CSRStatusReconnectingString     @"Reconnecting..."
#define CSRStatusReconnectedString      @"Reconnected. Initialising..."
#define CSRStatusPairingString          @"Initialised."
#define CSRStatusFinalisingString       @"Finalising..."
#define CSRStatusReStartingString       @"Restarting update..."

/*!
 @header CSRGaiaManager
 Manage long running operations
 */

@protocol CSRGaiaManagerDelegate;
@protocol SolosGaiaInterface;

/*!
 @class CSRGaiaManager
 @abstract Singleton class that manages long running operations
 @discussion The connection manager implements CSRGaiaDelegate and CSRConnectionManagerDelegate
 */
@interface CSRGaiaManager : NSObject <CSRConnectionManagerDelegate, SolosGaiaDelegate, CSRGaiaInterface, SolosGaiaInterface>

/// @brief True of an OTAU is in progress
@property (nonatomic) BOOL updateInProgress;

/// @brief The name of the file being used for OTAU
@property (nonatomic) NSString * _Nullable updateFileName;

/// @brief A percentage complete value
@property (nonatomic) double updateProgress;

/// @brief Delegate class for callbacks.
- (void) addDelegate:(id<CSRGaiaManagerDelegate>_Nonnull) delegate;
- (void) removeDelegate:(id<CSRGaiaManagerDelegate>_Nonnull) delegate;

/// @brief If the data length extension is availble then use it to send more data in each OTAU packet
@property (nonatomic) BOOL useDLEifAvailable;

/// @brief The maximum message size.
@property (nonatomic) NSUInteger maximumMessageSize;

@property (nonatomic, assign) NSUInteger initCongestWndSize;
@property (nonatomic, assign) NSUInteger maxCongestWndSize;

- (id _Nonnull) init:(CSRConnectionManager *_Nonnull) connectionManager;

/*!
 @brief Start an OTAU
 @param fileName The file name to use.
 @param useDataEndpoint True if the upgrade should use RWCP
 */
- (void)start:(NSString *_Nonnull)fileName useDataEndpoint:(BOOL)useDataEndpoint;

/*!
 @brief Stop the current OTAU. An abort message will be sent and acknowledged.
 */
- (void)stop;

/*!
 @brief The OTAU data transfer is complete. The user can choose not to apply the new data.
 @param value True to go ahead and apply the update.
 */
- (void)commitConfirm:(BOOL)value;

/*!
 @brief The OTAU protocol can ask the user can stop and wait for the user to OK.
 OTAU will continue after calling this method.
 */
- (void)eraseSqifConfirm;

/*!
 @brief The OTAU protocol can ask the user to confirm an error.
 OTAU will continue after calling this method.
 */
- (void)confirmError;

/*!
 @brief If you want to cancel the upgrade.
 */
- (void)abort;

/*!
 @brief If there is a problem with the update the user can force the process to reset and try again.
 */
- (void)abortAndRestart;

/*!
 @brief The OTAU protocol can ask the user can stop and wait once the file transfer is complete.
 OTAU will continue after calling this method.
 */
- (void)updateTransferComplete;

/*!
 @brief The OTAU protocol can ask the user can stop and wait once the file transfer is complete.
 OTAU will abort after calling this method.
 */
- (void)updateTransferAborted;

/*!
 @brief The OTAU protocol can raise low battery warnings.
 OTAU will continue after calling this method.
 */
- (void)syncRequest;


/// @brief Prepare CSRGaiaManager by set up delegates and listeners.
- (void)connect;

/// @brief Clear delegates and listeners.
- (void)disconnect;



/*!
 @brief Send solos GAIA command
 @param cmd The solos sub command
 @param payload payload of the solos sub command
 */
- (void) sendSolosCommand: (uint8_t)cmd payload:(NSData *_Nullable)payload;


@end


/*!
 @protocol CSRUpdateManagerDelegate
 @discussion Callbacks from changes to state
 */
@protocol CSRUpdateManagerDelegate <NSObject>

@optional
/*!
 @brief The upgrade aborted.
 @param error Look at the error so see what went wrong
*/
- (void)didAbortWithError:(NSError *_Nonnull)error;


/// @brief The upgrade completed successfully
- (void)didCompleteUpgrade;

/// @brief The upgrade was aborted
- (void)didAbortUpgrade;

/*!
 @brief The upgrade made some progress
 @param value Percentage complete
 @param eta Estimaged time of completion
 */
- (void)didMakeProgress:(double)value eta:(NSString *_Nonnull)eta;

/// @brief The device rebooted after the upgrade
- (void)didWarmBoot;

/*!
 @brief State information about the device. Used when the device is in it's reboot cycle.
 @param value A string with some status information
 */
- (void)didUpdateStatus:(NSString *_Nonnull)value;

/*!
 @brief A response was recieved
 @param command The command response. @see //apple_ref/doc/CSRGaiaGattCommand
 */
- (void)didReceiveGaiaGattResponse:(CSRGaiaGattCommand *_Nonnull)command;

/// @brief Present the user with a yes no choice
- (void)confirmRequired;

/// @brief Present the user with an okay
- (void)okayRequired;

/// @brief Present the user with a yes no choice about forcing the upgrade
- (void)confirmForceUpgrade;

/// @brief Present the user with a yes no choice about the file transfer
- (void)confirmTransferRequired;

/// @brief Present the user with an okay about plugging their device into mains
- (void)confirmBatteryOkay;

/*!
 @brief Called when the service is setup and the characterists are ready to use.
 */
- (void)gaiaReady;

@end

@protocol CSRGaiaManagerDelegate <CSRUpdateManagerDelegate, CSRGaiaDelegate, SolosGaiaDelegate>


@end
