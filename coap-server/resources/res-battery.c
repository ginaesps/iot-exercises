//funcionalidad de coap con recursos necesarios
#include "contiki.h"
#include "coap-engine.h"
#include "lib/random.h"
#include <stdio.h>

static void
res_get_handler( //solo se va a configurar el get, pero podria ser todo el CRUD
    coap_message_t *request, 
    coap_message_t *response,
    uint8_t *buffer, //en caso de que la peticion traiga datos, aunque no deberia
    uint16_t preferred_size,
    int32_t *offset
);

RESOURCE(
    res_battery,
    "title=\"Battery status\";rt=\"battery\"",
    //las diagonales invertidas son para poder introducir cadenas dentro de cadenas
    //rt = resource type
    res_get_handler,
    NULL, 
    NULL, 
    NULL
);

static void
res_get_handler(
    coap_message_t *request,
    coap_message_t *response,
    uint8_t *buffer,
    uint16_t preferred_size,
    int32_t *offset
)
{
    int battery = random_rand() % 100;//metodo_para_obtener_nivel_bateria();
    unsigned int accept = -1;

    coap_get_header_accept(request, &accept);
    //el msj del request va a indicar el tipo de dato que esta esperando el cliente

    if(accept == -1) {
        coap_set_header_content_format(response, APPLICATION_JSON);
        snprintf((char *)buffer, COAP_MAX_CHUNK_SIZE, "{\battery\": %d", battery);
        //el snprintf le va a dar formato a la cant obtenida que se va a asignar a la bateria del servidor
        //la 1a parte indica que el valor se va a guardar en la variable buffer
        //posterior a coap max se encuentra un obj JSON (cada param se indica dentro de \ en caso de ser string)
        coap_set_payload(response, buffer, strlen((char *)buffer));
        //payload es el cont del msj y esa linea verifica que el content type sea el esperado
    } else {
        coap_set_status_code(response, NOT_ACCEPTABLE_4_06);
        //se esta indicando que el tipo de request enviado no tiene soporte con el codigo de error coap 4_06
        const char *message = "Only application/json as content-type is supported.";
        coap_set_payload(response, message, strlen(message));
    }

}