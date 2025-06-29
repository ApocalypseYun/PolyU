//
//  SolosGaia.h
//  GaiaControl
//
//  Created by Sam Yu on 11/5/2020.
//  Copyright © 2020 Solos Technology Limited. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "GaiaLibrary.h"
#import "SolosGaiaDelegate.h"

NS_ASSUME_NONNULL_BEGIN

/**
 @enum SolosCommand
 */
typedef NS_ENUM(uint8_t, SolosCommand) {
    /// Read FW version
    SolosCommand_ReadFWVersion               = 0x00,
    /// Write the registers with I2C
    SolosCommand_WriteI2C                    = 0x01,
    /// Read the registers with I2C
    SolosCommand_ReadI2C                     = 0x02,
    /// Set Language
    SolosCommand_SetLanguage                 = 0x03,
    /// Get Language
    SolosCommand_GetLanguage                 = 0x04,
    /// Set RTC function
    SolosCommand_SetRTC                      = 0x05,
    /// UART write
    SolosCommand_WriteUart                   = 0x06,
    /// set LED
    SolosCommand_SetLED                      = 0x07,
        /// reboot
    SolosCommand_Reboot                      = 0x08,
    /// Reset the sensors and re-initial the registers
    SolosCommand_ResetSensors                = 0x10,
    /// Read Proximity Value
    SolosCommand_ReadProximity               = 0x11,
    /// Read 9-axis: gyro, accelerometer and magnetometer
    SolosCommand_Read9Axis                   = 0x12,
    /// Read temperature
    SolosCommand_ReadTemperature             = 0x14,
    /// ASR mode
    SolosCommand_SetASRMode                  = 0x16,
    /// Enable report events
    SolosCommand_EnableReport                = 0x20,
    /// Get status of report events
    SolosCommand_GetEnabledReport            = 0x21,
    /// Set report interval of 9-axis event
    SolosCommand_SetReportInterval           = 0x22,
    /// Get report interval of 9-axis event
    SolosCommand_GetReportInterval           = 0x23,
    /// Enable UART
    SolosCommand_EnableUart                  = 0x24,
    /// Set debug events
    SolosCommand_SetDebugEvents              = 0x25,
    /// Get debug events
    SolosCommand_GetDebugEvents              = 0x26,
    /// Set AV events
    SolosCommand_SetAvEvents                 = 0x27,
    /// Get AV events
    SolosCommand_GetAvEvents                 = 0x28,
    /// Get AV Info
    SolosCommand_GetAvInfo                   = 0x29,
    /// Set Va stream
    SolosCommand_SetVaStream                 = 0x2A,
    /// Write confguration parameters
    SolosCommand_WriteConfig                 = 0x30,
    /// Read configuration parameters
    SolosCommand_ReadConfig                  = 0x31,
    /// Write DSP Key
    SolosCommand_WriteDSPKey                 = 0x32,
    /// Read DSP Key
    SolosCommand_ReadDSPKey                  = 0x33,
    /// Set volatile config timeout
    SolosCommand_SetVolatileConfigTimeout    = 0x34,
    // set multi input configs
    SolosCommand_SetMultiInputConfigs        = 0x35,
    /// reset to factory status
    SolosCommand_FactoryReset                = 0x40,
    /// Set 24/7 monitor
    SolosCommand_SetAllDayMonitor            = 0x50,
    /// Get 24/7 monitor
    SolosCommand_GetAllDayMonitor            = 0x51,
    /// Set reporting for all day monitor
    SolosCommand_SetAllDayMonitorReporting   = 0x52,
    /// Get reporting for all day monitor
    SolosCommand_GetAllDayMonitorReporting   = 0x53,
    /// Set all day posture monitor config
    SolosCommand_SetAllDayPostureMonitorConfig  = 0x54,
    /// Get all day posture monitor config
    SolosCommand_GetAllDayPostureMonitorConfig  = 0x55,
    /// Download all day step count report
    SolosCommand_DownloadAllDayStepCountReport  = 0x56,
    /// Delete all day step count report
    SolosCommand_DeleteAllDayStepCountReport    = 0x57,
    /// Download all day posture monitor  report
    SolosCommand_DownloadAllDayPostureMonitorReport  = 0x58,
    /// Delete all day posture monitor  report
    SolosCommand_DeleteAllDayPostureMonitorReport    = 0x59,
    /// Download all day posture monitor  report 2
    SolosCommand_DownloadAllDayPostureMonitorReport2  = 0x5a,
    
};


/**
 @enum SolosReportType
 */
typedef NS_ENUM(uint8_t, SolosReportType) {
    SolosReportType_GAM                       = 0x10,
    SolosReportType_StepCount                 = 0x11,
    SolosReportType_Gesture                   = 0x12,
    SolosReportType_Motion                    = 0x13,
    SolosReportType_VadChange                 = 0x14,
};

/**
 @enum SolosAllDayReportType
 */
typedef NS_ENUM(uint8_t, SolosAllDayReportType) {
    SolosAllDayReportType_StepCount           = 0x20,
    SolosAllDayReportType_Posture             = 0x21,
    SolosAllDayReportType_Posture2            = 0x22,
};

/**
 @enum SolosAvInfoReportType
 */
typedef NS_ENUM(uint8_t, SolosAvInfoReportType) {
    SolosAvInfoReportType_Media               = 0x25
};

/**
 @enum SolosUartReportType
 */
typedef NS_ENUM(uint8_t, SolosUartReportType) {
    SolosUartReportType_DataRx                = 0x30
};

/**
 @enum SolosDebugEventType
 */
typedef NS_ENUM(uint8_t, SolosDebugEventType) {
    SolosDebugEventType_AmbientNoise          = 0x40
};

/**
 @enum SolosAncsReportType
 */
typedef NS_ENUM(uint8_t, SolosAncsReportType) {
    SolosAncsReportType_Notification          = 0x50
};

/**
 @enum SolosParamCategory
 */
typedef NS_ENUM(uint8_t, SolosParamCategory) {
    SolosParamCategory_Whisper              = 0x00,
    SolosParamCategory_SensorsCalibration   = 0x01,
    SolosParamCategory_System               = 0x02,
    SolosParamCategory_Sensors              = 0x03,
    SolosParamCategory_InputConfiguration   = 0x04,
    SolosParamCategory_Factory              = 0x05,
    SolosParamCategory_AllDayMonitor        = 0x06,
    SolosparamCategory_WhisperDownlinkRT    = 0x10,
    SolosparamCategory_WhisperDownlinkRT2   = 0x11,
    SolosParamCategory_Unknown              = 0xff,
};

/**
 @enum SolosParamSensor
 */
typedef NS_ENUM(uint8_t, SolosParamSensor) {
    SolosParamSensor_Enable                         = 0x00,
    SolosParamSensor_ProximityThreshold             = 0x01,
    SolosParamSensor_TapSensitivity                 = 0x02,
    SolosParamSensor_DoubleTapDuration              = 0x03,
    SolosParamSensor_StepCountThreshold             = 0x04,
    SolosParamSensor_FallThreshold                  = 0x05,
    SolosParamSensor_SignificantMotionThreshold     = 0x06,
    SolosParamSensor_AmbientNoiseLevel5_8           = 0x07
};

/**
 @enum SolosParamSystem
 */
typedef NS_ENUM(uint8_t, SolosParamSystem) {
    SolosParamSystem_AutoPowerOffTimeout            = 0x00,
    SolosParamSystem_AutoPowerOffEnabled            = 0x01,
    SolosParamSystem_LanguageSelection              = 0x02,
    SolosParamSystem_OnHeadVolume                   = 0x03,
    SolosParamSystem_OffHeadVolume                  = 0x04,
    SolosParamSystem_SystemConfig                   = 0x05,
    SolosParamSystem_LostLinkDuration               = 0x06,
    SolosParamSystem_LostLinkAlertVolume            = 0x07,
    SolosParamSystem_AllDayPostureAlertVolume       = 0x08,
    SolosParamSystem_AmbientNoiseLevel1_4           = 0x09
};

/**
 @enum SolosParamSystemConfigOptions
 */
typedef NS_ENUM(uint8_t, SolosParamSystemConfigOptions) {
    SolosParamSystemConfigOptions_UnplugChargerautoPowerOn     = 0x0001
};

/**
 @enum SolosParamAllDayMonitor
 */
typedef NS_ENUM(uint8_t, SolosParamAllDayMonitor) {
    SolosParamAllDayMonitor_SaveInterval            = 0x01
};

/**
 @enum SolosParamWhisperDownlinkRT
 */
typedef NS_ENUM(uint8_t, SolosParamWhisperDownlinkRT) {
    SolosParamWhisperDownlinkRT_OutGain             = 0x02,
    SolosParamWhisperDownlinkRT_OutFlag             = 0x03,
    SolosParamWhisperDownlinkRT_OutFlag2            = 0x0D,
    SolosParamWhisperDownlinkRT_EQBand1Gain         = 0x0E,
    SolosParamWhisperDownlinkRT_EQBand2Gain         = 0x0F,
    SolosParamWhisperDownlinkRT_EQBand3Gain         = 0x10,
    SolosParamWhisperDownlinkRT_EQBand4Gain         = 0x11,
    SolosParamWhisperDownlinkRT_EQBand5Gain         = 0x12,
    SolosParamWhisperDownlinkRT_EQBand6Gain         = 0x13,
    SolosParamWhisperDownlinkRT_EQBand7Gain         = 0x14,
    SolosParamWhisperDownlinkRT_EQBand8Gain         = 0x15,
    SolosParamWhisperDownlinkRT_EQBand9Gain         = 0x16,
    SolosParamWhisperDownlinkRT_EQBand10Gain        = 0x17,
};

/**
 @enum SolosParamWhisperDownlinkRT2
 */
typedef NS_ENUM(uint8_t, SolosParamWhisperDownlinkRT2) {
    SolosParamWhisperDownlinkRT2_EQBand1Gain         = 0x00,
    SolosParamWhisperDownlinkRT2_EQBand2Gain         = 0x01,
    SolosParamWhisperDownlinkRT2_EQBand3Gain         = 0x02,
    SolosParamWhisperDownlinkRT2_EQBand4Gain         = 0x03,
    SolosParamWhisperDownlinkRT2_EQBand5Gain         = 0x04,
    SolosParamWhisperDownlinkRT2_EQBand6Gain         = 0x05,
    SolosParamWhisperDownlinkRT2_EQBand7Gain         = 0x06,
    SolosParamWhisperDownlinkRT2_EQBand8Gain         = 0x07,
    SolosParamWhisperDownlinkRT2_EQBand9Gain         = 0x08,
    SolosParamWhisperDownlinkRT2_EQBand10Gain        = 0x09,
    SolosParamWhisperDownlinkRT2_EQMasterGain        = 0x0A,
    SolosParamWhisperDownlinkRT2_AGCEnable           = 0x0B,
    SolosParamWhisperDownlinkRT2_OutFlag             = 0x0C,
    SolosParamWhisperDownlinkRT2_AGCPowerThres       = 0x0D,
    SolosParamWhisperDownlinkRT2_OutputGain          = 0x0E,
    
};

/**
 @enum SolosAvEvents
 */
typedef NS_ENUM(uint8_t, SolosAvEvents) {
    SolosAvEvents_MediaTitle                = 0x01,
    SolosAvEvents_MediaArtist               = 0x02,
    SolosAvEvents_TotalPlayTime             = 0x04,
    SolosAvEvents_CurrentPlayTime           = 0x08,
    SolosAvEvents_PlayStatus                = 0x80
};

@interface SolosInputConfig : NSObject
@property (nonatomic, assign) uint8_t actionId;
@property (nonatomic, assign) uint8_t inputHi;
@property (nonatomic, assign) uint8_t inputLo;

- (id) initWithActionId: (uint8_t) actionId inputHi: (uint8_t) inputHi inputLo: (uint8_t) inputLo;
@end


@protocol SolosGaiaInterface <NSObject>

- (void) readFWVersion;
- (void) resetSensors;
- (void) readProximity;
- (void) read9Axis:(BOOL)accelerometer gyro:(BOOL)gyro magnetometer:(BOOL)magnetometer ;
- (void) readTemperature:(SolosParamTemperatureSensorType)sensorType;
- (void) getEnabledReport;
- (void) enableReport:(BOOL)accelerometer gyro:(BOOL)gyro magnetometer:(BOOL)magnetometer touch:(BOOL)touch proximity:(BOOL)proximity singleTap:(BOOL)singleTap doubleTap:(BOOL)doubleTap button:(BOOL)button stepCount:(BOOL)stepCount fall:(BOOL)fall activity:(BOOL)activity significantMotion:(BOOL)significantMotion orientation:(BOOL)orientation vad:(BOOL)vad vadChangeEvent:(BOOL)vadChangeDetection;
- (void) setReportInterval:(SolosIntervalType)intervalType ms:(int)ms;
- (void) getReportInterval:(SolosIntervalType)intervalType;
// sensor config
- (void) enableSensors:(SolosConfigStorageType)type accelerometer:(BOOL)accelerometer gyro:(BOOL)gyro magnetometer:(BOOL)magnetometer touch:(BOOL)touch proximity:(BOOL)proximity singleTap:(BOOL)singleTap doubleTap:(BOOL)doubleTap button:(BOOL)button stepCount:(BOOL)stepCount fall:(BOOL)fall activity:(BOOL)activity significantMotion:(BOOL)significantMotion orientationDetection:(BOOL)orientationDetection vad:(BOOL)vad;
- (void) getEnabledSensor:(SolosConfigStorageType)type;
- (void) setProximity:(SolosConfigStorageType)type threshold:(int)threshold;
- (void) getProximityThreshold:(SolosConfigStorageType)type;
- (void) setTap:(SolosConfigStorageType)type sensitivity:(int)sensitivity;
- (void) getTapSensitivity:(SolosConfigStorageType)type;
- (void) setDoubleTap:(SolosConfigStorageType)type duration:(int)duration;
- (void) getDoubleTapDuration:(SolosConfigStorageType)type;
- (void) setStepCount:(SolosConfigStorageType)type threshold:(int)threshold;
- (void) getStepCountThreshold:(SolosConfigStorageType)type;
- (void) setFallDetection:(SolosConfigStorageType)type threshold:(int)threshold;
- (void) getFallDetectionThreshold:(SolosConfigStorageType)type;
- (void) setSignificantMotion:(SolosConfigStorageType)type threshold:(int)threshold;
- (void) getSignificantMotionThreshold:(SolosConfigStorageType)type;
// system config
- (void) setAutoPowerOff:(SolosConfigStorageType) type timeout:(int)timeoutMins;
- (void) getAutoPowerOffTimeout:(SolosConfigStorageType) type;
- (void) setAutoPowerOff:(SolosConfigStorageType) type enabled:(BOOL)enabled;
- (void) getAutoPowerOffEnabled:(SolosConfigStorageType) type;
- (void) setLanguageConfig:(SolosConfigStorageType) type languageCode:(SolosLanguageCode)languageCode;
- (void) getLanguageConfig:(SolosConfigStorageType) type;
- (void) setOnHead:(SolosConfigStorageType) type volume:(int)volume;
- (void) getOnHeadVolume:(SolosConfigStorageType) type;
- (void) setOffHead:(SolosConfigStorageType) type volume:(int)volume;
- (void) getOffHeadVolume:(SolosConfigStorageType) type;
- (void) setLostLink:(SolosConfigStorageType) type volume:(int)volume;
- (void) getLostLinkVolume:(SolosConfigStorageType) type;
- (void) setAllDayPostureAlert:(SolosConfigStorageType) type volume:(int)volume;
- (void) getAllDayPostureAlertVolume:(SolosConfigStorageType) type;
- (void) setSystemConfig:(SolosConfigStorageType) type unplugChargerAutoPowerOn:(BOOL)unplugChargerAutoPowerOn multipoint:(BOOL)multipoint multipointBothDevicesLostLinkAlert:(BOOL) multipointBothDevicesLostLinkAlert vaToneSoundOn:(BOOL)vaToneSoundOn harDetectionOn:(BOOL)harDetectionOn ambientNoiseDetectionOn:(BOOL)ambientNoiseDetectionOn ancsNotificationOn:(BOOL)ancsNotificationOn smartPowerOffOn:(BOOL)smartPowerOffOn useTempleLED:(BOOL)useTempleLED;
- (void) getSystemConfig:(SolosConfigStorageType) type;
- (void) setLostLink:(SolosConfigStorageType) type duration:(int) durInSec;
- (void) getLostLinkDuration: (SolosConfigStorageType) type;
// input config
- (void) setInputConfigAction:(SolosConfigStorageType) type action:(SolosInputConfigAction)action withInputLo:(SolosInputConfigType)inputLo andInputHi:(SolosInputConfigType)inputHi;
- (void) getInputConfigAction:(SolosConfigStorageType) type action:(SolosInputConfigAction)action;
- (void) setVolatileInputConfigTimeout:(int)timeoutInSec;
- (void) setMultiInputConfigs:(SolosConfigStorageType) type inputConfigs:(NSArray <SolosInputConfig *>*) inputConfigs;
// factory
- (void) setProductSerialNum:(NSData *)serialNum;
- (void) getProductSerialNum;
- (void) setProductModelNum:(NSData *)modelNum;
- (void) getProductModelNum;
- (void) setFactoryOptions:(SolosConfigStorageType) type testMode:(BOOL)testMode;
- (void) getFactoryOptions:(SolosConfigStorageType)storageType;
- (void) setCameraBtName:(NSData *)btName;
- (void) getCameraBtName;
// whisper
- (void) setWhisperData:(uint16_t)inGain outGain:(uint16_t)outGain outFlag:(uint16_t)outFlag channelSelect:(uint16_t)channelSelect bfMainGain:(uint32_t)bfMainGain bfRefGain:(uint32_t)bfRefGain vad:(uint32_t)vad scvad:(uint32_t)scvad hangOver:(uint16_t)hangOver scHangOver:(uint16_t)scHangOver aecRefGain:(uint16_t)aecRefGain ;
- (void) getWhisperData;
// whisper real time
- (void) setWhisperDataRtOutGain:(uint32_t)outGain;
- (void) setWhisperDataRtOutFlag:(uint32_t)outFlag;
- (void) getWhisperDataRtOutGain;
- (void) getWhisperDataRtOutFlag;
// whisper downlink
- (void) setWhisperDownlink:(uint16_t)band1Gain band2Gain:(uint16_t)band2Gain band3Gain:(uint16_t)band3Gain band4Gain:(uint16_t)band4Gain band5Gain:(uint16_t)band5Gain band6Gain:(uint16_t)band6Gain band7Gain:(uint16_t)band7Gain band8Gain:(uint16_t)band8Gain band9Gain:(uint16_t)band9Gain band10Gain:(uint16_t)band10Gain masterGain:(uint16_t)masterGain enableAGC:(uint16_t)enableAGC powerThresAGC:(uint16_t)powerThresAGC outFlag:(uint16_t)outFlag dlGain:(uint16_t)dlGain;
- (void) getWhisperDownlink;
// whisper downlink RT
- (void) setWhisperDownlinkRtAGC:(uint16_t)enableAGC;
- (void) setWhisperDownlinkRtOutFlag:(uint16_t)outFlag;
- (void) setWhisperDownlinkRt:(uint8_t)band gain:(uint16_t)gain;
// whisper eq
- (void) setWhisperEq:(uint16_t)outFlag band1Gain:(uint16_t)band1Gain band2Gain:(uint16_t)band2Gain band3Gain:(uint16_t)band3Gain band4Gain:(uint16_t)band4Gain band5Gain:(uint16_t)band5Gain band6Gain:(uint16_t)band6Gain band7Gain:(uint16_t)band7Gain band8Gain:(uint16_t)band8Gain band9Gain:(uint16_t)band9Gain band10Gain:(uint16_t)band10Gain;
- (void) getWhisperEq;
// whisper eq rt
- (void) setWhisperEqRtOutFlag:(uint16_t)outFlag;
- (void) setWhisperEqRt:(uint16_t)band gain:(uint16_t)gain;
// whisper hearable
- (void) setWhisperHearableData:(uint16_t)inGain outGain:(uint16_t)outGain outFlag:(uint16_t)outFlag channelSelect:(uint16_t)channelSelect bfMainGain:(uint32_t)bfMainGain bfRefGain:(uint32_t)bfRefGain nearEndThreshold:(uint16_t)nearEndThreshold eqBand1Gain:(uint16_t)eqBand1Gain eqBand2Gain:(uint16_t)eqBand2Gain eqBand3Gain:(uint16_t)eqBand3Gain bfOutGain:(uint16_t)bfOutGain;
- (void) getWhisperHearableData;
// whisper wind filter
- (void) setWhisperFeature:(uint16_t)feature noiseThreshold:(uint16_t)noiseThreshold agcNoiseLevelUpAlpha:(uint16_t)agcNoiseLevelUpAlpha agcNoiseLevelDnAlpha:(uint16_t)agcNoiseLevelDnAlpha vadOnValueThreshold:(uint16_t)vadOnValueThreshold vadOnHoldTimeMs:(uint16_t)vadOnHoldTimeMs vadOffHoldTimeMs:(uint16_t)vadOffHoldTimeMs vadMicOffTimeoutMs:(uint16_t)vadMicOffTimeoutMs reserved6:(uint16_t)reserved6 reserved7:(uint16_t)reserved7 reserved8:(uint16_t)reserved8 reserved9:(uint16_t)reserved9 reserved10:(uint16_t)reserved10 reserved11:(uint16_t)reserved11 reserved12:(uint16_t)reserved12;
- (void) getWhisperFeature;
// magnet calibration
- (void) setMagnetCalibrationData:(uint16_t)maxX maxY:(uint16_t)maxY maxZ:(uint16_t)maxZ minX:(uint16_t)minX minY:(uint16_t)minY minZ:(uint16_t)minZ;
- (void) getMagnetCalibrationData;
// gyro/accel
- (void) setGyroAccelMagnetCalibrationData:(uint16_t)gyroShiftX gyroShiftY:(uint16_t)gyroShiftY gyroShiftZ:(uint16_t)gyroShiftZ
                            accelShiftX:(uint16_t)accelShiftX accelShiftY:(uint16_t)accelShiftY accelShiftZ:(uint16_t)accelShiftZ
                              magnetShiftX:(uint16_t)magnetShiftX magnetShiftY:(uint16_t)magnetShiftY magnetShiftZ:(uint16_t)magnetShiftZ
                              magnetScaleX:(uint16_t)magnetScaleX magnetScaleY:(uint16_t)magnetScaleY magnetScaleZ:(uint16_t)magnetScaleZ;
- (void) getGyroAccelMagnetCalibrationData;
// factory reset
- (void) factoryReset;
// i2c
- (void) writeI2C:(uint8_t)deviceAddress registerAddress:(uint8_t)registerAddress data:(NSData *)data;
- (void) readI2C:(uint8_t)deviceAddress registerAddress:(uint8_t)registerAddress dataSize:(uint8_t)dataSize;
// language
- (void) setLanguage:(SolosLanguageCode) code;
- (void) getLanguage;
// uart
- (void) enableUart:(BOOL)enable;
- (void) writeUart:(uint8_t)cmd data:(NSData *)data;
// debug
- (void) setDebugEvents:(BOOL)ambientNoiseDetection;
- (void) getDebugEvents;
// LED
- (void) setLED:(BOOL)redOn blue:(BOOL)blueOn;
// reboot
- (void) reboot:(uint8_t)mode;
// all day monitor settings
- (void) setAllDayMonitorSaveInterval:(int)min;
- (void) getAllDayMonitorSaveInterval;
// RTC
- (void) setRTC:(uint32_t)secSince2020;
// 24/7 monitor
- (void) setAllDayMonitor:(BOOL)stepCount posture:(BOOL)posture;
- (void) getAllDayMonitor;
// all day monitor reporting
- (void) setAllDayMonitorReporting:(BOOL)stepCount posture3030:(BOOL)posture3030 posture0060:(BOOL)posture0060 since:(uint32_t)secSince2020;
- (void) getAllDayMonitorReporting;
// all day posture monitor config
- (void) setAllDayPostureMonitorConfig:(int8_t)refPitchAngle maxPitchAngle:(uint8_t)maxPitchAngle timeBeyondMaxPitchAngleToAlert:(uint16_t)timeInSec alertMethod:(SolosParamAllDayPostureAlertMethod)alertMethod;
- (void) getAllDayPostureMonitorConfig;
// all day step count report
- (void) downloadAllDayStepCountReport:(uint32_t)secSince2020 dur:(uint16_t)durInMin;
- (void) deleteAllDayStepCountReport:(uint32_t)secSince2020 dur:(uint16_t)durInMin;
// all day posture monitor report
- (void) downloadAllDayPostureMonitorReport:(uint32_t)secSince2020 dur:(uint16_t)durInMin;
- (void) downloadAllDayPostureMonitorReport2:(uint32_t)secSince2020 dur:(uint16_t)durInMin;
- (void) deleteAllDayPostureMonitorReport:(uint32_t)secSince2020 dur:(uint16_t)durInMin;
// ambient noise
- (void) getAmbientNoise1_4Mapping:(SolosConfigStorageType) type;
- (void) getAmbientNoise5_8Mapping:(SolosConfigStorageType) type;
- (void) setAmbientNoise1_4Mapping:(SolosConfigStorageType) type noiseLv1:(uint8_t) speakerVolLv1 noiseLv2:(uint8_t) speakerVolLv2 noiseLv3:(uint8_t) speakerVolLv3 noiseLv4:(uint8_t) speakerVolLv4;
- (void) setAmbientNoise5_8Mapping:(SolosConfigStorageType) type noiseLv5:(uint8_t) speakerVolLv5 noiseLv6:(uint8_t) speakerVolLv6 noiseLv7:(uint8_t) speakerVolLv7 noiseLv8:(uint8_t) speakerVolLv8;
// av media event
- (void) setAvEvents:(BOOL)title artist: (BOOL)artist totalPlayTime: (BOOL)totalPlayTime currentPlayTime:(BOOL)currentPlayTime playStatus: (BOOL)playStatus;
- (void) getAvEvents;
- (void) getAvInfo;
// ASR
- (void) setASRMode:(uint8_t)mode;
// VA stream
- (void) setVaStream:(BOOL)on;
@end

@interface SolosGaia : CSRGaia <SolosGaiaInterface>

@end

NS_ASSUME_NONNULL_END
