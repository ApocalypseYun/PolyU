//
// Copyright 2016 Qualcomm Technologies International, Ltd.
//

#import <Foundation/Foundation.h>

// GATT Framed command
//0 bytes  1        2        3        4          5    len+4
//+--------+--------+--------+--------+ +--------+--------+
//|    VENDOR ID    |   COMMAND ID    | | PAYLOAD   ...   |
//+--------+--------+--------+--------+ +--------+--------+

#define GAIA_GATT_HEADER_SIZE                4
#define GAIA_GATT_HEADER_OFFSET_VENDOR_ID    0
#define GAIA_GATT_HEADER_OFFSET_COMMAND_ID   2
#define GAIA_GATT_HEADER_OFFSET_PAYLOAD      4
#define GAIA_GATT_COMMAND_ACK_MASK           0x8000

/*!
 @header CSRGaiaGattCommand
 This object encapsulates commands sent to Gaia.
 */

/**
 @enum GaiaCommandType - All the high level Gaia Commands
 */
typedef NS_ENUM(uint16_t, GaiaCommandType) {
    /// Retrieves the version of the configuration set
    GaiaCommand_GetConfigurationVersion         = 0x0180,
    /// Configures the LED indicators. Determines patterns to be displayed in given states and on events and configures filters to be applied as events occur.
    GaiaCommand_SetLEDConfiguration             = 0x0101,
    /// Retrieves the current LED configuration.
    GaiaCommand_GetLEDConfiguration             = 0x0181,
    /// Configures informational tones on the device.
    GaiaCommand_SetToneConfiguration            = 0x0102,
    /// Retrieves the currently configured tone configuration.
    GaiaCommand_GetToneConfiguration            = 0x0182,
    /// Sets the default volume for tones and audio.
    GaiaCommand_SetDefaultVolume                = 0x0103,
    /// Requests the default volume settings for tones and audio.
    GaiaCommand_GetDefaultVolume                = 0x0183,
    /// Resets all settings (deletes PS keys) which override factory defaults.
    GaiaCommand_FactoryDefaultReset             = 0x0104,
    /// Configures per-event vibrator patterns.
    GaiaCommand_SetVibratorConfiguration        = 0x0105,
    /// Retrieves the currently configured vibratorconfiguration.
    GaiaCommand_GetVibratorConfiguration        = 0x0185,
    /// Configures voice prompts to select a different language, voice etc.
    GaiaCommand_SetVoicePromptConfiguration     = 0x0106,
    /// Retrieves the currently configured voice prompt configuration.
    GaiaCommand_GetVoicePromptConfiguration     = 0x0186,
    /**
     Configures the various timers on the device. This command has a long form (where the payload holds the value of every timer) and a short form (where the payload holds a timer number and the value of that timer). Timer numbers, and thus the format of the long form of the command, are application-specific; for example the ADK3.5 Audio Sink app timers are
     1. AutoSwitchOffTime_s
     2. LimboTimeout_s
     3. NetworkServiceIndicatorRepeatTime_s
     4. DisablePowerOffAfterPowerOnTime_s
     5. PairModeTimeout_s
     6. MuteRemindTime_s
     7. ConnectableTimeout_
     8. PairModeTimeoutIfPDL_s
     9. ReconnectionAttempts
     10. EncryptionRefreshTimeout_m
     11. InquiryTimeout_s
     12. SecondAGConnectDelayTime_s
     13. MissedCallIndicateTime_s
     14. MissedCallIndicateAttemps
     15. A2dpLinkLossReconnectionTime_s
     16. LanguageConfirmTime_s
     17. SpeechRecRepeatTime_ms
     18. StoreCurrentSinkVolumeTimeout_s
     19. WiredAudioConnectedPowerOffTimeout_s
     20. StoreCurrentPEQSettingsTimeout_s
     21. DefragCheckTimer_s
     22. AudioAmpPowerDownTimeoutInLimbo_s     */
    GaiaCommand_SetTimerConfiguration           = 0x0109,
    /**
     Retrieves the configuration of the various timers on the device. This command has a long form (where the response holds the value of every timer) and a short form (where the command payload holds a timer number and the response holds the number and value of that timer). Timer numbers, and thus the format of the long form of the acknowledgement, are application-specific
     */
    GaiaCommand_GetTimerConfiguration           = 0x0189,
    /**
     Configures the device volume control for each of the 16 volume levels:
     1. Level to change to when Volume Up is actioned
     2. Level to change to when Volume Down is actioned
     3. Tone to play when this volume level is selected
     4. Music (A2DP) Gain at this level; must be zero since GAIA API V2.2
     5. Voice (HFP) Gain at this level
     This command has a long form (where the payload holds every one of the 16 × 5 parameters) and a short form (where the payload holds a volume profile number and the parameter values of that profile).
     */
    GaiaCommand_SetAudioGainsConfiguration      = 0x010A,
    /**
     Requests the device volume control configuration for each of the 16 volume levels:
     1. Level to change to when Volume Up is actioned
     2. Level to change to when Volume Down is actioned
     3. Tone to play when this volume level is selected
     4. Music (A2DP) Gain at this level; must be zero since GAIA API V2.2
     5. Voice (HFP) Gain at this level
     This command has a long form (where the response holds every one of the 16 × 5 parameters) and a short form (where the response holds a Volume Profile number and the values of the parameters for that profile).
     */
    GaiaCommand_GetAudioGainsConfiguration      = 0x018A,
    /// Sets the credentials to access the Wi-Fi access point.
    GaiaCommand_SetWLANCredentials              = 0x0110,
    /// Retrieves the credentials to access the Wi-Fi access point.
    GaiaCommand_GetWLANCredentials              = 0x0190,
    /// Get the mounted partitions
    GaiaCommand_GetMountedPartitions            = 0x01A0,
    /// Configures which SQIF partition is to be used for DFU operations.
    GaiaCommand_SetDFUPartition                 = 0x0121,
    /// Retrieves the index and size of the configured DFU partition.
    GaiaCommand_GetDFUPartition                 = 0x01A1,
    
    /**
     The host can raise/lower the current volume or mute/unmute audio using this command.
     The command takes a single parameter in the first byte of payload.
     */
    GaiaCommand_Volume                          = 0x0201,
    /**
     A host can cause a device to warm reset using this command. The device will transmit an acknowledgement and then do a warm reset.
     The host must be authenticated to use this command.
     */
    GaiaCommand_DeviceReset                     = 0x0202,
    /// Get the power state of the device
    GaiaCommand_GetPowerState                   = 0x0284,
    /// Set the power state of the device
    GaiaCommand_SetPowerState                   = 0x0204,
    /// Sets the orientation of the volume control buttons on the device
    GaiaCommand_SetVolumeOrientation            = 0x0205,
    /// Requests the current orientation of the volume control buttons on the device
    GaiaCommand_GetVolumeOrientation            = 0x0285,
    /// Enables or disables use of the vibrator in the headset, if one is present
    GaiaCommand_SetVibratorControl              = 0x0206,
    /// Requests the current setting of the vibrator
    GaiaCommand_GetVibratorControl              = 0x0286,
    /// Enables or disables LEDs (or equivalent indicators) on the headset
    GaiaCommand_SetLEDControl                   = 0x0207,
    /// Establishes whether LED indicators are enabled
    GaiaCommand_GetLEDControl                   = 0x0287,
    /// Sent from a headset to control an FM receiver on the phone, or from a handset to control a reciever in a headset.
    GaiaCommand_FMControl                       = 0x0208,
    /// Play a tone
    GaiaCommand_PlayTone                        = 0x0209,
    /// Enables or disables voice prompts on the headset
    GaiaCommand_SetVoicePromptControl           = 0x020A,
    /// Establishes whether voice prompts are enabled
    GaiaCommand_GetVoicePromptControl           = 0x028A,
    /// Selects the next available language for Text-to-Speech functions
    GaiaCommand_ChangeTTSLanguage               = 0x020B,
    /// Enables or disables simple speech recognition on the headset
    GaiaCommand_SetSpeechRecognitionControl     = 0x020C,
    /// Establishes whether speech recognition is enabled
    GaiaCommand_GetSpeechRecognitionControl     = 0x028C,
    /// Undocumented
    GaiaCommand_AlertLEDs                       = 0x020D,
    /// Undocumented
    GaiaCommand_AlertTone                       = 0x020E,
    /// Undocumented
    GaiaCommand_AlertEvent                      = 0x0210,
    /// Undocumented
    GaiaCommand_AlertVoice                      = 0x0211,
    /// Undocumented
    GaiaCommand_SetTextToSpeechLanguage         = 0x0212,
    /// Undocumented
    GaiaCommand_GetTextToSpeechLanguage         = 0x0292,
    /// Undocumented
    GaiaCommand_StartSpeechRecognition          = 0x0213,
    /// Selects an audio equaliser preset
    GaiaCommand_SetEQControl                    = 0x0214,
    /// Gets the currently selected audio equaliser preset
    GaiaCommand_GetEQControl                    = 0x0294,
    /// Enables or disables bass boost on the headset
    GaiaCommand_SetBassBoostControl             = 0x0215,
    /// Establishes whether bass boost is enabled
    GaiaCommand_GetBassBoostControl             = 0x0295,
    /// Enables or disables 3D sound enhancement on the headset
    GaiaCommand_Set3DEnhancementControl         = 0x0216,
    /// Establishes whether 3D Enhancement is enabled
    GaiaCommand_Get3DEnhancementControl         = 0x0296,
    /// Switches to the next available equaliser preset. If issued while the last available preset is selected, switches to the first.
    GaiaCommand_SwitchEQControl                 = 0x0217,
    /// Turns on the Bass Boost effect if it was turned off; turns Bass Boost off if it was on.
    GaiaCommand_ToggleBassBoostControl          = 0x0218,
    /// Turns on the 3D Enhancement effect if it was turned off; turns 3D Enhancement off if it was on.
    GaiaCommand_Toggle3DEnhancementControl      = 0x0219,
    /// Sets a parameter of the parametric equaliser and optionally recalculates the filter coefficients.
    GaiaCommand_SetEQParameter                  = 0x021A,
    /// Gets a parameter of the parametric equaliser.
    GaiaCommand_GetEQParameter                  = 0x029A,
    /// Sets a group of parameters of the parametric equaliser.
    GaiaCommand_SetEQGroupParameter             = 0x021B,
    /// Gets a group of parameters of the parametric equaliser.
    GaiaCommand_GetEQGroupParameter             = 0x029B,
    /// Undocumented
    GaiaCommand_DisplayControl                  = 0x021C,
    /// Puts a Bluetooth device into pairing mode, making it discoverable and connectable.
    GaiaCommand_EnterBluetoothPairingMode       = 0x021D,
    /// Sends an AVRC command to the device
    GaiaCommand_AVRemoteControl                 = 0x021F,
    /// Enables or disables the User-configured parametric equaliser on the device (compare Set EQ Control)
    GaiaCommand_SetUserEQControl                = 0x0220,
    /// Establishes whether User EQ is enabled
    GaiaCommand_GetUserEQControl                = 0x02A0,
    /// Turns on the User EQ if it was turned off; turns User EQ off if it was on.
    GaiaCommand_ToggleUserEQControl             = 0x0221,
    /// Controls the routing of True Wireless Stereo channels
    GaiaCommand_SetTWSAudioRouting              = 0x0224,
    /// Returns the current routing of True Wireless Stereo channels
    GaiaCommand_GetTWSAudioRouting              = 0x02A4,
    /// Controls the volume of True Wireless Stereo output
    GaiaCommand_SetTWSVolume                    = 0x0225,
    /// Returns the current volume setting of True Wireless Stereo
    GaiaCommand_GetTWSVolume                    = 0x02A5,
    /// Trims the volume of True Wireless Stereo output
    GaiaCommand_TrimTWSVolume                   = 0x0226,
    /// Requests the peer in a True Wireless Stereo session to begin Advertising. The command payload length will be 1 if no target address is specified or 8 if a Typed Bluetooth Device Address is specified.
    GaiaCommand_TWSPeerStartAdvertising         = 0x022A,

    /// Find my remote command
    GaiaCommand_FindMe                          = 0x022B,

    /// Reliable write characterestic supported
    GaiaCommand_SetDataEndPointMode             = 0x022E,

    /// Reliable write characterestic supported
    GaiaCommand_GetDataEndPointMode             = 0x02AE,

    /// Gets the current audio source
    GaiaCommand_GetAudioSource                  = 0x029E,
    /// Set the current audio source
    GaiaCommand_SetAudioSource                  = 0x021E,
    
    /// solos gaia commands
    GaiaCommand_Solos                           = 0x0288,
    
    /// Get the Gaia Protocol and API version numbers from the device.
    GaiaCommand_GetAPIVersion                   = 0x0300,
    /// Get the current RSSI value for the Bluetooth link from the device. The RSSI is specified in dBm using 2's compliment representation, e.g. -20 = 0xEC.
    GaiaCommand_GetCurrentRSSI                  = 0x0301,
    /// Get the current battery level from the device. Battery level is specified in mV stored as a uint16, e.g. 3,300mV = 0x0CE4.
    GaiaCommand_GetCurrentBatteryLevel          = 0x0302,
    /// Requests the BlueCore hardware, design and module identification.
    GaiaCommand_GetModuleID                     = 0x0303,
    /**
     Requests the application software to identify itself. The acknowledgement payload contains eight octets of application identification optionally followed by nul-terminated human-readable text. The identification information is application dependent; the headset copies fields from the Bluetooth Device ID.
     */
    GaiaCommand_GetApplicationVersion           = 0x0304,
    /// Requests the logic state of the chip PIOs
    GaiaCommand_GetPIOState                     = 0x0306,
    /// Requests the value read by a given analogue-to-digital converter.
    GaiaCommand_ReadADC                         = 0x0307,
    /// Requests the Bluetooth device address of the peer
    GaiaCommand_GetPeerAddress                  = 0x030A,
    /// Requests the status of the last completed DFU operation.
    GaiaCommand_GetDFUStatus                    = 0x0310,
    
    /// Initiate a Gaia Authentication exchange.
    GaiaCommand_AuthenticateRequest             = 0x0501,
    /// Provide authentication credentials
    GaiaCommand_AuthenticateResponse            = 0x0502,
    /// The host can use this command to enable or disable a feature which it is authenticated to use.
    GaiaCommand_SetFeature                      = 0x0503,
    /// The host can use this command to request the status of a feature.
    GaiaCommand_GetFeature                      = 0x0583,
    /// Undocumented
    GaiaCommand_EnableSession                   = 0x0504,
    
    /**
     Initialise a data transfer session.
     The host provides a uint16 Session ID identifying the data session. The Session ID must be used by both host and device in the Host To Device Data and Device To Host Data commands.
     An acknowledgement containing a 'Success' (0x00) command status indicates the device has successfully initialised data transfer for the Session ID.
     If a Session ID outside the valid range, or a duplicate of an existing Session ID is used by the host, the acknowledgement packet will indicate failure with 'Invalid Parameter' (0x05) command status.
     If Data Transfer Setup command is correct, but the device cannot initialise a data session, the acknowledgement packet will indicate failure with 'Failed Insufficient Resources' (0x03) command status.
     If the host is not authenticated it will receive an acknowledgement containing a 'Failed Not Authenticated' (0x02) command status.
     */
    GaiaCommand_DataTransferSetup               = 0x0601,
    /**
     The host uses this command to indicate closure of a data transfer session, providing the Session ID in the packet payload. The device can release any resources required to maintain a data transfer session at this point, as the host must perform another Data Transfer Setup before sending any more data.
     If the Session ID is outside the valid range, or is not an existing open Session ID, the acknowledgement packet will indicate failure with 'Invalid Parameter' (0x05) command status.
     An acknowledgement containing a 'Success' (0x00) command status indicates the device has successfully closed data transfer for the Session ID.
     If the host is not authenticated it will receive an acknowledgement containing a 'Failed Not Authenticated' (0x02) command status.
     */
    GaiaCommand_DataTransferClose               = 0x0602,
    /**
     A host can use this command to transfer data to a device.
     This command can only be used following a successful acknowledgement by the device to a Data Transfer Setup command.
     The host can transfer upto 252 bytes of data in a single packet.
     An acknowledgement containing 'Success' (0x00) command status indicates the host successfully received the data transfer. The device is then permitted to make another transfer.
     */
    GaiaCommand_HostToDeviceData                = 0x0603,
    /**
     A device can use this command to transfer data to the host.
     This command can only be used following a successful acknowledgement by the device to a Data Transfer Setup command.
     The device can transfer upto 252 bytes of data in a single packet.
     An acknowledgement containing 'Success' (0x00) command status indicates the host successfully received the data transfer. The device is then permitted to make another transfer.
     */
    GaiaCommand_DeviceToHostData                = 0x0604,
    /// Retrieves information on a storage partition.
    GaiaCommand_GetStoragePartitionStatus       = 0x0610,
    /// Prepares a device storage partition for access from the host.
    GaiaCommand_OpenStoragePartition            = 0x0611,
    /// Prepares a UART for access from the host.
    GaiaCommand_OpenUART                        = 0x0612,
    /// Writes raw data to an open storage partition.
    GaiaCommand_WriteStoragePartition           = 0x0615,
    /// Writes data to an open stream.
    GaiaCommand_WriteStream                     = 0x0617,
    /// Closes a storage partition.
    GaiaCommand_CloseStoragePartition           = 0x0618,
    /// Mounts a device storage partition for access from the device.
    GaiaCommand_MountStoragePartition           = 0x061A,
    /// Undocumented
    GaiaCommand_GetFileStatus                   = 0x0620,
    /// Closes a file.
    GaiaCommand_OpenFile                        = 0x0621,
    /// Reads data from an open file.
    GaiaCommand_ReadFile                        = 0x0624,
    /// Closes a file.
    GaiaCommand_CloseFile                       = 0x0628,
    /// Indicates to the host that the device wishes to recieve a Device Firmware Upgrade image.
    GaiaCommand_DFURequest                      = 0x0630,
    /// Readies the device to recieve a Device Firmware Upgrade image. The payload will be 8 or 136 octets depending on the message digest type
    GaiaCommand_DFUBegin                        = 0x0631,
    /// Commands the device to install the DFU image and restart.
    GaiaCommand_DFUCommit                       = 0x0633,
    /// Requests the status of the last completed DFU operation.
    GaiaCommand_DFUGetResult                    = 0x0634,
    /// Begins a VM Upgrade session over GAIA, allowing VM Upgrade Protocol packets to be sent using the VM Upgrade Control and VM Upgrade Data commands.
    GaiaCommand_VMUpgradeConnect                = 0x0640,
    /// Ends a VM Upgrade session over GAIA
    GaiaCommand_VMUpgradeDisconnect             = 0x0641,
    /// Tunnels a VM Upgrade Protocol packet
    GaiaCommand_VMUpgradeControl                = 0x0642,
    /// Introduces VM Upgrade Protocol data
    GaiaCommand_VMUpgradeData                   = 0x0643,
    
    /// Requests the device to perform no operation; serves to establish that the Gaia protocol handler is alive.
    GaiaCommand_NoOperation                     = 0x0700,
    /// Requests the values of the device debugging flags.
    GaiaCommand_GetDebugFlags                   = 0x0701,
    /// Sets the values of the device debugging flags.
    GaiaCommand_SetDebugFlags                   = 0x0702,
    /// Retrieves the value of the indicated PS key. Note that the key is interpreted as an index into PSKEY_USR0, ... PSKEY_USR49, PSKEY_DSP0 ... PSKEY_DSP49
    GaiaCommand_RetrievePSKey                   = 0x0710,
    /// Retrieves the value of the indicated PS key. Note that this uses full CSR PS key numbering, not the 0..99 space used by the other PS functions.
    GaiaCommand_RetrieveFullPSKey               = 0x0711,
    /**
     Sets the value of the indicated PS key. Note that the key is interpreted as an index into PSKEY_USR0, ... PSKEY_USR49, PSKEY_DSP0 ... PSKEY_DSP49
     The PS key value is stored in 16-bit words. It is an error to attempt to store an odd number of bytes.
     */
    GaiaCommand_StorePSKey                      = 0x0712,
    /// Flood fill the store to force a defragment at next boot.
    GaiaCommand_FloodPersistentStore            = 0x0713,
    /// Results in a GAIA_DEBUG_MESSAGE being sent up from the Gaia library to the application task. Its interpretation is entirely user defined.
    GaiaCommand_SendDebugMessage                = 0x0720,
    /// Sends an arbitrary message to the onchip application.
    GaiaCommand_SendApplicationMessage          = 0x0721,
    /// Sends an arbitrary message to the Kalimba DSP (essentially KalimbaSendMessage(message, a, b, c, d))
    GaiaCommand_SendKalimbaMessage              = 0x0722,
    /// Retrieves the number of available malloc() slots and the space available for PS keys.
    GaiaCommand_GetMemorySlots                  = 0x0730,
    /// Retrieves the value of the specified 16-bit debug variable.
    GaiaCommand_GetDebugVariable                = 0x0740,
    /// Sets the value of the specified 16-bit debug variable.
    GaiaCommand_SetDebugVariable                = 0x0741,
    /// Removes all authenticated devices from the paired device list and any associated attribute data.
    GaiaCommand_DeletePairedDeviceList          = 0x0750,
    /// Sent to a BLE slave device, causing it to request a new set of connection parameters.
    GaiaCommand_SetBLEConnectionParameters      = 0x0752,
    
    /**
     Hosts register for notifications using the Register Notification command, specifying an Event Type from table below as the first byte of payload, with optional parameters as defined per event in successive payload bytes.
     The host will receive a standard acknowledgement (top-bit set), with the first byte of the payload indicating command status of the event registration, and the second byte indicating the Event Type.
     */
    GaiaCommand_RegisterNotification            = 0x4001,
    /**
     Requests the current status of an event type. For threshold type events where multiple levels may be registered, the response indicates how many notifications are registered. Where an event may be simply registered or not the number will be 1 or 0.
     */
    GaiaCommand_GetNotification                 = 0x4081,
    /**
     A host can cancel event notification by sending a Cancel Notification command, the first byte of payload will be the Event Type being cancelled.
     The cancel event command is acknowledged, in the same manner as for the Register Notification command; byte 1 indicating command status, byte 2 indicating Event Type.
     */
    GaiaCommand_CancelNotification              = 0x4002,
    /**
     Assuming successful registration, the host will asynchronously receive one or more Event Notification command(s) (Command ID 0x4003). The first byte of the Event Notification command payload will be the Event Type code, indicating the notification type. For example, 0x03 indicating a battery level low threshold event notification. Further data in the Event Notification payload is dependent on the notification type and defined on a per-notification basis below.
     The host must send an acknowledgement packet. The acknowledgement packet specifies an Event Notification Command ID with the top-bit set (0xC003). The packet payload has a success command status in the first byte, and the Event Type code as the second byte.
     */
    GaiaCommand_EventNotification               = 0x4003,
    
    /// solos event notification 
    GaiaCommand_SolosEventNotification          = 0x4288,
    
    // solos event va stream
    GaiaCommand_SolosEventVaStream              = 0x4289
};

/**
 @enum GaiaCommandStatus - Response to a command
 */
typedef NS_ENUM(uint8_t, GaiaCommandStatus) {
    /// The command succeeded.
    GaiaStatus_Success                          = 0x00,
    /// An invalid Command ID was specified.
    GaiaStatus_FailedNotSupported               = 0x01,
    /// The host is not authenticated to use a Command ID orcontrol a Feature Type.
    GaiaStatus_FailedNotAuthenticated           = 0x02,
    /// The command was valid, but the device could not successfully carry out the command.
    GaiaStatus_FailedInsufficientResources      = 0x03,
    /// The device is in the process of authenticating the host.
    GaiaStatus_Authenticating                   = 0x04,
    /// An invalid parameter was used in the command.
    GaiaStatus_InvalidParameter                 = 0x05,
    /// The device is not in the correct state to process the command.
    GaiaStatus_IncorrectState                   = 0x06,
    /// The command is in progress
    GaiaStatus_InProgress                       = 0x07,
    /// Timoeut
    GaiaStatus_Timeout                          = 0x08,
    GaiaStatus_InvalidPayloadLength             = 0x09,
    GaiaStatus_InvalidEQBank                    = 0x0a,
    /// Undocumented
    GaiaStatus_NoStatusAvailable                = 0xFF
};

/**
 @enum GaiaIVORCommand - Voice Assistant commands
 */
typedef NS_ENUM(uint16_t, GaiaIVORCommand) {
    /// Used by a device to request the start of a voice assistant session.
    GaiaIVORCommand_Start = 0x1000,
     /// Used by the host to request the device to stream the voice request of a voice assistant session.
    GaiaIVORCommand_VoiceDataRequest = 0x1001,
    /// Used by the device to stream the voice.
    /// Warning: no acknowledgement is sent for this command.
    GaiaIVORCommand_VoiceData = 0x1002,
    /// Used by the host to indicate the device to stop to stream the voice.
    GaiaIVORCommand_VoiceEnd = 0x1003,
    /// Used by the host or the device to cancel a voice assistant session.
    GaiaIVORCommand_Cancel = 0x1004,
    /// Used by the device to check if the host supports its IVOR version.
    GaiaIVORCommand_CheckVersion = 0x1005,
    /// Used by the host to indicate to the device that the voice assistant response is going to be played.
    GaiaIVORCommand_AnswerStart = 0x1006,
    /// Used by the host to indicate to the device that the voice assistant response has finished to be played.
    GaiaIVORCommand_AnswerEnd = 0x1007,
    /// Check the device is responding
    GaiaIVORCommand_Ping = 0x10F0
};

/**
 @enum GaiaCommandUpdate - OTAU commands
 */
typedef NS_ENUM(NSUInteger, GaiaCommandUpdate) {
    GaiaUpdate_Unknown                          = 0x00,
    GaiaUpdate_StartRequest                     = 0x01,
    GaiaUpdate_StartConfirm                     = 0x02,
    GaiaUpdate_DataBytesRequest                 = 0x03,
    GaiaUpdate_Data                             = 0x04,
    GaiaUpdate_SuspendIndicator                 = 0x05,
    GaiaUpdate_ResumeIndicator                  = 0x06,
    GaiaUpdate_AbortRequest                     = 0x07,
    GaiaUpdate_AbortConfirm                     = 0x08,
    GaiaUpdate_ProgressRequest                  = 0x09,
    GaiaUpdate_ProgressConfirm                  = 0x0A,
    GaiaUpdate_TransferCompleteIndicator        = 0x0B,
    GaiaUpdate_TransferCompleteResult           = 0x0C,
    GaiaUpdate_InProgressIndicator              = 0x0D,
    GaiaUpdate_InProgressResult                 = 0x0E,
    GaiaUpdate_CommitRequest                    = 0x0F,
    GaiaUpdate_CommitConfirm                    = 0x10,
    GaiaUpdate_ErrorWarnIndicator               = 0x11,
    GaiaUpdate_CompleteIndicator                = 0x12,
    GaiaUpdate_SyncRequest                      = 0x13,
    GaiaUpdate_SyncConfirm                      = 0x14,
    GaiaUpdate_StartDataRequest                 = 0x15,
    GaiaUpdate_IsValidationDoneRequest          = 0x16,
    GaiaUpdate_IsValidationDoneConfirm          = 0x17,
    GaiaUpdate_SyncAferRebootRequest            = 0x18,
    GaiaUpdate_VersionRequest                   = 0x19,
    GaiaUpdate_VersionConfirm                   = 0x1A,
    GaiaUpdate_VariantRequest                   = 0x1B,
    GaiaUpdate_VariantConform                   = 0x1C,
    GaiaUpdate_HostEraseSquifRequest            = 0x1D,
    GaiaUpdate_HostEraseSquifConfirm            = 0x1E,
    GaiaUpdate_ErrorWarnResponse                = 0x1F
};

/**
 @enum GaiaCommandUpdateResponse - OTAU command responses
 */
typedef NS_ENUM(NSUInteger, GaiaCommandUpdateResponse) {
    GaiaUpdateResponse_Success                          = 0x00,
    GaiaUpdateResponse_ErrorUnknownId                   = 0x11,
    GaiaUpdateResponse_ErrorBadLength                   = 0x12,
    GaiaUpdateResponse_ErrorWrongVariant                = 0x13,
    GaiaUpdateResponse_ErrorWrongPartitionNumber        = 0x14,
    GaiaUpdateResponse_ErrorPartitionSizeMismatch       = 0x15,
    GaiaUpdateResponse_ErrorPartitionTypeNotFound       = 0x16,
    GaiaUpdateResponse_ErrorPartitionOpenFailed         = 0x17,
    GaiaUpdateResponse_ErrorPartitionWriteFailed        = 0x18,
    GaiaUpdateResponse_ErrorPartitionCloseFailed        = 0x19,
    GaiaUpdateResponse_ErrorSFSValidationFailed         = 0x1A,
    GaiaUpdateResponse_ErrorOEMValidationFailed         = 0x1B,
    GaiaUpdateResponse_ErrorUpdateFailed                = 0x1C,
    GaiaUpdateResponse_ErrorAppNotReady                 = 0x1D,
    GaiaUpdateResponse_ErrorLoaderError                 = 0x1E,
    GaiaUpdateResponse_ErrorUnexpectedLoaderMessage     = 0x1F,
    GaiaUpdateResponse_ErrorMissingLoaderMessage        = 0x20,
    GaiaUpdateResponse_ErrorBatteryLow                  = 0x21,
    GaiaUpdateResponse_ErrorInvalidSyncId               = 0x22,
    GaiaUpdateResponse_ErrorInErrorState                = 0x23,
    GaiaUpdateResponse_ErrorNoMemory                    = 0x24,
    GaiaUpdateResponse_ErrorBadLengthPartitionParse     = 0x30,
    GaiaUpdateResponse_ErrorBadLengthTooShort           = 0x31,
    GaiaUpdateResponse_ErrorBadLengthUpgradeHeader      = 0x32,
    GaiaUpdateResponse_ErrorBadLengthPartitionHeader    = 0x33,
    GaiaUpdateResponse_ErrorBadLengthSignature          = 0x34,
    GaiaUpdateResponse_ErrorBadLengthDataHeaderResume   = 0x35,
    GaiaUpdateResponse_ErrorOEMValidationFailedHeader   = 0x38,
    GaiaUpdateResponse_ErrorOEMValidationFailedUpgradeHeader = 0x39,
    GaiaUpdateResponse_ErrorOEMValidationFailedPartitionHeader = 0x3A,
    GaiaUpdateResponse_ErrorOEMValidationFailedPartitionHeader2 = 0x3B,
    GaiaUpdateResponse_ErrorOEMValidationFailedPartitionData = 0x3C,
    GaiaUpdateResponse_ErrorOEMValidationFailedFooter   = 0x3D,
    GaiaUpdateResponse_ErrorOEMValidationFailedMemory   = 0x3E,
    GaiaUpdateResponse_ErrorPartitionCloseFailed2       = 0x40,
    GaiaUpdateResponse_ErrorPartitionCloseFailedHeader  = 0x41,
    GaiaUpdateResponse_ErrorPartitionCloseFailedPSSpace = 0x42,
    GaiaUpdateResponse_ErrorPartitionTypeNotMatching    = 0x48,
    GaiaUpdateResponse_ErrorPartitionTypeTwoDFU         = 0x49,
    GaiaUpdateResponse_ErrorPartitionWriteFailedHeader  = 0x50,
    GaiaUpdateResponse_ErrorPartitionWriteFailedData    = 0x51,
    GaiaUpdateResponse_ErrorFileTooSmall                = 0x58,
    GaiaUpdateResponse_ErrorFileTooBig                  = 0x59,
    GaiaUpdateResponse_ErrorInternalError1              = 0x65,
    GaiaUpdateResponse_ErrorInternalError2              = 0x66,
    GaiaUpdateResponse_ErrorInternalError3              = 0x67,
    GaiaUpdateResponse_ErrorInternalError4              = 0x68,
    GaiaUpdateResponse_ErrorInternalError5              = 0x69,
    GaiaUpdateResponse_ErrorInternalError6              = 0x6A,
    GaiaUpdateResponse_ErrorInternalError7              = 0x6B,
    GaiaUpdateResponse_WarnAppConfigVersionIncompatible = 0x80,
    GaiaUpdateResponse_ForceSync                        = 0x81
};

/**
 @enum GaiaEvent - Events that you can recieve notifications for
 */
typedef NS_ENUM(NSUInteger, GaiaEvent) {
    GaiaEvent_RSSILowThreshold                  = 0x01,
    GaiaEvent_RSSIHighThreshold                 = 0x02,
    GaiaEvent_BatteryLowThreshold               = 0x03,
    GaiaEvent_BatteryHighThreshold              = 0x04,
    GaiaEvent_DeviceStateChanged                = 0x05,
    GaiaEvent_PioChanged                        = 0x06,
    GaiaEvent_DebugMessage                      = 0x07,
    GaiaEvent_BatteryCharged                    = 0x08,
    GaiaEvent_ChargerConnection                 = 0x09,
    GaiaEvent_CapsenseUpdate                    = 0x0A,
    GaiaEvent_UserAction                        = 0x0B,
    GaiaEvent_SpeechRecognition                 = 0x0C,
    GaiaEvent_AVCommand                         = 0x0D,
    GaiaEvent_RemoteBatteryIndication           = 0x0E,
    GaiaEvent_KeyEvent                          = 0x0F,
    GaiaEvent_DFUState                          = 0x10,
    GaiaEvent_UARTReceivedData                  = 0x11,
    GaiaEvent_VMUpgradeProtocolPacket           = 0x12,
    GaiaEvent_UnknownEvent                      = 0xFF
};

/**
 @enum GaiaCommandFeature - Enable or disable a feature
 */
typedef NS_ENUM(NSUInteger, GaiaCommandFeature) {
    GaiaCommandFeature_Enable                   = 0x00,
    GaiaCommandFeature_Disable                  = 0x01
};

/**
 @enum GaiaCommandAction - continue or abort
 */
typedef NS_ENUM(NSUInteger, GaiaCommandAction) {
    GaiaCommandAction_Continue                  = 0x00,
    GaiaCommandAction_Abort                     = 0x01
};

/**
 @enum GaiaCommandAction - continue or abort
 */
typedef NS_ENUM(NSUInteger, GaiaUpdateResumePoint) {
    GaiaUpdateResumePoint_Start,
    GaiaUpdateResumePoint_Validate,
    GaiaUpdateResumePoint_Reboot,
    GaiaUpdateResumePoint_PostReboot,
    GaiaUpdateResumePoint_Commit
};

/**
 @enum GaiaAVControlOperation - AV commands
 */
typedef NS_ENUM(NSUInteger, GaiaAVControlOperation) {
    GaiaAVControlOperation_Power                = 0x40,
    GaiaAVControlOperation_VolumeUp             = 0x41,
    GaiaAVControlOperation_VolumeDown           = 0x42,
    GaiaAVControlOperation_Mute                 = 0x43,
    GaiaAVControlOperation_Play                 = 0x44,
    GaiaAVControlOperation_Stop                 = 0x45,
    GaiaAVControlOperation_Pause                = 0x46,
    GaiaAVControlOperation_SkipForward          = 0x4B,
    GaiaAVControlOperation_SkipBackward         = 0x4C
};

/**
 @enum GaiaAudioSource - Audio sources.
 */
typedef NS_ENUM(NSUInteger, GaiaAudioSource) {
    GaiaAudioSourceNone = 0,
    GaiaAudioSourceFM,
    GaiaAudioSourceANALOG,
    GaiaAudioSourceSPDIF,
    GaiaAudioSourceUSB,
    GaiaAudioSourceAG1,
    GaiaAudioSourceAG2,
    GaiaAudioSourceEndOfList
};

/**
 @enum SolosParamEQParameterType
 */
typedef NS_ENUM(int, GaiaParamEQParameterType) {
    GaiaParamEQParameterType_Filter = 0,
    GaiaParamEQParameterType_Frequency,
    GaiaParamEQParameterType_Gain,
    GaiaParamEQParameterType_Q
} ;

/// @class CSRGaiaGattCommand encapsulates a data packet containing a frame and some data.
@interface CSRGaiaGattCommand : NSObject

/// @brief The raw data of the command
@property (nonatomic) NSMutableData * _Nullable command;

/// @brief tag
@property (nonatomic) NSString * _Nullable tag;

/// @brief The command type @see //apple_ref/doc/GaiaCommandType
@property (nonatomic) GaiaCommandType command_id;

/// @brief the vendor id
@property (nonatomic) uint16_t vendor_id;

/*!
 @brief Create a command with some data
 @param data The data for the command
 @return CSRGaiaGattCommand
 */
- (id _Nonnull)initWithNSData:(NSData *_Nullable)data;

/*!
 @brief Create a command with a length. Note that the data must be set separately
 @param length The length of the complete command packet
 @return CSRGaiaGattCommand
 */
- (id _Nonnull)initWithLength:(NSInteger)length;

/**
 @brief Create a command with just command and vendor

 @param commandType Command type
 @param vendor Vendor id
 @return CSRGaiaGattCommand
 */
- (id _Nonnull)initWithCommand:(GaiaCommandType)commandType vendor:(uint16_t)vendor;

/// @brief the length of the packet.
- (NSUInteger)length;

/// @brief the data for the packet
- (NSData *_Nullable)getPacket;

/*!
 @brief Set the command type
 @param type The command to send. @see //apple_ref/doc/GaiaCommandType
 */
- (void)setCommandId:(GaiaCommandType)type;

/*!
 @brief Get the command type
 @return The command type. @see //apple_ref/doc/GaiaCommandType
 */
- (GaiaCommandType)getCommandId;

/*!
 @brief Set the vendor id
 @param vendor_id The vendor id
 */
- (void)setVendorId:(uint16_t)vendor_id;

/*!
 @brief Get the vendor id
 @return The vendor id
 */
- (uint16_t)getVendorId;

/*!
 @brief Add a payload to a Gaia command
 @param payload The data to send with the command
 */
- (void)addPayload:(NSData *_Nonnull)payload;

/*!
 @brief Return an NSData object containing a copy of the GaiaCommand payload
 */
- (NSData *_Nullable)getPayload;

/*!
 @brief Determine if a GaiaCommand is an acknowledgement or not
 @return true of the command is an acknowledgement
 */
- (BOOL)isAcknowledgement;

/*!
 @brief Determine if a GaiaCommand is an control command or not
 @return true of the command is an control command
 */
- (BOOL)isControl;

/*!
 @brief Determine if a GaiaCommand is an configuration command or not
 @return true of the command is an configuration command
 */
- (BOOL)isConfiguration;

/*!
 @brief Read the command status
 @return The command status. @see //apple_ref/doc/GaiaCommandStatus
 */
- (GaiaCommandStatus)status;

/*!
 @brief Get event type from notification
 @return The Gaia event. @see //apple_ref/doc/GaiaEvent
 */
- (GaiaEvent)event;

/*!
 @brief Read the status of an OTAU command response
 @return The command response. @see //apple_ref/doc/GaiaCommandUpdate
 */
- (GaiaCommandUpdate)updateStatus;

/*!
 @brief Read the status of an OTAU command response
 @return The command response. @see //apple_ref/doc/GaiaCommandUpdateResponse
 */
- (GaiaCommandUpdateResponse)updateResponse;

@end
