#include "contiki.h"
#include "coap-engine.h"
#include "virtual-sensor.h"
#include <stdio.h>

static void res_get_handler(
    coap_message_t *request,
    coap_message_t *response,
    uint8_t *buffer,
    uint16_t preferred size,
    int32_t *offset
    //este encabezado es variable, offset rellena dichos datos
);

//recurso observable actualiza un param cada cierto t
static void res_periodic_handler(void);

PERIODIC_RESOURCE(
    res_temperature,
    "title\"Temperature\";rt=\"temperature\";obs",
    //obs es param para indicar que es res-observable
    //abajo estan manejadores de peticiones para metodos REST
    res_get_handler, //GET
    NULL,            //POST
    NULL,            //PUT
    NULL,            //DELETE
    5000,            //intervalo de actualizacion de valor, 5s o 5ms
    //en la practica, T cada hora y humedad cada 3h
    res_periodic_handler //handler de res-observable periodico
);

static void res_get_handler(
    coap_message_t *request,
    coap_message_t *response,
    uint8_t *buffer,
    uint16_t preferred size,
    int32_t *offset
    //en C es necesario definir handler antes de usarlo
)
{
    float temperature = read_temperature();
    unsigned int accept = -1;

    if (accept == APPLICATION_JSON || accept == -1)
    {
        coap_set_handler_content_format(response, APPLICATION_JSON);
        snprintf((char *)buffer, COAP_MAX_CHUNK_SIZE, "{\"temperature\":\" % .2f\"}", temperature);
        coap_set_payload(response, (uint8_t *)buffer, strlen((char *)buffer));
    }
    else
    {
        coap_set_status_code(response, NOT_ACCEPTABLE_4_06);
        const char *message = "Only application/json as content-type is supported.";
        coap_set_payload(response, message, strlen(message));
    }
}

static void
res_periodic_handler()
{
    coap_notify_observers(&res_temperature);
}

//cada que el usuario el res-observable (se va a actualizar cada x t)
//se va a ejecutar funcion de abajo
static void
res_periodic_handler()
{
    coap_notify_observers(&res_temperature); //se indica uso de recurso GET
    //ya que no hay procesamiento de valores antes o post, solo se crea-envia nueva medicion
}