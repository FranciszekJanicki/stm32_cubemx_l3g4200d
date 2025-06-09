#include "l3g4200d.h"
#include <assert.h>
#include <string.h>

static l3g4200d_err_t l3g4200d_bus_init(l3g4200d_t const* l3g4200d)
{
    return l3g4200d->interface.bus_init ? l3g4200d->interface.bus_init(l3g4200d->interface.bus_user)
                                        : L3G4200D_ERR_NULL;
}

static l3g4200d_err_t l3g4200d_bus_deinit(l3g4200d_t const* l3g4200d)
{
    return l3g4200d->interface.bus_deinit
               ? l3g4200d->interface.bus_deinit(l3g4200d->interface.bus_user)
               : L3G4200D_ERR_NULL;
}

static l3g4200d_err_t l3g4200d_bus_write(l3g4200d_t const* l3g4200d,
                                         uint8_t address,
                                         uint8_t const* data,
                                         size_t data_size)
{
    return l3g4200d->interface.bus_write
               ? l3g4200d->interface.bus_write(l3g4200d->interface.bus_user,
                                               address,
                                               data,
                                               data_size)
               : L3G4200D_ERR_NULL;
}

static l3g4200d_err_t l3g4200d_bus_read(l3g4200d_t const* l3g4200d,
                                        uint8_t address,
                                        uint8_t* data,
                                        size_t data_size)
{
    return l3g4200d->interface.bus_read ? l3g4200d->interface.bus_read(l3g4200d->interface.bus_user,
                                                                       address,
                                                                       data,
                                                                       data_size)
                                        : L3G4200D_ERR_NULL;
}

l3g4200d_err_t l3g4200d_initialize(l3g4200d_t* l3g4200d,
                                   l3g4200d_config_t const* config,
                                   l3g4200d_interface_t const* interface)
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

    *raw = reg.out_x;

    return err;
}

l3g4200d_err_t l3g4200d_get_gyro_data_y_raw(l3g4200d_t const* l3g4200d, int16_t* raw)
{
    assert(l3g4200d && raw);

    l3g4200d_out_y_reg_t reg = {};

    l3g4200d_err_t err = l3g4200d_get_out_y_reg(l3g4200d, &reg);

    *raw = reg.out_y;

    return err;
}

l3g4200d_err_t l3g4200d_get_gyro_data_z_raw(l3g4200d_t const* l3g4200d, int16_t* raw)
{
    assert(l3g4200d && raw);

    l3g4200d_out_z_reg_t reg = {};

    l3g4200d_err_t err = l3g4200d_get_out_z_reg(l3g4200d, &reg);

    *raw = reg.out_z;

    return err;
}

l3g4200d_err_t l3g4200d_get_gyro_data_raw(l3g4200d_t const* l3g4200d, vec3_int16_t* raw)
{
    assert(l3g4200d && raw);

    l3g4200d_out_reg_t reg = {};

    l3g4200d_err_t err = l3g4200d_get_out_reg(l3g4200d, &reg);

    raw->x = reg.out_x;
    raw->y = reg.out_y;
    raw->z = reg.out_z;

    return err;
}

l3g4200d_err_t l3g4200d_get_temp_data_raw(l3g4200d_t const* l3g4200d, int16_t* raw)
{
    assert(l3g4200d && raw);

    l3g4200d_out_temp_reg_t reg = {};

    l3g4200d_err_t err = l3g4200d_get_out_temp_reg(l3g4200d, &reg);

    *raw = reg.temp;

    return err;
}

l3g4200d_err_t l3g4200d_get_who_am_i_reg(l3g4200d_t const* l3g4200d, l3g4200d_who_am_i_reg_t* reg)
{
    assert(l3g4200d && reg);

    uint8_t data = {};

    l3g4200d_err_t err =
        l3g4200d_bus_read(l3g4200d, L3G4200D_REG_ADDR_WHO_AM_I, &data, sizeof(data));

    reg->who_am_i = data & 0xFFU;

    return err;
}

l3g4200d_err_t l3g4200d_get_ctrl1_reg(l3g4200d_t const* l3g4200d, l3g4200d_ctrl1_reg_t* reg)
{
    assert(l3g4200d && reg);

    uint8_t data = {};

    l3g4200d_err_t err = l3g4200d_bus_read(l3g4200d, L3G4200D_REG_ADDR_CTRL1, &data, sizeof(data));

    reg->dr = (data >> 6U) & 0x03U;
    reg->bw = (data >> 4U) & 0x03U;
    reg->pd = (data >> 3U) & 0x01U;
    reg->z_en = (data >> 2U) & 0x01U;
    reg->y_en = (data >> 1U) & 0x01U;
    reg->x_en = data & 0x01U;

    return err;
}

l3g4200d_err_t l3g4200d_set_ctrl1_reg(l3g4200d_t const* l3g4200d, l3g4200d_ctrl1_reg_t const* reg)
{
    assert(l3g4200d && reg);

    uint8_t data = {};

    data |= (reg->dr & 0x03U) << 6U;
    data |= (reg->bw & 0x03U) << 4U;
    data |= (reg->pd & 0x01U) << 3U;
    data |= (reg->z_en & 0x01U) << 2U;
    data |= (reg->y_en & 0x01U) << 1U;
    data |= reg->x_en & 0x01U;

    l3g4200d_err_t err = l3g4200d_bus_write(l3g4200d, L3G4200D_REG_ADDR_CTRL1, &data, sizeof(data));

    return err;
}

l3g4200d_err_t l3g4200d_get_ctrl2_reg(l3g4200d_t const* l3g4200d, l3g4200d_ctrl2_reg_t* reg)
{
    assert(l3g4200d && reg);

    uint8_t data = {};

    l3g4200d_err_t err = l3g4200d_bus_read(l3g4200d, L3G4200D_REG_ADDR_CTRL2, &data, sizeof(data));

    reg->hpm = (data >> 4U) & 0x03U;
    reg->hpcf = data & 0x0FU;

    return err;
}

l3g4200d_err_t l3g4200d_set_ctrl2_reg(l3g4200d_t const* l3g4200d, l3g4200d_ctrl2_reg_t const* reg)
{
    assert(l3g4200d && reg);

    uint8_t data = {};

    data |= (reg->hpm & 0x03U) << 4U;
    data |= reg->hpcf & 0x0FU;

    l3g4200d_err_t err = l3g4200d_bus_write(l3g4200d, L3G4200D_REG_ADDR_CTRL2, &data, sizeof(data));

    return err;
}

l3g4200d_err_t l3g4200d_get_ctrl3_reg(l3g4200d_t const* l3g4200d, l3g4200d_ctrl3_reg_t* reg)
{
    assert(l3g4200d && reg);

    uint8_t data = {};

    l3g4200d_err_t err = l3g4200d_bus_read(l3g4200d, L3G4200D_REG_ADDR_CTRL3, &data, sizeof(data));

    reg->i1_int1 = (data >> 7U) & 0x01U;
    reg->i1_boot = (data >> 6U) & 0x01U;
    reg->hl_active = (data >> 5U) & 0x01U;
    reg->pp_od = (data >> 4U) & 0x01U;
    reg->i2_drdy = (data >> 3U) & 0x01U;
    reg->i2_wtm = (data >> 2U) & 0x01U;
    reg->i2_orun = (data >> 1U) & 0x01U;
    reg->i2_empty = data & 0x01U;

    return err;
}

l3g4200d_err_t l3g4200d_set_ctrl3_reg(l3g4200d_t const* l3g4200d, l3g4200d_ctrl3_reg_t const* reg)
{
    assert(l3g4200d && reg);

    uint8_t data = {};

    data |= (reg->i1_int1 & 0x01U) << 7U;
    data |= (reg->i1_boot & 0x01U) << 6U;
    data |= (reg->hl_active & 0x01U) << 5U;
    data |= (reg->pp_od & 0x01U) << 4U;
    data |= (reg->i2_drdy & 0x01U) << 3U;
    data |= (reg->i2_wtm & 0x01U) << 2U;
    data |= (reg->i2_orun & 0x01U) << 1U;
    data |= reg->i2_empty & 0x01U;

    l3g4200d_err_t err = l3g4200d_bus_read(l3g4200d, L3G4200D_REG_ADDR_CTRL3, &data, sizeof(data));

    return err;
}

l3g4200d_err_t l3g4200d_get_ctrl4_reg(l3g4200d_t const* l3g4200d, l3g4200d_ctrl4_reg_t* reg)
{
    assert(l3g4200d && reg);

    uint8_t data = {};

    l3g4200d_err_t err = l3g4200d_bus_read(l3g4200d, L3G4200D_REG_ADDR_CTRL4, &data, sizeof(data));

    reg->bdu = (data >> 7U) & 0x01U;
    reg->ble = (data >> 6U) & 0x01U;
    reg->fs = (data >> 4U) & 0x03U;
    reg->st = (data >> 1U) & 0x03U;
    reg->sim = data & 0x01U;

    return err;
}

l3g4200d_err_t l3g4200d_set_ctrl4_reg(l3g4200d_t const* l3g4200d, l3g4200d_ctrl4_reg_t const* reg)
{
    assert(l3g4200d && reg);

    uint8_t data = {};

    l3g4200d_err_t err = l3g4200d_bus_read(l3g4200d, L3G4200D_REG_ADDR_CTRL4, &data, sizeof(data));

    data &= ~((0x01U << 7U) | (0x01U << 6U) | (0x03U << 4U) | (0x03U << 1U) | 0x01U);

    data |= (reg->bdu & 0x01U) << 7U;
    data |= (reg->ble & 0x01U) << 6U;
    data |= (reg->fs & 0x03U) << 4U;
    data |= (reg->ble & 0x03U) << 1U;
    data |= reg->ble & 0x01U;

    err |= l3g4200d_bus_write(l3g4200d, L3G4200D_REG_ADDR_CTRL4, &data, sizeof(data));

    return err;
}

l3g4200d_err_t l3g4200d_get_ctrl5_reg(l3g4200d_t const* l3g4200d, l3g4200d_ctrl5_reg_t* reg)
{
    assert(l3g4200d && reg);

    uint8_t data = {};

    l3g4200d_err_t err = l3g4200d_bus_read(l3g4200d, L3G4200D_REG_ADDR_CTRL5, &data, sizeof(data));

    reg->boot = (data >> 7U) & 0x01U;
    reg->fifo_en = (data >> 6U) & 0x01U;
    reg->hp_en = (data >> 4U) & 0x01U;
    reg->int1_sel = (data >> 2U) & 0x03U;
    reg->out_sel = data & 0x03U;

    return err;
}

l3g4200d_err_t l3g4200d_set_ctrl5_reg(l3g4200d_t const* l3g4200d, l3g4200d_ctrl5_reg_t const* reg)
{
    assert(l3g4200d && reg);

    uint8_t data = {};

    l3g4200d_err_t err = l3g4200d_bus_read(l3g4200d, L3G4200D_REG_ADDR_CTRL5, &data, sizeof(data));

    data &= ~((0x01U << 7U) | (0x01U << 6U) | (0x01U << 4U) | (0x03U << 2U) | 0x03U);

    data |= (reg->boot & 0x01U) << 7U;
    data |= (reg->fifo_en & 0x01U) << 6U;
    data |= (reg->hp_en & 0x01U) << 4U;
    data |= (reg->int1_sel & 0x03U) << 2U;
    data |= reg->out_sel & 0x03U;

    err |= l3g4200d_bus_write(l3g4200d, L3G4200D_REG_ADDR_CTRL5, &data, sizeof(data));

    return err;
}

l3g4200d_err_t l3g4200d_get_out_temp_reg(l3g4200d_t const* l3g4200d, l3g4200d_out_temp_reg_t* reg)
{
    assert(l3g4200d && reg);

    uint8_t data = {};

    l3g4200d_err_t err =
        l3g4200d_bus_read(l3g4200d, L3G4200D_REG_ADDR_WHO_AM_I, &data, sizeof(data));

    reg->temp = (int8_t)(data & 0xFF);

    return err;
}

l3g4200d_err_t l3g4200d_get_status_reg(l3g4200d_t const* l3g4200d, l3g4200d_status_reg_t* reg)
{
    assert(l3g4200d && reg);

    uint8_t data = {};

    l3g4200d_err_t err = l3g4200d_bus_read(l3g4200d, L3G4200D_REG_ADDR_STATUS, &data, sizeof(data));

    reg->zyx_or = (data >> 7U) & 0x01U;
    reg->z_or = (data >> 6U) & 0x01U;
    reg->y_or = (data >> 5U) & 0x01U;
    reg->x_or = (data >> 4U) & 0x01U;
    reg->zyx_da = (data >> 3U) & 0x01U;
    reg->z_da = (data >> 2U) & 0x01U;
    reg->y_da = (data >> 1U) & 0x01U;
    reg->x_da = data & 0x01U;

    return err;
}

l3g4200d_err_t l3g4200d_get_out_x_reg(l3g4200d_t const* l3g4200d, l3g4200d_out_x_reg_t* reg)
{
    assert(l3g4200d && reg);

    uint8_t data[2] = {};

    l3g4200d_err_t err = l3g4200d_bus_read(l3g4200d, L3G4200D_REG_ADDR_OUT_X_L, data, sizeof(data));

    reg->out_x = (int16_t)((data[0] & 0xFF) | ((data[1] & 0xFF) << 8));

    return err;
}

l3g4200d_err_t l3g4200d_get_out_y_reg(l3g4200d_t const* l3g4200d, l3g4200d_out_y_reg_t* reg)
{
    assert(l3g4200d && reg);

    uint8_t data[2] = {};

    l3g4200d_err_t err = l3g4200d_bus_read(l3g4200d, L3G4200D_REG_ADDR_OUT_Y_L, data, sizeof(data));

    reg->out_y = (int16_t)((data[0] & 0xFF) | ((data[1] & 0xFF) << 8));

    return err;
}

l3g4200d_err_t l3g4200d_get_out_z_reg(l3g4200d_t const* l3g4200d, l3g4200d_out_z_reg_t* reg)
{
    assert(l3g4200d && reg);

    uint8_t data[2] = {};

    l3g4200d_err_t err = l3g4200d_bus_read(l3g4200d, L3G4200D_REG_ADDR_OUT_Z_L, data, sizeof(data));

    reg->out_z = (int16_t)((data[0] & 0xFF) | ((data[1] & 0xFF) << 8));

    return err;
}

l3g4200d_err_t l3g4200d_get_out_reg(l3g4200d_t const* l3g4200d, l3g4200d_out_reg_t* reg)
{
    assert(l3g4200d && reg);

    uint8_t data[6] = {};

    l3g4200d_err_t err = l3g4200d_bus_read(l3g4200d, L3G4200D_REG_ADDR_OUT_X_L, data, sizeof(data));

    reg->out_x = (int16_t)((data[0] & 0xFF) | ((data[1] & 0xFF) << 8));
    reg->out_y = (int16_t)((data[2] & 0xFF) | ((data[3] & 0xFF) << 8));
    reg->out_z = (int16_t)((data[4] & 0xFF) | ((data[5] & 0xFF) << 8));

    return err;
}

l3g4200d_err_t l3g4200d_get_fifo_ctrl_reg(l3g4200d_t const* l3g4200d, l3g4200d_fifo_ctrl_reg_t* reg)
{
    assert(l3g4200d && reg);

    uint8_t data = {};

    l3g4200d_err_t err =
        l3g4200d_bus_read(l3g4200d, L3G4200D_REG_ADDR_FIFO_CTRL, &data, sizeof(data));

    reg->fm = (data >> 5U) & 0x07U;
    reg->wtm = data & 0x1FU;

    return err;
}

l3g4200d_err_t l3g4200d_set_fifo_ctrl_reg(l3g4200d_t const* l3g4200d,
                                          l3g4200d_fifo_ctrl_reg_t const* reg)
{
    assert(l3g4200d && reg);

    uint8_t data = {};

    data |= (reg->fm & 0x07U) << 5U;
    data |= reg->wtm & 0x1FU;

    l3g4200d_err_t err =
        l3g4200d_bus_write(l3g4200d, L3G4200D_REG_ADDR_FIFO_CTRL, &data, sizeof(data));

    return err;
}

l3g4200d_err_t l3g4200d_get_fifo_src_reg(l3g4200d_t const* l3g4200d, l3g4200d_fifo_src_reg_t* reg)
{
    assert(l3g4200d && reg);

    uint8_t data = {};

    l3g4200d_err_t err =
        l3g4200d_bus_read(l3g4200d, L3G4200D_REG_ADDR_FIFO_SRC, &data, sizeof(data));

    reg->wtm = (data >> 7U) & 0x01U;
    reg->ovrn = (data >> 6U) & 0x01U;
    reg->empty = (data >> 5U) & 0x01U;
    reg->fss = data & 0x1FU;

    return err;
}

l3g4200d_err_t l3g4200d_set_fifo_src_reg(l3g4200d_t const* l3g4200d,
                                         l3g4200d_fifo_src_reg_t const* reg)
{
    assert(l3g4200d && reg);

    uint8_t data = {};

    data |= (reg->wtm & 0x01U) << 7U;
    data |= (reg->ovrn & 0x01U) << 6U;
    data |= (reg->empty & 0x01U) << 5U;
    data |= reg->fss & 0x1FU;

    l3g4200d_err_t err =
        l3g4200d_bus_write(l3g4200d, L3G4200D_REG_ADDR_FIFO_SRC, &data, sizeof(data));

    return err;
}

l3g4200d_err_t l3g4200d_get_int1_cfg_reg(l3g4200d_t const* l3g4200d, l3g4200d_int1_cfg_reg_t* reg)
{
    assert(l3g4200d && reg);

    uint8_t data = {};

    l3g4200d_err_t err =
        l3g4200d_bus_read(l3g4200d, L3G4200D_REG_ADDR_INT1_CFG, &data, sizeof(data));

    reg->and_or = (data >> 7U) & 0x01U;
    reg->lir = (data >> 6U) & 0x01U;
    reg->z_hie = (data >> 5U) & 0x01U;
    reg->z_lie = (data >> 4U) & 0x01U;
    reg->y_hie = (data >> 3U) & 0x01U;
    reg->y_lie = (data >> 2U) & 0x01U;
    reg->x_hie = (data >> 1U) & 0x01U;
    reg->x_lie = data & 0x01U;

    return err;
}

l3g4200d_err_t l3g4200d_set_int1_cfg_reg(l3g4200d_t const* l3g4200d,
                                         l3g4200d_int1_cfg_reg_t const* reg)
{
    assert(l3g4200d && reg);

    uint8_t data = {};

    data |= (reg->and_or & 0x01U) << 7U;
    data |= (reg->lir & 0x01U) << 6U;
    data |= (reg->z_hie & 0x01U) << 5U;
    data |= (reg->z_lie & 0x01U) << 4U;
    data |= (reg->y_hie & 0x01U) << 3U;
    data |= (reg->y_lie & 0x01U) << 2U;
    data |= (reg->x_hie & 0x01U) << 1U;
    data |= reg->x_lie & 0x01U;

    l3g4200d_err_t err =
        l3g4200d_bus_write(l3g4200d, L3G4200D_REG_ADDR_INT1_CFG, &data, sizeof(data));

    return err;
}

l3g4200d_err_t l3g4200d_get_int1_src_reg(l3g4200d_t const* l3g4200d, l3g4200d_int1_src_reg_t* reg)
{
    assert(l3g4200d && reg);

    uint8_t data = {};

    l3g4200d_err_t err =
        l3g4200d_bus_read(l3g4200d, L3G4200D_REG_ADDR_INT1_SRC, &data, sizeof(data));

    reg->ia = (data >> 6U) & 0x01U;
    reg->z_h = (data >> 5U) & 0x01U;
    reg->z_l = (data >> 4U) & 0x01U;
    reg->y_h = (data >> 3U) & 0x01U;
    reg->y_l = (data >> 2U) & 0x01U;
    reg->x_h = (data >> 1U) & 0x01U;
    reg->x_l = data & 0x01U;

    return err;
}

l3g4200d_err_t l3g4200d_set_int1_src_reg(l3g4200d_t const* l3g4200d,
                                         l3g4200d_int1_src_reg_t const* reg)
{
    assert(l3g4200d && reg);

    uint8_t data = {};

    l3g4200d_err_t err =
        l3g4200d_bus_read(l3g4200d, L3G4200D_REG_ADDR_INT1_SRC, &data, sizeof(data));

    data &= ~((0x01U << 6U) | (0x01U << 5U) | (0x01U << 4U) | (0x01U << 3U) | (0x01U << 2U) |
              (0x01U << 1U) | 0x01U);

    data |= (reg->ia & 0x01U) << 6U;
    data |= (reg->z_h & 0x01U) << 5U;
    data |= (reg->z_l & 0x01U) << 4U;
    data |= (reg->y_h & 0x01U) << 3U;
    data |= (reg->y_l & 0x01U) << 2U;
    data |= (reg->x_h & 0x01U) << 1U;
    data |= reg->x_l & 0x01U;

    err |= l3g4200d_bus_write(l3g4200d, L3G4200D_REG_ADDR_INT1_SRC, &data, sizeof(data));

    return err;
}

l3g4200d_err_t l3g4200d_get_int1_ths_x_reg(l3g4200d_t const* l3g4200d,
                                           l3g4200d_int1_ths_x_reg_t* reg)
{
    assert(l3g4200d && reg);

    uint8_t data[2] = {};

    l3g4200d_err_t err =
        l3g4200d_bus_read(l3g4200d, L3G4200D_REG_ADDR_INT1_THS_XH, data, sizeof(data));

    reg->ths_x = (int16_t)(((data[0] & 0x7F) << 8) | ((data[1] & 0xFF)));

    return err;
}

l3g4200d_err_t l3g4200d_set_int1_ths_x_reg(l3g4200d_t const* l3g4200d,
                                           l3g4200d_int1_ths_x_reg_t const* reg)
{
    assert(l3g4200d && reg);

    uint8_t data[2] = {};

    l3g4200d_err_t err =
        l3g4200d_bus_read(l3g4200d, L3G4200D_REG_ADDR_INT1_THS_XH, data, sizeof(data));

    data[0] |= (uint8_t)((reg->ths_x >> 8) & 0x7F);
    data[1] |= (uint8_t)(reg->ths_x & 0xFF);

    err |= l3g4200d_bus_write(l3g4200d, L3G4200D_REG_ADDR_INT1_THS_XH, data, sizeof(data));

    return err;
}

l3g4200d_err_t l3g4200d_get_int1_ths_y_reg(l3g4200d_t const* l3g4200d,
                                           l3g4200d_int1_ths_y_reg_t* reg)
{
    assert(l3g4200d && reg);

    uint8_t data[2] = {};

    l3g4200d_err_t err =
        l3g4200d_bus_read(l3g4200d, L3G4200D_REG_ADDR_INT1_THS_YH, data, sizeof(data));

    reg->ths_y = (int16_t)(((data[0] & 0x7F) << 8) | ((data[1] & 0xFF)));

    return err;
}

l3g4200d_err_t l3g4200d_set_int1_ths_y_reg(l3g4200d_t const* l3g4200d,
                                           l3g4200d_int1_ths_y_reg_t const* reg)
{
    assert(l3g4200d && reg);

    uint8_t data[2] = {};

    l3g4200d_err_t err =
        l3g4200d_bus_read(l3g4200d, L3G4200D_REG_ADDR_INT1_THS_YH, data, sizeof(data));

    data[0] |= (uint8_t)((reg->ths_y >> 8) & 0x7F);
    data[1] |= (uint8_t)(reg->ths_y & 0xFF);

    err |= l3g4200d_bus_write(l3g4200d, L3G4200D_REG_ADDR_INT1_THS_YH, data, sizeof(data));

    return err;
}

l3g4200d_err_t l3g4200d_get_int1_ths_z_reg(l3g4200d_t const* l3g4200d,
                                           l3g4200d_int1_ths_z_reg_t* reg)
{
    assert(l3g4200d && reg);

    uint8_t data[2] = {};

    l3g4200d_err_t err =
        l3g4200d_bus_read(l3g4200d, L3G4200D_REG_ADDR_INT1_THS_ZH, data, sizeof(data));

    reg->ths_z = (int16_t)(((data[0] & 0x7F) << 8) | ((data[1] & 0xFF)));

    return err;
}

l3g4200d_err_t l3g4200d_set_int1_ths_z_reg(l3g4200d_t const* l3g4200d,
                                           l3g4200d_int1_ths_z_reg_t const* reg)
{
    assert(l3g4200d && reg);

    uint8_t data[2] = {};

    l3g4200d_err_t err =
        l3g4200d_bus_read(l3g4200d, L3G4200D_REG_ADDR_INT1_THS_ZH, data, sizeof(data));

    data[0] |= (uint8_t)((reg->ths_z >> 8) & 0x7F);
    data[1] |= (uint8_t)(reg->ths_z & 0xFF);

    err |= l3g4200d_bus_write(l3g4200d, L3G4200D_REG_ADDR_INT1_THS_ZH, data, sizeof(data));

    return err;
}

l3g4200d_err_t l3g4200d_get_int1_duration_reg(l3g4200d_t const* l3g4200d,
                                              l3g4200d_int1_duration_reg_t* reg)
{
    assert(l3g4200d && reg);

    uint8_t data = {};

    l3g4200d_err_t err =
        l3g4200d_bus_read(l3g4200d, L3G4200D_REG_ADDR_INT1_DURATION, &data, sizeof(data));

    reg->wait = (data >> 7U) & 0x01U;
    reg->d = data & 0x7FU;

    return err;
}

l3g4200d_err_t l3g4200d_set_int1_duration_reg(l3g4200d_t const* l3g4200d,
                                              l3g4200d_int1_duration_reg_t const* reg)
{
    assert(l3g4200d && reg);

    uint8_t data = {};

    data |= (reg->wait & 0x01U) << 7U;
    data |= reg->d & 0x7FU;

    l3g4200d_err_t err =
        l3g4200d_bus_write(l3g4200d, L3G4200D_REG_ADDR_INT1_DURATION, &data, sizeof(data));

    return err;
}
