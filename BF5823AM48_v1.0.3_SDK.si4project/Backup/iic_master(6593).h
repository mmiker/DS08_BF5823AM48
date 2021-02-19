/*!
    \file  iic_master.h
    \brief iic_master define
*/

/*
    Copyright (C) 2018 BYD

    2018-09-13, V1.0.0, app for byd
*/

#ifndef IIC_MASTER_H
#define	IIC_MASTER_H

#include "mcu02_sfr.h"

#define SET_SDA()   DATAC |= 0x10
#define CLR_SDA()   DATAC &= ~0x10
#define OUT_SDA()   TRISC &= ~0x10
#define IN_SDA()    TRISC |= 0x10
#define SDA()       DATAC & 0x10

#define SET_SCL()   DATAC |= 0x08
#define CLR_SCL()   DATAC &= ~0x08
#define OUT_SCL()   TRISC &= ~0x08
#define IN_SCL()    TRISC |= 0x08

#define NACK    1
#define ACK     0


void iic_master_start(void);
void iic_master_stop(void);
void iic_respond(uint8_t ack);

uint8_t iic_receive_byte(void);
bit iic_sendbyte_and_getnack(uint8_t send_data);


void iic_master_read_data(uint8_t device_addr, uint8_t *receivedata, uint8_t length);

void iic_master_writer_data(uint8_t device_addr, uint8_t *writedata, uint8_t length);
#endif
