#ifndef L3G4200D_L3G4200D_H
#define L3G4200D_L3G4200D_H

#include "l3g4200d_config.h"
#include "l3g4200d_registers.h"

typedef struct {
    l3g4200d_config_t config;
    l3g4200d_interface_t interface;
} l3g4200d_t;

l3g4200d_err_t
l3g4200d_initialize(l3g4200d_t* l3g4200d, l3g4200d_config_t const* config, l3g4200d_interface_t const* interface);
l3g4200d_err_t l3g4200d_deinitialize(l3g4200d_t* l3g4200d);

l3g4200d_err_t l3g4200d_get_gyro_data_x_scaled(l3g4200d_t const* l3g4200d, float32_t* scaled);
l3g4200d_err_t l3g4200d_get_gyro_data_y_scaled(l3g4200d_t const* l3g4200d, float32_t* scaled);
l3g4200d_err_t l3g4200d_get_gyro_data_z_scaled(l3g4200d_t const* l3g4200d, float32_t* scaled);
l3g4200d_err_t l3g4200d_get_gyro_data_scaled(l3g4200d_t const* l3g4200d, vec3_float32_t* scaled);

l3g4200d_err_t l3g4200d_get_temp_data_scaled(l3g4200d_t const* l3g4200d, float32_t* scaled);

l3g4200d_err_t l3g4200d_get_gyro_data_x_raw(l3g4200d_t const* l3g4200d, int16_t* raw);
l3g4200d_err_t l3g4200d_get_gyro_data_y_raw(l3g4200d_t const* l3g4200d, int16_t* raw);
l3g4200d_err_t l3g4200d_get_gyro_data_z_raw(l3g4200d_t const* l3g4200d, int16_t* raw);
l3g4200d_err_t l3g4200d_get_gyro_data_raw(l3g4200d_t const* l3g4200d, vec3_int16_t* raw);

l3g4200d_err_t l3g4200d_get_temp_data_raw(l3g4200d_t const* l3g4200d, int16_t* raw);

l3g4200d_err_t l3g4200d_get_who_am_i_reg(l3g4200d_t const* l3g4200d, l3g4200d_who_am_i_reg_t* reg);

l3g4200d_err_t l3g4200d_get_ctrl1_reg(l3g4200d_t const* l3g4200d, l3g4200d_ctrl1_reg_t* reg);
l3g4200d_err_t l3g4200d_set_ctrl1_reg(l3g4200d_t const* l3g4200d, l3g4200d_ctrl1_reg_t const* reg);

l3g4200d_err_t l3g4200d_get_ctrl2_reg(l3g4200d_t const* l3g4200d, l3g4200d_ctrl2_reg_t* reg);
l3g4200d_err_t l3g4200d_set_ctrl2_reg(l3g4200d_t const* l3g4200d, l3g4200d_ctrl2_reg_t const* reg);

l3g4200d_err_t l3g4200d_get_ctrl3_reg(l3g4200d_t const* l3g4200d, l3g4200d_ctrl3_reg_t* reg);
l3g4200d_err_t l3g4200d_set_ctrl3_reg(l3g4200d_t const* l3g4200d, l3g4200d_ctrl3_reg_t const* reg);

l3g4200d_err_t l3g4200d_get_ctrl4_reg(l3g4200d_t const* l3g4200d, l3g4200d_ctrl4_reg_t* reg);
l3g4200d_err_t l3g4200d_set_ctrl4_reg(l3g4200d_t const* l3g4200d, l3g4200d_ctrl4_reg_t const* reg);

l3g4200d_err_t l3g4200d_get_ctrl5_reg(l3g4200d_t const* l3g4200d, l3g4200d_ctrl5_reg_t* reg);
l3g4200d_err_t l3g4200d_set_ctrl5_reg(l3g4200d_t const* l3g4200d, l3g4200d_ctrl5_reg_t const* reg);

l3g4200d_err_t l3g4200d_get_out_temp_reg(l3g4200d_t const* l3g4200d, l3g4200d_out_temp_reg_t* reg);

l3g4200d_err_t l3g4200d_get_status_reg(l3g4200d_t const* l3g4200d, l3g4200d_status_reg_t* reg);

l3g4200d_err_t l3g4200d_get_out_x_reg(l3g4200d_t const* l3g4200d, l3g4200d_out_x_reg_t* reg);

l3g4200d_err_t l3g4200d_get_out_y_reg(l3g4200d_t const* l3g4200d, l3g4200d_out_y_reg_t* reg);

l3g4200d_err_t l3g4200d_get_out_z_reg(l3g4200d_t const* l3g4200d, l3g4200d_out_z_reg_t* reg);

l3g4200d_err_t l3g4200d_get_out_reg(l3g4200d_t const* l3g4200d, l3g4200d_out_reg_t* reg);

l3g4200d_err_t l3g4200d_get_fifo_ctrl_reg(l3g4200d_t const* l3g4200d, l3g4200d_fifo_ctrl_reg_t* reg);
l3g4200d_err_t l3g4200d_set_fifo_ctrl_reg(l3g4200d_t const* l3g4200d, l3g4200d_fifo_ctrl_reg_t const* reg);

l3g4200d_err_t l3g4200d_get_fifo_src_reg(l3g4200d_t const* l3g4200d, l3g4200d_fifo_src_reg_t* reg);
l3g4200d_err_t l3g4200d_set_fifo_src_reg(l3g4200d_t const* l3g4200d, l3g4200d_fifo_src_reg_t const* reg);

l3g4200d_err_t l3g4200d_get_int1_cfg_reg(l3g4200d_t const* l3g4200d, l3g4200d_int1_cfg_reg_t* reg);
l3g4200d_err_t l3g4200d_set_int1_cfg_reg(l3g4200d_t const* l3g4200d, l3g4200d_int1_cfg_reg_t const* reg);

l3g4200d_err_t l3g4200d_get_int1_src_reg(l3g4200d_t const* l3g4200d, l3g4200d_int1_src_reg_t* reg);
l3g4200d_err_t l3g4200d_set_int1_src_reg(l3g4200d_t const* l3g4200d, l3g4200d_int1_src_reg_t const* reg);

l3g4200d_err_t l3g4200d_get_int1_ths_x_reg(l3g4200d_t const* l3g4200d, l3g4200d_int1_ths_x_reg_t* reg);
l3g4200d_err_t l3g4200d_set_int1_ths_x_reg(l3g4200d_t const* l3g4200d, l3g4200d_int1_ths_x_reg_t const* reg);

l3g4200d_err_t l3g4200d_get_int1_ths_y_reg(l3g4200d_t const* l3g4200d, l3g4200d_int1_ths_y_reg_t* reg);
l3g4200d_err_t l3g4200d_set_int1_ths_y_reg(l3g4200d_t const* l3g4200d, l3g4200d_int1_ths_y_reg_t const* reg);

l3g4200d_err_t l3g4200d_get_int1_ths_z_reg(l3g4200d_t const* l3g4200d, l3g4200d_int1_ths_z_reg_t* reg);
l3g4200d_err_t l3g4200d_set_int1_ths_z_reg(l3g4200d_t const* l3g4200d, l3g4200d_int1_ths_z_reg_t const* reg);

l3g4200d_err_t l3g4200d_get_int1_duration_reg(l3g4200d_t const* l3g4200d, l3g4200d_int1_duration_reg_t* reg);
l3g4200d_err_t l3g4200d_set_int1_duration_reg(l3g4200d_t const* l3g4200d, l3g4200d_int1_duration_reg_t const* reg);

#endif // L3G4200D_L3G4200D_H