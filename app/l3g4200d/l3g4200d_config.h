#ifndef L3G4200D_L3G4200D_CONFIG_H
#define L3G4200D_L3G4200D_CONFIG_H

#include "l3g4200d_registers.h"
#include <stddef.h>
#include <stdint.h>

#define L3G4200D_DEVICE_ID 0b11010011

typedef float float32_t;

typedef struct {
    int16_t x;
    int16_t y;
    int16_t z;
} vec3_int16_t;

typedef struct {
    float32_t x;
    float32_t y;
    float32_t z;
} vec3_float32_t;

typedef enum {
    L3G4200D_ERR_OK = 0,
    L3G4200D_ERR_FAIL = 1 << 0,
    L3G4200D_ERR_NULL = 1 << 1,
} l3g4200d_err_t;

typedef enum {
    L3G4200D_REG_ADDR_WHO_AM_I = 0x0F,
    L3G4200D_REG_ADDR_CTRL1 = 0x20,
    L3G4200D_REG_ADDR_CTRL2 = 0x21,
    L3G4200D_REG_ADDR_CTRL3 = 0x22,
    L3G4200D_REG_ADDR_CTRL4 = 0x23,
    L3G4200D_REG_ADDR_CTRL5 = 0x24,
    L3G4200D_REG_ADDR_REFERENCE = 0x25,
    L3G4200D_REG_ADDR_OUT_TEMP = 0x26,
    L3G4200D_REG_ADDR_STATUS = 0x27,
    L3G4200D_REG_ADDR_OUT_X_L = 0x28,
    L3G4200D_REG_ADDR_OUT_X_H = 0x29,
    L3G4200D_REG_ADDR_OUT_Y_L = 0x2A,
    L3G4200D_REG_ADDR_OUT_Y_H = 0x2B,
    L3G4200D_REG_ADDR_OUT_Z_L = 0x2C,
    L3G4200D_REG_ADDR_OUT_Z_H = 0x2D,
    L3G4200D_REG_ADDR_FIFO_CTRL = 0x2E,
    L3G4200D_REG_ADDR_FIFO_SRC = 0x2F,
    L3G4200D_REG_ADDR_INT1_CFG = 0x30,
    L3G4200D_REG_ADDR_INT1_SRC = 0x31,
    L3G4200D_REG_ADDR_INT1_THS_XH = 0x32,
    L3G4200D_REG_ADDR_INT1_THS_XL = 0x33,
    L3G4200D_REG_ADDR_INT1_THS_YH = 0x34,
    L3G4200D_REG_ADDR_INT1_THS_YL = 0x35,
    L3G4200D_REG_ADDR_INT1_THS_ZH = 0x36,
    L3G4200D_REG_ADDR_INT1_THS_ZL = 0x37,
    L3G4200D_REG_ADDR_INT1_DURATION = 0x38,
} l3g4200d_reg_addr_t;

typedef enum {
    L3G4200D_DEV_ADDR_SD0_LOW = 0b1101000,
    L3G4200D_DEV_ADDR_SD0_HIGH = 0b1101001,
} l3g4200d_dev_addr_t;

typedef enum {
    L3G4200D_MODE_BYPASS,
    L3G4200D_MODE_FIFO,
    L3G4200D_MODE_STREAM,
    L3G4200D_MODE_BYPASS_TO_STREAM,
    L3G4200D_MODE_STREAM_TO_FIFO,
} l3g4200d_mode_t;

typedef enum {
    L3G4200D_OUTPUT_DATA_RATE_100HZ = 0b00,
    L3G4200D_OUTPUT_DATA_RATE_200HZ = 0b01,
    L3G4200D_OUTPUT_DATA_RATE_400HZ = 0b10,
    L3G4200D_OUTPUT_DATA_RATE_800HZ = 0b11,
} l3g4200d_output_data_rate_t;

typedef enum {
    L3G4200D_BANDWIDTH_12HZ5 = 0b00,
    L3G4200D_BANDWIDTH_25HZ = 0b01,
    L3G4200D_BANDWIDTH_50HZ = 0b10,
    L3G4200D_BANDWIDTH_70HZ = 0b11,
    L3G4200D_BANDWIDTH_20HZ = 0b00,
    L3G4200D_BANDWIDTH_110HZ = 0b11,
    L3G4200D_BANDWIDTH_30HZ = 0b00,
    L3G4200D_BANDWIDTH_35HZ = 0b01,
} l3g4200d_bandwidth_t;

typedef enum HPFMode {
    L3G4200D_HPF_MODE_NORMAL_RR = 0b00,
    L3G4200D_HPF_MODE_REFERENCE = 0b01,
    L3G4200D_HPF_MODE_NORMAL = 0b10,
    L3G4200D_HPF_MODE_AUTORSEET = 0b11,
} l3g4200d_hpf_mode_t;

typedef enum Range {
    L3G4200D_FULL_SCALE_RANGE_250DPS = 0b00,
    L3G4200D_FULL_SCALE_RANGE_500DPS = 0b01,
    L3G4200D_FULL_SCALE_RANGE_2000DPS = 0b11,
} l3g4200d_full_scale_range_t;

typedef enum {
    L3G4200D_SELF_TEST_NORMAL_MODE = 0b00,
    L3G4200D_SELF_TEST_SELT_TEST_0 = 0b01,
    L3G4200D_SELF_TEST_DISABLED = 0b10,
    L3G4200D_SELF_TEST_SELF_TEST_1 = 0b11,
} l3g4200d_self_test_T;

typedef struct {
    float32_t scale;
} l3g4200d_config_t;

typedef struct {
    void* bus_user;
    l3g4200d_err_t (*bus_init)(void*);
    l3g4200d_err_t (*bus_deinit)(void*);
    l3g4200d_err_t (*bus_write)(void*, uint8_t, uint8_t const*, size_t);
    l3g4200d_err_t (*bus_read)(void*, uint8_t, uint8_t*, size_t);
} l3g4200d_interface_t;

inline float32_t l3g4200d_range_to_scale(l3g4200d_full_scale_range_t range)
{
    switch (range) {
        case L3G4200D_FULL_SCALE_RANGE_250DPS:
            return 0.00762F;
        case L3G4200D_FULL_SCALE_RANGE_500DPS:
            return 0.01524F;
        case L3G4200D_FULL_SCALE_RANGE_2000DPS:
            return 0.06096F;
        default:
            return 0.0F;
    }
}

#endif // L3G4200D_L3G4200D_CONFIG_H