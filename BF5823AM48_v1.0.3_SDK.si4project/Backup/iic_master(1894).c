#include "iic_master.h"
#include "delay.h"

/*!
    \brief      iic master init
    \param[in]  none
    \param[out] none
    \retval     none
*/
void iic_master_init(void)
{
    OUT_SDA();
    OUT_SCL();
    SET_SDA();
    SET_SCL();
}

/*!
    \brief      iic start signal
    \param[in]  none
    \param[out] none
    \retval     none
*/
void iic_master_start(void)
{
    OUT_SDA();
    SET_SDA();  
    SET_SCL();
    delay_us(1);
    CLR_SDA();
    delay_us(1);
    CLR_SCL();
    delay_us(1);
}

/*!
    \brief      iic stop signal
    \param[in]  none
    \param[out] none
    \retval     none
*/
void iic_master_stop(void)
{   
    CLR_SCL();
    OUT_SDA();  
    CLR_SDA();
    delay_us(1);
    SET_SCL();
    delay_us(1);
    SET_SDA();
}

/*!
    \brief      iic receive byte
    \param[in]  none
    \param[out] none
    \retval     receive data
*/
uint8_t iic_receive_byte(void)
{
    uint8_t i;
    uint8_t buffer;
    buffer = 0;
	 
    IN_SDA();
        
    for (i = 0; i < 8; i++) {   
        CLR_SCL();
        delay_us(2);
        SET_SCL();
        delay_us(2);           
        if (SDA()) {        
            buffer |= 0x01;
        }
        if (i < 7) {
            buffer <<= 1;
        }
    }
    
    CLR_SCL();
    OUT_SDA();
    CLR_SDA();

    return (buffer);
}

/*!
    \brief      iic send byte
    \param[in]  none
    \param[out] none
    \retval     ack signal
*/
bit iic_sendbyte_and_getnack(uint8_t send_data)
{
    uint8_t i;
    bit ack;

    for (i = 0; i < 8; i++) {   
        CLR_SCL();
        delay_us(1);
        if (send_data & 0x80) {
            SET_SDA();
        }
        else {
            CLR_SDA();
        }
        delay_us(1);
        SET_SCL();
        delay_us(1);

        send_data <<= 1;
    }
    
    CLR_SCL();
    delay_us(1);
    
    IN_SDA();
    delay_us(1);
    SET_SCL();
    delay_us(2);

    ack = SDA();

    CLR_SCL();
    delay_us(1);                    
    OUT_SDA();
    CLR_SDA();
    delay_us(1); 
    

    return (ack);
}

/*!
    \brief      iic respond
    \param[in]  ack signal
    \param[out] none
    \retval     none
*/
void iic_respond(uint8_t ack)
{
    OUT_SDA();
    CLR_SDA();
    CLR_SCL();
    if (ack) {
        SET_SDA();
    }
    else {
        CLR_SDA();
    }
	delay_us(1);
    SET_SCL();
    delay_us(1);
    CLR_SCL();
}

/*!
    \brief      iic master write
    \param[in]  device_addr:iic device address
				writedata
				length
    \param[out] none
    \retval     none
*/
void iic_master_writer_data(uint8_t device_addr, uint8_t *writedata, uint8_t length)  
{   
    uint8_t i;    

	EA = 0;
    iic_master_start();
        
    if (iic_sendbyte_and_getnack(device_addr & ~0x01)) {   
        iic_master_stop();
		EA = 1;
        return;
    }

    for (i = 0; i < length; i++) {
        if (iic_sendbyte_and_getnack(writedata[i])) {
            iic_master_stop();
			EA = 1;
            return;
        }
    }   
    EA = 1;                        
    iic_master_stop();
}

/*!
    \brief      iic master read
    \param[in]  device_addr:iic device address
				receivedata
				length
    \param[out] none
    \retval     none
*/
void iic_master_read_data(uint8_t device_addr, uint8_t *receivedata, uint8_t length)
{
    uint8_t i;    

	EA = 0;
    iic_master_start();                
    if (iic_sendbyte_and_getnack(device_addr | 0x01)) {
        iic_master_stop();
		EA = 1; 
        return;
    }   
    
    for (i = 0; i < length; i++) {
        receivedata[i] = iic_receive_byte();
        if (i == (length - 1))
            break;
        iic_respond(ACK);
    }

    iic_respond(NACK);
	EA = 1;
    iic_master_stop();           
}
