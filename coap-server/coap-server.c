#include "contiki.h"
#include "coap-engine.h" //motor de coap

#include "sys/log.h" //encabezados para bitacoras
#define LOG_MODULE "CoAP Server"
#define LOG_LEVEL LOG_LEVEL_INFO

extern coap_resource_t res_battery, res_temperature, res_humidity;
//en caso de querer agregar mas recursos, seria en esta seccion

PROCESS(coap_server, "CoAP Server");
AUTOSTART_PROCESSES(&coap_server);

PROCESS_THREAD(coap_server, ev, data)
{
    PROCESS_BEGIN();

    PROCESS_PAUSE();

    LOG_INFO("Starting the CoAP Server \n");
    coap_activate_resource(&res_battery, "system/batery");
    //&recurso, "endpoint/accesoRecurso"
    coap_activate_resource(&res_temperature, "sensor/temperature");
    coap_activate_resource(&res_humidity, "sensor/humidity");

    while (1)
    {
        PROCESS_WAIT_EVENT();
    }

    PROCESS_END();
}
