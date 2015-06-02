#define BAUD 19200

#include <stdlib.h>
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include "uart.h"
#include "enc28j60/network.h"
#include "enc28j60/enc28j60.h"
#include "uip/uip.h"
#include "uip/uiparp.h"
#include "uip/timer.h"
#include "uip/clock.h"
#include "nethandler.h"
#include "dht.h"

#include "uart.h"

static volatile bool flag_packet_rx = true;

void tcpip_output(void) {
}

int main (void) {
    uart_init(BAUD);
    //clock_init();
    //network_init();
    //uip_init();
    
    //EIMSK = _BV(INT0);
    //EICRA = _BV(ISC01);
    //enc28j60_write(EIE, 0b11000000);
    
    //sei();
    
    //struct uip_eth_addr mac;
    //uip_ipaddr_t ip;
    
    //mac.addr[0] = ETHADDR0;
    //mac.addr[1] = ETHADDR1;
    //mac.addr[2] = ETHADDR2;
    //mac.addr[3] = ETHADDR3;
    //mac.addr[4] = ETHADDR4;
    //mac.addr[5] = ETHADDR5;
    
    //uip_setethaddr(mac);
    //uip_ipaddr(&ip, 192, 168, 1, 236);
    //uip_sethostaddr(&ip);
    
    //struct uip_conn *uc;
    //uip_ipaddr_t dst_ip;
    //uip_ipaddr(&dst_ip, 192, 168, 1, 70);
    //uc = uip_connect(&dst_ip, HTONS(9999));
    
    //if (uc == NULL) {
        ///* check if connection was successful */
        //uart_println("connection failed");
    //}
    
    //struct timer periodic_timer;
    //struct timer arp_timer;
    //timer_set(&periodic_timer, CLOCK_SECOND / 2);
    //timer_set(&arp_timer, CLOCK_SECOND * 10);
    dht_init();
    uint8_t state;
    char buff[10];
    for(;;) {
        state = dht_read();
        switch(state) {
            case DHT_OK:
                uart_println("OK");
                itoa(dht_data.temperature, buff, 10);
                uart_println(buff);
                break;
            case DHT_ERROR_CHECKSUM:
                uart_println("Error checksum");
                break;
            case DHT_ERROR_TIMEOUT:
                uart_println("Timeout");
                break;
            case DHT_ERROR_CONNECT:
                uart_println("Error connect");
                break;
            case DHT_ERROR_ACK_L:
                uart_println("Error ACK L");
                break;
            case DHT_ERROR_ACK_H:
                uart_println("Error ACK H");
                break;
        }
        _delay_ms(3000);
        //if(flag_packet_rx) {
            //flag_packet_rx = false;
            //nethandler_rx();
        //}
        
        //if(timer_tryrestart(&periodic_timer))
            //nethandler_periodic();
        
        //if(timer_tryrestart(&arp_timer))
            //uip_arp_timer();

        //uart_puts("test\r\n");
        //enc28j60_phy_write(PHLCON, PHLCON_LACFG_ON | PHLCON_LBCFG_ON | PHLCON_LFRQ_TMSTRCH | PHLCON_STRCH);
        //_delay_ms(1000);
        //enc28j60_phy_write(PHLCON, PHLCON_LACFG_OFF | PHLCON_LBCFG_OFF | PHLCON_LFRQ_TMSTRCH | PHLCON_STRCH);
        //_delay_ms(1000);
    }
    return 0;
}

ISR(INT0_vect) {
    flag_packet_rx = true;
}
