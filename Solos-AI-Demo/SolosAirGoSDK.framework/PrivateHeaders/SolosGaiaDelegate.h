//
//  SolosGaiaDelegate.h
//  GaiaControl
//
//  Created by Sam Yu on 12/5/2020.
//  Copyright © 2020 Solos Technology Limited. All rights reserved.
//

#ifndef SolosGaiaDelegate_h
#define SolosGaiaDelegate_h

//#import "GaiaLibrary.h"
/**
 @enum SolosGaiaResponseStatus
 */
typedef NS_ENUM(uint16_t, SolosGaiaResponseStatus) {
    SolosGaiaStatus_Success                      = GaiaStatus_Success,
    SolosGaiaStatus_FailedNotSupported           = GaiaStatus_FailedNotSupported,
    SolosGaiaStatus_FailedNotAuthenticated       = GaiaStatus_FailedNotAuthenticated,
    SolosGaiaStatus_FailedInsufficientResources  = GaiaStatus_FailedInsufficientResources,
    SolosGaiaStatus_Authenticating               = GaiaStatus_Authenticating,
    SolosGaiaStatus_InvalidParameter             = GaiaStatus_InvalidParameter,
    SolosGaiaStatus_IncorrectState               = GaiaStatus_IncorrectState,
    SolosGaiaStatus_InProgress                   = GaiaStatus_InProgress,
    SolosGaiaStatus_NoStatusAvailable            = GaiaStatus_NoStatusAvailable,
    SolosGaiaStatus_InvalidPayloadLength         = GaiaStatus_InvalidPayloadLength,
    SolosGaiaStatus_InvalidEQBank                = GaiaStatus_InvalidEQBank,
    SolosGaiaStatus_InvalidStorage               = 0x101,
    
};

/**
 @enum SolosIntervalType
 */
typedef NS_ENUM(uint8_t, SolosIntervalType) {
    SolosIntervalType_GAM                 = 0x1,
};


/**
 @enum SolosConfigStorageType
 */
typedef NS_ENUM(uint8_t, SolosConfigStorageType) {
    SolosConfigStorageType_Instant          = 0x00,
    SolosConfigStorageType_Configurable     = 0x01,
    SolosConfigStorageType_Factory          = 0x02,
};

/**
 @enum SolosLanguageCode
 */
typedef NS_ENUM(uint8_t, SolosLanguageCode) {
    SolosLanguageCode_English           = 0,
    SolosLanguageCode_Mandarin          = 1,
    SolosLanguageCode_Cantonese         = 2
};

/**
 @enum SolosInputConfigType
 */
typedef NS_ENUM(uint8_t, SolosInputConfigType) {
    SolosInputConfigType_None = 0,
    SolosInputConfigType_SlideForward,
    SolosInputConfigType_SlideBackward,
    SolosInputConfigType_SingleTap,
    SolosInputConfigType_DoubleTap,
    SolosInputConfigType_ShortPressMFB,
    SolosInputConfigType_ShortPressTwiceMFB,
    SolosInputConfigType_LongPress1SecMFB,
    SolosInputConfigType_LongPress2SecMFB,
    SolosInputConfigType_LongPress3SecMFB,
    SolosInputConfigType_LongPress5SecMFB,
    SolosInputConfigType_LongPress8SecMFB,
    SolosInputConfigType_LongPressRightTemple,
    SolosInputConfigType_LongPressVirtualButton,
    SolosInputConfigType_SuperLongPressVirtualButton,
    SolosInputConfigType_DoublePressVirtualButton,
    SolosInputConfigType_LongPressSlidingArea
};

/**
 @enum SolosInputConfigAction
 */
typedef NS_ENUM(uint8_t, SolosInputConfigAction) {
    SolosInputConfigAction_PowerOn = 0,
    SolosInputConfigAction_PowerOnPairing,
    SolosInputConfigAction_PowerOnPairingEraseList,
    SolosInputConfigAction_PowerOff,
    SolosInputConfigAction_PlayMusic,
    SolosInputConfigAction_PauseMusic,
    SolosInputConfigAction_PrevTrack,
    SolosInputConfigAction_NextTrack,
    SolosInputConfigAction_OpenVoiceAssistant,
    SolosInputConfigAction_CloseVoiceAssistant,
    SolosInputConfigAction_AnswerCall,
    SolosInputConfigAction_RejectCall,
    SolosInputConfigAction_Answer2ndCall,
    SolosInputConfigAction_Reject2ndCall,
    SolosInputConfigAction_VolumeUp,
    SolosInputConfigAction_VolumeDn,
    SolosInputConfigAction_EndCall
};

/**
 @enum SolosFactoryType
 */
typedef NS_ENUM(uint8_t, SolosFactoryType) {
    SolosFactoryType_ProductSerialNum = 0,
    SolosFactoryType_ProductModelNum,
    SolosFactoryType_Options
};

/**
 @enum SolosDSPKeyID
 */
typedef NS_ENUM(uint32_t, SolosDSPKeyID) {
    SolosDSPKeyID_Unknown = 0,
    SolosDSPKeyID_Whisper = 0x600082,
    SolosDSPKeyID_WhisperDownlink = 0x600084,
    SolosDSPKeyID_WhisperEQ = 0x600086,
    SolosDSPKeyID_WhisperFestureFilter = 0x600088,
    SolosDSPKeyID_WhisperHearable = 0x600402,
    SolosDSPKeyID_Magnet_Calibration = 0x6000c0,
    SolosDSPKeyID_GyroAccelMagnet_Calibration = 0x6000c2,
    SolosDSPKeyID_SystemPsKey_CameraBtName = 0x600096
};

/**
 @enum SolosMagetCalibration
 */
typedef NS_ENUM(uint8_t, SolosMagnetCalibration) {
    SolosMagnetCalibration_MaxX=0,
    SolosMagnetCalibration_MaxY,
    SolosMagnetCalibration_MaxZ,
    SolosMagnetCalibration_MinX,
    SolosMagnetCalibration_MinY,
    SolosMagnetCalibration_MinZ,
};

/**
 @enum SolosGyroAccelMangetCalibration
 */
typedef NS_ENUM(uint8_t, SolosGyroAccelMagnetCalibration) {
    SolosGyroAccelMagnetCalibration_GyroShiftX = 0,
    SolosGyroAccelMagnetCalibration_GyroShiftY,
    SolosGyroAccelMagnetCalibration_GyroShiftZ,
    SolosGyroAccelMagnetCalibration_AccelShiftX,
    SolosGyroAccelMagnetCalibration_AccelShiftY,
    SolosGyroAccelMagnetCalibration_AccelShiftZ,
    SolosGyroAccelMagnetCalibration_MagnetShiftX,
    SolosGyroAccelMagnetCalibration_MagnetShiftY,
    SolosGyroAccelMagnetCalibration_MagnetShiftZ,
    SolosGyroAccelMagnetCalibration_MagnetScaleX,
    SolosGyroAccelMagnetCalibration_MagnetScaleY,
    SolosGyroAccelMagnetCalibration_MagnetScaleZ
};

/**
 @enum SolosParamAllDayPostureAlertMethod
 */
typedef NS_ENUM(uint8_t, SolosParamAllDayPostureAlertMethod) {
    SolosParamAllDayPostureAlertMethod_NoAlert = 0,
    SolosParamAllDayPostureAlertMethod_Beep = 1,
    SolosParamAllDayPostureAlertMethod_VoicePrompt = 2
};

/**
 @enum SolosParamEQFilterType
 */
typedef NS_ENUM(int, SolosParamEQFilterType) {
    SolosParamEQFilterType_Bypass = 0,
    SolosParamEQFilterType_FirstOrderLowPass,
    SolosParamEQFilterType_FirstOrderHighPass,
    SolosParamEQFilterType_FirstOrderAllPass,
    SolosParamEQFilterType_FirstOrderLowShelf,
    SolosParamEQFilterType_FirstOrderHighShelf,
    SolosParamEQFilterType_FirstOrderTilt,
    SolosParamEQFilterType_SecondOrderLowPass,
    SolosParamEQFilterType_SecondOrderHighPass,
    SolosParamEQFilterType_SecondOrderAllPass,
    SolosParamEQFilterType_SecondOrderLowShelf,
    SolosParamEQFilterType_SecondOrderHighShelf,
    SolosParamEQFilterType_SecondOrderTilt,
    SolosParamEQFilterType_ParametricEQualizer,
};

/**
 @enum SolosParamTemperature
 */
typedef NS_ENUM(int, SolosParamTemperatureSensorType) {
    SolosParamTemperatureSensorType_PMU = 0,
    SolosParamTemperatureSensorType_GAM,
    SolosParamTemperatureSensorType_MLX,
    SolosParamTemperatureSensorType_MLXAmbient,
    SolosParamTemperatureSensorType_MLXObject
};

/**
 @enum SolosAvInfoPlayStatus
 */
typedef NS_ENUM(int, SolosAvInfoPlayStatus) {
    SolosAvInfoPlayStatus_Pause = 0,
    SolosAvInfoPlayStatus_Play
};

typedef NS_ENUM(uint8_t, SolosGestureMode) {
    SolosGestureMode_Idle       = 0,
    SolosGestureMode_Music      = 1,
    SolosGestureMode_Call       = 2,
    SolosGestureMode_Unknown    = 100
};

typedef NS_ENUM(uint8_t, SolosVadEvent) {
    SolosVadEvent_Low2High      = 0,
    SolosVadEvent_High2Low      = 1,
    SolosVadEvent_Timeout       = 2
};

@protocol SolosGaiaDelegate <CSRGaiaDelegate>
@optional
// control
- (void) didReadFWVersion:(SolosGaiaResponseStatus)status majorVer:(int)majorVer minorVer:(int)minorVer boardVer:(int)boardVer buildVer:(int)buildVer;
- (void) didWriteI2C:(SolosGaiaResponseStatus)status deviceAddr:(uint8_t)deviceAddr registerAddr:(uint8_t)registerAddr;
- (void) didReadI2C:(SolosGaiaResponseStatus)status deviceAddr:(uint8_t)deviceAddr registerAddr:(uint8_t)registerAddr data:(NSData*)data;
- (void) didSetLanguage:(SolosGaiaResponseStatus)status;
- (void) didGetLanguage:(SolosGaiaResponseStatus)status languageCode:(SolosLanguageCode)code;
- (void) didResetSensors:(SolosGaiaResponseStatus)status resetProximityErr:(BOOL)resetProxmityErr reset6AxisErr:(BOOL)reset6AxisErr resetMagnetometerErr:(BOOL)resetMagnetometerErr;
- (void) didReadProximity:(SolosGaiaResponseStatus)status value:(int)value;
- (void) didRead9Axis:(SolosGaiaResponseStatus)status accelAvail:(BOOL) accelAval accelX:(int)accelX accelY:(int)accelY accelZ:(int)accelZ gyroAvail:(BOOL)gyroAvail gyroX:(int)gyroX gyroY:(int)gyroY gyroZ:(int)gyroZ magAvail:(BOOL)magAvail magX:(int)magX magY:(int)magY magZ:(int)magZ;
- (void) didReadTemperature:(SolosGaiaResponseStatus)status sensorType:(SolosParamTemperatureSensorType)sensorType temperature:(double)temperature;
- (void) didSetASRMode:(SolosGaiaResponseStatus)status mode:(uint8_t)mode;
- (void) didEnableReport:(SolosGaiaResponseStatus)status;
- (void) didGetEnabledReport:(SolosGaiaResponseStatus)status acceleration:(BOOL)acceleration gyro:(BOOL)gyro magnetometer:(BOOL)magnetometer proximity:(BOOL)proximity touch:(BOOL)touch singleTap:(BOOL)singleTap doubleTap:(BOOL)doubleTap button:(BOOL)button stepCount:(BOOL)stepCount fall:(BOOL)fall activity:(BOOL)activity significantMotion:(BOOL)significantMotion orientation:(BOOL)orientation vad:(BOOL)vad;
- (void) didSetReportInterval:(SolosGaiaResponseStatus)status;
- (void) didGetReportInterval:(SolosGaiaResponseStatus)status intervalType:(SolosIntervalType)intervalType ms:(int)ms;
- (void) didReadConfig:(SolosGaiaResponseStatus)status data:(NSData *)data;
- (void) didFactoryReset:(SolosGaiaResponseStatus)status;
// uart
- (void) didEnableUart:(SolosGaiaResponseStatus)status enable:(BOOL)enable;
- (void) didWriteUart:(SolosGaiaResponseStatus)status;
// debug
- (void) didSetDebugEvents:(SolosGaiaResponseStatus)status;
- (void) didGetDebugEvents:(SolosGaiaResponseStatus)status ambientNoiseDetectionOn:(BOOL)ambientNoiseDetectionOn;
// av events
- (void) didSetAvEvents:(SolosGaiaResponseStatus)status title:(BOOL)title artist: (BOOL)artist totalPlayTime: (BOOL)totalPlayTime currentPlayTime:(BOOL)currentPlayTime playStatus: (BOOL)playStatus;
- (void) didGetAvEvents:(SolosGaiaResponseStatus)status title:(BOOL)title artist: (BOOL)artist totalPlayTime: (BOOL)totalPlayTime currentPlayTime:(BOOL)currentPlayTime playStatus: (BOOL)playStatus;
- (void) didGetAvInfo:(SolosGaiaResponseStatus)status;
// VA stream
- (void) didSetVaStream:(SolosGaiaResponseStatus)status on:(BOOL)on;
// LED
- (void) didSetLED:(SolosGaiaResponseStatus)status;
// reboot
- (void) didReboot:(SolosGaiaResponseStatus)status;
// all day settings
- (void) didSetAllDayMonitorSaveInterval:(SolosGaiaResponseStatus)status;
- (void) didGetAllDayMonitor:(SolosGaiaResponseStatus)status saveInterval:(int)min;
// RTC
- (void) didSetRTC:(SolosGaiaResponseStatus)status;
// all day monitor
- (void) didSetAllDayMonitor:(SolosGaiaResponseStatus)status;
- (void) didGetAllDayMonitor:(SolosGaiaResponseStatus)status stepCount:(BOOL)stepCount posture:(BOOL)posture;
- (void) didSetAllDayMonitorReporting:(SolosGaiaResponseStatus)status;
- (void) didGetAllDayMonitorReporting:(SolosGaiaResponseStatus)status stepCount:(BOOL)stepCount posture3030:(BOOL)posture3030 posture0060:(BOOL)posture0060 since:(uint32_t)secSince2020;
- (void) didSetAllDayPostureMonitorConfig:(SolosGaiaResponseStatus)status;
- (void) didGetAllDayPostureMonitorConfig:(SolosGaiaResponseStatus)status refPitchAngle:(int8_t)refPitchAngle maxPitchAngle:(uint8_t)maxPitchAngle timeBeyondMaxPitchAngleToAlert:(uint16_t)timeInSec alertMethod:(SolosParamAllDayPostureAlertMethod)alertMethod;
- (void) didDownloadAllDayStepCountReport:(SolosGaiaResponseStatus)status since:(uint32_t)secSince2020 dur:(uint16_t)durInMin stepCount:(uint16_t)stepCount;
- (void) didDeleteAllDayStepCountReport:(SolosGaiaResponseStatus)status since:(uint32_t)secSince2020 dur:(uint16_t)durInMin;
- (void) didDownloadAllDayPostureMonitorReport:(SolosGaiaResponseStatus)status since:(uint32_t)secSince2020 dur:(uint16_t)durInMin tiltUp0_5:(uint32_t)tiltUp0_5 tiltUp5_10:(uint32_t)tiltUp5_10 tiltUp10_15:(uint32_t)tiltUp10_15 tiltUp15_20:(uint32_t)tiltUp15_20 tiltUp20_25:(uint32_t)tiltUp20_25 tiltUp25_30:(uint32_t)tiltUp25_30 tiltUp30_:(uint32_t)tiltUp30_ tiltDn0_5:(uint32_t)tiltDn0_5 tiltDn5_10:(uint32_t)tiltDn5_10 tiltDn10_15:(uint32_t)tiltDn10_15 tiltDn15_20:(uint32_t)tiltDn15_20 tiltDn20_25:(uint32_t)tiltDn20_25 tiltDn25_30:(uint32_t)tiltDn25_30 tiltDn30_:(uint32_t)tiltDn30_ ;
- (void) didDownloadAllDayPostureMonitorReport:(SolosGaiaResponseStatus)status since:(uint32_t)secSince2020 dur:(uint16_t)durInMin tiltUp0_:(uint32_t)tiltUp0_ tiltDn0_5:(uint32_t)tiltDn0_5 tiltDn5_10:(uint32_t)tiltDn5_10 tiltDn10_15:(uint32_t)tiltDn10_15 tiltDn15_20:(uint32_t)tiltDn15_20 tiltDn20_25:(uint32_t)tiltDn20_25 tiltDn25_30:(uint32_t)tiltDn25_30 tiltDn30_35:(uint32_t)tiltDn30_35 tiltDn35_40:(uint32_t)tiltDn35_40 tiltDn40_45:(uint32_t)tiltDn40_45 tiltDn45_50:(uint32_t)tiltDn45_50 tiltDn50_55:(uint32_t)tiltDn50_55 tiltDn55_60:(uint32_t)tiltDn55_60 tiltDn60_:(uint32_t)tiltDn60_;
- (void) didDeleteAllDayPostureMonitorReport:(SolosGaiaResponseStatus)status since:(uint32_t)secSince2020 dur:(uint16_t)durInMin;
// reporting
- (void) onReport9Axis:(uint32_t)timestamp accelAvail:(BOOL) accelAval accelX:(int)accelX accelY:(int)accelY accelZ:(int)accelZ gyroAvail:(BOOL)gyroAvail gyroX:(int)gyroX gyroY:(int)gyroY gyroZ:(int)gyroZ magAvail:(BOOL)magAvail magX:(int)magX magY:(int)magY magZ:(int)magZ vad:(int)vad;
- (void) onReportStepCount:(uint32_t)timestamp stepCount:(int)stepCount;
- (void) onReportVadEvent:(uint32_t)timestamp event:(SolosVadEvent)event;
- (void) onReportGestureVolumeUp:(uint32_t)timestamp mode:(SolosGestureMode)mode;
- (void) onReportGestureVolumeDn:(uint32_t)timestamp mode:(SolosGestureMode)mode;
- (void) onReportGestureGlassOff:(uint32_t)timestamp mode:(SolosGestureMode)mode;
- (void) onReportGestureGlassOn:(uint32_t)timestamp mode:(SolosGestureMode)mode;
- (void) onReportGestureSingleTap:(uint32_t)timestamp mode:(SolosGestureMode)mode;
- (void) onReportGestureDoubleTap:(uint32_t)timestamp mode:(SolosGestureMode)mode;
- (void) onReportGestureSinglePressMFB:(uint32_t)timestamp mode:(SolosGestureMode)mode;
- (void) onReportGestureDoublePressMFB:(uint32_t)timestamp mode:(SolosGestureMode)mode;
- (void) onReportGestureSlidePressed:(uint32_t)timestamp mode:(SolosGestureMode)mode;
- (void) onReportGestureSlideReleased:(uint32_t)timestamp mode:(SolosGestureMode)mode;
- (void) onReportGestureVbPressed:(uint32_t)timestamp mode:(SolosGestureMode)mode;
- (void) onReportGestureVbReleased:(uint32_t)timestamp mode:(SolosGestureMode)mode;
- (void) onReportMotionFall:(uint32_t)timestamp;
- (void) onReportMotionActivity:(uint32_t)timestamp;
- (void) onReportMotionSignificantMotion:(uint32_t)timestamp;
- (void) onUartDataRx:(uint8_t)cmd data:(NSData *)data;
- (void) onAmbientNoiseDebugEvent:(BOOL)hfpPhoneCallOn; 
- (void) onAmbientNoiseDebugEvent:(uint8_t)currentNoiseLevel filteredNoiseLevel:(uint8_t)filteredNoiseLevel currentSpeakerLevel:(uint8_t)currentSpeakerLevel;
- (void) onAmbientNoiseDebugEvent:(uint8_t)noise1Vol noise2Vol:(uint8_t)noise2Vol noise3Vol:(uint8_t)noise3Vol noise4Vol:(uint8_t)noise4Vol noise5Vol:(uint8_t)noise5Vol noise6Vol:(uint8_t)noise6Vol noise7Vol:(uint8_t)noise7Vol noise8Vol:(uint8_t)noise8Vol;
- (void) onAllDayStepCount:(uint32_t)secSince2020 stepCount:(uint16_t)stepCount;
- (void) onAllDayPosture:(uint32_t)secSince2020 tiltUp0_5:(uint32_t)tiltUp0_5 tiltUp5_10:(uint32_t)tiltUp5_10 tiltUp10_15:(uint32_t)tiltUp10_15 tiltUp15_20:(uint32_t)tiltUp15_20 tiltUp20_25:(uint32_t)tiltUp20_25 tiltUp25_30:(uint32_t)tiltUp25_30 tiltUp30_:(uint32_t)tiltUp30_ tiltDn0_5:(uint32_t)tiltDn0_5 tiltDn5_10:(uint32_t)tiltDn5_10 tiltDn10_15:(uint32_t)tiltDn10_15 tiltDn15_20:(uint32_t)tiltDn15_20 tiltDn20_25:(uint32_t)tiltDn20_25 tiltDn25_30:(uint32_t)tiltDn25_30 tiltDn30_:(uint32_t)tiltDn30_ ;
- (void) onAllDayPosture:(uint32_t)secSince2020 tiltUp0_:(uint32_t)tiltUp0_  tiltDn0_5:(uint32_t)tiltDn0_5 tiltDn5_10:(uint32_t)tiltDn5_10 tiltDn10_15:(uint32_t)tiltDn10_15 tiltDn15_20:(uint32_t)tiltDn15_20 tiltDn20_25:(uint32_t)tiltDn20_25 tiltDn25_30:(uint32_t)tiltDn25_30 tiltDn30_35:(uint32_t)tiltDn30_35 tiltDn35_40:(uint32_t)tiltDn35_40 tiltDn40_45:(uint32_t)tiltDn40_45 tiltDn45_50:(uint32_t)tiltDn45_50 tiltDn50_55:(uint32_t)tiltDn50_55 tiltDn55_60:(uint32_t)tiltDn55_60 tiltDn60_:(uint32_t)tiltDn60_;
- (void) onReportAvInfoTitle:(NSData*)title;
- (void) onReportAvInfoArtist:(NSData*)artist;
- (void) onReportAvInfoTotalPlayTime:(uint32_t)ms;
- (void) onReportAvInfoCurrentPlayTime:(uint32_t)ms;
- (void) onReportAvInfoPlayStatus:(SolosAvInfoPlayStatus)status;
- (void) onReportAncsNotification:(NSString *)appId date:(NSString *)date title:(NSString*)title message:(NSString*)message;
- (void) onVaStream:(NSData *)data;
// sensor config
- (void) didEnableSensor:(SolosGaiaResponseStatus)status storageType:(SolosConfigStorageType)storageType;
- (void) didGetEnabledSensors:(SolosGaiaResponseStatus)status storageType:(SolosConfigStorageType)storageType acceleration:(BOOL)acceleration gyro:(BOOL)gyro magnetometer:(BOOL)magnetometer touch:(BOOL)touch proximity:(BOOL)proximity singleTap:(BOOL)singleTap doubleTap:(BOOL)doubleTap button:(BOOL)button stepCount:(BOOL)stepCount fall:(BOOL)fall activity:(BOOL)activity significantMotion:(BOOL)significantMotion orientationDetection:(BOOL)orientationDetection vad:(BOOL)vad;
- (void) didSetProximityThreshold:(SolosGaiaResponseStatus)status storageType:(SolosConfigStorageType)storageType;
- (void) didGet:(SolosGaiaResponseStatus)status storageType:(SolosConfigStorageType)storageType proximityThreshod:(int)proximityThreshold;
- (void) didSetTapSensitivity:(SolosGaiaResponseStatus)status storageType:(SolosConfigStorageType)storageType;
- (void) didGet:(SolosGaiaResponseStatus)status storageType:(SolosConfigStorageType)storageType tapSensitivity:(int)tapSensitivity;
- (void) didSetDoubleTapDuration:(SolosGaiaResponseStatus)status storageType:(SolosConfigStorageType)storageType;
- (void) didGet:(SolosGaiaResponseStatus)status storageType:(SolosConfigStorageType)storageType doubleTapDuration:(int)doubleTapDuration;
- (void) didSetStepCountThreshold:(SolosGaiaResponseStatus)status storageType:(SolosConfigStorageType)storageType;
- (void) didGet:(SolosGaiaResponseStatus)status storageType:(SolosConfigStorageType)storageType stepCountThreshold:(int)stepCountThreshold;
- (void) didSetFallDetectionThreshold:(SolosGaiaResponseStatus)status storageType:(SolosConfigStorageType)storageType;
- (void) didGet:(SolosGaiaResponseStatus)status storageType:(SolosConfigStorageType)storageType fallDetectionThreshold:(int)fallDetectionThreshold;
- (void) didSetSignificantMotionThreshold:(SolosGaiaResponseStatus)status storageType:(SolosConfigStorageType)storageType;
- (void) didGet:(SolosGaiaResponseStatus)status storageType:(SolosConfigStorageType)storageType significantMotionThreshold:(int)significantMotionThreshold;
- (void) didGet:(SolosGaiaResponseStatus)status storageType:(SolosConfigStorageType)storageType noiseLv5:(uint8_t)speakerVolLv5 noiseLv6:(uint8_t)speakerVolLv6 noiseLv7:(uint8_t)speakerVolLv7 noiseLv8:(uint8_t)speakerVolLv8;
- (void) didSetAmbientNoiseLevel5_8Mapping:(SolosGaiaResponseStatus)status storageType:(SolosConfigStorageType)storageType;

// system config
- (void) didSetAutoPowerOffTimeout:(SolosGaiaResponseStatus)status storageType:(SolosConfigStorageType)storageType;
- (void) didGet:(SolosGaiaResponseStatus)status storageType:(SolosConfigStorageType)storageType autoPowerOffTimeout:(int)timeoutMins;
- (void) didSetAutoPowerOffEnabled:(SolosGaiaResponseStatus)status storageType:(SolosConfigStorageType)storageType;
- (void) didGet:(SolosGaiaResponseStatus)status storageType:(SolosConfigStorageType)storageType autoPowerOffEnabled:(BOOL)enabled;
- (void) didSetLanguageConfig:(SolosGaiaResponseStatus)status storageType:(SolosConfigStorageType)storageType;
- (void) didGet:(SolosGaiaResponseStatus)status storageType:(SolosConfigStorageType)storageType languageConfig:(SolosLanguageCode)languageCode;
- (void) didSetOnHeadVolume:(SolosGaiaResponseStatus)status storageType:(SolosConfigStorageType)storageType;
- (void) didGet:(SolosGaiaResponseStatus)status storageType:(SolosConfigStorageType)storageType onHeadVolume:(int)volume;
- (void) didSetOffHeadVolume:(SolosGaiaResponseStatus)status storageType:(SolosConfigStorageType)storageType;
- (void) didGet:(SolosGaiaResponseStatus)status storageType:(SolosConfigStorageType)storageType offHeadVolume:(int)volume;
- (void) didSetLostLinkAlertVolume:(SolosGaiaResponseStatus)status storageType:(SolosConfigStorageType)storageType;
- (void) didGet:(SolosGaiaResponseStatus)status storageType:(SolosConfigStorageType)storageType lostLinkVolume:(int)volume;
- (void) didSetAllDayPostureAlertVolume:(SolosGaiaResponseStatus)status storageType:(SolosConfigStorageType)storageType;
- (void) didGet:(SolosGaiaResponseStatus)status storageType:(SolosConfigStorageType)storageType allDayPostureAlertVolume:(int)volume;
- (void) didSetSystemConfig:(SolosGaiaResponseStatus)status storageType:(SolosConfigStorageType)storageType;
- (void) didGet:(SolosGaiaResponseStatus)status storageType:(SolosConfigStorageType)storageType systemConfig:(BOOL)unplugChargerAutoPowerOn multipoint:(BOOL)multipoint multipointBothDevicesLostLinkAlert:(BOOL)multipointBothDevicesLostLinkAlert vaToneSoundOn:(BOOL)vaToneSoundOn harDetectionOn:(BOOL)harDetectionOn ambientNoiseDetectionOn:(BOOL)ambientNoiseDetectionOn ancsNotificationOn:(BOOL)ancsNotificationOn smartPowerOffOn:(BOOL)smartPowerOffOn useTempleLED:(BOOL)useTempleLED;
- (void) didSetLostLinkDuration:(SolosGaiaResponseStatus)status storageType:(SolosConfigStorageType)storageType;
- (void) didGet:(SolosGaiaResponseStatus)status storageType:(SolosConfigStorageType)storageType lostLinkDuration:(int)durInSec;
- (void) didGet:(SolosGaiaResponseStatus)status storageType:(SolosConfigStorageType)storageType noiseLv1:(uint8_t)speakerVolLv1 noiseLv2:(uint8_t)speakerVolLv2 noiseLv3:(uint8_t)speakerVolLv3 noiseLv4:(uint8_t)speakerVolLv4;
- (void) didSetAmbientNoiseLevel1_4Mapping:(SolosGaiaResponseStatus)status storageType:(SolosConfigStorageType)storageType;

// input config
- (void) didSetInputConfigAction:(SolosGaiaResponseStatus)status storageType:(SolosConfigStorageType)storageType  action:(SolosInputConfigAction)action;
- (void) didGet:(SolosGaiaResponseStatus)status storageType:(SolosConfigStorageType)storageType  inputConfigAction:(SolosInputConfigAction)action withInputLo:(SolosInputConfigType)inputLo andInputHi:(SolosInputConfigType)inputHi;
- (void) didSetVolatileInputConfigTimeout:(SolosGaiaResponseStatus)status;
- (void) didSetMultiInputConfigs:(SolosGaiaResponseStatus)status type:(SolosConfigStorageType)type prevInputConfigs:(NSArray*)prevInputConfigs;
// factory
- (void) didSetProductSerialNum:(SolosGaiaResponseStatus)status;
- (void) didGet:(SolosGaiaResponseStatus)status productSerialNum:(NSData*)serialNum;
- (void) didSetProductModelNum:(SolosGaiaResponseStatus)status;
- (void) didGet:(SolosGaiaResponseStatus)status productModelNum:(NSData*)productNum;
- (void) didSetFactoryOptions:(SolosGaiaResponseStatus)status storageType:(SolosConfigStorageType)storageType;
- (void) didGet:(SolosGaiaResponseStatus)status storageType:(SolosConfigStorageType)storageType testMode:(BOOL)testMode;
- (void) didSetCameraBtName:(SolosGaiaResponseStatus)status;
- (void) didGet:(SolosGaiaResponseStatus)status cameraBtName:(NSData*)name;
// whisper
- (void) didSetWhisperData:(SolosGaiaResponseStatus)status;
- (void) didGet:(SolosGaiaResponseStatus)status whisperData:(uint16_t)inGain outGain:(uint16_t)outGain outFlag:(uint16_t)outFlag channelSelect:(uint16_t)channelSelect bfMainGain:(uint32_t)bfMainGain bfRefGain:(uint32_t)bfRefGain vad:(uint32_t)vad scvad:(uint32_t)scvad hangOver:(uint16_t)hangOver scHangOver:(uint16_t)scHangOver aecRefGain:(uint16_t)aecRefGain;
// whisper realtime
- (void) didSetWhisperDataRtOutGain:(SolosGaiaResponseStatus)status;
- (void) didSetWhisperDataRtOutFlag:(SolosGaiaResponseStatus)status;
- (void) didGetWhisperDataRt:(SolosGaiaResponseStatus)status outGain:(int32_t)outGain;
- (void) didGetWhisperDataRt:(SolosGaiaResponseStatus)status outFlag:(int32_t)outFlag;
// whisper downlink rt
- (void) didSetWhisperDownlinkRtAGC:(SolosGaiaResponseStatus)status;
- (void) didSetWhisperDownlinkRtOutFlag:(SolosGaiaResponseStatus)status;
- (void) didSetWhisperDownlinkRt:(SolosGaiaResponseStatus)status;
// whisper downlink
- (void) didSetWhisperDownlinkResponse:(SolosGaiaResponseStatus)status;
- (void) didGet:(SolosGaiaResponseStatus)status whisperDownlink:(uint16_t)band1Gain band2Gain:(uint16_t)band2Gain band3Gain:(uint16_t)band3Gain band4Gain:(uint16_t)band4Gain band5Gain:(uint16_t)band5Gain band6Gain:(uint16_t)band6Gain band7Gain:(uint16_t)band7Gain band8Gain:(uint16_t)band8Gain band9Gain:(uint16_t)band9Gain band10Gain:(uint16_t)band10Gain masterGain:(uint16_t)masterGain enableAGC:(uint16_t)enableAGC powerThreAGC:(uint16_t)powerThreAGC outFlag:(uint16_t)outFlag dlGain:(uint16_t)dlGain;
// whisper eq
- (void) didSetWhisperEqResponse:(SolosGaiaResponseStatus)status;
- (void) didGet:(SolosGaiaResponseStatus)status whisperEq:(uint16_t)outFlag band1Gain:(uint16_t)band1Gain band2Gain:(uint16_t)band2Gain band3Gain:(uint16_t)band3Gain band4Gain:(uint16_t)band4Gain band5Gain:(uint16_t)band5Gain band6Gain:(uint16_t)band6Gain band7Gain:(uint16_t)band7Gain band8Gain:(uint16_t)band8Gain band9Gain:(uint16_t)band9Gain band10Gain:(uint16_t)band10Gain;
// whisper hearable
- (void) didSetWhisperHearableData:(SolosGaiaResponseStatus)status;
- (void) didGet:(SolosGaiaResponseStatus)status whisperHearableData:(uint16_t)inGain outGain:(uint16_t)outGain outFlag:(uint16_t)outFlag channelSelect:(uint16_t)channelSelect bfMainGain:(uint32_t)bfMainGain bfRefGain:(uint32_t)bfRefGain nearEndThreshold:(uint16_t)nearEndThreshold eqBand1Gain:(uint16_t)eqBand1Gain eqBand2Gain:(uint16_t)eqBand2Gain eqBand3Gain:(uint16_t)eqBand3Gain bfOutGain:(uint16_t)bfOutGain;
// magnet calibration
- (void) didSetMagnetCalibrationData:(SolosGaiaResponseStatus)status;
- (void) didGet:(SolosGaiaResponseStatus)status magnetCalibrationData:(uint16_t)maxX maxY:(uint16_t)maxY maxZ:(uint16_t)maxZ minX:(uint16_t)minX minY:(uint16_t)minY minZ:(uint16_t)minZ;
// gyro/accel/magnet calibration
- (void) didSetGyroAccelMagnetCalibrationData:(SolosGaiaResponseStatus)status;
- (void) didGet:(SolosGaiaResponseStatus)status gyroAccelMagnetCalibrationData:(uint16_t)gyroShiftX gyroShiftY:(uint16_t)gyroShiftY gyroShiftZ:(uint16_t)gyroShiftZ accelShiftX:(uint16_t)accelShiftX accelShiftY:(uint16_t)accelShiftY accelShiftZ:(uint16_t)accelShiftZ magnetShiftX:(uint16_t)magnetShiftX magnetShiftY:(uint16_t)magnetShiftY magnetShiftZ:(uint16_t)magnetShiftZ magnetScaleX:(uint16_t)magnetScaleX magnetScaleY:(uint16_t)magnetScaleY magnetScaleZ:(uint16_t)magnetScaleZ;

// touch firmware
- (void) didTouchFirmwareReadVer:(SolosGaiaResponseStatus)status reserved:(uint8_t) reserved major:(uint8_t)major minor:(uint8_t)minor;
- (void) didTouchFirmwareReadTouchEvent:(SolosGaiaResponseStatus)status volDn:(BOOL)volDn volUp:(BOOL)volUp doubleTouch:(BOOL)doubleTouch longTouch:(BOOL)longTouch;
- (void) didTouchFirmwareOtaUpdateStart;
- (void) didTouchFirmwareOtaUpdateComplete;
- (void) didTouchFirmwareOtaUpdateAbort;
- (void) didTouchFirmwareOtaUpdateProgress:(int)progress;
- (void) didTouchFirmwareVerifyStart;
- (void) didTouchFirmwareVerifyComplete;
- (void) didTouchFirmwareVerifyProgress:(int)progress;
- (void) didTouchFirmwareVerifyAbort;
// wind filter
- (void) didSetWhisperFeatureResponse:(SolosGaiaResponseStatus)status;
- (void) didGetWhisperFeatureResponse:(SolosGaiaResponseStatus)status feature:(uint16_t)feature noiseThreshold:(uint16_t)noiseThreshold agcNoiseLevelUpAlpha:(uint16_t)agcNoiseLevelUpAlpha agcNoiseLevelDnAlpha:(uint16_t)agcNoiseLevelDnAlpha vadOnValueThreshold:(uint16_t)vadOnValueThreshold vadOnHoldTimeMs:(uint16_t)vadOnHoldTimeMs vadOffHoldTimeMs:(uint16_t)vadOffHoldTimeMs vadMicOffTimeoutMs:(uint16_t)vadMicOffTimeoutMs reserved6:(uint16_t)reserved6 reserved7:(uint16_t)reserved7 reserved8:(uint16_t)reserved8 reserved9:(uint16_t)reserved9 reserved10:(uint16_t)reserved10 reserved11:(uint16_t)reserved11 reserved12:(uint16_t)reserved12;
@end


#endif /* SolosGaiaDelegate_h */
