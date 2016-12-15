/*------------------------------------------------------------------------------
 * MDK - Component ::Event Recorder
 * Copyright (c) 2016 ARM Germany GmbH. All rights reserved.
 *------------------------------------------------------------------------------
 * Name:    EventRecorder.h
 * Purpose: Event Recorder Header File
 * Rev.:    V1.2.0-Beta
 *----------------------------------------------------------------------------*/

#ifndef __EVENT_RECORDER_H
#define __EVENT_RECORDER_H

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif


// Event Levels ----------------------------------------------------------------
#define EventLevelError         0x00000U    ///< Run-time error in the component
#define EventLevelAPI           0x10000U    ///< API function call 
#define EventLevelOp            0x20000U    ///< Internal operation 
#define EventLevelDetail        0x30000U    ///< Additional detailed information of operations

/// Composed event id from level, component number and message number
#define EventID(level, comp_no, msg_no) ((level & 0x30000U) | ((comp_no & 0xFFU) << 8) | (msg_no & 0xFFU))

// Event Recording Control -----------------------------------------------------
#define EventRecordError        0x01U       ///< Record events with level \ref EventLevelError
#define EventRecordAPI          0x02U       ///< Record events with level \ref EventLevelAPI
#define EventRecordOp           0x04U       ///< Record events with level \ref EventLevelOp
#define EventRecordDetail       0x08U       ///< Record events with level \ref EventLevelDetail
#define EventRecordAll          0x0FU       ///< Record events with any level

// Callback function for user provided timer -----------------------------------

/// Initialize timer hardware.
/// \return  timer frequency in Hz
extern uint32_t EventRecorderTimerInit (void);

/// Get Time from timer hardware.
/// \return  timer value (32-bit)
extern uint32_t EventRecorderTimerGet (void);


// Event Recorder Setup Functions ----------------------------------------------

/// Initialize Event Recorder
/// \param[in]    recording   initial level mask for event record filter
/// \param[in]    start       initial recording setup (1=start, 0=stop)
/// \return       status (1=Success, 0=Failure)
extern uint32_t EventRecorderInitialize (uint32_t recording, uint32_t start);

/// Enable recording of events with specified level and component range
/// \param[in]    recording   level mask for event record filter
/// \param[in]    comp_start  first component number of range
/// \param[in]    comp_end    last Component number of range
/// \return       status (1=Success, 0=Failure)
extern uint32_t EventRecorderEnable (uint32_t recording, uint32_t comp_start, uint32_t comp_end);

/// Disable recording of events with specified level and component range
/// \param[in]    recording   level mask for event record filter
/// \param[in]    comp_start  first component number of range
/// \param[in]    comp_end    last Component number of range
/// \return       status (1=Success, 0=Failure)
extern uint32_t EventRecorderDisable (uint32_t recording, uint32_t comp_start, uint32_t comp_end);

/// Start event recording
/// \return       status (1=Success, 0=Failure)
extern uint32_t EventRecorderStart (void);

/// Stop event recording
/// \return       status (1=Success, 0=Failure)
extern uint32_t EventRecorderStop (void);


// Event Data Recording Functions ----------------------------------------------

/// Record an event with variable data size
/// \param[in]    id     event identifier (level, component number, message number)
/// \param[in]    data   event data buffer
/// \param[in]    len    event data length
/// \return       status (1=Success, 0=Failure)
extern uint32_t EventRecordData (uint32_t id, const void *data, uint32_t len);

/// Record an event with two 32-bit data values
/// \param[in]    id     event identifier (level, component number, message number)
/// \param[in]    val1   first data value
/// \param[in]    val2   second data value
/// \return       status (1=Success, 0=Failure)
extern uint32_t EventRecord2 (uint32_t id, uint32_t val1, uint32_t val2);

/// Record an event with four 32-bit data values
/// \param[in]    id     event identifier (level, component number, message number)
/// \param[in]    val1   first data value
/// \param[in]    val2   second data value
/// \param[in]    val3   third data value
/// \param[in]    val4   fourth data value
/// \return       status (1=Success, 0=Failure)
extern uint32_t EventRecord4 (uint32_t id, uint32_t val1, uint32_t val2, uint32_t val3, uint32_t val4);


#ifdef __cplusplus
}
#endif

#endif /* __EVENT_RECORDER_H */
