#include "l3g4200d.h"
#include <assert.h>
#include <string.h>

static l3g4200d_err_t l3g4200d_bus_init(l3g4200d_t const* l3g4200d)
{
    assert(l3g4200d);

    if (l3g4200d->interface.bus_init) {
        return l3g4200d->interface.bus_init(l3g4200d->interface.bus_user);
    }

    return L3G4200D_ERR_NULL;
}

static l3g4200d_err_t l3g4200d_bus_deinit(l3g4200d_t const* l3g4200d)
{
    assert(l3g4200d);

    if (l3g4200d->interface.bus_deinit) {
        return l3g4200d->interface.bus_deinit(l3g4200d->interface.bus_user);
    }

    return L3G4200D_ERR_NULL;
}

static l3g4200d_err_t
l3g4200d_bus_write(l3g4200d_t const* l3g4200d, uint8_t write_address, uint8_t const* write_data, size_t write_size)
{
    assert(l3g4200d && write_data);

    if (l3g4200d->interface.bus_write) {
        return l3g4200d->interface.bus_write(l3g4200d->interface.bus_user, write_address, write_data, write_size);
    }

    return L3G4200D_ERR_NULL;
}

static l3g4200d_err_t
l3g4200d_bus_read(l3g4200d_t const* l3g4200d, uint8_t read_address, uint8_t* read_data, size_t read_size)
{
    assert(l3g4200d && read_data);

    if (l3g4200d->interface.bus_read) {
        return l3g4200d->interface.bus_read(l3g4200d->interface.bus_user, read_address, read_data, read_size);
    }

    return L3G4200D_ERR_NULL;
}

l3g4200d_err_t
l3g4200d_initialize(l3g4200d_t* l3g4200d, l3g4200d_config_t const* config, l3g4200d_interface_t const* interface)
{
    assert(l3g4200d && config && interface);

    memset(l3g4200d, 0, sizeof(*l3g4200d));
    memcpy(&l3g4200d->config, config, sizeof(*config));
    memcpy(&l3g4200d->interface, interface, sizeof(*interface));

    return l3g4200d_bus_init(l3g4200d);
}

l3g4200d_err_t l3g4200d_deinitialize(l3g4200d_t* l3g4200d)
{
    assert(l3g4200d);

    l3g4200d_err_t err = l3g4200d_bus_deinit(l3g4200d);

    memset(l3g4200d, 0, sizeof(*l3g4200d));

    return err;
}

l3g4200d_err_t l3g4200d_get_gyro_data_x_scaled(l3g4200d_t const* l3g4200d, float32_t* scaled)
{
    assert(l3g4200d && scaled);

    int16_t raw = {};

    l3g4200d_err_t err = l3g4200d_get_gyro_data_x_raw(l3g4200d, &raw);

    *scaled = (float32_t)raw * l3g4200d->config.scale;

    return err;
}

l3g4200d_err_t l3g4200d_get_gyro_data_y_scaled(l3g4200d_t const* l3g4200d, float32_t* scaled)
{
    assert(l3g4200d && scaled);

    int16_t raw = {};

    l3g4200d_err_t err = l3g4200d_get_gyro_data_y_raw(l3g4200d, &raw);

    *scaled = (float32_t)raw * l3g4200d->config.scale;

    return err;
}

l3g4200d_err_t l3g4200d_get_gyro_data_z_scaled(l3g4200d_t const* l3g4200d, float32_t* scaled)
{
    assert(l3g4200d && scaled);

    int16_t raw = {};

    l3g4200d_err_t err = l3g4200d_get_gyro_data_z_raw(l3g4200d, &raw);

    *scaled = (float32_t)raw * l3g4200d->config.scale;

    return err;
}

l3g4200d_err_t l3g4200d_get_gyro_data_scaled(l3g4200d_t const* l3g4200d, vec3_float32_t* scaled)
{
    assert(l3g4200d && scaled);

    vec3_int16_t raw = {};

    l3g4200d_err_t err = l3g4200d_get_gyro_data_raw(l3g4200d, &raw);

    scaled->x = (float32_t)raw.x * l3g4200d->config.scale;
    scaled->y = (float32_t)raw.y * l3g4200d->config.scale;
    scaled->z = (float32_t)raw.z * l3g4200d->config.scale;

    return err;
}

l3g4200d_err_t l3g4200d_get_temp_data_scaled(l3g4200d_t const* l3g4200d, float32_t* scaled)
{
    assert(l3g4200d && scaled);

    int16_t raw = {};

    l3g4200d_err_t err = l3g4200d_get_temp_data_raw(l3g4200d, &raw);

    *scaled = ((float32_t)raw + 128.0F) * 125.0F / 255.0F - 40.0F;

    return err;
}

l3g4200d_err_t l3g4200d_get_gyro_data_x_raw(l3g4200d_t const* l3g4200d, int16_t* raw)
{
    assert(l3g4200d && raw);

    l3g4200d_out_x_reg_t reg = {};

    l3g4200d_err_t err = l3g4200d_get_out_x_reg(l3g4200d, &reg);

    *raw = (reg.out_x_15to8 << 8) | (reg.out_x_7to0 << 0);

    return err;
}

l3g4200d_err_t l3g4200d_get_gyro_data_y_raw(l3g4200d_t const* l3g4200d, int16_t* raw)
{
    assert(l3g4200d && raw);

    l3g4200d_out_y_reg_t reg = {};

    l3g4200d_err_t err = l3g4200d_get_out_y_reg(l3g4200d, &reg);

    *raw = (reg.out_y_15to8 << 8) | (reg.out_y_7to0 << 0);

    return err;
}

l3g4200d_err_t l3g4200d_get_gyro_data_z_raw(l3g4200d_t const* l3g4200d, int16_t* raw)
{
    assert(l3g4200d && raw);

    l3g4200d_out_z_reg_t reg = {};

    l3g4200d_err_t err = l3g4200d_get_out_z_reg(l3g4200d, &reg);

    *raw = (reg.out_z_15to8 << 8) | (reg.out_z_7to0 << 0);

    return err;
}

l3g4200d_err_t l3g4200d_get_gyro_data_raw(l3g4200d_t const* l3g4200d, vec3_int16_t* raw)
{
    assert(l3g4200d && raw);

    l3g4200d_out_reg_t reg = {};

    l3g4200d_err_t err = l3g4200d_get_out_reg(l3g4200d, &reg);

    raw->x = (reg.out_x_15to8 << 8) | (reg.out_x_7to0 << 0);
    raw->y = (reg.out_y_15to8 << 8) | (reg.out_y_7to0 << 0);
    raw->z = (reg.out_z_15to8 << 8) | (reg.out_z_7to0 << 0);

    return err;
}

l3g4200d_err_t l3g4200d_get_temp_data_raw(l3g4200d_t const* l3g4200d, int16_t* raw)
{
    assert(l3g4200d && raw);

    l3g4200d_out_temp_reg_t reg = {};

    l3g4200d_err_t err = l3g4200d_get_out_temp_reg(l3g4200d, &reg);

    *raw = (reg.temp_7to0 << 0);

    return err;
}

l3g4200d_err_t l3g4200d_get_who_am_i_reg(l3g4200d_t const* l3g4200d, l3g4200d_who_am_i_reg_t* reg)
{
    assert(l3g4200d && reg);

    uint8_t data[1] = {};

    l3g4200d_err_t err = l3g4200d_bus_read(l3g4200d, L3G4200D_REG_ADDR_WHO_AM_I, data, sizeof(data));

    reg->who_am_i = (data[0] >> 0U) & 0xFFU;

    return err;
}

l3g4200d_err_t l3g4200d_get_ctrl1_reg(l3g4200d_t const* l3g4200d, l3g4200d_ctrl1_reg_t* reg)
{
    assert(l3g4200d && reg);

    uint8_t data[1] = {};

    l3g4200d_err_t err = l3g4200d_bus_read(l3g4200d, L3G4200D_REG_ADDR_CTRL1, data, sizeof(data));

    reg->dr = (data[0] >> 6U) & 0x03U;
    reg->bw = (data[0] >> 4U) & 0x03U;
    reg->pd = (data[0] >> 3U) & 0x01U;
    reg->z_en = (data[0] >> 2U) & 0x01U;
    reg->y_en = (data[0] >> 1U) & 0x01U;
    reg->x_en = (data[0] >> 0U) & 0x01U;

    return err;
}

l3g4200d_err_t l3g4200d_set_ctrl1_reg(l3g4200d_t const* l3g4200d, l3g4200d_ctrl1_reg_t const* reg)
{
    assert(l3g4200d && reg);

    uint8_t data[1] = {};

    data[0] |= (reg->dr & 0x03U) << 6U;
    data[0] |= (reg->bw & 0x03U) << 4U;
    data[0] |= (reg->pd & 0x01U) << 3U;
    data[0] |= (reg->z_en & 0x01U) << 2U;
    data[0] |= (reg->y_en & 0x01U) << 1U;
    data[0] |= (reg->x_en & 0x01U) << 0U;

    l3g4200d_err_t err = l3g4200d_bus_write(l3g4200d, L3G4200D_REG_ADDR_CTRL1, data, sizeof(data));

    return err;
}

l3g4200d_err_t l3g4200d_get_ctrl2_reg(l3g4200d_t const* l3g4200d, l3g4200d_ctrl2_reg_t* reg)
{
    assert(l3g4200d && reg);

    uint8_t data[1] = {};

    l3g4200d_err_t err = l3g4200d_bus_read(l3g4200d, L3G4200D_REG_ADDR_CTRL2, data, sizeof(data));

    reg->hpm = (data[0] >> 4U) & 0x03U;
    reg->hpcf = (data[0] >> 0U) & 0x0FU;

    return err;
}

l3g4200d_err_t l3g4200d_set_ctrl2_reg(l3g4200d_t const* l3g4200d, l3g4200d_ctrl2_reg_t const* reg)
{
    assert(l3g4200d && reg);

    uint8_t data[1] = {};

    data[0] |= (reg->hpm & 0x03U) << 4U;
    data[0] |= (reg->hpcf & 0x0FU) << 0U;

    l3g4200d_err_t err = l3g4200d_bus_write(l3g4200d, L3G4200D_REG_ADDR_CTRL2, data, sizeof(data));

    return err;
}

l3g4200d_err_t l3g4200d_get_ctrl3_reg(l3g4200d_t const* l3g4200d, l3g4200d_ctrl3_reg_t* reg)
{
    assert(l3g4200d && reg);

    uint8_t data[1] = {};

    l3g4200d_err_t err = l3g4200d_bus_read(l3g4200d, L3G4200D_REG_ADDR_CTRL3, data, sizeof(data));

    reg->i1_int1 = (data[0] >> 7U) & 0x01U;
    reg->i1_boot = (data[0] >> 6U) & 0x01U;
    reg->hl_active = (data[0] >> 5U) & 0x01U;
    reg->pp_od = (data[0] >> 4U) & 0x01U;
    reg->i2_drdy = (data[0] >> 3U) & 0x01U;
    reg->i2_wtm = (data[0] >> 2U) & 0x01U;
    reg->i2_orun = (data[0] >> 1U) & 0x01U;
    reg->i2_empty = (data[0] >> 0U) & 0x01U;

    return err;
}

l3g4200d_err_t l3g4200d_set_ctrl3_reg(l3g4200d_t const* l3g4200d, l3g4200d_ctrl3_reg_t const* reg)
{
    assert(l3g4200d && reg);

    uint8_t data[1] = {};

    data[0] |= (reg->i1_int1 & 0x01U) << 7U;
    data[0] |= (reg->i1_boot & 0x01U) << 6U;
    data[0] |= (reg->hl_active & 0x01U) << 5U;
    data[0] |= (reg->pp_od & 0x01U) << 4U;
    data[0] |= (reg->i2_drdy & 0x01U) << 3U;
    data[0] |= (reg->i2_wtm & 0x01U) << 2U;
    data[0] |= (reg->i2_orun & 0x01U) << 1U;
    data[0] |= (reg->i2_empty & 0x01U) << 0U;

    l3g4200d_err_t err = l3g4200d_bus_read(l3g4200d, L3G4200D_REG_ADDR_CTRL3, data, sizeof(data));

    return err;
}

l3g4200d_err_t l3g4200d_get_ctrl4_reg(l3g4200d_t const* l3g4200d, l3g4200d_ctrl4_reg_t* reg)
{
    assert(l3g4200d && reg);

    uint8_t data[1] = {};

    l3g4200d_err_t err = l3g4200d_bus_read(l3g4200d, L3G4200D_REG_ADDR_CTRL4, data, sizeof(data));

    reg->bdu = (data[0] >> 7U) & 0x01U;
    reg->ble = (data[0] >> 6U) & 0x01U;
    reg->fs = (data[0] >> 4U) & 0x03U;
    reg->st = (data[0] >> 1U) & 0x03U;
    reg->sim = (data[0] >> 0U) & 0x01U;

    return err;
}

l3g4200d_err_t l3g4200d_set_ctrl4_reg(l3g4200d_t const* l3g4200d, l3g4200d_ctrl4_reg_t const* reg)
{
    assert(l3g4200d && reg);

    uint8_t data[1] = {};

    l3g4200d_err_t err = l3g4200d_bus_read(l3g4200d, L3G4200D_REG_ADDR_CTRL4, data, sizeof(data));

    data[0] &= ~(0x01U << 7U);
    data[0] &= ~(0x01U << 6U);
    data[0] &= ~(0x03U << 4U);
    data[0] &= ~(0x03U << 1U);
    data[0] &= ~(0x01U << 0U);

    data[0] |= (reg->bdu & 0x01U) << 7U;
    data[0] |= (reg->ble & 0x01U) << 6U;
    data[0] |= (reg->fs & 0x03U) << 4U;
    data[0] |= (reg->ble & 0x03U) << 1U;
    data[0] |= (reg->ble & 0x01U) << 0U;

    err |= l3g4200d_bus_write(l3g4200d, L3G4200D_REG_ADDR_CTRL4, data, sizeof(data));

    return err;
}

l3g4200d_err_t l3g4200d_get_ctrl5_reg(l3g4200d_t const* l3g4200d, l3g4200d_ctrl5_reg_t* reg)
{
    assert(l3g4200d && reg);

    uint8_t data[1] = {};

    l3g4200d_err_t err = l3g4200d_bus_read(l3g4200d, L3G4200D_REG_ADDR_CTRL5, data, sizeof(data));

    reg->boot = (data[0] >> 7U) & 0x01U;
    reg->fifo_en = (data[0] >> 6U) & 0x01U;
    reg->hp_en = (data[0] >> 4U) & 0x01U;
    reg->int1_sel = (data[0] >> 2U) & 0x03U;
    reg->out_sel = (data[0] >> 0U) & 0x03U;

    return err;
}

l3g4200d_err_t l3g4200d_set_ctrl5_reg(l3g4200d_t const* l3g4200d, l3g4200d_ctrl5_reg_t const* reg)
{
    assert(l3g4200d && reg);

    uint8_t data[1] = {};

    l3g4200d_err_t err = l3g4200d_bus_read(l3g4200d, L3G4200D_REG_ADDR_CTRL5, data, sizeof(data));

    data[0] &= ~(0x01U << 7U);
    data[0] &= ~(0x01U << 6U);
    data[0] &= ~(0x01U << 4U);
    data[0] &= ~(0x03U << 2U);
    data[0] &= ~(0x03U << 0U);

    data[0] |= (reg->boot & 0x01U) << 7U;
    data[0] |= (reg->fifo_en & 0x01U) << 6U;
    data[0] |= (reg->hp_en & 0x01U) << 4U;
    data[0] |= (reg->int1_sel & 0x03U) << 2U;
    data[0] |= (reg->out_sel & 0x03U) << 0U;

    err |= l3g4200d_bus_write(l3g4200d, L3G4200D_REG_ADDR_CTRL5, data, sizeof(data));

    return err;
}

l3g4200d_err_t l3g4200d_get_out_temp_reg(l3g4200d_t const* l3g4200d, l3g4200d_out_temp_reg_t* reg)
{
    assert(l3g4200d && reg);

    uint8_t data[1] = {};

    l3g4200d_err_t err = l3g4200d_bus_read(l3g4200d, L3G4200D_REG_ADDR_WHO_AM_I, data, sizeof(data));

    reg->temp_7to0 = (int8_t)((data[0] >> 0) & 0xFF);

    return err;
}

l3g4200d_err_t l3g4200d_get_status_reg(l3g4200d_t const* l3g4200d, l3g4200d_status_reg_t* reg)
{
    assert(l3g4200d && reg);

    uint8_t data[1] = {};

    l3g4200d_err_t err = l3g4200d_bus_read(l3g4200d, L3G4200D_REG_ADDR_STATUS, data, sizeof(data));

    reg->zyx_or = (data[0] >> 7U) & 0x01U;
    reg->z_or = (data[0] >> 6U) & 0x01U;
    reg->y_or = (data[0] >> 5U) & 0x01U;
    reg->x_or = (data[0] >> 4U) & 0x01U;
    reg->zyx_da = (data[0] >> 3U) & 0x01U;
    reg->z_da = (data[0] >> 2U) & 0x01U;
    reg->y_da = (data[0] >> 1U) & 0x01U;
    reg->x_da = (data[0] >> 0U) & 0x01U;

    return err;
}

l3g4200d_err_t l3g4200d_get_out_x_reg(l3g4200d_t const* l3g4200d, l3g4200d_out_x_reg_t* reg)
{
    assert(l3g4200d && reg);

    uint8_t data[2] = {};

    l3g4200d_err_t err = l3g4200d_bus_read(l3g4200d, L3G4200D_REG_ADDR_OUT_X_L, data, sizeof(data));

    reg->out_x_7to0 = (int8_t)((data[0] >> 0) & 0xFF);
    reg->out_x_15to8 = (int8_t)((data[1] >> 0) & 0xFF);

    return err;
}

l3g4200d_err_t l3g4200d_get_out_y_reg(l3g4200d_t const* l3g4200d, l3g4200d_out_y_reg_t* reg)
{
    assert(l3g4200d && reg);

    uint8_t data[2] = {};

    l3g4200d_err_t err = l3g4200d_bus_read(l3g4200d, L3G4200D_REG_ADDR_OUT_Y_L, data, sizeof(data));

    reg->out_y_7to0 = (int8_t)((data[0] >> 0) & 0xFF);
    reg->out_y_15to8 = (int8_t)((data[1] >> 0) & 0xFF);

    return err;
}

l3g4200d_err_t l3g4200d_get_out_z_reg(l3g4200d_t const* l3g4200d, l3g4200d_out_z_reg_t* reg)
{
    assert(l3g4200d && reg);

    uint8_t data[2] = {};

    l3g4200d_err_t err = l3g4200d_bus_read(l3g4200d, L3G4200D_REG_ADDR_OUT_Z_L, data, sizeof(data));

    reg->out_z_7to0 = (int8_t)((data[0] >> 0) & 0xFF);
    reg->out_z_15to8 = (int8_t)((data[1] >> 0) & 0xFF);

    return err;
}

l3g4200d_err_t l3g4200d_get_out_reg(l3g4200d_t const* l3g4200d, l3g4200d_out_reg_t* reg)
{
    assert(l3g4200d && reg);

    uint8_t data[6] = {};

    l3g4200d_err_t err = l3g4200d_bus_read(l3g4200d, L3G4200D_REG_ADDR_OUT_X_L, data, sizeof(data));

    reg->out_x_7to0 = (int8_t)((data[0] >> 0) & 0xFF);
    reg->out_x_15to8 = (int8_t)((data[1] >> 0) & 0xFF);
    reg->out_y_7to0 = (int8_t)((data[2] >> 0) & 0xFF);
    reg->out_y_15to8 = (int8_t)((data[3] >> 0) & 0xFF);
    reg->out_z_7to0 = (int8_t)((data[4] >> 0) & 0xFF);
    reg->out_z_15to8 = (int8_t)((data[5] >> 0) & 0xFF);

    return err;
}

l3g4200d_err_t l3g4200d_get_fifo_ctrl_reg(l3g4200d_t const* l3g4200d, l3g4200d_fifo_ctrl_reg_t* reg)
{
    assert(l3g4200d && reg);

    uint8_t data[1] = {};

    l3g4200d_err_t err = l3g4200d_bus_read(l3g4200d, L3G4200D_REG_ADDR_FIFO_CTRL, data, sizeof(data));

    reg->fm = (data[0] >> 5U) & 0x07U;
    reg->wtm = (data[0] >> 0U) & 0x1FU;

    return err;
}

l3g4200d_err_t l3g4200d_set_fifo_ctrl_reg(l3g4200d_t const* l3g4200d, l3g4200d_fifo_ctrl_reg_t const* reg)
{
    assert(l3g4200d && reg);

    uint8_t data[1] = {};

    data[0] |= (reg->fm & 0x07U) << 5U;
    data[0] |= (reg->wtm & 0x1FU) << 0U;

    l3g4200d_err_t err = l3g4200d_bus_write(l3g4200d, L3G4200D_REG_ADDR_FIFO_CTRL, data, sizeof(data));

    return err;
}

l3g4200d_err_t l3g4200d_get_fifo_src_reg(l3g4200d_t const* l3g4200d, l3g4200d_fifo_src_reg_t* reg)
{
    assert(l3g4200d && reg);

    uint8_t data[1] = {};

    l3g4200d_err_t err = l3g4200d_bus_read(l3g4200d, L3G4200D_REG_ADDR_FIFO_SRC, data, sizeof(data));

    reg->wtm = (data[0] >> 7U) & 0x01U;
    reg->ovrn = (data[0] >> 6U) & 0x01U;
    reg->empty = (data[0] >> 5U) & 0x01U;
    reg->fss = (data[0] >> 0U) & 0x1FU;

    return err;
}

l3g4200d_err_t l3g4200d_set_fifo_src_reg(l3g4200d_t const* l3g4200d, l3g4200d_fifo_src_reg_t const* reg)
{
    assert(l3g4200d && reg);

    uint8_t data[1] = {};

    data[0] |= (reg->wtm & 0x01U) << 7U;
    data[0] |= (reg->ovrn & 0x01U) << 6U;
    data[0] |= (reg->empty & 0x01U) << 5U;
    data[0] |= (reg->fss & 0x1FU) << 0U;

    l3g4200d_err_t err = l3g4200d_bus_write(l3g4200d, L3G4200D_REG_ADDR_FIFO_SRC, data, sizeof(data));

    return err;
}

l3g4200d_err_t l3g4200d_get_int1_cfg_reg(l3g4200d_t const* l3g4200d, l3g4200d_int1_cfg_reg_t* reg)
{
    assert(l3g4200d && reg);

    uint8_t data[1] = {};

    l3g4200d_err_t err = l3g4200d_bus_read(l3g4200d, L3G4200D_REG_ADDR_INT1_CFG, data, sizeof(data));

    reg->and_or = (data[0] >> 7U) & 0x01U;
    reg->lir = (data[0] >> 6U) & 0x01U;
    reg->z_hie = (data[0] >> 5U) & 0x01U;
    reg->z_lie = (data[0] >> 4U) & 0x01U;
    reg->y_hie = (data[0] >> 3U) & 0x01U;
    reg->y_lie = (data[0] >> 2U) & 0x01U;
    reg->x_hie = (data[0] >> 1U) & 0x01U;
    reg->x_lie = (data[0] >> 0U) & 0x01U;

    return err;
}

l3g4200d_err_t l3g4200d_set_int1_cfg_reg(l3g4200d_t const* l3g4200d, l3g4200d_int1_cfg_reg_t const* reg)
{
    assert(l3g4200d && reg);

    uint8_t data[1] = {};

    data[0] |= (reg->and_or & 0x01U) << 7U;
    data[0] |= (reg->lir & 0x01U) << 6U;
    data[0] |= (reg->z_hie & 0x01U) << 5U;
    data[0] |= (reg->z_lie & 0x01U) << 4U;
    data[0] |= (reg->y_hie & 0x01U) << 3U;
    data[0] |= (reg->y_lie & 0x01U) << 2U;
    data[0] |= (reg->x_hie & 0x01U) << 1U;
    data[0] |= (reg->x_lie & 0x01U) << 0U;

    l3g4200d_err_t err = l3g4200d_bus_write(l3g4200d, L3G4200D_REG_ADDR_INT1_CFG, data, sizeof(data));

    return err;
}

l3g4200d_err_t l3g4200d_get_int1_src_reg(l3g4200d_t const* l3g4200d, l3g4200d_int1_src_reg_t* reg)
{
    assert(l3g4200d && reg);

    uint8_t data[1] = {};

    l3g4200d_err_t err = l3g4200d_bus_read(l3g4200d, L3G4200D_REG_ADDR_INT1_SRC, data, sizeof(data));

    reg->ia = (data[0] >> 6U) & 0x01U;
    reg->z_h = (data[0] >> 5U) & 0x01U;
    reg->z_l = (data[0] >> 4U) & 0x01U;
    reg->y_h = (data[0] >> 3U) & 0x01U;
    reg->y_l = (data[0] >> 2U) & 0x01U;
    reg->x_h = (data[0] >> 1U) & 0x01U;
    reg->x_l = (data[0] >> 0U) & 0x01U;

    return err;
}

l3g4200d_err_t l3g4200d_set_int1_src_reg(l3g4200d_t const* l3g4200d, l3g4200d_int1_src_reg_t const* reg)
{
    assert(l3g4200d && reg);

    uint8_t data[1] = {};

    l3g4200d_err_t err = l3g4200d_bus_read(l3g4200d, L3G4200D_REG_ADDR_INT1_SRC, data, sizeof(data));

    data[0] &= ~(0x01U << 6U);
    data[0] &= ~(0x01U << 5U);
    data[0] &= ~(0x01U << 4U);
    data[0] &= ~(0x01U << 3U);
    data[0] &= ~(0x01U << 2U);
    data[0] &= ~(0x01U << 1U);
    data[0] &= ~(0x01U << 0U);

    data[0] |= (reg->ia & 0x01U) << 6U;
    data[0] |= (reg->z_h & 0x01U) << 5U;
    data[0] |= (reg->z_l & 0x01U) << 4U;
    data[0] |= (reg->y_h & 0x01U) << 3U;
    data[0] |= (reg->y_l & 0x01U) << 2U;
    data[0] |= (reg->x_h & 0x01U) << 1U;
    data[0] |= (reg->x_l & 0x01U) << 0U;

    err |= l3g4200d_bus_write(l3g4200d, L3G4200D_REG_ADDR_INT1_SRC, data, sizeof(data));

    return err;
}

l3g4200d_err_t l3g4200d_get_int1_ths_x_reg(l3g4200d_t const* l3g4200d, l3g4200d_int1_ths_x_reg_t* reg)
{
    assert(l3g4200d && reg);

    uint8_t data[2] = {};

    l3g4200d_err_t err = l3g4200d_bus_read(l3g4200d, L3G4200D_REG_ADDR_INT1_THS_XH, data, sizeof(data));

    reg->ths_x_8to14 = (int8_t)((data[0] >> 0) & 0x7F);
    reg->ths_x_7to0 = (int8_t)((data[1] >> 0) & 0xFF);

    return err;
}

l3g4200d_err_t l3g4200d_set_int1_ths_x_reg(l3g4200d_t const* l3g4200d, l3g4200d_int1_ths_x_reg_t const* reg)
{
    assert(l3g4200d && reg);

    uint8_t data[2] = {};

    l3g4200d_err_t err = l3g4200d_bus_read(l3g4200d, L3G4200D_REG_ADDR_INT1_THS_XH, data, sizeof(data));

    data[0] |= (uint8_t)((reg->ths_x_8to14 & 0x7F) << 0);
    data[1] |= (uint8_t)((reg->ths_x_7to0 & 0xFF) << 0);

    err |= l3g4200d_bus_write(l3g4200d, L3G4200D_REG_ADDR_INT1_THS_XH, data, sizeof(data));

    return err;
}

l3g4200d_err_t l3g4200d_get_int1_ths_y_reg(l3g4200d_t const* l3g4200d, l3g4200d_int1_ths_y_reg_t* reg)
{
    assert(l3g4200d && reg);

    uint8_t data[2] = {};

    l3g4200d_err_t err = l3g4200d_bus_read(l3g4200d, L3G4200D_REG_ADDR_INT1_THS_YH, data, sizeof(data));

    reg->ths_y_8to14 = (int8_t)((data[0] >> 0) & 0x7F);
    reg->ths_y_7to0 = (int8_t)((data[1] >> 0) & 0xFF);

    return err;
}

l3g4200d_err_t l3g4200d_set_int1_ths_y_reg(l3g4200d_t const* l3g4200d, l3g4200d_int1_ths_y_reg_t const* reg)
{
    assert(l3g4200d && reg);

    uint8_t data[2] = {};

    l3g4200d_err_t err = l3g4200d_bus_read(l3g4200d, L3G4200D_REG_ADDR_INT1_THS_YH, data, sizeof(data));

    data[0] |= (uint8_t)((reg->ths_y_8to14 & 0x7F) << 0);
    data[1] |= (uint8_t)((reg->ths_y_7to0 & 0xFF) << 0);

    err |= l3g4200d_bus_write(l3g4200d, L3G4200D_REG_ADDR_INT1_THS_YH, data, sizeof(data));

    return err;
}

l3g4200d_err_t l3g4200d_get_int1_ths_z_reg(l3g4200d_t const* l3g4200d, l3g4200d_int1_ths_z_reg_t* reg)
{
    assert(l3g4200d && reg);

    uint8_t data[2] = {};

    l3g4200d_err_t err = l3g4200d_bus_read(l3g4200d, L3G4200D_REG_ADDR_INT1_THS_ZH, data, sizeof(data));

    reg->ths_z_8to14 = (int8_t)((data[0] >> 0) & 0x7F);
    reg->ths_z_7to0 = (int8_t)((data[1] >> 0) & 0xFF);

    return err;
}

l3g4200d_err_t l3g4200d_set_int1_ths_z_reg(l3g4200d_t const* l3g4200d, l3g4200d_int1_ths_z_reg_t const* reg)
{
    assert(l3g4200d && reg);

    uint8_t data[2] = {};

    l3g4200d_err_t err = l3g4200d_bus_read(l3g4200d, L3G4200D_REG_ADDR_INT1_THS_ZH, data, sizeof(data));

    data[0] |= (uint8_t)((reg->ths_z_8to14 & 0x7F) << 0);
    data[1] |= (uint8_t)((reg->ths_z_7to0 & 0xFF) << 0);

    err |= l3g4200d_bus_write(l3g4200d, L3G4200D_REG_ADDR_INT1_THS_ZH, data, sizeof(data));

    return err;
}

l3g4200d_err_t l3g4200d_get_int1_duration_reg(l3g4200d_t const* l3g4200d, l3g4200d_int1_duration_reg_t* reg)
{
    assert(l3g4200d && reg);

    uint8_t data[1] = {};

    l3g4200d_err_t err = l3g4200d_bus_read(l3g4200d, L3G4200D_REG_ADDR_INT1_DURATION, data, sizeof(data));

    reg->wait = (data[0] >> 7U) & 0x01U;
    reg->d = (data[0] >> 0U) & 0x7FU;

    return err;
}

l3g4200d_err_t l3g4200d_set_int1_duration_reg(l3g4200d_t const* l3g4200d, l3g4200d_int1_duration_reg_t const* reg)
{
    assert(l3g4200d && reg);

    uint8_t data[1] = {};

    data[0] |= (reg->wait & 0x01U) << 7U;
    data[0] |= (reg->d & 0x7FU) << 0U;

    l3g4200d_err_t err = l3g4200d_bus_write(l3g4200d, L3G4200D_REG_ADDR_INT1_DURATION, data, sizeof(data));

    return err;
}
