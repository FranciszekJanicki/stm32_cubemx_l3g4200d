#ifndef L3G4200D_L3G4200D_REGISTERS_H
#define L3G4200D_L3G4200D_REGISTERS_H

#include <stdint.h>

#define PACKED __attribute__((packed))

typedef struct {
    uint8_t who_am_i : 8;
} PACKED l3g4200d_who_am_i_reg_t;

typedef struct {
    uint8_t dr : 2;
    uint8_t bw : 2;
    uint8_t pd : 1;
    uint8_t z_en : 1;
    uint8_t y_en : 1;
    uint8_t x_en : 1;
} PACKED l3g4200d_ctrl1_reg_t;

typedef struct {
    uint8_t hpm : 2;
    uint8_t hpcf : 4;
} PACKED l3g4200d_ctrl2_reg_t;

typedef struct {
    uint8_t i1_int1 : 1;
    uint8_t i1_boot : 1;
    uint8_t hl_active : 1;
    uint8_t pp_od : 1;
    uint8_t i2_drdy : 1;
    uint8_t i2_wtm : 1;
    uint8_t i2_orun : 1;
    uint8_t i2_empty : 1;
} PACKED l3g4200d_ctrl3_reg_t;

typedef struct {
    uint8_t bdu : 1;
    uint8_t ble : 1;
    uint8_t fs : 2;
    uint8_t st : 2;
    uint8_t sim : 1;
} PACKED l3g4200d_ctrl4_reg_t;

typedef struct {
    uint8_t boot : 1;
    uint8_t fifo_en : 1;
    uint8_t hp_en : 1;
    uint8_t int1_sel : 2;
    uint8_t out_sel : 2;
} PACKED l3g4200d_ctrl5_reg_t;

typedef struct {
    int8_t temp : 8;
} PACKED l3g4200d_out_temp_reg_t;

typedef struct {
    uint8_t zyx_or : 1;
    uint8_t z_or : 1;
    uint8_t y_or : 1;
    uint8_t x_or : 1;
    uint8_t zyx_da : 1;
    uint8_t z_da : 1;
    uint8_t y_da : 1;
    uint8_t x_da : 1;
} PACKED l3g4200d_status_reg_t;

typedef struct {
    int16_t out_x : 16;
} PACKED l3g4200d_out_x_reg_t;

typedef struct {
    int16_t out_y : 16;
} PACKED l3g4200d_out_y_reg_t;

typedef struct {
    int16_t out_z : 16;
} PACKED l3g4200d_out_z_reg_t;

typedef struct {
    int16_t out_x : 16;
    int16_t out_y : 16;
    int16_t out_z : 16;
} PACKED l3g4200d_out_reg_t;

typedef struct {
    uint8_t fm : 3;
    uint8_t wtm : 5;
} PACKED l3g4200d_fifo_ctrl_reg_t;

typedef struct {
    uint8_t wtm : 1;
    uint8_t ovrn : 1;
    uint8_t empty : 1;
    uint8_t fss : 5;
} PACKED l3g4200d_fifo_src_reg_t;

typedef struct {
    uint8_t and_or : 1;
    uint8_t lir : 1;
    uint8_t z_hie : 1;
    uint8_t z_lie : 1;
    uint8_t y_hie : 1;
    uint8_t y_lie : 1;
    uint8_t x_hie : 1;
    uint8_t x_lie : 1;
} PACKED l3g4200d_int1_cfg_reg_t;

typedef struct {
    uint8_t ia : 1;
    uint8_t z_h : 1;
    uint8_t z_l : 1;
    uint8_t y_h : 1;
    uint8_t y_l : 1;
    uint8_t x_h : 1;
    uint8_t x_l : 1;
} PACKED l3g4200d_int1_src_reg_t;

typedef struct {
    int16_t ths_x : 15;
} PACKED l3g4200d_int1_ths_x_reg_t;

typedef struct {
    int16_t ths_y : 15;
} PACKED l3g4200d_int1_ths_y_reg_t;

typedef struct {
    int16_t ths_z : 15;
} PACKED l3g4200d_int1_ths_z_reg_t;

typedef struct {
    uint8_t wait : 1;
    uint8_t d : 7;
} PACKED l3g4200d_int1_duration_reg_t;

#undef PACKED

#endif // L3G4200D_L3G4200D_REGISTERS_H