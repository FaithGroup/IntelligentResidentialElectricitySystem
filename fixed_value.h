#ifndef _FIXED_VALUE_H
#define _FIXED_VALUE_H

enum _MESSAGE_TYPE_ {
    TYPE_DEVICE_LIST_REQ = 1,
    TYPE_DEVICE_LIST_RSP,
    TYPE_DEVICE_STATUS_CHANGE,
    TYPE_DEVICE_ADD,
    TYPE_USE_LIST_REQ,
    TYPE_USE_LIST_RSP,
    TYPE_ENERGY_LIST_REQ,
    TYPE_ENERGY_LIST_RSP,
    TYPE_TIME_CHANGE
};

#define STR_TYPE "type"
#define STR_ID "id"
#define STR_NAME "name"
#define STR_VALTAGE "valtage"
#define STR_POWER "power"
#define STR_ELECTRICITY "electricity"
#define STR_STATE "state"
#define STR_NUM "num"


#endif