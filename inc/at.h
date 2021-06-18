#ifndef AT_H
#define AT_H

#include <stddef.h>
#include "at_hal.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef AT_PRINT
#define AT_PRINT(...)
#warning "To enable debug-print please define AT_PRINT as output mechanism";
#endif

typedef enum {
    AT_ST_IDLE,
    AT_ST_START,
    AT_ST_RSP,
    AT_ST_ARGS_START,
    AT_ST_ARGS,
    AT_ST_CODE,
    AT_ST_TEXT,
    AT_ST_END,
    // NOTE: Leave AT_ST_num at the end.
    AT_ST_num,
} AT_State;

typedef enum {
    AT_EV_CR,
    AT_EV_LF,
    AT_EV_MARK,
    AT_EV_SEMI,
    AT_EV_SPACE,
    AT_EV_DIGIT,
    AT_EV_LETTER,
    AT_EV_OTHER,
    // NOTE: Leave AT_EV_num at the end.
    AT_EV_num,
} AT_Event;

typedef struct AT AT;
typedef void (*AT_Callback)(AT*);   // Callback typedef
typedef AT_State (*AT_Trans)(AT*);  // Transition function typedef

typedef struct {
    const char  *cmd;
    AT_Callback cb;
    AT_Callback *res_cbks;
} AT_Cmd;

typedef struct {
    AT_Cmd  *cbks;
    char    *buf;
    size_t  cbks_size;
    size_t  buf_size;
} AT_Cfg;

struct AT {
    AT_Status   status;
    AT_State    st;
    AT_State    parse_st;
    AT_Event    ev;
    AT_Event    prev_ev;
    AT_Code     code;
    AT_Cmd      *cbks;
    char        *buf;
    char        *args;
    char        c;
    size_t      cbks_size;
    size_t      buf_size;
    size_t      pos;
    size_t      cb_idx;
};

void at_init(AT *at, const AT_Cfg *cfg);
void at_process(AT *at);
void at_clear(AT *at);

#ifdef __cplusplus
}
#endif

#endif // AT_H