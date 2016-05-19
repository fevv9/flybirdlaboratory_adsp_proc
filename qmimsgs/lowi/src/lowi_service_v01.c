/*====*====*====*====*====*====*====*====*====*====*====*====*====*====*====*

                        L O W I _ S E R V I C E _ V 0 1  . C

GENERAL DESCRIPTION
  This is the file which defines the lowi service Data structures.

  Copyright (c) 2014 Qualcomm Technologies, Inc.
  All rights reserved.
  Confidential and Proprietary - Qualcomm Technologies, Inc.


  $Header: //components/rel/qmimsgs.adsp/2.6.1/lowi/src/lowi_service_v01.c#1 $
 *====*====*====*====*====*====*====*====*====*====*====*====*====*====*====*/
/*====*====*====*====*====*====*====*====*====*====*====*====*====*====*====* 
 *THIS IS AN AUTO GENERATED FILE. DO NOT ALTER IN ANY WAY 
 *====*====*====*====*====*====*====*====*====*====*====*====*====*====*====*/

/* This file was generated with Tool version 6.10 
   It was generated on: Fri Aug 15 2014 (Spin 0)
   From IDL File: lowi_service_v01.idl */

#include "stdint.h"
#include "qmi_idl_lib_internal.h"
#include "lowi_service_v01.h"
#include "common_v01.h"


/*Type Definitions*/
static const uint8_t sQmiLowiSsid_data_v01[] = {
  QMI_IDL_GENERIC_1_BYTE,
  QMI_IDL_OFFSET8(sQmiLowiSsid_v01, isSsidValid),

  QMI_IDL_FLAGS_IS_ARRAY | QMI_IDL_FLAGS_IS_VARIABLE_LEN |QMI_IDL_GENERIC_1_BYTE,
  QMI_IDL_OFFSET8(sQmiLowiSsid_v01, ssid),
  LOWI_MAX_SSID_LEN_V01,
  QMI_IDL_OFFSET8(sQmiLowiSsid_v01, ssid) - QMI_IDL_OFFSET8(sQmiLowiSsid_v01, ssid_len),

  QMI_IDL_FLAG_END_VALUE
};

static const uint8_t sQmiLowiMsapInfo_data_v01[] = {
  QMI_IDL_GENERIC_1_BYTE,
  QMI_IDL_OFFSET8(sQmiLowiMsapInfo_v01, valid),

  QMI_IDL_GENERIC_1_BYTE,
  QMI_IDL_OFFSET8(sQmiLowiMsapInfo_v01, protocolVersion),

  QMI_IDL_GENERIC_4_BYTE,
  QMI_IDL_OFFSET8(sQmiLowiMsapInfo_v01, venueHash),

  QMI_IDL_GENERIC_1_BYTE,
  QMI_IDL_OFFSET8(sQmiLowiMsapInfo_v01, serverIdx),

  QMI_IDL_FLAG_END_VALUE
};

static const uint8_t sLOWIDiscoveryMeasurementInfo_data_v01[] = {
  QMI_IDL_GENERIC_4_BYTE,
  QMI_IDL_OFFSET8(sLOWIDiscoveryMeasurementInfo_v01, meas_age),

  QMI_IDL_GENERIC_2_BYTE,
  QMI_IDL_OFFSET8(sLOWIDiscoveryMeasurementInfo_v01, rssi),

  QMI_IDL_FLAG_END_VALUE
};

static const uint8_t sQmiLowiMacAddress_data_v01[] = {
  QMI_IDL_GENERIC_4_BYTE,
  QMI_IDL_OFFSET8(sQmiLowiMacAddress_v01, lo24),

  QMI_IDL_GENERIC_4_BYTE,
  QMI_IDL_OFFSET8(sQmiLowiMacAddress_v01, hi24),

  QMI_IDL_FLAG_END_VALUE
};

static const uint8_t sLowiDiscoveryScanMeasurement_data_v01[] = {
  QMI_IDL_AGGREGATE,
  QMI_IDL_OFFSET8(sLowiDiscoveryScanMeasurement_v01, bssid),
  QMI_IDL_TYPE88(0, 3),
  QMI_IDL_GENERIC_4_BYTE,
  QMI_IDL_OFFSET8(sLowiDiscoveryScanMeasurement_v01, frequency),

  QMI_IDL_GENERIC_1_BYTE,
  QMI_IDL_OFFSET8(sLowiDiscoveryScanMeasurement_v01, isSecure),

  QMI_IDL_GENERIC_4_BYTE,
  QMI_IDL_OFFSET8(sLowiDiscoveryScanMeasurement_v01, type),

  QMI_IDL_AGGREGATE,
  QMI_IDL_OFFSET8(sLowiDiscoveryScanMeasurement_v01, ssid),
  QMI_IDL_TYPE88(0, 0),
  QMI_IDL_AGGREGATE,
  QMI_IDL_OFFSET8(sLowiDiscoveryScanMeasurement_v01, msapInfo),
  QMI_IDL_TYPE88(0, 1),
  QMI_IDL_GENERIC_1_BYTE,
  QMI_IDL_OFFSET8(sLowiDiscoveryScanMeasurement_v01, cellPowerLimitdBm),

  QMI_IDL_GENERIC_4_BYTE,
  QMI_IDL_OFFSET8(sLowiDiscoveryScanMeasurement_v01, transmitRate),

  QMI_IDL_GENERIC_1_BYTE,
  QMI_IDL_OFFSET8(sLowiDiscoveryScanMeasurement_v01, rtt3_supported),

  QMI_IDL_GENERIC_8_BYTE,
  QMI_IDL_OFFSET8(sLowiDiscoveryScanMeasurement_v01, tsf),

  QMI_IDL_GENERIC_4_BYTE,
  QMI_IDL_OFFSET8(sLowiDiscoveryScanMeasurement_v01, band_center_freq_1),

  QMI_IDL_GENERIC_4_BYTE,
  QMI_IDL_OFFSET8(sLowiDiscoveryScanMeasurement_v01, band_center_freq_2),

  QMI_IDL_FLAGS_IS_ARRAY | QMI_IDL_FLAGS_IS_VARIABLE_LEN |QMI_IDL_AGGREGATE,
  QMI_IDL_OFFSET8(sLowiDiscoveryScanMeasurement_v01, measurementsInfo),
  LOWI_MAX_MEASUREMENTS_V01,
  QMI_IDL_OFFSET8(sLowiDiscoveryScanMeasurement_v01, measurementsInfo) - QMI_IDL_OFFSET8(sLowiDiscoveryScanMeasurement_v01, measurementsInfo_len),
  QMI_IDL_TYPE88(0, 2),
  QMI_IDL_FLAG_END_VALUE
};

static const uint8_t sLowiNodeInfo_data_v01[] = {
  QMI_IDL_AGGREGATE,
  QMI_IDL_OFFSET8(sLowiNodeInfo_v01, bssid),
  QMI_IDL_TYPE88(0, 3),
  QMI_IDL_GENERIC_4_BYTE,
  QMI_IDL_OFFSET8(sLowiNodeInfo_v01, frequency),

  QMI_IDL_AGGREGATE,
  QMI_IDL_OFFSET8(sLowiNodeInfo_v01, ssid),
  QMI_IDL_TYPE88(0, 0),
  QMI_IDL_GENERIC_2_BYTE,
  QMI_IDL_OFFSET8(sLowiNodeInfo_v01, rssi),

  QMI_IDL_FLAG_END_VALUE
};

/*Message Definitions*/
static const uint8_t QmiLOWIGenResp_data_v01[] = {
  QMI_IDL_TLV_FLAGS_LAST_TLV | 0x02,
   QMI_IDL_AGGREGATE,
  QMI_IDL_OFFSET8(QmiLOWIGenResp_v01, resp),
  QMI_IDL_TYPE88(1, 0)
};

static const uint8_t QmiLowiDiscoveryRequest_data_v01[] = {
  0x01,
   QMI_IDL_GENERIC_8_BYTE,
  QMI_IDL_OFFSET8(QmiLowiDiscoveryRequest_v01, requestId),

  QMI_IDL_TLV_FLAGS_OPTIONAL | (QMI_IDL_OFFSET8(QmiLowiDiscoveryRequest_v01, scanType) - QMI_IDL_OFFSET8(QmiLowiDiscoveryRequest_v01, scanType_valid)),
  0x10,
   QMI_IDL_GENERIC_4_BYTE,
  QMI_IDL_OFFSET8(QmiLowiDiscoveryRequest_v01, scanType),

  QMI_IDL_TLV_FLAGS_OPTIONAL | (QMI_IDL_OFFSET8(QmiLowiDiscoveryRequest_v01, requestMode) - QMI_IDL_OFFSET8(QmiLowiDiscoveryRequest_v01, requestMode_valid)),
  0x11,
   QMI_IDL_GENERIC_4_BYTE,
  QMI_IDL_OFFSET8(QmiLowiDiscoveryRequest_v01, requestMode),

  QMI_IDL_TLV_FLAGS_OPTIONAL | (QMI_IDL_OFFSET8(QmiLowiDiscoveryRequest_v01, band) - QMI_IDL_OFFSET8(QmiLowiDiscoveryRequest_v01, band_valid)),
  0x12,
   QMI_IDL_GENERIC_8_BYTE,
  QMI_IDL_OFFSET8(QmiLowiDiscoveryRequest_v01, band),

  QMI_IDL_TLV_FLAGS_OPTIONAL | (QMI_IDL_OFFSET8(QmiLowiDiscoveryRequest_v01, measAgeFilterSec) - QMI_IDL_OFFSET8(QmiLowiDiscoveryRequest_v01, measAgeFilterSec_valid)),
  0x13,
   QMI_IDL_GENERIC_4_BYTE,
  QMI_IDL_OFFSET8(QmiLowiDiscoveryRequest_v01, measAgeFilterSec),

  QMI_IDL_TLV_FLAGS_OPTIONAL | (QMI_IDL_OFFSET8(QmiLowiDiscoveryRequest_v01, fallbackToleranceSec) - QMI_IDL_OFFSET8(QmiLowiDiscoveryRequest_v01, fallbackToleranceSec_valid)),
  0x14,
   QMI_IDL_GENERIC_4_BYTE,
  QMI_IDL_OFFSET8(QmiLowiDiscoveryRequest_v01, fallbackToleranceSec),

  QMI_IDL_TLV_FLAGS_OPTIONAL | (QMI_IDL_OFFSET8(QmiLowiDiscoveryRequest_v01, requestTimeoutSec) - QMI_IDL_OFFSET8(QmiLowiDiscoveryRequest_v01, requestTimeoutSec_valid)),
  0x15,
   QMI_IDL_GENERIC_4_BYTE,
  QMI_IDL_OFFSET8(QmiLowiDiscoveryRequest_v01, requestTimeoutSec),

  QMI_IDL_TLV_FLAGS_OPTIONAL | (QMI_IDL_OFFSET8(QmiLowiDiscoveryRequest_v01, channelFreq) - QMI_IDL_OFFSET8(QmiLowiDiscoveryRequest_v01, channelFreq_valid)),
  0x16,
  QMI_IDL_FLAGS_IS_ARRAY | QMI_IDL_FLAGS_IS_VARIABLE_LEN |  QMI_IDL_GENERIC_4_BYTE,
  QMI_IDL_OFFSET8(QmiLowiDiscoveryRequest_v01, channelFreq),
  LOWI_MAX_FREQ_LIST_SIZE_V01,
  QMI_IDL_OFFSET8(QmiLowiDiscoveryRequest_v01, channelFreq) - QMI_IDL_OFFSET8(QmiLowiDiscoveryRequest_v01, channelFreq_len),

  QMI_IDL_TLV_FLAGS_LAST_TLV | QMI_IDL_TLV_FLAGS_OPTIONAL | (QMI_IDL_OFFSET8(QmiLowiDiscoveryRequest_v01, ssidList) - QMI_IDL_OFFSET8(QmiLowiDiscoveryRequest_v01, ssidList_valid)),
  0x17,
  QMI_IDL_FLAGS_IS_ARRAY | QMI_IDL_FLAGS_IS_VARIABLE_LEN |  QMI_IDL_AGGREGATE,
  QMI_IDL_OFFSET8(QmiLowiDiscoveryRequest_v01, ssidList),
  LOWI_MAX_AP_SSID_LIST_SIZE_V01,
  QMI_IDL_OFFSET8(QmiLowiDiscoveryRequest_v01, ssidList) - QMI_IDL_OFFSET8(QmiLowiDiscoveryRequest_v01, ssidList_len),
  QMI_IDL_TYPE88(0, 0)
};

static const uint8_t QmiLowiDiscoveryResponseInd_data_v01[] = {
  0x01,
   QMI_IDL_GENERIC_8_BYTE,
  QMI_IDL_OFFSET8(QmiLowiDiscoveryResponseInd_v01, requestId),

  QMI_IDL_TLV_FLAGS_OPTIONAL | (QMI_IDL_OFFSET8(QmiLowiDiscoveryResponseInd_v01, scanType) - QMI_IDL_OFFSET8(QmiLowiDiscoveryResponseInd_v01, scanType_valid)),
  0x10,
   QMI_IDL_GENERIC_4_BYTE,
  QMI_IDL_OFFSET8(QmiLowiDiscoveryResponseInd_v01, scanType),

  QMI_IDL_TLV_FLAGS_OPTIONAL | (QMI_IDL_OFFSET8(QmiLowiDiscoveryResponseInd_v01, scanStatus) - QMI_IDL_OFFSET8(QmiLowiDiscoveryResponseInd_v01, scanStatus_valid)),
  0x11,
   QMI_IDL_GENERIC_4_BYTE,
  QMI_IDL_OFFSET8(QmiLowiDiscoveryResponseInd_v01, scanStatus),

  QMI_IDL_TLV_FLAGS_OPTIONAL | (QMI_IDL_OFFSET8(QmiLowiDiscoveryResponseInd_v01, scanMeasurements) - QMI_IDL_OFFSET8(QmiLowiDiscoveryResponseInd_v01, scanMeasurements_valid)),
  0x12,
  QMI_IDL_FLAGS_IS_ARRAY | QMI_IDL_FLAGS_IS_VARIABLE_LEN |  QMI_IDL_AGGREGATE,
  QMI_IDL_OFFSET8(QmiLowiDiscoveryResponseInd_v01, scanMeasurements),
  LOWI_MAX_AP_ALLOWED_V01,
  QMI_IDL_OFFSET8(QmiLowiDiscoveryResponseInd_v01, scanMeasurements) - QMI_IDL_OFFSET8(QmiLowiDiscoveryResponseInd_v01, scanMeasurements_len),
  QMI_IDL_TYPE88(0, 4),

  QMI_IDL_TLV_FLAGS_OPTIONAL | (QMI_IDL_OFFSET16RELATIVE(QmiLowiDiscoveryResponseInd_v01, scannedFreqList) - QMI_IDL_OFFSET16RELATIVE(QmiLowiDiscoveryResponseInd_v01, scannedFreqList_valid)),
  0x13,
  QMI_IDL_FLAGS_IS_ARRAY | QMI_IDL_FLAGS_IS_VARIABLE_LEN |  QMI_IDL_FLAGS_OFFSET_IS_16 | QMI_IDL_GENERIC_4_BYTE,
  QMI_IDL_OFFSET16ARRAY(QmiLowiDiscoveryResponseInd_v01, scannedFreqList),
  LOWI_MAX_FREQ_LIST_SIZE_V01,
  QMI_IDL_OFFSET16RELATIVE(QmiLowiDiscoveryResponseInd_v01, scannedFreqList) - QMI_IDL_OFFSET16RELATIVE(QmiLowiDiscoveryResponseInd_v01, scannedFreqList_len),

  QMI_IDL_TLV_FLAGS_OPTIONAL | (QMI_IDL_OFFSET16RELATIVE(QmiLowiDiscoveryResponseInd_v01, countryCode) - QMI_IDL_OFFSET16RELATIVE(QmiLowiDiscoveryResponseInd_v01, countryCode_valid)),
  0x14,
  QMI_IDL_FLAGS_IS_ARRAY | QMI_IDL_FLAGS_IS_VARIABLE_LEN |  QMI_IDL_FLAGS_OFFSET_IS_16 | QMI_IDL_GENERIC_1_BYTE,
  QMI_IDL_OFFSET16ARRAY(QmiLowiDiscoveryResponseInd_v01, countryCode),
  LOWI_MAX_COUNTRY_CODE_LENGTH_V01,
  QMI_IDL_OFFSET16RELATIVE(QmiLowiDiscoveryResponseInd_v01, countryCode) - QMI_IDL_OFFSET16RELATIVE(QmiLowiDiscoveryResponseInd_v01, countryCode_len),

  QMI_IDL_TLV_FLAGS_LAST_TLV | QMI_IDL_TLV_FLAGS_OPTIONAL | (QMI_IDL_OFFSET16RELATIVE(QmiLowiDiscoveryResponseInd_v01, isLast) - QMI_IDL_OFFSET16RELATIVE(QmiLowiDiscoveryResponseInd_v01, isLast_valid)),
  0x15,
   QMI_IDL_FLAGS_OFFSET_IS_16 | QMI_IDL_GENERIC_1_BYTE,
  QMI_IDL_OFFSET16ARRAY(QmiLowiDiscoveryResponseInd_v01, isLast)
};

static const uint8_t QmiLowiCapabilitiesRequest_data_v01[] = {
  QMI_IDL_TLV_FLAGS_LAST_TLV | 0x01,
   QMI_IDL_GENERIC_8_BYTE,
  QMI_IDL_OFFSET8(QmiLowiCapabilitiesRequest_v01, requestId)
};

static const uint8_t QmiLowiCapabilitiesResponseInd_data_v01[] = {
  0x01,
   QMI_IDL_GENERIC_8_BYTE,
  QMI_IDL_OFFSET8(QmiLowiCapabilitiesResponseInd_v01, requestId),

  QMI_IDL_TLV_FLAGS_OPTIONAL | (QMI_IDL_OFFSET8(QmiLowiCapabilitiesResponseInd_v01, lowi_lp_version) - QMI_IDL_OFFSET8(QmiLowiCapabilitiesResponseInd_v01, lowi_lp_version_valid)),
  0x10,
  QMI_IDL_FLAGS_IS_ARRAY | QMI_IDL_FLAGS_IS_VARIABLE_LEN |  QMI_IDL_STRING,
  QMI_IDL_OFFSET8(QmiLowiCapabilitiesResponseInd_v01, lowi_lp_version),
  LOWI_MAX_STRING_LENGTH_V01,

  QMI_IDL_TLV_FLAGS_OPTIONAL | (QMI_IDL_OFFSET16RELATIVE(QmiLowiCapabilitiesResponseInd_v01, rangingScanSupported) - QMI_IDL_OFFSET16RELATIVE(QmiLowiCapabilitiesResponseInd_v01, rangingScanSupported_valid)),
  0x11,
   QMI_IDL_FLAGS_OFFSET_IS_16 | QMI_IDL_GENERIC_1_BYTE,
  QMI_IDL_OFFSET16ARRAY(QmiLowiCapabilitiesResponseInd_v01, rangingScanSupported),

  QMI_IDL_TLV_FLAGS_OPTIONAL | (QMI_IDL_OFFSET16RELATIVE(QmiLowiCapabilitiesResponseInd_v01, activeScanSupported) - QMI_IDL_OFFSET16RELATIVE(QmiLowiCapabilitiesResponseInd_v01, activeScanSupported_valid)),
  0x12,
   QMI_IDL_FLAGS_OFFSET_IS_16 | QMI_IDL_GENERIC_1_BYTE,
  QMI_IDL_OFFSET16ARRAY(QmiLowiCapabilitiesResponseInd_v01, activeScanSupported),

  QMI_IDL_TLV_FLAGS_OPTIONAL | (QMI_IDL_OFFSET16RELATIVE(QmiLowiCapabilitiesResponseInd_v01, truePassiveScanSupported) - QMI_IDL_OFFSET16RELATIVE(QmiLowiCapabilitiesResponseInd_v01, truePassiveScanSupported_valid)),
  0x13,
   QMI_IDL_FLAGS_OFFSET_IS_16 | QMI_IDL_GENERIC_1_BYTE,
  QMI_IDL_OFFSET16ARRAY(QmiLowiCapabilitiesResponseInd_v01, truePassiveScanSupported),

  QMI_IDL_TLV_FLAGS_OPTIONAL | (QMI_IDL_OFFSET16RELATIVE(QmiLowiCapabilitiesResponseInd_v01, snoopScanSupported) - QMI_IDL_OFFSET16RELATIVE(QmiLowiCapabilitiesResponseInd_v01, snoopScanSupported_valid)),
  0x14,
   QMI_IDL_FLAGS_OFFSET_IS_16 | QMI_IDL_GENERIC_1_BYTE,
  QMI_IDL_OFFSET16ARRAY(QmiLowiCapabilitiesResponseInd_v01, snoopScanSupported),

  QMI_IDL_TLV_FLAGS_OPTIONAL | (QMI_IDL_OFFSET16RELATIVE(QmiLowiCapabilitiesResponseInd_v01, wlanEventsSupported) - QMI_IDL_OFFSET16RELATIVE(QmiLowiCapabilitiesResponseInd_v01, wlanEventsSupported_valid)),
  0x15,
   QMI_IDL_FLAGS_OFFSET_IS_16 | QMI_IDL_GENERIC_1_BYTE,
  QMI_IDL_OFFSET16ARRAY(QmiLowiCapabilitiesResponseInd_v01, wlanEventsSupported),

  QMI_IDL_TLV_FLAGS_OPTIONAL | (QMI_IDL_OFFSET16RELATIVE(QmiLowiCapabilitiesResponseInd_v01, chipOEM) - QMI_IDL_OFFSET16RELATIVE(QmiLowiCapabilitiesResponseInd_v01, chipOEM_valid)),
  0x16,
  QMI_IDL_FLAGS_IS_ARRAY | QMI_IDL_FLAGS_IS_VARIABLE_LEN |  QMI_IDL_FLAGS_OFFSET_IS_16 | QMI_IDL_STRING,
  QMI_IDL_OFFSET16ARRAY(QmiLowiCapabilitiesResponseInd_v01, chipOEM),
  LOWI_MAX_WLAN_STRING_LEN_V01,

  QMI_IDL_TLV_FLAGS_OPTIONAL | (QMI_IDL_OFFSET16RELATIVE(QmiLowiCapabilitiesResponseInd_v01, chipName) - QMI_IDL_OFFSET16RELATIVE(QmiLowiCapabilitiesResponseInd_v01, chipName_valid)),
  0x17,
  QMI_IDL_FLAGS_IS_ARRAY | QMI_IDL_FLAGS_IS_VARIABLE_LEN |  QMI_IDL_FLAGS_OFFSET_IS_16 | QMI_IDL_STRING,
  QMI_IDL_OFFSET16ARRAY(QmiLowiCapabilitiesResponseInd_v01, chipName),
  LOWI_MAX_WLAN_STRING_LEN_V01,

  QMI_IDL_TLV_FLAGS_OPTIONAL | (QMI_IDL_OFFSET16RELATIVE(QmiLowiCapabilitiesResponseInd_v01, wlan_chip_id) - QMI_IDL_OFFSET16RELATIVE(QmiLowiCapabilitiesResponseInd_v01, wlan_chip_id_valid)),
  0x18,
   QMI_IDL_FLAGS_OFFSET_IS_16 | QMI_IDL_GENERIC_4_BYTE,
  QMI_IDL_OFFSET16ARRAY(QmiLowiCapabilitiesResponseInd_v01, wlan_chip_id),

  QMI_IDL_TLV_FLAGS_OPTIONAL | (QMI_IDL_OFFSET16RELATIVE(QmiLowiCapabilitiesResponseInd_v01, wifiDriverVersion) - QMI_IDL_OFFSET16RELATIVE(QmiLowiCapabilitiesResponseInd_v01, wifiDriverVersion_valid)),
  0x19,
  QMI_IDL_FLAGS_IS_ARRAY | QMI_IDL_FLAGS_IS_VARIABLE_LEN |  QMI_IDL_FLAGS_OFFSET_IS_16 | QMI_IDL_STRING,
  QMI_IDL_OFFSET16ARRAY(QmiLowiCapabilitiesResponseInd_v01, wifiDriverVersion),
  LOWI_MAX_WLAN_STRING_LEN_V01,

  QMI_IDL_TLV_FLAGS_LAST_TLV | QMI_IDL_TLV_FLAGS_OPTIONAL | (QMI_IDL_OFFSET16RELATIVE(QmiLowiCapabilitiesResponseInd_v01, fwVersion) - QMI_IDL_OFFSET16RELATIVE(QmiLowiCapabilitiesResponseInd_v01, fwVersion_valid)),
  0x1A,
  QMI_IDL_FLAGS_IS_ARRAY | QMI_IDL_FLAGS_IS_VARIABLE_LEN |  QMI_IDL_FLAGS_OFFSET_IS_16 | QMI_IDL_STRING,
  QMI_IDL_OFFSET16ARRAY(QmiLowiCapabilitiesResponseInd_v01, fwVersion),
  LOWI_MAX_WLAN_STRING_LEN_V01
};

static const uint8_t QmiLowiWlanInterfaceEventsSubscriptionRequest_data_v01[] = {
  0x01,
   QMI_IDL_GENERIC_8_BYTE,
  QMI_IDL_OFFSET8(QmiLowiWlanInterfaceEventsSubscriptionRequest_v01, requestId),

  0x02,
   QMI_IDL_GENERIC_1_BYTE,
  QMI_IDL_OFFSET8(QmiLowiWlanInterfaceEventsSubscriptionRequest_v01, subscribe),

  QMI_IDL_TLV_FLAGS_LAST_TLV | QMI_IDL_TLV_FLAGS_OPTIONAL | (QMI_IDL_OFFSET8(QmiLowiWlanInterfaceEventsSubscriptionRequest_v01, interface) - QMI_IDL_OFFSET8(QmiLowiWlanInterfaceEventsSubscriptionRequest_v01, interface_valid)),
  0x10,
   QMI_IDL_GENERIC_4_BYTE,
  QMI_IDL_OFFSET8(QmiLowiWlanInterfaceEventsSubscriptionRequest_v01, interface)
};

static const uint8_t QmiLowiWlanInterfaceEventsResponseInd_data_v01[] = {
  0x01,
   QMI_IDL_GENERIC_8_BYTE,
  QMI_IDL_OFFSET8(QmiLowiWlanInterfaceEventsResponseInd_v01, requestId),

  QMI_IDL_TLV_FLAGS_OPTIONAL | (QMI_IDL_OFFSET8(QmiLowiWlanInterfaceEventsResponseInd_v01, event) - QMI_IDL_OFFSET8(QmiLowiWlanInterfaceEventsResponseInd_v01, event_valid)),
  0x10,
   QMI_IDL_GENERIC_8_BYTE,
  QMI_IDL_OFFSET8(QmiLowiWlanInterfaceEventsResponseInd_v01, event),

  QMI_IDL_TLV_FLAGS_OPTIONAL | (QMI_IDL_OFFSET8(QmiLowiWlanInterfaceEventsResponseInd_v01, wlan_on) - QMI_IDL_OFFSET8(QmiLowiWlanInterfaceEventsResponseInd_v01, wlan_on_valid)),
  0x11,
   QMI_IDL_GENERIC_1_BYTE,
  QMI_IDL_OFFSET8(QmiLowiWlanInterfaceEventsResponseInd_v01, wlan_on),

  QMI_IDL_TLV_FLAGS_OPTIONAL | (QMI_IDL_OFFSET8(QmiLowiWlanInterfaceEventsResponseInd_v01, connected) - QMI_IDL_OFFSET8(QmiLowiWlanInterfaceEventsResponseInd_v01, connected_valid)),
  0x12,
   QMI_IDL_GENERIC_1_BYTE,
  QMI_IDL_OFFSET8(QmiLowiWlanInterfaceEventsResponseInd_v01, connected),

  QMI_IDL_TLV_FLAGS_OPTIONAL | (QMI_IDL_OFFSET8(QmiLowiWlanInterfaceEventsResponseInd_v01, handoff) - QMI_IDL_OFFSET8(QmiLowiWlanInterfaceEventsResponseInd_v01, handoff_valid)),
  0x13,
   QMI_IDL_GENERIC_1_BYTE,
  QMI_IDL_OFFSET8(QmiLowiWlanInterfaceEventsResponseInd_v01, handoff),

  QMI_IDL_TLV_FLAGS_OPTIONAL | (QMI_IDL_OFFSET8(QmiLowiWlanInterfaceEventsResponseInd_v01, connectedNodeInfo) - QMI_IDL_OFFSET8(QmiLowiWlanInterfaceEventsResponseInd_v01, connectedNodeInfo_valid)),
  0x14,
   QMI_IDL_AGGREGATE,
  QMI_IDL_OFFSET8(QmiLowiWlanInterfaceEventsResponseInd_v01, connectedNodeInfo),
  QMI_IDL_TYPE88(0, 5),

  QMI_IDL_TLV_FLAGS_LAST_TLV | QMI_IDL_TLV_FLAGS_OPTIONAL | (QMI_IDL_OFFSET8(QmiLowiWlanInterfaceEventsResponseInd_v01, handoffNodeInfo) - QMI_IDL_OFFSET8(QmiLowiWlanInterfaceEventsResponseInd_v01, handoffNodeInfo_valid)),
  0x15,
   QMI_IDL_AGGREGATE,
  QMI_IDL_OFFSET8(QmiLowiWlanInterfaceEventsResponseInd_v01, handoffNodeInfo),
  QMI_IDL_TYPE88(0, 5)
};

static const uint8_t QmiLowiWlanInterfaceEventTriggerRequest_data_v01[] = {
  0x01,
   QMI_IDL_GENERIC_8_BYTE,
  QMI_IDL_OFFSET8(QmiLowiWlanInterfaceEventTriggerRequest_v01, requestId),

  QMI_IDL_TLV_FLAGS_LAST_TLV | QMI_IDL_TLV_FLAGS_OPTIONAL | (QMI_IDL_OFFSET8(QmiLowiWlanInterfaceEventTriggerRequest_v01, interface) - QMI_IDL_OFFSET8(QmiLowiWlanInterfaceEventTriggerRequest_v01, interface_valid)),
  0x10,
   QMI_IDL_GENERIC_4_BYTE,
  QMI_IDL_OFFSET8(QmiLowiWlanInterfaceEventTriggerRequest_v01, interface)
};

static const uint8_t QmiLowiSnoopScanSubscriptionRequest_data_v01[] = {
  0x01,
   QMI_IDL_GENERIC_8_BYTE,
  QMI_IDL_OFFSET8(QmiLowiSnoopScanSubscriptionRequest_v01, requestId),

  0x02,
   QMI_IDL_GENERIC_1_BYTE,
  QMI_IDL_OFFSET8(QmiLowiSnoopScanSubscriptionRequest_v01, subscribe),

  0x03,
   QMI_IDL_GENERIC_1_BYTE,
  QMI_IDL_OFFSET8(QmiLowiSnoopScanSubscriptionRequest_v01, sendScansNotSentToApss),

  QMI_IDL_TLV_FLAGS_LAST_TLV | 0x04,
   QMI_IDL_GENERIC_4_BYTE,
  QMI_IDL_OFFSET8(QmiLowiSnoopScanSubscriptionRequest_v01, request_timer_sec)
};

/* Type Table */
static const qmi_idl_type_table_entry  lowi_type_table_v01[] = {
  {sizeof(sQmiLowiSsid_v01), sQmiLowiSsid_data_v01},
  {sizeof(sQmiLowiMsapInfo_v01), sQmiLowiMsapInfo_data_v01},
  {sizeof(sLOWIDiscoveryMeasurementInfo_v01), sLOWIDiscoveryMeasurementInfo_data_v01},
  {sizeof(sQmiLowiMacAddress_v01), sQmiLowiMacAddress_data_v01},
  {sizeof(sLowiDiscoveryScanMeasurement_v01), sLowiDiscoveryScanMeasurement_data_v01},
  {sizeof(sLowiNodeInfo_v01), sLowiNodeInfo_data_v01}
};

/* Message Table */
static const qmi_idl_message_table_entry lowi_message_table_v01[] = {
  {sizeof(QmiLOWIGenResp_v01), QmiLOWIGenResp_data_v01},
  {sizeof(QmiLowiDiscoveryRequest_v01), QmiLowiDiscoveryRequest_data_v01},
  {sizeof(QmiLowiDiscoveryResponseInd_v01), QmiLowiDiscoveryResponseInd_data_v01},
  {sizeof(QmiLowiCapabilitiesRequest_v01), QmiLowiCapabilitiesRequest_data_v01},
  {sizeof(QmiLowiCapabilitiesResponseInd_v01), QmiLowiCapabilitiesResponseInd_data_v01},
  {sizeof(QmiLowiWlanInterfaceEventsSubscriptionRequest_v01), QmiLowiWlanInterfaceEventsSubscriptionRequest_data_v01},
  {sizeof(QmiLowiWlanInterfaceEventsResponseInd_v01), QmiLowiWlanInterfaceEventsResponseInd_data_v01},
  {sizeof(QmiLowiWlanInterfaceEventTriggerRequest_v01), QmiLowiWlanInterfaceEventTriggerRequest_data_v01},
  {sizeof(QmiLowiSnoopScanSubscriptionRequest_v01), QmiLowiSnoopScanSubscriptionRequest_data_v01}
};

/* Range Table */
/* No Ranges Defined in IDL */

/* Predefine the Type Table Object */
static const qmi_idl_type_table_object lowi_qmi_idl_type_table_object_v01;

/*Referenced Tables Array*/
static const qmi_idl_type_table_object *lowi_qmi_idl_type_table_object_referenced_tables_v01[] =
{&lowi_qmi_idl_type_table_object_v01, &common_qmi_idl_type_table_object_v01};

/*Type Table Object*/
static const qmi_idl_type_table_object lowi_qmi_idl_type_table_object_v01 = {
  sizeof(lowi_type_table_v01)/sizeof(qmi_idl_type_table_entry ),
  sizeof(lowi_message_table_v01)/sizeof(qmi_idl_message_table_entry),
  1,
  lowi_type_table_v01,
  lowi_message_table_v01,
  lowi_qmi_idl_type_table_object_referenced_tables_v01,
  NULL
};

/*Arrays of service_message_table_entries for commands, responses and indications*/
static const qmi_idl_service_message_table_entry lowi_service_command_messages_v01[] = {
  {QMI_LOWI_DISCOVERY_REQ_V01, QMI_IDL_TYPE16(0, 1), 825},
  {QMI_LOWI_CAPABILITIES_REQ_V01, QMI_IDL_TYPE16(0, 3), 11},
  {QMI_LOWI_WLAN_INTERFACE_EVENTS_REQ_V01, QMI_IDL_TYPE16(0, 5), 22},
  {QMI_LOWI_WLAN_INTERFACE_EVENT_TRIGGER_REQ_V01, QMI_IDL_TYPE16(0, 7), 18},
  {QMI_LOWI_SNOOP_SCAN_SUBSCRIPTION_REQ_V01, QMI_IDL_TYPE16(0, 8), 26}
};

static const qmi_idl_service_message_table_entry lowi_service_response_messages_v01[] = {
  {QMI_LOWI_DISCOVERY_RESP_V01, QMI_IDL_TYPE16(0, 0), 7},
  {QMI_LOWI_CAPABILITIES_RESP_V01, QMI_IDL_TYPE16(0, 0), 7},
  {QMI_LOWI_WLAN_INTERFACE_EVENTS_RESP_V01, QMI_IDL_TYPE16(0, 0), 7},
  {QMI_LOWI_WLAN_INTERFACE_EVENT_TRIGGER_RESP_V01, QMI_IDL_TYPE16(0, 0), 7},
  {QMI_LOWI_SNOOP_SCAN_SUBSCRIPTION_RESP_V01, QMI_IDL_TYPE16(0, 0), 7}
};

static const qmi_idl_service_message_table_entry lowi_service_indication_messages_v01[] = {
  {QMI_LOWI_DISCOVERY_IND_V01, QMI_IDL_TYPE16(0, 2), 2301},
  {QMI_LOWI_CAPABILITIES_IND_V01, QMI_IDL_TYPE16(0, 4), 432},
  {QMI_LOWI_WLAN_INTERFACE_EVENTS_IND_V01, QMI_IDL_TYPE16(0, 6), 136},
  {QMI_LOWI_WLAN_INTERFACE_EVENT_TRIGGER_IND_V01, QMI_IDL_TYPE16(0, 6), 136},
  {QMI_LOWI_SNOOP_SCAN_SUBSCRIPTION_IND_V01, QMI_IDL_TYPE16(0, 2), 2301}
};

/*Service Object*/
struct qmi_idl_service_object lowi_qmi_idl_service_object_v01 = {
  0x06,
  0x01,
  0x38,
  2301,
  { sizeof(lowi_service_command_messages_v01)/sizeof(qmi_idl_service_message_table_entry),
    sizeof(lowi_service_response_messages_v01)/sizeof(qmi_idl_service_message_table_entry),
    sizeof(lowi_service_indication_messages_v01)/sizeof(qmi_idl_service_message_table_entry) },
  { lowi_service_command_messages_v01, lowi_service_response_messages_v01, lowi_service_indication_messages_v01},
  &lowi_qmi_idl_type_table_object_v01,
  0x00,
  NULL
};

/* Service Object Accessor */
qmi_idl_service_object_type lowi_get_service_object_internal_v01
 ( int32_t idl_maj_version, int32_t idl_min_version, int32_t library_version ){
  if ( LOWI_V01_IDL_MAJOR_VERS != idl_maj_version || LOWI_V01_IDL_MINOR_VERS != idl_min_version 
       || LOWI_V01_IDL_TOOL_VERS != library_version) 
  {
    return NULL;
  } 
  return (qmi_idl_service_object_type)&lowi_qmi_idl_service_object_v01;
}

