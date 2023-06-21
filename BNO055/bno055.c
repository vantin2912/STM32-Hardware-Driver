#include "bno055.h"
#include <string.h>

uint16_t accelScale = 100;
uint16_t tempScale = 1;
uint16_t angularRateScale = 16;
uint16_t eulerScale = 16;
uint16_t magScale = 16;
uint16_t quaScale = (1<<14);    // 2^14


__weak uint8_t BNO055_writeData(BNO055_HandlerStruct* bno055, uint8_t reg, uint8_t data)
{
	int status;
#ifdef USE_RTOS
	status = I2C_OS_MEM_Write_DMA(bno055->i2c, bno055->Address << 1, reg, 1, &data, 1, BNO055_WRITE_TIMEOUT);

#else
	status = HAL_I2C_Mem_Write_DMA(bno055->i2c, bno055->Address << 1, reg, 1, data, 1, BNO055_WRITE_TIMEOUT);
#endif

	return status;
}
__weak uint8_t BNO055_readData(BNO055_HandlerStruct* bno055, uint8_t reg, uint8_t *data, uint8_t len)
{
	int status;
#ifdef USE_RTOS
	status = I2C_OS_MEM_Read_DMA(bno055->i2c, bno055->Address << 1, reg, 1, data, len, BNO055_READ_TIMEOUT);

#else
	status = HAL_I2C_Mem_Read_DMA(bno055->i2c, bno055->Address << 1, reg, 1, data, len, BNO055_READ_TIMEOUT);
#endif
	return status;
}

void BNO055_Init(BNO055_HandlerStruct* bno055, BNO055_I2CHandler* i2c, uint8_t Address)
{
	bno055->Address = Address;
	bno055->i2c = i2c;
	BNO055_setup(bno055);
}



void BNO055_setPage(BNO055_HandlerStruct* bno055, uint8_t page) {
	BNO055_writeData(bno055, BNO055_PAGE_ID, page);
}

BNO055_opmode_t BNO055_getOperationMode(BNO055_HandlerStruct* bno055) {
  BNO055_opmode_t mode;
  BNO055_readData(bno055, BNO055_OPR_MODE, &mode, 1);
  return mode;
}

void BNO055_setOperationMode(BNO055_HandlerStruct* bno055, BNO055_opmode_t mode) {
  BNO055_writeData(bno055, BNO055_OPR_MODE, mode);
  if (mode == BNO055_OPERATION_MODE_CONFIG) {
	  BNO055_Delay(5);
  } else {
	  BNO055_Delay(7);
  }
}

void BNO055_setOperationModeConfig(BNO055_HandlerStruct* bno055) {
  BNO055_setOperationMode(bno055, BNO055_OPERATION_MODE_CONFIG);
}

void BNO055_setOperationModeNDOF(BNO055_HandlerStruct* bno055) {
  BNO055_setOperationMode(bno055, BNO055_OPERATION_MODE_NDOF);
}

void BNO055_setExternalCrystalUse( BNO055_HandlerStruct* bno055, bool state) {
  BNO055_setPage(bno055, 0);
  uint8_t tmp = 0;
  BNO055_readData(bno055, BNO055_SYS_TRIGGER, &tmp, 1);
  tmp |= (state == true) ? 0x80 : 0x0;
  BNO055_writeData(bno055, BNO055_SYS_TRIGGER, tmp);
  BNO055_Delay(700);
}

void BNO055_enableExternalCrystal(BNO055_HandlerStruct* bno055) { BNO055_setExternalCrystalUse(bno055, true); }
void BNO055_disableExternalCrystal(BNO055_HandlerStruct* bno055) { BNO055_setExternalCrystalUse(bno055, false); }

void BNO055_reset(BNO055_HandlerStruct* bno055) {
  BNO055_writeData(bno055, BNO055_SYS_TRIGGER, 0x20);
  BNO055_Delay(700);
}

int8_t BNO055_getTemp(BNO055_HandlerStruct* bno055) {
  BNO055_setPage(bno055, 0);
  uint8_t t;
  BNO055_readData(bno055, BNO055_TEMP, &t, 1);
  return t;
}

void BNO055_setup(BNO055_HandlerStruct* bno055) {
  BNO055_reset(bno055);

  uint8_t id = 0;
  BNO055_readData(bno055, BNO055_CHIP_ID, &id, 1);
  if (id != BNO055_ID) {
    BNO055_printf("Can't find BNO055, id: 0x%02x. Please check your wiring.\r\n", id);
  }
  BNO055_setPage(bno055, 0);
  BNO055_writeData(bno055, BNO055_SYS_TRIGGER, 0x0);

  // Select BNO055 config mode
  BNO055_setOperationModeConfig(bno055);
  BNO055_Delay(10);
}

int16_t BNO055_getSWRevision(BNO055_HandlerStruct* bno055) {
  BNO055_setPage(bno055, 0);
  uint8_t buffer[2];
  BNO055_readData(bno055, BNO055_SW_REV_ID_LSB, buffer, 2);
  return (int16_t)((buffer[1] << 8) | buffer[0]);
}

uint8_t BNO055_getBootloaderRevision(BNO055_HandlerStruct* bno055) {
  BNO055_setPage(bno055, 0);
  uint8_t tmp;
  BNO055_readData(bno055, BNO055_BL_REV_ID, &tmp, 1);
  return tmp;
}

uint8_t BNO055_getSystemStatus(BNO055_HandlerStruct* bno055) {
  BNO055_setPage(bno055, 0);
  uint8_t tmp;
  BNO055_readData(bno055, BNO055_SYS_STATUS, &tmp, 1);
  return tmp;
}

BNO055_self_test_result_t BNO055_getSelfTestResult(BNO055_HandlerStruct* bno055) {
  BNO055_setPage(bno055, 0);
  uint8_t tmp;
  BNO055_self_test_result_t res = {
      .mcuState = 0, .gyrState = 0, .magState = 0, .accState = 0};
  BNO055_readData(bno055, BNO055_ST_RESULT, &tmp, 1);
  res.mcuState = (tmp >> 3) & 0x01;
  res.gyrState = (tmp >> 2) & 0x01;
  res.magState = (tmp >> 1) & 0x01;
  res.accState = (tmp >> 0) & 0x01;
  return res;
}

uint8_t BNO055_getSystemError(BNO055_HandlerStruct* bno055) {
  BNO055_setPage(bno055, 0);
  uint8_t tmp;
  BNO055_readData(bno055, BNO055_SYS_ERR, &tmp, 1);
  return tmp;
}

int BNO055_getCalibrationState(BNO055_HandlerStruct* bno055, BNO055_calibration_state_t* calib_state) {
  BNO055_setPage(bno055, 0);
  uint8_t calState = 0;
  BNO055_readData(bno055, BNO055_CALIB_STAT, &calState, 1);
  calib_state->sys = (calState >> 6) & 0x03;
  calib_state->gyro = (calState >> 4) & 0x03;
  calib_state->accel = (calState >> 2) & 0x03;
  calib_state->mag = calState & 0x03;
  return 0;
}

//BNO055_calibration_state_t BNO055_getCalibrationState(BNO055_HandlerStruct* bno055) {
//  BNO055_setPage(bno055, 0);
//  BNO055_calibration_state_t cal = {.sys = 0, .gyro = 0, .mag = 0, .accel = 0};
//  uint8_t calState = 0;
//  BNO055_readData(bno055, BNO055_CALIB_STAT, &calState, 1);
//  cal.sys = (calState >> 6) & 0x03;
//  cal.gyro = (calState >> 4) & 0x03;
//  cal.accel = (calState >> 2) & 0x03;
//  cal.mag = calState & 0x03;
//  return cal;
//}

BNO055_calibration_data_t BNO055_getCalibrationData(BNO055_HandlerStruct* bno055) {
  BNO055_calibration_data_t calData;
  uint8_t buffer[22];
  BNO055_opmode_t operationMode = BNO055_getOperationMode(bno055);
  BNO055_setOperationModeConfig(bno055);
  BNO055_setPage(bno055, 0);

  BNO055_readData(bno055, BNO055_ACC_OFFSET_X_LSB, buffer, 22);

  // Assumes little endian processor
  memcpy(&calData.offset.accel, buffer, 6);
  memcpy(&calData.offset.mag, buffer + 6, 6);
  memcpy(&calData.offset.gyro, buffer + 12, 6);
  memcpy(&calData.radius.accel, buffer + 18, 2);
  memcpy(&calData.radius.mag, buffer + 20, 2);

  BNO055_setOperationMode(bno055, operationMode);

  return calData;
}

void BNO055_setCalibrationData(BNO055_HandlerStruct* bno055, BNO055_calibration_data_t calData) {
  uint8_t buffer[22];
  BNO055_opmode_t operationMode = BNO055_getOperationMode(bno055);
  BNO055_setOperationModeConfig(bno055);
  BNO055_setPage(bno055, 0);

  // Assumes litle endian processor
  memcpy(buffer, &calData.offset.accel, 6);
  memcpy(buffer + 6, &calData.offset.mag, 6);
  memcpy(buffer + 12, &calData.offset.gyro, 6);
  memcpy(buffer + 18, &calData.radius.accel, 2);
  memcpy(buffer + 20, &calData.radius.mag, 2);

  for (uint8_t i=0; i < 22; i++) {
    // TODO(oliv4945): create multibytes write
    BNO055_writeData(bno055, BNO055_ACC_OFFSET_X_LSB+i, buffer[i]);
  }

  BNO055_setOperationMode(bno055, operationMode);
}

int BNO055_getVector(BNO055_HandlerStruct* bno055, uint8_t vec, BNO055_vector_t* result) {
  BNO055_setPage(bno055, 0);
  uint8_t buffer[8] = {0};    // Quaternion need 8 bytes

  if (vec == BNO055_VECTOR_QUATERNION)
    BNO055_readData(bno055, vec, buffer, 8);
  else
    BNO055_readData(bno055, vec, buffer, 6);

  double scale = 1;

  if (vec == BNO055_VECTOR_MAGNETOMETER) {
    scale = magScale;
  } else if (vec == BNO055_VECTOR_ACCELEROMETER ||
           vec == BNO055_VECTOR_LINEARACCEL || vec == BNO055_VECTOR_GRAVITY) {
    scale = accelScale;
  } else if (vec == BNO055_VECTOR_GYROSCOPE) {
    scale = angularRateScale;
  } else if (vec == BNO055_VECTOR_EULER) {
    scale = eulerScale;
  } else if (vec == BNO055_VECTOR_QUATERNION) {
    scale = quaScale;
  }

//  BNO055_vector_t xyz = {.w = 0, .x = 0, .y = 0, .z = 0};
  if (vec == BNO055_VECTOR_QUATERNION) {
	result->w = (int16_t)((buffer[1] << 8) | buffer[0]) / scale;
	result->x = (int16_t)((buffer[3] << 8) | buffer[2]) / scale;
	result->y = (int16_t)((buffer[5] << 8) | buffer[4]) / scale;
	result->z = (int16_t)((buffer[7] << 8) | buffer[6]) / scale;
  } else {
	result->x = (int16_t)((buffer[1] << 8) | buffer[0]) / scale;
	result->y = (int16_t)((buffer[3] << 8) | buffer[2]) / scale;
	result->z = (int16_t)((buffer[5] << 8) | buffer[4]) / scale;
  }

  return 0;
}

int BNO055_getVectorAccelerometer(BNO055_HandlerStruct* bno055, BNO055_vector_t* result) {
  return BNO055_getVector(bno055, BNO055_VECTOR_ACCELEROMETER, result);
}
int BNO055_getVectorMagnetometer(BNO055_HandlerStruct* bno055, BNO055_vector_t* result) {
  return BNO055_getVector(bno055, BNO055_VECTOR_MAGNETOMETER, result);
}
int BNO055_getVectorGyroscope(BNO055_HandlerStruct* bno055, BNO055_vector_t* result) {
  return BNO055_getVector(bno055, BNO055_VECTOR_GYROSCOPE, result);
}
int BNO055_getVectorEuler(BNO055_HandlerStruct* bno055, BNO055_vector_t* result) {
  return BNO055_getVector(bno055, BNO055_VECTOR_EULER, result);
}
int BNO055_getVectorLinearAccel(BNO055_HandlerStruct* bno055, BNO055_vector_t* result) {
  return BNO055_getVector(bno055, BNO055_VECTOR_LINEARACCEL, result);
}
int BNO055_getVectorGravity(BNO055_HandlerStruct* bno055, BNO055_vector_t* result) {
  return BNO055_getVector(bno055, BNO055_VECTOR_GRAVITY, result);
}
int BNO055_getVectorQuaternion(BNO055_HandlerStruct* bno055, BNO055_vector_t* result) {
  return BNO055_getVector(bno055, BNO055_VECTOR_QUATERNION, result);
}

void BNO055_setAxisMap(BNO055_HandlerStruct* bno055, BNO055_axis_map_t axis) {
  uint8_t axisRemap = (axis.z << 4) | (axis.y << 2) | (axis.x);
  uint8_t axisMapSign = (axis.x_sign << 2) | (axis.y_sign << 1) | (axis.z_sign);
  BNO055_writeData(bno055, BNO055_AXIS_MAP_CONFIG, axisRemap);
  BNO055_writeData(bno055, BNO055_AXIS_MAP_SIGN, axisMapSign);
}
