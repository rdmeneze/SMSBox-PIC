#ifndef __STATUS__
#define __STATUS__

#include "defs.h"

// state definitions
#define _INIT_ST_LIST     7  // __LINE__
#define ST_COM_PC_OK  ((WORD)(1))
#define ST_MODEM_RDY  ((WORD)(1 << 1))
#define ST_RST_BOR    ((WORD)(1 << 2))
#define ST_RST_WDT    ((WORD)(1 << 3))
#define ST_RST_LVD    ((WORD)(1 << 4))
#define _END_ST_LIST      13 // __LINE__

#define NSTATE ((_END_ST_LIST - _INIT_ST_LIST) - 1)

/**
 *  \brief Set a new operation state of machine
 *  \param st state to be activate
 */
void SetStatus( WORD st );

/**
 *  \brief Clean a operation state of machine
 *  \param st state to be cleanned
 */
void CleanStatus( WORD st );

/**
 *  \brief Get a operation state of machine
 *  \return bit map of states of machine
 */
WORD GetStatus (void);

/**
 *  \brief Get a machine network ID 
 *  \return ID id of machine
 */
BYTE GetID ( void );

#endif

