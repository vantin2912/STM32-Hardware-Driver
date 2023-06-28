/*
 * INA219.c
 *
 *  Created on: Dec 30, 2020
 *       Author: Piotr Smolen <komuch@gmail.com>
 */

#include "main.h"
#include "INA219.h"
//#include "math.h"


uint16_t Read16(INA219_t *ina219, uint8_t Register)
{
	uint8_t Value[2] = {0};
	INA219_Mem_Read(ina219->ina219_i2c, (ina219->Address<<1), Register, 1, Value, 2, 1000);
	return ((Value[0] << 8) | Value[1]);
}


void Write16(INA219_t *ina219, uint8_t Register, uint16_t Value)
{
	uint8_t addr[2];
	addr[0] = (Value >> 8) & 0xff;  // upper byte
	addr[1] = (Value >> 0) & 0xff; // lower byte
	INA219_Mem_Write(ina219->ina219_i2c, (ina219->Address<<1), Register, 1, (uint8_t*)addr, 2, 100);
}

uint16_t INA219_ReadBusVoltage(INA219_t *ina219)
{
	uint16_t result = Read16(ina219, INA219_REG_BUSVOLTAGE);\
	return ((result >> 3  ) * 4);

}

int16_t INA219_ReadCurrent_raw(INA219_t *ina219)
{
	int16_t result = Read16(ina219, INA219_REG_CURRENT);

	return (result );
}

int16_t INA219_ReadCurrent(INA219_t *ina219)
{
	int16_t result = INA219_ReadCurrent_raw(ina219);

	return result/ ina219->currentDivider_mA;
}

uint16_t INA219_ReadShuntVolage(INA219_t *ina219)
{
	uint16_t result = Read16(ina219, INA219_REG_SHUNTVOLTAGE);

	return (result * 0.01 );
}


int16_t INA219_ReadPower(INA219_t *ina219)
{
	int16_t result = Read16(ina219, INA219_REG_POWER);

	return (result * ina219->powerMultiplier_mW );
}
void INA219_Reset(INA219_t *ina219)
{
	Write16(ina219, INA219_REG_CONFIG, INA219_CONFIG_RESET);
	osDelay(1);
}

void INA219_setCalibration(INA219_t *ina219, uint16_t CalibrationData)
{
	Write16(ina219, INA219_REG_CALIBRATION, CalibrationData);
}

uint16_t INA219_getConfig(INA219_t *ina219)
{
	uint16_t result = Read16(ina219, INA219_REG_CONFIG);
	return result;
}

void INA219_setConfig(INA219_t *ina219, uint16_t Config)
{
	Write16(ina219, INA219_REG_CONFIG, Config);
}
/**
 *	Calib for 0.1 Ohm Shunt Resistor
 */
void INA219_setCalibration_32V_2A(INA219_t *ina219)
{
	uint16_t config = INA219_CONFIG_BVOLTAGERANGE_32V |
	             INA219_CONFIG_GAIN_8_320MV | INA219_CONFIG_BADCRES_12BIT |
	             INA219_CONFIG_SADCRES_12BIT_1S_532US |
	             INA219_CONFIG_MODE_SANDBVOLT_CONTINUOUS;

	ina219->calibrationValue = 4096;
//	ina219->calibrationValue = 6710<<1;

	ina219->currentDivider_mA = 10; // Current LSB = 100uA per bit (1000/100 = 10)
	ina219->powerMultiplier_mW = 2; // Power LSB = 1mW per bit (2/1)


	INA219_setCalibration(ina219, ina219->calibrationValue);
	INA219_setConfig(ina219, config);
}
/**
 *	Calib for 0.1 Ohm Shunt Resistor
 */
void INA219_setCalibration_32V_1A(INA219_t *ina219)
{
	uint16_t config = INA219_CONFIG_BVOLTAGERANGE_32V |
	                    INA219_CONFIG_GAIN_8_320MV | INA219_CONFIG_BADCRES_12BIT |
	                    INA219_CONFIG_SADCRES_12BIT_1S_532US |
	                    INA219_CONFIG_MODE_SANDBVOLT_CONTINUOUS;

	ina219->calibrationValue = 10240;
	ina219->currentDivider_mA = 25;    // Current LSB = 40uA per bit (1000/40 = 25)
	ina219->powerMultiplier_mW = 0.8f; // Power LSB = 800uW per bit

	INA219_setCalibration(ina219, ina219->calibrationValue);
	INA219_setConfig(ina219, config);
}

/**
 *	Calib for 5 mOhm Shunt Resistor
 */
void INA219_setCalibration_32V_10A_5mOhm(INA219_t *ina219)
{
	uint16_t config = INA219_CONFIG_BVOLTAGERANGE_32V |
						INA219_CONFIG_GAIN_8_320MV | INA219_CONFIG_BADCRES_12BIT |
						INA219_CONFIG_SADCRES_12BIT_1S_532US |
						INA219_CONFIG_MODE_SANDBVOLT_CONTINUOUS;


	ina219->calibrationValue = 16384;
	ina219->currentDivider_mA = 2;    // Current LSB = 500uA per bit (1000/40 = 25)
	ina219->powerMultiplier_mW = 10; // Power LSB = 10000uW per bit

	INA219_setCalibration(ina219, ina219->calibrationValue);
	INA219_setConfig(ina219, config);
}
/**
 *	Calib for 1 mOhm Shunt Resistor
 *	@warning Not test yet
 */
void INA219_setCalibration_32V_10A_1mOhm(INA219_t *ina219)
{
	uint16_t config = INA219_CONFIG_BVOLTAGERANGE_32V |
						INA219_CONFIG_GAIN_8_320MV | INA219_CONFIG_BADCRES_12BIT |
						INA219_CONFIG_SADCRES_12BIT_1S_532US |
						INA219_CONFIG_MODE_SANDBVOLT_CONTINUOUS;


	ina219->calibrationValue = 40960;
	ina219->currentDivider_mA = 1;    //
	ina219->powerMultiplier_mW = 20; //

	INA219_setCalibration(ina219, ina219->calibrationValue);
	INA219_setConfig(ina219, config);
}
/**
 *	Calib for 0.1 Ohm Shunt Resistor
 */
void INA219_setCalibration_16V_400mA(INA219_t *ina219)
{
	uint16_t config = INA219_CONFIG_BVOLTAGERANGE_16V |
	                    INA219_CONFIG_GAIN_1_40MV | INA219_CONFIG_BADCRES_12BIT |
	                    INA219_CONFIG_SADCRES_12BIT_1S_532US |
	                    INA219_CONFIG_MODE_SANDBVOLT_CONTINUOUS;

	ina219->calibrationValue = 8192;
	ina219->currentDivider_mA = 20;    // Current LSB = 50uA per bit (1000/50 = 20)
	ina219->powerMultiplier_mW = 1.0f; // Power LSB = 1mW per bit


	INA219_setCalibration(ina219, ina219->calibrationValue);
	INA219_setConfig(ina219, config);
}

void INA219_setPowerMode(INA219_t *ina219, uint8_t Mode)
{
	uint16_t config = INA219_getConfig(ina219);

	switch (Mode) {
		case INA219_CONFIG_MODE_POWERDOWN:
			config = (config & ~INA219_CONFIG_MODE_MASK) | (INA219_CONFIG_MODE_POWERDOWN & INA219_CONFIG_MODE_MASK);
			INA219_setConfig(ina219, config);
			break;

		case INA219_CONFIG_MODE_SANDBVOLT_TRIGGERED:
			config = (config & ~INA219_CONFIG_MODE_MASK) | (INA219_CONFIG_MODE_SANDBVOLT_TRIGGERED & INA219_CONFIG_MODE_MASK);
			INA219_setConfig(ina219, config);
			break;

		case INA219_CONFIG_MODE_SANDBVOLT_CONTINUOUS:
			config = (config & ~INA219_CONFIG_MODE_MASK) | (INA219_CONFIG_MODE_SANDBVOLT_CONTINUOUS & INA219_CONFIG_MODE_MASK);
			INA219_setConfig(ina219, config);
			break;

		case INA219_CONFIG_MODE_ADCOFF:
			config = (config & ~INA219_CONFIG_MODE_MASK) | (INA219_CONFIG_MODE_ADCOFF & INA219_CONFIG_MODE_MASK);
			INA219_setConfig(ina219, config);
			break;
	}
}

uint8_t INA219_Init(INA219_t *ina219, INA219_I2C_Handle *i2c, uint8_t Address)
{
	ina219->ina219_i2c = i2c;
	ina219->Address = Address;

	ina219->currentDivider_mA = 0;
	ina219->powerMultiplier_mW = 0;

	uint8_t ina219_isReady = INA219_DeviceReady(i2c, (Address << 1), 3, 2);

	if(ina219_isReady == HAL_OK)
	{

		INA219_Reset(ina219);
		INA219_setCalibration_32V_2A(ina219);

		return HAL_OK;
	}

	else
	{
		return HAL_ERROR;
	}
}
