CONTIKI_PROJECT = coap-server
all: $(CONTIKI_PROJECT)

MODULES_REL += ./resources
PROJECT_SOURCEFILES += virtual-sensor.c
#linea anterior da acceso a funciones de virtual-sensor.h

CONTIKI = ../..

#include the CoAP implementation
include $(CONTIKI)/Makefile.dir-variables
MODULES += $(CONTIKI_NG_APP_LAYER_DIR)/coap

include $(CONTIKI)/Makefile.include